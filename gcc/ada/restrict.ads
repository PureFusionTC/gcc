------------------------------------------------------------------------------
--                                                                          --
--                         GNAT COMPILER COMPONENTS                         --
--                                                                          --
--                             R E S T R I C T                              --
--                                                                          --
--                                 S p e c                                  --
--                                                                          --
--          Copyright (C) 1992-2004 Free Software Foundation, Inc.          --
--                                                                          --
-- GNAT is free software;  you can  redistribute it  and/or modify it under --
-- terms of the  GNU General Public License as published  by the Free Soft- --
-- ware  Foundation;  either version 2,  or (at your option) any later ver- --
-- sion.  GNAT is distributed in the hope that it will be useful, but WITH- --
-- OUT ANY WARRANTY;  without even the  implied warranty of MERCHANTABILITY --
-- or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License --
-- for  more details.  You should have  received  a copy of the GNU General --
-- Public License  distributed with GNAT;  see file COPYING.  If not, write --
-- to  the Free Software Foundation,  59 Temple Place - Suite 330,  Boston, --
-- MA 02111-1307, USA.                                                      --
--                                                                          --
-- GNAT was originally developed  by the GNAT team at  New York University. --
-- Extensive contributions were provided by Ada Core Technologies Inc.      --
--                                                                          --
------------------------------------------------------------------------------

--  This package deals with the implementation of the Restrictions pragma

with Rident; use Rident;
with Types;  use Types;
with Uintp;  use Uintp;

package Restrict is

   Restrictions : Restrictions_Info;
   --  This variable records restrictions found in any units in the main
   --  extended unit, and in the case of restrictions checked for partition
   --  consistency, restrictions found in any with'ed units, parent specs
   --  etc, since we may as well check as much as we can at compile time.
   --  These variables should not be referenced directly by clients. Instead
   --  use Check_Restrictions to record a violation of a restriction, and
   --  Restriction_Active to test if a given restriction is active.

   Restrictions_Loc : array (All_Restrictions) of Source_Ptr :=
                       (others => No_Location);
   --  Locations of Restrictions pragmas for error message purposes.
   --  Valid only if corresponding entry in Restrictions is set. A value
   --  of No_Location is used for implicit restrictions set by another
   --  pragma, and a value of System_Location is used for restrictions
   --  set from package Standard by the processing in Targparm.

   Main_Restrictions : Restrictions_Info;
   --  This variable records only restrictions found in any units of the
   --  main extended unit. These are the variables used for ali file output,
   --  since we want the binder to be able to accurately diagnose inter-unit
   --  restriction violations.

   Restriction_Warnings : Rident.Restriction_Flags;
   --  If one of these flags is set, then it means that violation of the
   --  corresponding restriction results only in a warning message, not
   --  in an error message, and the restriction is not otherwise enforced.
   --  Note that the flags in Restrictions are set to indicate that the
   --  restriction is set in this case, but Main_Restrictions is never
   --  set if Restriction_Warnings is set, so this does not look like a
   --  restriction to the binder.

   type Save_Cunit_Boolean_Restrictions is private;
   --  Type used for saving and restoring compilation unit restrictions.
   --  See Cunit_Boolean_Restrictions_[Save|Restore] subprograms.

   --  The following declarations establish a mapping between restriction
   --  identifiers, and the names of corresponding restriction library units.

   type Unit_Entry is record
      Res_Id : Restriction_Id;
      Filenm : String (1 .. 8);
   end record;

   Unit_Array : constant array (Positive range <>) of Unit_Entry := (
     (No_Asynchronous_Control,     "a-astaco"),
     (No_Calendar,                 "a-calend"),
     (No_Calendar,                 "calendar"),
     (No_Delay,                    "a-calend"),
     (No_Delay,                    "calendar"),
     (No_Dynamic_Priorities,       "a-dynpri"),
     (No_Finalization,             "a-finali"),
     (No_IO,                       "a-direio"),
     (No_IO,                       "directio"),
     (No_IO,                       "a-sequio"),
     (No_IO,                       "sequenio"),
     (No_IO,                       "a-ststio"),
     (No_IO,                       "a-textio"),
     (No_IO,                       "text_io "),
     (No_IO,                       "a-witeio"),
     (No_Task_Attributes_Package,  "a-tasatt"),
     (No_Streams,                  "a-stream"),
     (No_Unchecked_Conversion,     "a-unccon"),
     (No_Unchecked_Conversion,     "unchconv"),
     (No_Unchecked_Deallocation,   "a-uncdea"),
     (No_Unchecked_Deallocation,   "unchdeal"));

   --  The following map has True for all GNAT pragmas. It is used to
   --  implement pragma Restrictions (No_Implementation_Restrictions)
   --  (which is why this restriction itself is excluded from the list).

   Implementation_Restriction : array (All_Restrictions) of Boolean :=
     (Simple_Barriers                    => True,
      No_Calendar                        => True,
      No_Dynamic_Attachment              => True,
      No_Enumeration_Maps                => True,
      No_Entry_Calls_In_Elaboration_Code => True,
      No_Entry_Queue                     => True,
      No_Exception_Handlers              => True,
      No_Exception_Registration          => True,
      No_Implicit_Conditionals           => True,
      No_Implicit_Dynamic_Code           => True,
      No_Implicit_Loops                  => True,
      No_Local_Protected_Objects         => True,
      No_Protected_Type_Allocators       => True,
      No_Relative_Delay                  => True,
      No_Requeue_Statements              => True,
      No_Secondary_Stack                 => True,
      No_Select_Statements               => True,
      No_Standard_Storage_Pools          => True,
      No_Streams                         => True,
      No_Task_Attributes_Package         => True,
      No_Task_Termination                => True,
      No_Wide_Characters                 => True,
      Static_Priorities                  => True,
      Static_Storage_Size                => True,
      No_Implementation_Attributes       => True,
      No_Implementation_Pragmas          => True,
      No_Elaboration_Code                => True,
      others                             => False);

   -----------------
   -- Subprograms --
   -----------------

   function Abort_Allowed return Boolean;
   pragma Inline (Abort_Allowed);
   --  Tests to see if abort is allowed by the current restrictions settings.
   --  For abort to be allowed, either No_Abort_Statements must be False,
   --  or Max_Asynchronous_Select_Nesting must be non-zero.

   procedure Check_Restricted_Unit (U : Unit_Name_Type; N : Node_Id);
   --  Checks if loading of unit U is prohibited by the setting of some
   --  restriction (e.g. No_IO restricts the loading of unit Ada.Text_IO).
   --  If a restriction exists post error message at the given node.

   procedure Check_Restriction
     (R : Restriction_Id;
      N : Node_Id;
      V : Uint := Uint_Minus_1);
   --  Checks that the given restriction is not set, and if it is set, an
   --  appropriate message is posted on the given node. Also records the
   --  violation in the appropriate internal arrays. Note that it is
   --  mandatory to always use this routine to check if a restriction
   --  is violated. Such checks must never be done directly by the caller,
   --  since otherwise violations in the absence of restrictions are not
   --  properly recorded. The value of V is relevant only for parameter
   --  restrictions, and in this case indicates the exact count for the
   --  violation. If the exact count is not known, V is left at its
   --  default value of -1 which indicates an unknown count.

   procedure Check_Elaboration_Code_Allowed (N : Node_Id);
   --  Tests to see if elaboration code is allowed by the current restrictions
   --  settings. This function is called by Gigi when it needs to define
   --  an elaboration routine. If elaboration code is not allowed, an error
   --  message is posted on the node given as argument.

   procedure Check_No_Implicit_Heap_Alloc (N : Node_Id);
   --  Equivalent to Check_Restriction (No_Implicit_Heap_Allocations, N).
   --  Provided for easy use by back end, which has to check this restriction.

   function Cunit_Boolean_Restrictions_Save
     return Save_Cunit_Boolean_Restrictions;
   --  This function saves the compilation unit restriction settings, and
   --  resets them to False. This is used e.g. when compiling a with'ed
   --  unit to avoid incorrectly propagating restrictions. Note that it
   --  would not be wrong to also save and reset the partition restrictions,
   --  since the binder would catch inconsistencies, but actually it is a
   --  good thing to acquire restrictions from with'ed units if they are
   --  required to be partition wide, because it allows the restriction
   --  violation message to be given at compile time instead of link time.

   procedure Cunit_Boolean_Restrictions_Restore
     (R : Save_Cunit_Boolean_Restrictions);
   --  This is the corresponding restore procedure to restore restrictions
   --  previously saved by Cunit_Boolean_Restrictions_Save.

   function Get_Restriction_Id
     (N : Name_Id) return Restriction_Id;
   --  Given an identifier name, determines if it is a valid restriction
   --  identifier, and if so returns the corresponding Restriction_Id
   --  value, otherwise returns Not_A_Restriction_Id.

   function No_Exception_Handlers_Set return Boolean;
   --  Test to see if current restrictions settings specify that no exception
   --  handlers are present. This function is called by Gigi when it needs to
   --  expand an AT END clean up identifier with no exception handler.

   function Restriction_Active (R : All_Restrictions) return Boolean;
   pragma Inline (Restriction_Active);
   --  Determines if a given restriction is active. This call should only be
   --  used where the compiled code depends on whether the restriction is
   --  active. Always use Check_Restriction to record a violation.

   function Restricted_Profile return Boolean;
   --  Tests to see if tasking operations follow the GNAT restricted run time
   --  profile.

   procedure Set_Ravenscar (N : Node_Id);
   --  Enables the set of restrictions for Ravenscar. N is the corresponding
   --  pragma node, which is used for error messages on any constructs that
   --  violate the profile.

   procedure Set_Restriction
     (R : All_Boolean_Restrictions;
      N : Node_Id);
   --  N is a node (typically a pragma node) that has the effect of setting
   --  Boolean restriction R. The restriction is set in Restrictions, and
   --  also in Main_Restrictions if this is the main unit.

   procedure Set_Restriction
     (R : All_Parameter_Restrictions;
      N : Node_Id;
      V : Integer);
   --  Similar to the above, except that this is used for the case of a
   --  parameter restriction, and the corresponding value V is given.

   procedure Set_Restricted_Profile (N : Node_Id);
   --  Enables the set of restrictions for pragma Restricted_Run_Time. N is
   --  the corresponding pragma node, which is used for error messages on
   --  constructs that violate the profile.

   function Tasking_Allowed return Boolean;
   pragma Inline (Tasking_Allowed);
   --  Tests to see if tasking operations are allowed by the current
   --  restrictions settings. For tasking to be allowed Max_Tasks must
   --  be non-zero.

private
   type Save_Cunit_Boolean_Restrictions is
     array (Cunit_Boolean_Restrictions) of Boolean;
   --  Type used for saving and restoring compilation unit restrictions.
   --  See Compilation_Unit_Restrictions_[Save|Restore] subprograms.

end Restrict;
