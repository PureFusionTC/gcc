/* { dg-do compile { target powerpc*-*-* } } */
/* { dg-require-effective-target powerpc_altivec_ok } */
/* { dg-options "-maltivec" } */

/* Author: Ziemowit Laski  <zlaski@apple.com>  */

/* This test case exercises intrinsic/argument combinations that,
   while not in the Motorola AltiVec PIM, have nevertheless crept
   into the AltiVec vernacular over the years.  */

#include <altivec.h>

void foo (void) 
{
  vector bool int boolVec1 = (vector bool int) vec_splat_u32(3);
  vector bool short boolVec2 = (vector bool short) vec_splat_u16(3);
  vector bool char boolVec3 = (vector bool char) vec_splat_u8(3);
  vector signed char vsc1, vsc2, vscz;
  vector unsigned char vuc1, vuc2, vucz;
  vector signed short int vssi1, vssi2, vssiz;
  vector signed int vsi1, vsi2, vsiz;
  vector unsigned int vui1, vui2, vuiz;
  vector unsigned short int vusi1, vusi2, vusiz;
  vector bool long long vubll1, vubll2, vubllz;
  vector signed int long long vsill1, vsill2, vsillz;
  vector unsigned int long long vuill1, vuill2, vuillz;
  vector pixel vp1, vp2, vpz;
  vector float vf1, vf2, vfz;
  vector double vd1, vd2, vdz;
  
  boolVec1 = vec_sld( boolVec1, boolVec1, 4 );
  boolVec2 = vec_sld( boolVec2, boolVec2, 2 );
  boolVec3 = vec_sld( boolVec3, boolVec3, 1 );

  vscz = vec_sld( vsc1, vsc2, 1 );
  vucz = vec_sld( vuc1, vuc2, 1 );
  vsiz = vec_sld( vsi1, vsi2, 1 );
  vuiz = vec_sld( vui1, vui2, 1 );
  vubllz = vec_sld( vubll1, vubll2, 1 );
  vsillz = vec_sld( vsill1, vsill2, 1 );
  vuillz = vec_sld( vuill1, vuill2, 1 );
  vssiz = vec_sld( vssi1, vssi2, 1 );
  vusiz = vec_sld( vusi1, vusi2, 1 );
  
  vfz = vec_sld( vf1, vf2, 1 );
  vdz = vec_sld( vd1, vd2, 1 );

  vpz = vec_sld( vp1, vp2, 1 );

  vucz = vec_srl(vuc1, vuc2);
  vsiz = vec_srl(vsi1, vuc2);
  vuiz = vec_srl(vui1, vuc2);
  vsillz = vec_srl(vsill1, vuc2);
  vuillz = vec_srl(vuill1, vuc2);
  vpz = vec_srl(vp1, vuc2);
  vssiz = vec_srl(vssi1, vuc2);
  vusiz = vec_srl(vusi1, vuc2);

  vscz = vec_sro(vsc1, vsc2);
  vscz = vec_sro(vsc1, vuc2);
  vucz = vec_sro(vuc1, vsc2);
  vucz = vec_sro(vuc1, vuc2);
  vsiz = vec_sro(vsi1, vsc2);
  vsiz = vec_sro(vsi1, vuc2);
  vuiz = vec_sro(vui1, vsc2);
  vuiz = vec_sro(vui1, vuc2);
  vsillz = vec_sro(vsill1, vsc2);
  vsillz = vec_sro(vsill1, vuc2);
  vuillz = vec_sro(vuill1, vsc2);
  vuillz = vec_sro(vuill1, vuc2);
  vpz = vec_sro(vp1, vsc2);
  vpz = vec_sro(vp1, vuc2);
  vssiz = vec_sro(vssi1, vsc2);
  vssiz = vec_sro(vssi1, vuc2);
  vusiz = vec_sro(vusi1, vsc2);
  vusiz = vec_sro(vusi1, vuc2);
  vfz = vec_sro(vf1, vsc2);
  vfz = vec_sro(vf1, vuc2);
}

/* Expected results:
   vec_sld          vsldoi
   vec_srl          vsr
   vec_sro          vsro  */

/* { dg-final { scan-assembler-times "vsldoi" 15 } } */
/* { dg-final { scan-assembler-times "vsr " 8 } } */
/* { dg-final { scan-assembler-times "vsro" 20 } } */
