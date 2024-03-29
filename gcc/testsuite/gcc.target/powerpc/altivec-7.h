/* Origin: Aldy Hernandez  <aldyh@redhat.com>  */

/* This test code is included into altivec-7-be.c and altivec-7-le.c.  
   The two files have the tests for the number of instructions generated for
   LE versus BE.  */

#include <altivec.h>

int **intp;
int *var_int;
unsigned int **uintp;
vector pixel *varpixel;
vector signed char *vecchar;
vector signed int *vecint;
vector signed short *vecshort;
vector unsigned char *vecuchar;
vector unsigned int *vecuint;
vector unsigned short *vecushort;
vector float *vecfloat;
vector double *vecdouble;

int main ()
{
  *vecfloat++ = vec_andc((vector bool int)vecint[0], vecfloat[1]);
  *vecfloat++ = vec_andc(vecfloat[0], (vector bool int)vecint[1]);
  *vecfloat++ = vec_vxor((vector bool int)vecint[0], vecfloat[1]);
  *vecfloat++ = vec_vxor(vecfloat[0], (vector bool int)vecint[1]);
  *varpixel++ = vec_packpx(vecuint[0], vecuint[1]);
  *varpixel++ = vec_vpkpx(vecuint[0], vecuint[1]);
  *vecshort++ = vec_vmulesb(vecchar[0], vecchar[1]);
  *vecshort++ = vec_vmulosb(vecchar[0], vecchar[1]);
  *vecint++ = vec_ld(var_int[0], intp[1]);
  *vecint++ = vec_lde(var_int[0], intp[1]);
  *vecint++ = vec_ldl(var_int[0], intp[1]);
  *vecint++ = vec_lvewx(var_int[0], intp[1]);
  *vecint++ = vec_unpackh(vecshort[0]);
  *vecint++ = vec_unpackl(vecshort[0]);
  *vecushort++ = vec_andc((vector bool short)vecshort[0], vecushort[1]);
  *vecushort++ = vec_andc(vecushort[0], (vector bool short)vecshort[1]);
  *vecushort++ = vec_vxor((vector bool short)vecshort[0], vecushort[1]);
  *vecushort++ = vec_vxor(vecushort[0], (vector bool short)vecshort[1]);
  *vecuint++ = vec_ld(var_int[0], uintp[1]);
  *vecuint++ = vec_lvx(var_int[0], uintp[1]);
  *vecuint++ = vec_vmsumubm(vecuchar[0], vecuchar[1], vecuint[2]);
  *vecuchar++ = vec_xor(vecuchar[0], (vector unsigned char)vecchar[1]);
  *vecdouble++ = vec_unpackl(vecfloat[0]);
  *vecdouble++ = vec_unpackh(vecfloat[0]);

  return 0;
}
