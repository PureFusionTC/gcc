/* { dg-do run } */
/* { dg-options "-O3 -mpower8-vector -Wno-psabi" } */
/* { dg-require-effective-target lp64 } */
/* { dg-require-effective-target p8vector_hw } */

#ifndef CHECK_H
#define CHECK_H "sse2-check.h"
#endif

#include CHECK_H

#ifndef TEST
#define TEST sse2_test_psllq_1
#endif

#define N 60

#include <emmintrin.h>

#ifdef _ARCH_PWR8
static __m128i
__attribute__((noinline, unused))
test (__m128i s1)
{
  return _mm_slli_epi64 (s1, N); 
}
#endif

static void
TEST (void)
{
#ifdef _ARCH_PWR8
  union128i_q u, s;
  long long e[2] = {0};
  int i;
 
  s.x = _mm_set_epi64x (-1, 0xf);

  u.x = test (s.x);

  if (N < 64)
    for (i = 0; i < 2; i++)
      e[i] = s.a[i] << N; 

  if (check_union128i_q (u, e))
    abort (); 
#endif
}
