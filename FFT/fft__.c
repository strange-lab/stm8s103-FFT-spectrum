//************************************************************************
//  fft.c
//
//  FFT Audio Analysis
//  Copyright (C) 2011 Simon Inns
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
//  Email: simon.inns@gmail.com
//
//************************************************************************

#ifndef FFT_C
#define FFT_C
 
/*0..180*/
#include "fft__.h"
#ifndef N_SAMPLE
#define N_SAMPLE        32 /* Number of samples (64,128,256,512). Don't forget to clean! */
#define N               4
#endif

#if N_SAMPLE == 32
const u16 ham[N_SAMPLE] = {
 1144,  7561, 13905, 20115, 26132, 31897, 37355, 42453,  
47142, 51377, 55117, 58327, 60975, 63036, 64489, 65322,  
65525, 65097, 64043, 62372, 60100, 57249, 53847, 49926,  
45524, 40685, 35453, 29880, 24019, 17926, 11662, 5284  };

const u8 position[N_SAMPLE] = {
 0, 16,  8, 24, 4, 20, 12, 28, 2, 18, 10, 26, 6, 22, 14, 30, 
 1, 17,  9, 25, 5, 21, 13, 29, 3, 19, 11, 27, 7, 23, 15, 31 };

const s16 COS[N_SAMPLE/2] = { 
32767, 32130,  30245,  27185,  23068,  18056,  12341, 6147,  
 -286, -6708, -12869, -18530, -23471, -27500, -30461, -32238 };

const s16  SIN[N_SAMPLE/2] = { 
    0,  6428, 12605, 18293, 23271, 27344, 30354, 32185,  
32766, 32073, 30134, 27024, 22864, 17816, 12076, 5866 };

#elif N_SAMPLE == 64
const u16 ham[N_SAMPLE] = {
 1144,  4358,  7561, 10746, 13905, 17031, 20115, 23152,  
26132, 29049, 31897, 34668, 37355, 39952, 42453, 44851,  
47142, 49319, 51377, 53312, 55117, 56791, 58327, 59723,  
60975, 62080, 63036, 63839, 64489, 64984, 65322, 65502,  
65525, 65390, 65097, 64648, 64043, 63283, 62372, 61309,  
60100, 58745, 57249, 55615, 53847, 51949, 49926, 47783,  
45524, 43156, 40685, 38115, 35453, 32706, 29880, 26982,  
24019, 20998, 17926, 14812, 11662,  8483,  5284, 2073 };

const u8 position[N_SAMPLE] = {
 0,32,16,48, 8,40,24,56,4,36,20,52,12,44,28,60, 
 2,34,18,50,10,42,26,58,6,38,22,54,14,46,30,62, 
 1,33,17,49, 9,41,25,57,5,37,21,53,13,45,29,61, 
 3,35,19,51,11,43,27,59,7,39,23,55,15,47,31,63 };

const s16 COS[N_SAMPLE/2] = { 
 32767,  32607,  32130,  31340,  30245,  28856,  27185,  25250,  
 23068,  20663,  18056,  15273,  12341,   9289,   6147,   2945,  
  -286,  -3514,  -6708,  -9836, -12869, -15776, -18530, -21103,  
-23471, -25610, -27500, -29122, -30461, -31503, -32238, -32659 };

const s16  SIN[N_SAMPLE/2] = { 
    0,  3230,  6428,  9563, 12605, 15525, 18293, 20884,  
23271, 25431, 27344, 28990, 30354, 31423, 32185, 32634,  
32766, 32578, 32073, 31256, 30134, 28719, 27024, 25066,  
22864, 20440, 17816, 15019, 12076,  9015,  5866, 2660 };

#elif N_SAMPLE == 128

const u16 ham[N_SAMPLE] = {
1144,   2739,  4333,  5924,  7511,  9094, 10672, 12243,  
13808, 15363, 16910, 18447, 19973, 21487, 22988, 24476,  
25949, 27407, 28848, 30272, 31679, 33067, 34435, 35782,  
37108, 38413, 39694, 40952, 42186, 43395, 44578, 45734,  
46864, 47966, 49039, 50083, 51097, 52081, 53035, 53956,  
54846, 55703, 56528, 57318, 58075, 58797, 59485, 60137,  
60753, 61333, 61877, 62385, 62855, 63288, 63684, 64041,  
64361, 64643, 64886, 65091, 65257, 65385, 65473, 65523,  
65534, 65506, 65440, 65334, 65190, 65007, 64785, 64525,  
64227, 63891, 63517, 63105, 62656, 62169, 61646, 61086,  
60490, 59858, 59191, 58488, 57751, 56980, 56174, 55336,  
54464, 53561, 52625, 51659, 50661, 49634, 48577, 47492,  
46378, 45237, 44068, 42874, 41655, 40410, 39142, 37850,  
36536, 35201, 33844, 32468, 31072, 29657, 28226, 26777,  
25312, 23833, 22339, 20832, 19313, 17782, 16241, 14690,  
13131, 11563,  9989,  8409,  6824,  5235,  3642,  2048 };

const u8 position[N_SAMPLE] = {
0, 64, 32,  96, 16, 80, 48, 112,  8, 72, 40, 104, 24, 88 , 56 , 120 ,
4, 68, 36, 100, 20, 84, 52, 116, 12, 76, 44, 108, 28, 92 , 60 , 124 ,
2, 66, 34,  98, 18, 82, 50, 114, 10, 74, 42, 106, 26, 90 , 58 , 122 ,
6, 70, 38, 102, 22, 86, 54, 118, 14, 78, 46, 110, 30, 94 , 62 , 126 ,
1, 65, 33,  97, 17, 81, 49, 113,  9, 73, 41, 105, 25, 89 , 57 , 121 ,
5, 69, 37, 101, 21, 85, 53, 117, 13, 77, 45, 109, 29, 93 , 61 , 125 ,
3, 67, 35,  99, 19, 83, 51, 115, 11, 75, 43, 107, 27, 91 , 59 , 123 ,
7, 71, 39, 103, 23, 87, 55, 119, 15, 79, 47, 111, 31, 95 , 63 , 127 };

const s16 COS[N_SAMPLE/2] = { 
 32767,  32727,  32607,  32408,  32130,  31774,  31340,  30830,  
 30245,  29587,  28856,  28055,  27185,  26249,  25250,  24189,  
 23068,  21892,  20663,  19383,  18056,  16684,  15273,  13824,  
 12341,  10828,   9289,   7727,   6147,   4551,   2945,   1331,  
  -286,  -1902,  -3514,  -5117,  -6708,  -8282,  -9836, -11366,  
-12869, -14340, -15776, -17174, -18530, -19841, -21103, -22314,  
-23471, -24571, -25610, -26588, -27500, -28346, -29122, -29828,  
-30461, -31019, -31503, -31909, -32238, -32488, -32659, -32750 };

const s16 SIN[N_SAMPLE/2]= { 
    0,  1617,  3230,  4834,  6428,  8005,  9563, 11098,  
12605, 14082, 15525, 16930, 18293, 19612, 20884, 22104,  
23271, 24380, 25431, 26419, 27344, 28201, 28990, 29708,  
30354, 30926, 31423, 31843, 32185, 32449, 32634, 32740,  
32766, 32712, 32578, 32365, 32073, 31703, 31256, 30732,  
30134, 29463, 28719, 27906, 27024, 26077, 25066, 23995,  
22864, 21679, 20440, 19151, 17816, 16438, 15019, 13564,  
12076, 10558,  9015,  7449,  5866,  4268,  2660,  1045 };

#endif/***/

//----------------------------------------------------
s32 FIX_MPY     (s16 a, s16 b);
s32 FIX         (s16 a, u16 b);
u16 sqrt16      (u32 x);
//----------------------------------------------------
s32 FIX_MPY(s16 a, s16 b)
{
  s32  c  = a;
  c *= b;
  return (c>>15);
}
//----------------------------------------------------
s32 FIX(s16 a,u16 b)
{
  s32 c  = a;
  c *= b;
  return (c>>16);
}
//----------------------------------------------------
/*
  fix_fft() - perform forward fast Fourier transform.
  fr[n],fi[n] are real and imaginary arrays, both INPUT AND
  RESULT (in-place FFT), with 0 <= n < 2**m
*/
void fix_fft(s16 *inp, complex_t *compl )
{
  char  i = 0, j, l = 1, k = N, istep, m;
  short tr, ti, wr, wi, qr, qi;
   
//prepare the complex array:  add img part and recomb numbers
//  while( i < N_SAMPLE) 
//  {
//    compl[position[i]].real = FIX(*inp++,ham[i]);
//    compl[i].image = 0;
//    i++;
//  }
  
  while (l < N_SAMPLE)
  {   
    istep = l << 1;
    for (m = 0; m < l; ++m)
    {
      j = m << k;
      // 0 <= j < N_WAVE/2 
      
      wr = COS[j];
      wi = SIN[j];
           
      for (i = m; i < N_SAMPLE; i += istep)
      {
        j = i + l;       
        tr = compl[j].real;
        if(m)
        { 
          ti = FIX_MPY(wi,tr); 
          tr = FIX_MPY(wr,tr);
          
          if (compl[j].image)
          {                       
            tr  -= FIX_MPY(wi,compl[j].image);
            ti  += FIX_MPY(wr,compl[j].image);                                            
          }
          qi = compl[i].image;
          
          compl[j].image = qi - ti;
          compl[i].image = qi + ti;         
        }       
        qr = compl[i].real;
        compl[j].real = qr - tr;
        compl[i].real = qr + tr;        
      }      
    }    
    --k;
    l = istep;
  }
}

//----------------------------------------------------

void fft_out(complex_t *compl, s16 *out )
{
  char k;
  s32 temp; 
  s32 place;
  
  for (k=0; k < (N_SAMPLE/2); k++)
  {
    temp  = compl[k].real;
    temp *= temp;
    place = compl[k].image;
    //  compl++;
    place *= place;
    temp  += place; 
    //temp = (realNumbers[k] * realNumbers[k] + imaginaryNumbers[k] * imaginaryNumbers[k]);  
    out[k] = sqrt16(temp);
  }
}
#endif 


//------------------------------------------------------------------------
// Fast square root in C from IAR AN-G002 appnote
// this code does little bit error in result with high numbers operations
// but it doesn't matter for this project
//------------------------------------------------------------------------
u16 sqrt16(u32 x)
{
   u32 a,b;
   b = x;
   a = x = 0x3f;
   x = b/x;
   a = x = (x+a)>>1;
   x = b/x;
   a = x = (x+a)>>1;
   x = b/x;
   x = (x+a)>>1;
   return(x);
}
