// { dg-do run { target c++11 } }
// { dg-options "-D__STDCPP_WANT_MATH_SPEC_FUNCS__" }
//
// Copyright (C) 2016-2017 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 3, or (at your option)
// any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING3.  If not see
// <http://www.gnu.org/licenses/>.

//  ellint_2
//  Compare against values generated by the GNU Scientific Library.
//  The GSL can be found on the web: http://www.gnu.org/software/gsl/
#include <limits>
#include <cmath>
#if defined(__TEST_DEBUG)
#  include <iostream>
#  define VERIFY(A) \
  if (!(A)) \
    { \
      std::cout << "line " << __LINE__ \
	<< "  max_abs_frac = " << max_abs_frac \
	<< std::endl; \
    }
#else
#  include <testsuite_hooks.h>
#endif
#include <specfun_testcase.h>

// Test data for k=-0.90000000000000002.
// max(|f - f_Boost|): 6.6613381477509392e-16 at index 7
// max(|f - f_Boost| / |f_Boost|): 6.6116483711056727e-16
// mean(f - f_Boost): -8.6042284408449634e-17
// variance(f - f_Boost): 4.1543973284335233e-32
// stddev(f - f_Boost): 2.0382338748125847e-16
const testcase_ellint_2<double>
data001[10] =
{
  { 0.0000000000000000, -0.90000000000000002, 0.0000000000000000, 0.0 },
  { 0.17381690606167963, -0.90000000000000002, 0.17453292519943295, 0.0 },
  { 0.34337919186972055, -0.90000000000000002, 0.34906585039886590, 0.0 },
  { 0.50464268659856337, -0.90000000000000002, 0.52359877559829882, 0.0 },
  { 0.65400003842368593, -0.90000000000000002, 0.69813170079773179, 0.0 },
  { 0.78854928419904635, -0.90000000000000002, 0.87266462599716477, 0.0 },
  { 0.90645698626315396, -0.90000000000000002, 1.0471975511965976, 0.0 },
  { 1.0075154899135927, -0.90000000000000002, 1.2217304763960306, 0.0 },
  { 1.0940135583194071, -0.90000000000000002, 1.3962634015954636, 0.0 },
  { 1.1716970527816142, -0.90000000000000002, 1.5707963267948966, 0.0 },
};
const double toler001 = 2.5000000000000020e-13;

// Test data for k=-0.80000000000000004.
// max(|f - f_Boost|): 1.3322676295501878e-15 at index 9
// max(|f - f_Boost| / |f_Boost|): 1.0438106231598255e-15
// mean(f - f_Boost): 1.8318679906315082e-16
// variance(f - f_Boost): 1.6301071049293564e-31
// stddev(f - f_Boost): 4.0374584888632060e-16
const testcase_ellint_2<double>
data002[10] =
{
  { 0.0000000000000000, -0.80000000000000004, 0.0000000000000000, 0.0 },
  { 0.17396762274534805, -0.80000000000000004, 0.17453292519943295, 0.0 },
  { 0.34458685226969321, -0.80000000000000004, 0.34906585039886590, 0.0 },
  { 0.50872923654502433, -0.80000000000000004, 0.52359877559829882, 0.0 },
  { 0.66372016539176226, -0.80000000000000004, 0.69813170079773179, 0.0 },
  { 0.80760344410167406, -0.80000000000000004, 0.87266462599716477, 0.0 },
  { 0.93945480372495072, -0.80000000000000004, 1.0471975511965976, 0.0 },
  { 1.0597473310395040, -0.80000000000000004, 1.2217304763960306, 0.0 },
  { 1.1706981862452359, -0.80000000000000004, 1.3962634015954636, 0.0 },
  { 1.2763499431699064, -0.80000000000000004, 1.5707963267948966, 0.0 },
};
const double toler002 = 2.5000000000000020e-13;

// Test data for k=-0.69999999999999996.
// max(|f - f_Boost|): 6.6613381477509392e-16 at index 8
// max(|f - f_Boost| / |f_Boost|): 5.4138821888802831e-16
// mean(f - f_Boost): 1.9428902930940238e-17
// variance(f - f_Boost): 2.6524572947662036e-32
// stddev(f - f_Boost): 1.6286366368119696e-16
const testcase_ellint_2<double>
data003[10] =
{
  { 0.0000000000000000, -0.69999999999999996, 0.0000000000000000, 0.0 },
  { 0.17410041242702540, -0.69999999999999996, 0.17453292519943295, 0.0 },
  { 0.34564605085764760, -0.69999999999999996, 0.34906585039886590, 0.0 },
  { 0.51228495693314657, -0.69999999999999996, 0.52359877559829882, 0.0 },
  { 0.67207654098799530, -0.69999999999999996, 0.69813170079773179, 0.0 },
  { 0.82370932631556493, -0.69999999999999996, 0.87266462599716477, 0.0 },
  { 0.96672313309452806, -0.69999999999999996, 1.0471975511965976, 0.0 },
  { 1.1017090644949501, -0.69999999999999996, 1.2217304763960306, 0.0 },
  { 1.2304180097292916, -0.69999999999999996, 1.3962634015954636, 0.0 },
  { 1.3556611355719554, -0.69999999999999996, 1.5707963267948966, 0.0 },
};
const double toler003 = 2.5000000000000020e-13;

// Test data for k=-0.59999999999999998.
// max(|f - f_Boost|): 2.2204460492503131e-16 at index 7
// max(|f - f_Boost| / |f_Boost|): 1.9550519554437030e-16
// mean(f - f_Boost): 1.9428902930940238e-17
// variance(f - f_Boost): 4.6602749271592373e-35
// stddev(f - f_Boost): 6.8266206333435850e-18
const testcase_ellint_2<double>
data004[10] =
{
  { 0.0000000000000000, -0.59999999999999998, 0.0000000000000000, 0.0 },
  { 0.17421534919599127, -0.59999999999999998, 0.17453292519943295, 0.0 },
  { 0.34655927787174096, -0.59999999999999998, 0.34906585039886590, 0.0 },
  { 0.51533034538432143, -0.59999999999999998, 0.52359877559829882, 0.0 },
  { 0.67916550597453018, -0.59999999999999998, 0.69813170079773179, 0.0 },
  { 0.83720218180349881, -0.59999999999999998, 0.87266462599716477, 0.0 },
  { 0.98922159354937755, -0.59999999999999998, 1.0471975511965976, 0.0 },
  { 1.1357478470419362, -0.59999999999999998, 1.2217304763960306, 0.0 },
  { 1.2780617372844061, -0.59999999999999998, 1.3962634015954636, 0.0 },
  { 1.4180833944487241, -0.59999999999999998, 1.5707963267948966, 0.0 },
};
const double toler004 = 2.5000000000000020e-13;

// Test data for k=-0.50000000000000000.
// max(|f - f_Boost|): 4.4408920985006262e-16 at index 7
// max(|f - f_Boost| / |f_Boost|): 3.8178992821201131e-16
// mean(f - f_Boost): -4.9960036108132046e-17
// variance(f - f_Boost): 3.0133908324921077e-32
// stddev(f - f_Boost): 1.7359121039073689e-16
const testcase_ellint_2<double>
data005[10] =
{
  { 0.0000000000000000, -0.50000000000000000, 0.0000000000000000, 0.0 },
  { 0.17431249677315908, -0.50000000000000000, 0.17453292519943295, 0.0 },
  { 0.34732862537770803, -0.50000000000000000, 0.34906585039886590, 0.0 },
  { 0.51788193485993794, -0.50000000000000000, 0.52359877559829882, 0.0 },
  { 0.68506022954164547, -0.50000000000000000, 0.69813170079773179, 0.0 },
  { 0.84831662803347208, -0.50000000000000000, 0.87266462599716477, 0.0 },
  { 1.0075555551444719, -0.50000000000000000, 1.0471975511965976, 0.0 },
  { 1.1631768599287302, -0.50000000000000000, 1.2217304763960306, 0.0 },
  { 1.3160584048772548, -0.50000000000000000, 1.3962634015954636, 0.0 },
  { 1.4674622093394272, -0.50000000000000000, 1.5707963267948966, 0.0 },
};
const double toler005 = 2.5000000000000020e-13;

// Test data for k=-0.39999999999999991.
// max(|f - f_Boost|): 4.4408920985006262e-16 at index 9
// max(|f - f_Boost| / |f_Boost|): 2.9489138636265387e-16
// mean(f - f_Boost): 8.6042284408449634e-17
// variance(f - f_Boost): 1.5826864298542218e-32
// stddev(f - f_Boost): 1.2580486595733180e-16
const testcase_ellint_2<double>
data006[10] =
{
  { 0.0000000000000000, -0.39999999999999991, 0.0000000000000000, 0.0 },
  { 0.17439190872481267, -0.39999999999999991, 0.17453292519943295, 0.0 },
  { 0.34795581767099210, -0.39999999999999991, 0.34906585039886590, 0.0 },
  { 0.51995290683804463, -0.39999999999999991, 0.52359877559829882, 0.0 },
  { 0.68981638464431527, -0.39999999999999991, 0.69813170079773179, 0.0 },
  { 0.85722088859936030, -0.39999999999999991, 0.87266462599716477, 0.0 },
  { 1.0221301327876993, -0.39999999999999991, 1.0471975511965976, 0.0 },
  { 1.1848138019818375, -0.39999999999999991, 1.2217304763960306, 0.0 },
  { 1.3458259266501533, -0.39999999999999991, 1.3962634015954636, 0.0 },
  { 1.5059416123600404, -0.39999999999999991, 1.5707963267948966, 0.0 },
};
const double toler006 = 2.5000000000000020e-13;

// Test data for k=-0.29999999999999993.
// max(|f - f_Boost|): 6.6613381477509392e-16 at index 9
// max(|f - f_Boost| / |f_Boost|): 4.3401048387253188e-16
// mean(f - f_Boost): 7.2164496600635178e-17
// variance(f - f_Boost): 4.3555500115139682e-32
// stddev(f - f_Boost): 2.0869954507650391e-16
const testcase_ellint_2<double>
data007[10] =
{
  { 0.0000000000000000, -0.29999999999999993, 0.0000000000000000, 0.0 },
  { 0.17445362864048913, -0.29999999999999993, 0.17453292519943295, 0.0 },
  { 0.34844223535713470, -0.29999999999999993, 0.34906585039886590, 0.0 },
  { 0.52155353877411759, -0.29999999999999993, 0.52359877559829882, 0.0 },
  { 0.69347584418369890, -0.29999999999999993, 0.69813170079773179, 0.0 },
  { 0.86403609928237657, -0.29999999999999993, 0.87266462599716477, 0.0 },
  { 1.0332234514065408, -0.29999999999999993, 1.0471975511965976, 0.0 },
  { 1.2011943182068923, -0.29999999999999993, 1.2217304763960306, 0.0 },
  { 1.3682566113689625, -0.29999999999999993, 1.3962634015954636, 0.0 },
  { 1.5348334649232489, -0.29999999999999993, 1.5707963267948966, 0.0 },
};
const double toler007 = 2.5000000000000020e-13;

// Test data for k=-0.19999999999999996.
// max(|f - f_Boost|): 4.4408920985006262e-16 at index 6
// max(|f - f_Boost| / |f_Boost|): 4.2658819988515356e-16
// mean(f - f_Boost): -5.2735593669694933e-17
// variance(f - f_Boost): 3.0473442641042680e-32
// stddev(f - f_Boost): 1.7456644190978597e-16
const testcase_ellint_2<double>
data008[10] =
{
  { 0.0000000000000000, -0.19999999999999996, 0.0000000000000000, 0.0 },
  { 0.17449769027652809, -0.19999999999999996, 0.17453292519943295, 0.0 },
  { 0.34878893400762090, -0.19999999999999996, 0.34906585039886590, 0.0 },
  { 0.52269152856057410, -0.19999999999999996, 0.52359877559829882, 0.0 },
  { 0.69606913360157574, -0.19999999999999996, 0.69813170079773179, 0.0 },
  { 0.86884782374863379, -0.19999999999999996, 0.87266462599716477, 0.0 },
  { 1.0410255369689567, -0.19999999999999996, 1.0471975511965976, 0.0 },
  { 1.2126730391631364, -0.19999999999999996, 1.2217304763960306, 0.0 },
  { 1.3839259540325151, -0.19999999999999996, 1.3962634015954636, 0.0 },
  { 1.5549685462425293, -0.19999999999999996, 1.5707963267948966, 0.0 },
};
const double toler008 = 2.5000000000000020e-13;

// Test data for k=-0.099999999999999978.
// max(|f - f_Boost|): 4.4408920985006262e-16 at index 8
// max(|f - f_Boost| / |f_Boost|): 3.1875595485348024e-16
// mean(f - f_Boost): -4.7184478546569152e-17
// variance(f - f_Boost): 2.7486111305082032e-34
// stddev(f - f_Boost): 1.6578935823834422e-17
const testcase_ellint_2<double>
data009[10] =
{
  { 0.0000000000000000, -0.099999999999999978, 0.0000000000000000, 0.0 },
  { 0.17452411766649942, -0.099999999999999978, 0.17453292519943295, 0.0 },
  { 0.34899665805442409, -0.099999999999999978, 0.34906585039886590, 0.0 },
  { 0.52337222400508787, -0.099999999999999978, 0.52359877559829882, 0.0 },
  { 0.69761705217284864, -0.099999999999999978, 0.69813170079773179, 0.0 },
  { 0.87171309273007491, -0.099999999999999978, 0.87266462599716477, 0.0 },
  { 1.0456602197056326, -0.099999999999999978, 1.0471975511965976, 0.0 },
  { 1.2194762899272027, -0.099999999999999978, 1.2217304763960306, 0.0 },
  { 1.3931950229892747, -0.099999999999999978, 1.3962634015954636, 0.0 },
  { 1.5668619420216683, -0.099999999999999978, 1.5707963267948966, 0.0 },
};
const double toler009 = 2.5000000000000020e-13;

// Test data for k=0.0000000000000000.
// max(|f - f_Boost|): 2.2204460492503131e-16 at index 7
// max(|f - f_Boost| / |f_Boost|): 2.1203697876423447e-16
// mean(f - f_Boost): -1.9428902930940238e-17
// variance(f - f_Boost): 4.6602749271592373e-35
// stddev(f - f_Boost): 6.8266206333435850e-18
const testcase_ellint_2<double>
data010[10] =
{
  { 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, 0.0 },
  { 0.17453292519943295, 0.0000000000000000, 0.17453292519943295, 0.0 },
  { 0.34906585039886590, 0.0000000000000000, 0.34906585039886590, 0.0 },
  { 0.52359877559829882, 0.0000000000000000, 0.52359877559829882, 0.0 },
  { 0.69813170079773179, 0.0000000000000000, 0.69813170079773179, 0.0 },
  { 0.87266462599716477, 0.0000000000000000, 0.87266462599716477, 0.0 },
  { 1.0471975511965976, 0.0000000000000000, 1.0471975511965976, 0.0 },
  { 1.2217304763960306, 0.0000000000000000, 1.2217304763960306, 0.0 },
  { 1.3962634015954636, 0.0000000000000000, 1.3962634015954636, 0.0 },
  { 1.5707963267948966, 0.0000000000000000, 1.5707963267948966, 0.0 },
};
const double toler010 = 2.5000000000000020e-13;

// Test data for k=0.10000000000000009.
// max(|f - f_Boost|): 4.4408920985006262e-16 at index 8
// max(|f - f_Boost| / |f_Boost|): 3.1875595485348024e-16
// mean(f - f_Boost): -4.7184478546569152e-17
// variance(f - f_Boost): 2.7486111305082032e-34
// stddev(f - f_Boost): 1.6578935823834422e-17
const testcase_ellint_2<double>
data011[10] =
{
  { 0.0000000000000000, 0.10000000000000009, 0.0000000000000000, 0.0 },
  { 0.17452411766649942, 0.10000000000000009, 0.17453292519943295, 0.0 },
  { 0.34899665805442409, 0.10000000000000009, 0.34906585039886590, 0.0 },
  { 0.52337222400508787, 0.10000000000000009, 0.52359877559829882, 0.0 },
  { 0.69761705217284864, 0.10000000000000009, 0.69813170079773179, 0.0 },
  { 0.87171309273007491, 0.10000000000000009, 0.87266462599716477, 0.0 },
  { 1.0456602197056326, 0.10000000000000009, 1.0471975511965976, 0.0 },
  { 1.2194762899272027, 0.10000000000000009, 1.2217304763960306, 0.0 },
  { 1.3931950229892747, 0.10000000000000009, 1.3962634015954636, 0.0 },
  { 1.5668619420216683, 0.10000000000000009, 1.5707963267948966, 0.0 },
};
const double toler011 = 2.5000000000000020e-13;

// Test data for k=0.20000000000000018.
// max(|f - f_Boost|): 4.4408920985006262e-16 at index 6
// max(|f - f_Boost| / |f_Boost|): 4.2658819988515356e-16
// mean(f - f_Boost): -5.2735593669694933e-17
// variance(f - f_Boost): 3.0473442641042680e-32
// stddev(f - f_Boost): 1.7456644190978597e-16
const testcase_ellint_2<double>
data012[10] =
{
  { 0.0000000000000000, 0.20000000000000018, 0.0000000000000000, 0.0 },
  { 0.17449769027652809, 0.20000000000000018, 0.17453292519943295, 0.0 },
  { 0.34878893400762090, 0.20000000000000018, 0.34906585039886590, 0.0 },
  { 0.52269152856057410, 0.20000000000000018, 0.52359877559829882, 0.0 },
  { 0.69606913360157574, 0.20000000000000018, 0.69813170079773179, 0.0 },
  { 0.86884782374863379, 0.20000000000000018, 0.87266462599716477, 0.0 },
  { 1.0410255369689567, 0.20000000000000018, 1.0471975511965976, 0.0 },
  { 1.2126730391631364, 0.20000000000000018, 1.2217304763960306, 0.0 },
  { 1.3839259540325151, 0.20000000000000018, 1.3962634015954636, 0.0 },
  { 1.5549685462425291, 0.20000000000000018, 1.5707963267948966, 0.0 },
};
const double toler012 = 2.5000000000000020e-13;

// Test data for k=0.30000000000000004.
// max(|f - f_Boost|): 6.6613381477509392e-16 at index 9
// max(|f - f_Boost| / |f_Boost|): 4.3401048387253188e-16
// mean(f - f_Boost): 7.2164496600635178e-17
// variance(f - f_Boost): 4.3555500115139682e-32
// stddev(f - f_Boost): 2.0869954507650391e-16
const testcase_ellint_2<double>
data013[10] =
{
  { 0.0000000000000000, 0.30000000000000004, 0.0000000000000000, 0.0 },
  { 0.17445362864048913, 0.30000000000000004, 0.17453292519943295, 0.0 },
  { 0.34844223535713470, 0.30000000000000004, 0.34906585039886590, 0.0 },
  { 0.52155353877411759, 0.30000000000000004, 0.52359877559829882, 0.0 },
  { 0.69347584418369890, 0.30000000000000004, 0.69813170079773179, 0.0 },
  { 0.86403609928237657, 0.30000000000000004, 0.87266462599716477, 0.0 },
  { 1.0332234514065408, 0.30000000000000004, 1.0471975511965976, 0.0 },
  { 1.2011943182068923, 0.30000000000000004, 1.2217304763960306, 0.0 },
  { 1.3682566113689625, 0.30000000000000004, 1.3962634015954636, 0.0 },
  { 1.5348334649232489, 0.30000000000000004, 1.5707963267948966, 0.0 },
};
const double toler013 = 2.5000000000000020e-13;

// Test data for k=0.40000000000000013.
// max(|f - f_Boost|): 1.7763568394002505e-15 at index 9
// max(|f - f_Boost| / |f_Boost|): 1.1795655454506157e-15
// mean(f - f_Boost): 2.0816681711721685e-16
// variance(f - f_Boost): 3.0360740073926687e-31
// stddev(f - f_Boost): 5.5100580826273227e-16
const testcase_ellint_2<double>
data014[10] =
{
  { 0.0000000000000000, 0.40000000000000013, 0.0000000000000000, 0.0 },
  { 0.17439190872481267, 0.40000000000000013, 0.17453292519943295, 0.0 },
  { 0.34795581767099210, 0.40000000000000013, 0.34906585039886590, 0.0 },
  { 0.51995290683804463, 0.40000000000000013, 0.52359877559829882, 0.0 },
  { 0.68981638464431527, 0.40000000000000013, 0.69813170079773179, 0.0 },
  { 0.85722088859936030, 0.40000000000000013, 0.87266462599716477, 0.0 },
  { 1.0221301327876993, 0.40000000000000013, 1.0471975511965976, 0.0 },
  { 1.1848138019818375, 0.40000000000000013, 1.2217304763960306, 0.0 },
  { 1.3458259266501531, 0.40000000000000013, 1.3962634015954636, 0.0 },
  { 1.5059416123600402, 0.40000000000000013, 1.5707963267948966, 0.0 },
};
const double toler014 = 2.5000000000000020e-13;

// Test data for k=0.50000000000000000.
// max(|f - f_Boost|): 4.4408920985006262e-16 at index 7
// max(|f - f_Boost| / |f_Boost|): 3.8178992821201131e-16
// mean(f - f_Boost): -4.9960036108132046e-17
// variance(f - f_Boost): 3.0133908324921077e-32
// stddev(f - f_Boost): 1.7359121039073689e-16
const testcase_ellint_2<double>
data015[10] =
{
  { 0.0000000000000000, 0.50000000000000000, 0.0000000000000000, 0.0 },
  { 0.17431249677315908, 0.50000000000000000, 0.17453292519943295, 0.0 },
  { 0.34732862537770803, 0.50000000000000000, 0.34906585039886590, 0.0 },
  { 0.51788193485993794, 0.50000000000000000, 0.52359877559829882, 0.0 },
  { 0.68506022954164547, 0.50000000000000000, 0.69813170079773179, 0.0 },
  { 0.84831662803347208, 0.50000000000000000, 0.87266462599716477, 0.0 },
  { 1.0075555551444719, 0.50000000000000000, 1.0471975511965976, 0.0 },
  { 1.1631768599287302, 0.50000000000000000, 1.2217304763960306, 0.0 },
  { 1.3160584048772548, 0.50000000000000000, 1.3962634015954636, 0.0 },
  { 1.4674622093394272, 0.50000000000000000, 1.5707963267948966, 0.0 },
};
const double toler015 = 2.5000000000000020e-13;

// Test data for k=0.60000000000000009.
// max(|f - f_Boost|): 4.4408920985006262e-16 at index 7
// max(|f - f_Boost| / |f_Boost|): 3.9101039108874066e-16
// mean(f - f_Boost): 1.9428902930940238e-17
// variance(f - f_Boost): 7.1986981476874020e-33
// stddev(f - f_Boost): 8.4845142157270271e-17
const testcase_ellint_2<double>
data016[10] =
{
  { 0.0000000000000000, 0.60000000000000009, 0.0000000000000000, 0.0 },
  { 0.17421534919599127, 0.60000000000000009, 0.17453292519943295, 0.0 },
  { 0.34655927787174096, 0.60000000000000009, 0.34906585039886590, 0.0 },
  { 0.51533034538432143, 0.60000000000000009, 0.52359877559829882, 0.0 },
  { 0.67916550597453018, 0.60000000000000009, 0.69813170079773179, 0.0 },
  { 0.83720218180349881, 0.60000000000000009, 0.87266462599716477, 0.0 },
  { 0.98922159354937755, 0.60000000000000009, 1.0471975511965976, 0.0 },
  { 1.1357478470419360, 0.60000000000000009, 1.2217304763960306, 0.0 },
  { 1.2780617372844061, 0.60000000000000009, 1.3962634015954636, 0.0 },
  { 1.4180833944487241, 0.60000000000000009, 1.5707963267948966, 0.0 },
};
const double toler016 = 2.5000000000000020e-13;

// Test data for k=0.70000000000000018.
// max(|f - f_Boost|): 4.4408920985006262e-16 at index 6
// max(|f - f_Boost| / |f_Boost|): 4.5937579711009016e-16
// mean(f - f_Boost): 6.1062266354383615e-17
// variance(f - f_Boost): 1.8112301165881739e-32
// stddev(f - f_Boost): 1.3458194962877355e-16
const testcase_ellint_2<double>
data017[10] =
{
  { 0.0000000000000000, 0.70000000000000018, 0.0000000000000000, 0.0 },
  { 0.17410041242702540, 0.70000000000000018, 0.17453292519943295, 0.0 },
  { 0.34564605085764760, 0.70000000000000018, 0.34906585039886590, 0.0 },
  { 0.51228495693314657, 0.70000000000000018, 0.52359877559829882, 0.0 },
  { 0.67207654098799519, 0.70000000000000018, 0.69813170079773179, 0.0 },
  { 0.82370932631556493, 0.70000000000000018, 0.87266462599716477, 0.0 },
  { 0.96672313309452806, 0.70000000000000018, 1.0471975511965976, 0.0 },
  { 1.1017090644949501, 0.70000000000000018, 1.2217304763960306, 0.0 },
  { 1.2304180097292916, 0.70000000000000018, 1.3962634015954636, 0.0 },
  { 1.3556611355719552, 0.70000000000000018, 1.5707963267948966, 0.0 },
};
const double toler017 = 2.5000000000000020e-13;

// Test data for k=0.80000000000000004.
// max(|f - f_Boost|): 1.3322676295501878e-15 at index 9
// max(|f - f_Boost| / |f_Boost|): 1.0438106231598255e-15
// mean(f - f_Boost): 1.8318679906315082e-16
// variance(f - f_Boost): 1.6301071049293564e-31
// stddev(f - f_Boost): 4.0374584888632060e-16
const testcase_ellint_2<double>
data018[10] =
{
  { 0.0000000000000000, 0.80000000000000004, 0.0000000000000000, 0.0 },
  { 0.17396762274534805, 0.80000000000000004, 0.17453292519943295, 0.0 },
  { 0.34458685226969321, 0.80000000000000004, 0.34906585039886590, 0.0 },
  { 0.50872923654502433, 0.80000000000000004, 0.52359877559829882, 0.0 },
  { 0.66372016539176226, 0.80000000000000004, 0.69813170079773179, 0.0 },
  { 0.80760344410167406, 0.80000000000000004, 0.87266462599716477, 0.0 },
  { 0.93945480372495072, 0.80000000000000004, 1.0471975511965976, 0.0 },
  { 1.0597473310395040, 0.80000000000000004, 1.2217304763960306, 0.0 },
  { 1.1706981862452359, 0.80000000000000004, 1.3962634015954636, 0.0 },
  { 1.2763499431699064, 0.80000000000000004, 1.5707963267948966, 0.0 },
};
const double toler018 = 2.5000000000000020e-13;

// Test data for k=0.90000000000000013.
// max(|f - f_Boost|): 6.6613381477509392e-16 at index 7
// max(|f - f_Boost| / |f_Boost|): 6.6116483711056727e-16
// mean(f - f_Boost): 1.3877787807814457e-17
// variance(f - f_Boost): 2.3776912893669577e-35
// stddev(f - f_Boost): 4.8761575952454181e-18
const testcase_ellint_2<double>
data019[10] =
{
  { 0.0000000000000000, 0.90000000000000013, 0.0000000000000000, 0.0 },
  { 0.17381690606167963, 0.90000000000000013, 0.17453292519943295, 0.0 },
  { 0.34337919186972055, 0.90000000000000013, 0.34906585039886590, 0.0 },
  { 0.50464268659856337, 0.90000000000000013, 0.52359877559829882, 0.0 },
  { 0.65400003842368593, 0.90000000000000013, 0.69813170079773179, 0.0 },
  { 0.78854928419904635, 0.90000000000000013, 0.87266462599716477, 0.0 },
  { 0.90645698626315385, 0.90000000000000013, 1.0471975511965976, 0.0 },
  { 1.0075154899135927, 0.90000000000000013, 1.2217304763960306, 0.0 },
  { 1.0940135583194068, 0.90000000000000013, 1.3962634015954636, 0.0 },
  { 1.1716970527816140, 0.90000000000000013, 1.5707963267948966, 0.0 },
};
const double toler019 = 2.5000000000000020e-13;

template<typename Ret, unsigned int Num>
  void
  test(const testcase_ellint_2<Ret> (&data)[Num], Ret toler)
  {
    bool test __attribute__((unused)) = true;
    const Ret eps = std::numeric_limits<Ret>::epsilon();
    Ret max_abs_diff = -Ret(1);
    Ret max_abs_frac = -Ret(1);
    unsigned int num_datum = Num;
    for (unsigned int i = 0; i < num_datum; ++i)
      {
	const Ret f = std::ellint_2(data[i].k, data[i].phi);
	const Ret f0 = data[i].f0;
	const Ret diff = f - f0;
	if (std::abs(diff) > max_abs_diff)
	  max_abs_diff = std::abs(diff);
	if (std::abs(f0) > Ret(10) * eps
	 && std::abs(f) > Ret(10) * eps)
	  {
	    const Ret frac = diff / f0;
	    if (std::abs(frac) > max_abs_frac)
	      max_abs_frac = std::abs(frac);
	  }
      }
    VERIFY(max_abs_frac < toler);
  }

int
main()
{
  test(data001, toler001);
  test(data002, toler002);
  test(data003, toler003);
  test(data004, toler004);
  test(data005, toler005);
  test(data006, toler006);
  test(data007, toler007);
  test(data008, toler008);
  test(data009, toler009);
  test(data010, toler010);
  test(data011, toler011);
  test(data012, toler012);
  test(data013, toler013);
  test(data014, toler014);
  test(data015, toler015);
  test(data016, toler016);
  test(data017, toler017);
  test(data018, toler018);
  test(data019, toler019);
  return 0;
}
