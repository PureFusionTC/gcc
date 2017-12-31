/* { dg-do compile { target { ! x32 } } } */
/* { dg-options "-fcheck-pointer-bounds -mmpx -O2 -fdump-tree-chkpopt -fchkp-use-fast-string-functions" } */
/* { dg-final { scan-tree-dump "memmove_nobnd" "chkpopt" } } */

#include "../../gcc.dg/strlenopt.h"

void test (int *buf1, int *buf2, size_t len)
{
  memmove (buf1, buf2, len);
}
