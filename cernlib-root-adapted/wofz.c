// Stefan Hegglin
// 18.02.2016
#include <complex.h>
#include <math.h>
#include "erfc.h"
//#include <tgmath.h>

void wofz (double in_re, double in_im, double* out_re, double* out_im) {
    // wofz = exp(-z^2)*erfc(-i*z), z = in_re + i*in_im = a + i*b
    // two ways: using the math.h exp, sin, cos for real numbers:
    // z^2 = a^2 - b^2 + i*2*a*b
    // exp(-z) = exp(a)*(cos(b) + i*sin(b))
    // or the complex.h cexp(): double complex z = 1 + 2*I;

    // input *(-i): -i*(a+ib) = b-ia
    cerfc(in_im, -in_re, out_re, out_im);
    double complex result_cerf = *out_re + *out_im*I;
    // Multiply by exp(-z*z)
    double complex z = in_re + in_im*I;
    double complex result = cexp(-z*z)*result_cerf;
    *out_re = creal(result);
    *out_im = cimag(result);
}

void wofzf (float in_re, float in_im, float* out_re, float* out_im) {
    cerfcf(in_im, -in_re, out_re, out_im);
    float complex result_cerf = *out_re + *out_im*I;
    // Multiply by exp(-z*z)
    float complex z = in_re + in_im*I;
    float complex result = cexp(-z*z)*result_cerf;
    *out_re = creal(result);
    *out_im = cimag(result);
}
