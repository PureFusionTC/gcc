/* Missing <cstddef>.  */

void *ptr = NULL; // { dg-error "'NULL' was not declared" }
// { dg-message "'NULL' is defined in header '<cstddef>'; did you forget to '#include <cstddef>'?" "" { target *-*-* } .-1 }

ptrdiff_t pd; // { dg-error "'ptrdiff_t' does not name a type" }
// { dg-message "'ptrdiff_t' is defined in header '<cstddef>'; did you forget to '#include <cstddef>'?" "" { target *-*-* } .-1 }

size_t sz; // { dg-error "'size_t' does not name a type" }
// { dg-message "'size_t' is defined in header '<cstddef>'; did you forget to '#include <cstddef>'?" "" { target *-*-* } .-1 }

/* Missing <cstdio>.  */

void test_cstdio (void)
{
  FILE *f; // { dg-error "'FILE' was not declared in this scope" }
  // { dg-message "'FILE' is defined in header '<cstdio>'; did you forget to '#include <cstdio>'?" "" { target *-*-* } .-1 }
  // { dg-error "'f' was not declared in this scope" "" { target *-*-* } .-2 }
  // { dg-bogus "suggested alternative: 'if'" "PR c++/80567" { xfail *-*-* } .-3 }

  char buf[BUFSIZ]; // { dg-error "'BUFSIZ' was not declared" }
  // { dg-message "'BUFSIZ' is defined in header '<cstdio>'; did you forget to '#include <cstdio>'?" "" { target *-*-* } .-1 }

  char buf2[FILENAME_MAX]; // { dg-error "'FILENAME_MAX' was not declared" }
  // { dg-message "'FILENAME_MAX' is defined in header '<cstdio>'; did you forget to '#include <cstdio>'?" "" { target *-*-* } .-1 }

  stderr; // { dg-error "'stderr' was not declared" }
  // { dg-message "'stderr' is defined in header '<cstdio>'; did you forget to '#include <cstdio>'?" "" { target *-*-* } .-1 }

  stdin; // { dg-error "'stdin' was not declared" }
  // { dg-message "'stdin' is defined in header '<cstdio>'; did you forget to '#include <cstdio>'?" "" { target *-*-* } .-1 }

  stdout; // { dg-error "'stdout' was not declared" }
  // { dg-message "'stdout' is defined in header '<cstdio>'; did you forget to '#include <cstdio>'?" "" { target *-*-* } .-1 }

  EOF; // { dg-error "'EOF' was not declared" }
  // { dg-message "'EOF' is defined in header '<cstdio>'; did you forget to '#include <cstdio>'?" "" { target *-*-* } .-1 }
}

/* Missing <cerrno>.  */

int test_cerrno (void)
{
  return errno; // { dg-error "'errno' was not declared" }
  // { dg-message "'errno' is defined in header '<cerrno>'; did you forget to '#include <cerrno>'?" "" { target *-*-* } .-1 }
}

/* Missing <cstdarg>.  */

void test_cstdarg (void)
{
  va_list ap; // { dg-error "'va_list'" }
  // { dg-message "'va_list' is defined in header '<cstdarg>'; did you forget to '#include <cstdarg>'?" "" { target *-*-* } .-1 }
}

/* Missing <climits>.  */
int test_INT_MAX (void)
{
  return INT_MAX; // { dg-line INT_MAX_line }
  // { dg-error "'INT_MAX' was not declared" "" { target *-*-* } INT_MAX_line }
  // { dg-bogus "__INT_MAX__" "" { target *-*-* } INT_MAX_line }
  // { dg-message "'INT_MAX' is defined in header '<climits>'; did you forget to '#include <climits>'?" "" { target *-*-* } INT_MAX_line }
}

/* Verify that we don't offer suggestions to stdlib globals names when
   there's an explicit namespace.  */

namespace some_ns {}

int not_within_namespace (void)
{
  return some_ns::stdout; // { dg-error "'stdout' is not a member of 'some_ns'" }
  // { dg-bogus "is defined in header" "" { target *-*-* } .-1 }
}

/* Similarly for when there's an explicit class scope.  */

class some_class {};

int not_within_class (void)
{
  return some_class::stdout; // { dg-error "'stdout' is not a member of 'some_class'" }
  // { dg-bogus "is defined in header" "" { target *-*-* } .-1 }
}
