#  Copyright (C) 2003-2017 Free Software Foundation, Inc.
#  Contributed by Kelley Cook, June 2004.
#  Original code from Neil Booth, May 2003.
#
# This program is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation; either version 3, or (at your option) any
# later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program; see the file COPYING3.  If not see
# <http://www.gnu.org/licenses/>.

# This Awk script reads in the option records generated from 
# opt-gather.awk, combines the flags of duplicate options and generates a
# C file.
#

# This program uses functions from opt-functions.awk and code from
# opt-read.awk.
#
# Usage: awk -f opt-functions.awk -f opt-read.awk -f optc-save-gen.awk \
#            [-v header_name=header.h] < inputfile > options-save.c

# Dump that array of options into a C file.
END {
print "/* This file is auto-generated by optc-save-gen.awk.  */"
print ""
n_headers = split(header_name, headers, " ")
for (i = 1; i <= n_headers; i++)
	print "#include " quote headers[i] quote
print "#include " quote "opts.h" quote
print "#include " quote "intl.h" quote
print ""
print "#include " quote "flags.h" quote
print "#include " quote "target.h" quote
print "#include " quote "inchash.h" quote
print "#include " quote "hash-set.h" quote
print "#include " quote "machmode.h" quote
print "#include " quote "vec.h" quote
print "#include " quote "double-int.h" quote
print "#include " quote "input.h" quote
print "#include " quote "alias.h" quote
print "#include " quote "symtab.h" quote
print "#include " quote "wide-int.h" quote
print "#include " quote "inchash.h" quote
print "#include " quote "tree.h" quote
print "#include " quote "fold-const.h" quote
print "#include " quote "tree-ssa-alias.h" quote
print "#include " quote "is-a.h" quote
print "#include " quote "predict.h" quote
print "#include " quote "function.h" quote
print "#include " quote "basic-block.h" quote
print "#include " quote "gimple-expr.h" quote
print "#include " quote "gimple.h" quote
print "#include " quote "data-streamer.h" quote
print "#include " quote "ipa-ref.h" quote
print "#include " quote "cgraph.h" quote
print ""

if (n_extra_c_includes > 0) {
	for (i = 0; i < n_extra_c_includes; i++) {
		print "#include " quote extra_c_includes[i] quote
	}
	print ""
}

have_save = 0;
if (n_extra_target_vars)
	have_save = 1

for (i = 0; i < n_opts; i++) {
	if (flag_set_p("Save", flags[i]))
		have_save = 1;
}

print "/* Save optimization variables into a structure.  */"
print "void";
print "cl_optimization_save (struct cl_optimization *ptr, struct gcc_options *opts)";
print "{";

n_opt_char = 3;
n_opt_short = 0;
n_opt_int = 0;
n_opt_enum = 0;
n_opt_other = 0;
var_opt_char[0] = "optimize";
var_opt_char[1] = "optimize_size";
var_opt_char[2] = "optimize_debug";
var_opt_range["optimize"] = "0, 255";
var_opt_range["optimize_size"] = "0, 1";
var_opt_range["optimize_debug"] = "0, 1";

# Sort by size to mimic how the structure is laid out to be friendlier to the
# cache.

for (i = 0; i < n_opts; i++) {
	if (flag_set_p("(Optimization|PerFunction)", flags[i])) {
		name = var_name(flags[i])
		if(name == "")
			continue;

		if(name in var_opt_seen)
			continue;

		var_opt_seen[name]++;
		otype = var_type_struct(flags[i]);
		if (otype ~ "^((un)?signed +)?int *$")
			var_opt_int[n_opt_int++] = name;

		else if (otype ~ "^((un)?signed +)?short *$")
			var_opt_short[n_opt_short++] = name;

		else if (otype ~ ("^enum +[_" alnum "]+ *"))
			var_opt_enum[n_opt_enum++] = name;

		else if (otype ~ "^((un)?signed +)?char *$") {
			var_opt_char[n_opt_char++] = name;
			if (otype ~ "^unsigned +char *$")
				var_opt_range[name] = "0, 255"
			else if (otype ~ "^signed +char *$")
				var_opt_range[name] = "-128, 127"
		}
		else
			var_opt_other[n_opt_other++] = name;
	}
}

for (i = 0; i < n_opt_char; i++) {
	name = var_opt_char[i];
	if (var_opt_range[name] != "")
		print "  gcc_assert (IN_RANGE (opts->x_" name ", " var_opt_range[name] "));";
}

print "";
for (i = 0; i < n_opt_other; i++) {
	print "  ptr->x_" var_opt_other[i] " = opts->x_" var_opt_other[i] ";";
}

for (i = 0; i < n_opt_int; i++) {
	print "  ptr->x_" var_opt_int[i] " = opts->x_" var_opt_int[i] ";";
}

for (i = 0; i < n_opt_enum; i++) {
	print "  ptr->x_" var_opt_enum[i] " = opts->x_" var_opt_enum[i] ";";
}

for (i = 0; i < n_opt_short; i++) {
	print "  ptr->x_" var_opt_short[i] " = opts->x_" var_opt_short[i] ";";
}

for (i = 0; i < n_opt_char; i++) {
	print "  ptr->x_" var_opt_char[i] " = opts->x_" var_opt_char[i] ";";
}

print "}";

print "";
print "/* Restore optimization options from a structure.  */";
print "void";
print "cl_optimization_restore (struct gcc_options *opts, struct cl_optimization *ptr)";
print "{";

for (i = 0; i < n_opt_other; i++) {
	print "  opts->x_" var_opt_other[i] " = ptr->x_" var_opt_other[i] ";";
}

for (i = 0; i < n_opt_int; i++) {
	print "  opts->x_" var_opt_int[i] " = ptr->x_" var_opt_int[i] ";";
}

for (i = 0; i < n_opt_enum; i++) {
	print "  opts->x_" var_opt_enum[i] " = ptr->x_" var_opt_enum[i] ";";
}

for (i = 0; i < n_opt_short; i++) {
	print "  opts->x_" var_opt_short[i] " = ptr->x_" var_opt_short[i] ";";
}

for (i = 0; i < n_opt_char; i++) {
	print "  opts->x_" var_opt_char[i] " = ptr->x_" var_opt_char[i] ";";
}

print "  targetm.override_options_after_change ();";
print "}";

print "";
print "/* Print optimization options from a structure.  */";
print "void";
print "cl_optimization_print (FILE *file,";
print "                       int indent_to,";
print "                       struct cl_optimization *ptr)";
print "{";

print "  fputs (\"\\n\", file);";
for (i = 0; i < n_opt_other; i++) {
	print "  if (ptr->x_" var_opt_other[i] ")";
	print "    fprintf (file, \"%*s%s (%#lx)\\n\",";
	print "             indent_to, \"\",";
	print "             \"" var_opt_other[i] "\",";
	print "             (unsigned long)ptr->x_" var_opt_other[i] ");";
	print "";
}

for (i = 0; i < n_opt_int; i++) {
	print "  if (ptr->x_" var_opt_int[i] ")";
	print "    fprintf (file, \"%*s%s (%#x)\\n\",";
	print "             indent_to, \"\",";
	print "             \"" var_opt_int[i] "\",";
	print "             ptr->x_" var_opt_int[i] ");";
	print "";
}

for (i = 0; i < n_opt_enum; i++) {
	print "  fprintf (file, \"%*s%s (%#x)\\n\",";
	print "           indent_to, \"\",";
	print "           \"" var_opt_enum[i] "\",";
	print "           (int) ptr->x_" var_opt_enum[i] ");";
	print "";
}

for (i = 0; i < n_opt_short; i++) {
	print "  if (ptr->x_" var_opt_short[i] ")";
	print "    fprintf (file, \"%*s%s (%#x)\\n\",";
	print "             indent_to, \"\",";
	print "             \"" var_opt_short[i] "\",";
	print "             ptr->x_" var_opt_short[i] ");";
	print "";
}

for (i = 0; i < n_opt_char; i++) {
	print "  if (ptr->x_" var_opt_char[i] ")";
	print "    fprintf (file, \"%*s%s (%#x)\\n\",";
	print "             indent_to, \"\",";
	print "             \"" var_opt_char[i] "\",";
	print "             ptr->x_" var_opt_char[i] ");";
	print "";
}

print "}";

print "";
print "/* Print different optimization variables from structures provided as arguments.  */";
print "void";
print "cl_optimization_print_diff (FILE *file,";
print "                            int indent_to,";
print "                            struct cl_optimization *ptr1,";
print "                            struct cl_optimization *ptr2)";
print "{";

print "  fputs (\"\\n\", file);";
for (i = 0; i < n_opt_other; i++) {
	print "  if (ptr1->x_" var_opt_other[i] " != ptr2->x_" var_opt_other[i] ")";
	print "    fprintf (file, \"%*s%s (%#lx/%#lx)\\n\",";
	print "             indent_to, \"\",";
	print "             \"" var_opt_other[i] "\",";
	print "             (unsigned long)ptr1->x_" var_opt_other[i] ",";
	print "             (unsigned long)ptr2->x_" var_opt_other[i] ");";
	print "";
}

for (i = 0; i < n_opt_int; i++) {
	print "  if (ptr1->x_" var_opt_int[i] " != ptr2->x_" var_opt_int[i] ")";
	print "    fprintf (file, \"%*s%s (%#x/%#x)\\n\",";
	print "             indent_to, \"\",";
	print "             \"" var_opt_int[i] "\",";
	print "             ptr1->x_" var_opt_int[i] ",";
	print "             ptr2->x_" var_opt_int[i] ");";
	print "";
}

for (i = 0; i < n_opt_enum; i++) {
	print "  if (ptr1->x_" var_opt_enum[i] " != ptr2->x_" var_opt_enum[i] ")";
	print "  fprintf (file, \"%*s%s (%#x/%#x)\\n\",";
	print "           indent_to, \"\",";
	print "           \"" var_opt_enum[i] "\",";
	print "           (int) ptr1->x_" var_opt_enum[i] ",";
	print "           (int) ptr2->x_" var_opt_enum[i] ");";
	print "";
}

for (i = 0; i < n_opt_short; i++) {
	print "  if (ptr1->x_" var_opt_short[i] " != ptr2->x_" var_opt_short[i] ")";
	print "    fprintf (file, \"%*s%s (%#x/%#x)\\n\",";
	print "             indent_to, \"\",";
	print "             \"" var_opt_short[i] "\",";
	print "             ptr1->x_" var_opt_short[i] ",";
	print "             ptr2->x_" var_opt_short[i] ");";
	print "";
}

for (i = 0; i < n_opt_char; i++) {
	print "  if (ptr1->x_" var_opt_char[i] " != ptr2->x_" var_opt_char[i] ")";
	print "    fprintf (file, \"%*s%s (%#x/%#x)\\n\",";
	print "             indent_to, \"\",";
	print "             \"" var_opt_char[i] "\",";
	print "             ptr1->x_" var_opt_char[i] ",";
	print "             ptr2->x_" var_opt_char[i] ");";
	print "";
}

print "}";


print "";
print "/* Save selected option variables into a structure.  */"
print "void";
print "cl_target_option_save (struct cl_target_option *ptr, struct gcc_options *opts)";
print "{";

n_target_char = 0;
n_target_short = 0;
n_target_int = 0;
n_target_enum = 0;
n_target_other = 0;

if (have_save) {
	for (i = 0; i < n_opts; i++) {
		if (flag_set_p("Save", flags[i])) {
			name = var_name(flags[i])
			if(name == "")
				name = "target_flags";

			if(name in var_save_seen)
				continue;

			var_save_seen[name]++;
			otype = var_type_struct(flags[i])
			if (otype ~ "^((un)?signed +)?int *$")
				var_target_int[n_target_int++] = name;

			else if (otype ~ "^((un)?signed +)?short *$")
				var_target_short[n_target_short++] = name;

			else if (otype ~ ("^enum +[_" alnum "]+ *$"))
				var_target_enum[n_target_enum++] = name;

			else if (otype ~ "^((un)?signed +)?char *$") {
				var_target_char[n_target_char++] = name;
				if (otype ~ "^unsigned +char *$")
					var_target_range[name] = "0, 255"
				else if (otype ~ "^signed +char *$")
					var_target_range[name] = "-128, 127"
				if (otype == var_type(flags[i]))
					var_target_range[name] = ""
			}
			else
				var_target_other[n_target_other++] = name;
		}
	}
} else {
	var_target_int[n_target_int++] = "target_flags";
}

have_assert = 0;
for (i = 0; i < n_target_char; i++) {
	name = var_target_char[i];
	if (var_target_range[name] != "") {
		have_assert = 1;
		print "  gcc_assert (IN_RANGE (opts->x_" name ", " var_target_range[name] "));";
	}
}

if (have_assert)
	print "";

print "  if (targetm.target_option.save)";
print "    targetm.target_option.save (ptr, opts);";
print "";

for (i = 0; i < n_extra_target_vars; i++) {
	print "  ptr->x_" extra_target_vars[i] " = opts->x_" extra_target_vars[i] ";";
}

for (i = 0; i < n_target_other; i++) {
	print "  ptr->x_" var_target_other[i] " = opts->x_" var_target_other[i] ";";
}

for (i = 0; i < n_target_enum; i++) {
	print "  ptr->x_" var_target_enum[i] " = opts->x_" var_target_enum[i] ";";
}

for (i = 0; i < n_target_int; i++) {
	print "  ptr->x_" var_target_int[i] " = opts->x_" var_target_int[i] ";";
}

for (i = 0; i < n_target_short; i++) {
	print "  ptr->x_" var_target_short[i] " = opts->x_" var_target_short[i] ";";
}

for (i = 0; i < n_target_char; i++) {
	print "  ptr->x_" var_target_char[i] " = opts->x_" var_target_char[i] ";";
}

print "}";

print "";
print "/* Restore selected current options from a structure.  */";
print "void";
print "cl_target_option_restore (struct gcc_options *opts, struct cl_target_option *ptr)";
print "{";

for (i = 0; i < n_extra_target_vars; i++) {
	print "  opts->x_" extra_target_vars[i] " = ptr->x_" extra_target_vars[i] ";";
}

for (i = 0; i < n_target_other; i++) {
	print "  opts->x_" var_target_other[i] " = ptr->x_" var_target_other[i] ";";
}

for (i = 0; i < n_target_enum; i++) {
	print "  opts->x_" var_target_enum[i] " = ptr->x_" var_target_enum[i] ";";
}

for (i = 0; i < n_target_int; i++) {
	print "  opts->x_" var_target_int[i] " = ptr->x_" var_target_int[i] ";";
}

for (i = 0; i < n_target_short; i++) {
	print "  opts->x_" var_target_short[i] " = ptr->x_" var_target_short[i] ";";
}

for (i = 0; i < n_target_char; i++) {
	print "  opts->x_" var_target_char[i] " = ptr->x_" var_target_char[i] ";";
}

# This must occur after the normal variables in case the code depends on those
# variables.
print "";
print "  if (targetm.target_option.restore)";
print "    targetm.target_option.restore (opts, ptr);";

print "}";

print "";
print "/* Print optimization options from a structure.  */";
print "void";
print "cl_target_option_print (FILE *file,";
print "                        int indent,";
print "                        struct cl_target_option *ptr)";
print "{";

print "  fputs (\"\\n\", file);";
for (i = 0; i < n_target_other; i++) {
	print "  if (ptr->x_" var_target_other[i] ")";
	if (host_wide_int[var_target_other[i]] == "yes")
		print "    fprintf (file, \"%*s%s (%#\" HOST_WIDE_INT_PRINT \"x)\\n\",";
	else
		print "    fprintf (file, \"%*s%s (%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_other[i] "\",";
	if (host_wide_int[var_target_other[i]] == "yes")
		print "             ptr->x_" var_target_other[i] ");";
	else
		print "             (unsigned long)ptr->x_" var_target_other[i] ");";
	print "";
}

for (i = 0; i < n_target_enum; i++) {
	print "  if (ptr->x_" var_target_enum[i] ")";
	print "    fprintf (file, \"%*s%s (%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_enum[i] "\",";
	print "             ptr->x_" var_target_enum[i] ");";
	print "";
}

for (i = 0; i < n_target_int; i++) {
	print "  if (ptr->x_" var_target_int[i] ")";
	print "    fprintf (file, \"%*s%s (%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_int[i] "\",";
	print "             ptr->x_" var_target_int[i] ");";
	print "";
}

for (i = 0; i < n_target_short; i++) {
	print "  if (ptr->x_" var_target_short[i] ")";
	print "    fprintf (file, \"%*s%s (%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_short[i] "\",";
	print "             ptr->x_" var_target_short[i] ");";
	print "";
}

for (i = 0; i < n_target_char; i++) {
	print "  if (ptr->x_" var_target_char[i] ")";
	print "    fprintf (file, \"%*s%s (%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_char[i] "\",";
	print "             ptr->x_" var_target_char[i] ");";
	print "";
}

print "";
print "  if (targetm.target_option.print)";
print "    targetm.target_option.print (file, indent, ptr);";
print "}";

print "";
print "/* Print different target option variables from structures provided as arguments.  */";
print "void";
print "cl_target_option_print_diff (FILE *file,";
print "                             int indent ATTRIBUTE_UNUSED,";
print "                             struct cl_target_option *ptr1 ATTRIBUTE_UNUSED,";
print "                             struct cl_target_option *ptr2 ATTRIBUTE_UNUSED)";
print "{";

print "  fputs (\"\\n\", file);";
for (i = 0; i < n_target_other; i++) {
	print "  if (ptr1->x_" var_target_other[i] " != ptr2->x_" var_target_other[i] ")";
	if (host_wide_int[var_target_other[i]] == "yes")
		print "    fprintf (file, \"%*s%s (%#\" HOST_WIDE_INT_PRINT \"x/%#\" HOST_WIDE_INT_PRINT \"x)\\n\",";
	else
		print "    fprintf (file, \"%*s%s (%#x/%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_other[i] "\",";
	if (host_wide_int[var_target_other[i]] == "yes") {
		print "             ptr1->x_" var_target_other[i] ",";
		print "             ptr2->x_" var_target_other[i] ");";
	}
	else {
		print "             (unsigned long)ptr1->x_" var_target_other[i] ",";
		print "             (unsigned long)ptr2->x_" var_target_other[i] ");";
	}
	print "";
}

for (i = 0; i < n_target_enum; i++) {
	print "  if (ptr1->x_" var_target_enum[i] " != ptr2->x_" var_target_enum[i] ")";
	print "    fprintf (file, \"%*s%s (%#x/%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_enum[i] "\",";
	print "             ptr1->x_" var_target_enum[i] ",";
	print "             ptr2->x_" var_target_enum[i] ");";
	print "";
}

for (i = 0; i < n_target_int; i++) {
	print "  if (ptr1->x_" var_target_int[i] " != ptr2->x_" var_target_int[i] ")";
	print "    fprintf (file, \"%*s%s (%#x/%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_int[i] "\",";
	print "             ptr1->x_" var_target_int[i] ",";
	print "             ptr2->x_" var_target_int[i] ");";
	print "";
}

for (i = 0; i < n_target_short; i++) {
	print "  if (ptr1->x_" var_target_short[i] " != ptr2->x_" var_target_short[i] ")";
	print "    fprintf (file, \"%*s%s (%#x/%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_short[i] "\",";
	print "             ptr1->x_" var_target_short[i] ",";
	print "             ptr2->x_" var_target_short[i] ");";
	print "";
}

for (i = 0; i < n_target_char; i++) {
	print "  if (ptr1->x_" var_target_char[i] " != ptr2->x_" var_target_char[i] ")";
	print "    fprintf (file, \"%*s%s (%#x/%#x)\\n\",";
	print "             indent, \"\",";
	print "             \"" var_target_char[i] "\",";
	print "             ptr1->x_" var_target_char[i] ",";
	print "             ptr2->x_" var_target_char[i] ");";
	print "";
}

print "}";

print "";
print "/* Compare two target options  */";
print "bool";
print "cl_target_option_eq (struct cl_target_option const *ptr1 ATTRIBUTE_UNUSED,";
print "                     struct cl_target_option const *ptr2 ATTRIBUTE_UNUSED)";
print "{";
n_target_val = 0;
n_target_str = 0;
n_target_array = 0;

for (i = 0; i < n_target_save; i++) {
	var = target_save_decl[i];
	sub (" *=.*", "", var);
	name = var;
	type = var;
	sub("^.*[ *]", "", name)
	sub(" *" name "$", "", type)
	if (target_save_decl[i] ~ "^const char \\*+[_" alnum "]+$")
		var_target_str[n_target_str++] = name;
	else {
		if (target_save_decl[i] ~ " .*\\[.+\\]+$") {
			size = name;
			sub("[^\\[]+\\[", "", size);
			sub("\\]$", "", size);
			sub("\\[.+", "", name)
			sub(" [^ ]+$", "", type)
			var_target_array[n_target_array] = name
			var_target_array_type[n_target_array] = type
			var_target_array_size[n_target_array++] = size
		}
		else {
			var_target_val_type[n_target_val] = type;
			var_target_val[n_target_val++] = name;
		}
	}
}
if (have_save) {
	for (i = 0; i < n_opts; i++) {
		if (flag_set_p("Save", flags[i])) {
			name = var_name(flags[i])
			if(name == "")
				name = "target_flags";

			if(name in var_list_seen)
				continue;

			var_list_seen[name]++;
			otype = var_type_struct(flags[i])
			if (otype ~ "^const char \\**$")
				var_target_str[n_target_str++] = "x_" name;
			else {
				var_target_val_type[n_target_val] = otype;
				var_target_val[n_target_val++] = "x_" name;
			}
		}
	}
} else {
	var_target_val_type[n_target_val] = "int";
	var_target_val[n_target_val++] = "x_target_flags";
}

for (i = 0; i < n_target_str; i++) {
	name = var_target_str[i]
	print "  if (ptr1->" name" != ptr2->" name;
	print "      && (!ptr1->" name" || !ptr2->" name
	print "          || strcmp (ptr1->" name", ptr2->" name ")))";
	print "    return false;";
}
for (i = 0; i < n_target_array; i++) {
	name = var_target_array[i]
	size = var_target_array_size[i]
	type = var_target_array_type[i]
	print "  if (ptr1->" name" != ptr2->" name "";
	print "      || memcmp (ptr1->" name ", ptr2->" name ", " size " * sizeof(" type ")))"
	print "    return false;";
}
for (i = 0; i < n_target_val; i++) {
	name = var_target_val[i]
	print "  if (ptr1->" name" != ptr2->" name ")";
	print "    return false;";
}

print "  return true;";

print "}";

print "";
print "/* Hash target options  */";
print "hashval_t";
print "cl_target_option_hash (struct cl_target_option const *ptr ATTRIBUTE_UNUSED)";
print "{";
print "  inchash::hash hstate;";
for (i = 0; i < n_target_str; i++) {
	name = var_target_str[i]
	print "  if (ptr->" name")";
	print "    hstate.add (ptr->" name", strlen (ptr->" name"));";
	print "  else";
	print "    hstate.add_int (0);";
}
for (i = 0; i < n_target_array; i++) {
	name= var_target_array[i]
	size = var_target_array_size[i]
	type = var_target_array_type[i]
	print "  hstate.add_int (" size ");";
	print "  hstate.add (ptr->" name ", sizeof (" type ") * " size ");";
}
for (i = 0; i < n_target_val; i++) {
	name = var_target_val[i]
	print "  hstate.add_wide_int (ptr->" name");";
}
print "  return hstate.end ();";
print "}";

print "";
print "/* Stream out target options  */";
print "void";
print "cl_target_option_stream_out (struct output_block *ob ATTRIBUTE_UNUSED,";
print "                             struct bitpack_d *bp ATTRIBUTE_UNUSED,";
print "                             struct cl_target_option *ptr ATTRIBUTE_UNUSED)";
print "{";
for (i = 0; i < n_target_str; i++) {
	name = var_target_str[i]
	print "  bp_pack_string (ob, bp, ptr->" name", true);";
}
for (i = 0; i < n_target_array; i++) {
	name = var_target_array[i]
	size = var_target_array_size[i]
	print "  for (unsigned i = 0; i < " size "; i++)"
	print "    bp_pack_value (bp, ptr->" name "[i], 64);";
}
for (i = 0; i < n_target_val; i++) {
	name = var_target_val[i]
	print "  bp_pack_value (bp, ptr->" name", 64);";
}
print "}";

print "";
print "/* Stream in target options  */";
print "void";
print "cl_target_option_stream_in (struct data_in *data_in ATTRIBUTE_UNUSED,";
print "                            struct bitpack_d *bp ATTRIBUTE_UNUSED,";
print "                            struct cl_target_option *ptr ATTRIBUTE_UNUSED)";
print "{";
for (i = 0; i < n_target_str; i++) {
	name = var_target_str[i]
	print "  ptr->" name" = bp_unpack_string (data_in, bp);";
	print "  if (ptr->" name")";
	print "    ptr->" name" = xstrdup (ptr->" name");";
}
for (i = 0; i < n_target_array; i++) {
	name = var_target_array[i]
	size = var_target_array_size[i]
	print "  for (int i = " size " - 1; i >= 0; i--)"
	print "    ptr->" name "[i] = (" var_target_array_type[i] ") bp_unpack_value (bp, 64);";
}
for (i = 0; i < n_target_val; i++) {
	name = var_target_val[i]
	print "  ptr->" name" = (" var_target_val_type[i] ") bp_unpack_value (bp, 64);";
}

print "}";

n_opt_val = 3;
var_opt_val[0] = "x_optimize"
var_opt_val_type[0] = "char "
var_opt_val[1] = "x_optimize_size"
var_opt_val[2] = "x_optimize_debug"
var_opt_val_type[1] = "char "
var_opt_val_type[2] = "char "
for (i = 0; i < n_opts; i++) {
	if (flag_set_p("(Optimization|PerFunction)", flags[i])) {
		name = var_name(flags[i])
		if(name == "")
			continue;

		if(name in var_opt_list_seen)
			continue;

		var_opt_list_seen[name]++;

		otype = var_type_struct(flags[i])
		var_opt_val_type[n_opt_val] = otype;
		var_opt_val[n_opt_val++] = "x_" name;
		var_opt_hash[n_opt_val] = flag_set_p("Optimization", flags[i]);
	}
}
print "";
print "/* Hash optimization options  */";
print "hashval_t";
print "cl_optimization_hash (struct cl_optimization const *ptr ATTRIBUTE_UNUSED)";
print "{";
print "  inchash::hash hstate;";
for (i = 0; i < n_opt_val; i++) {
	if (!var_opt_hash[i])
		continue;
	name = var_opt_val[i]
	print "  hstate.add_wide_int (ptr->" name");";
}
print "  return hstate.end ();";
print "}";

print "";
print "/* Stream out optimization options  */";
print "void";
print "cl_optimization_stream_out (struct bitpack_d *bp,";
print "                            struct cl_optimization *ptr)";
print "{";
for (i = 0; i < n_opt_val; i++) {
	name = var_opt_val[i]
	print "  bp_pack_value (bp, ptr->" name", 64);";
}
print "}";

print "";
print "/* Stream in optimization options  */";
print "void";
print "cl_optimization_stream_in (struct bitpack_d *bp,";
print "                           struct cl_optimization *ptr)";
print "{";
for (i = 0; i < n_opt_val; i++) {
	name = var_opt_val[i]
	print "  ptr->" name" = (" var_opt_val_type[i] ") bp_unpack_value (bp, 64);";
}
print "}";
}
