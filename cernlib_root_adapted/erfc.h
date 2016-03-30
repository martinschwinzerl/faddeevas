#ifndef ERFC_H
#define ERFC_H

// Translated from C++ to C for SixTrack and MAD-X
// Author: Laurent Deniau, BE/ABP, laurent.deniau@cern.ch
// Date  : 2016.01.13

// interface of complex erf and erfc, faddeeva function

// single precision
void cerff (float in_re, float in_im, float* out_re, float* out_im);
void cerfcf(float in_re, float in_im, float* out_re, float* out_im);
void wofzf (float in_re, float in_im, float* out_re, float* out_im);

// double precision
void cerf (double in_re, double in_im, double* out_re, double* out_im);
void cerfc(double in_re, double in_im, double* out_re, double* out_im);
void wofz (double in_re, double in_im, double* out_re, double* out_im);

#endif // ERFC_H
