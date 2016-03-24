// Author: Laurent Deniau, BE/ABP, laurent.deniau@cern.ch
// Date  : 2016.01.13

// small tests of complex erf and erfc:
// void cerf  (T in_re, T in_im, T* out_re, T* out_im);
// void cerfc (T in_re, T in_im, T* out_re, T* out_im);
// void cerff (T in_re, T in_im, T* out_re, T* out_im);
// void cerfcf(T in_re, T in_im, T* out_re, T* out_im);

// compilation as test program:
// gcc -std=c99 -W -Wall -Wextra -pedantic -O3 -ffast-math -ftree-vectorize -flto erfc.c erfc_main.c -o erfc

// compilation options:
// - fast   implementation: -DFAST_IMPL
// - sincos implementation: -std=gnu99 -DSINCOS

#include <stdio.h>
#include <time.h>
#include "erfc.h"

int main(void)
{
  const int n = 50000000;

  {
	float re, im, rer, imr;

	re =  0.5, im = 0.5;
	cerff(re, im, &rer, &imr);
	printf("cerf (%21.14e,%21.14e) = (%21.14e, %21.14e)\n", re, im, rer, imr);
	cerfcf(re, im, &rer, &imr);
	printf("cerfc(%21.14e,%21.14e) = (%21.14e, %21.14e)\n", re, im, rer, imr);

	re = -0.5, im = 0.5;
	cerff(re, im, &rer, &imr);
	printf("cerf (%21.14e,%21.14e) = (%21.14e, %21.14e)\n", re, im, rer, imr);
	cerfcf(re, im, &rer, &imr);
	printf("cerfc(%21.14e,%21.14e) = (%21.14e, %21.14e)\n", re, im, rer, imr);

	double t0 = clock();
	for (int i=0; i < n; i++) cerff(re, im, &rer, &imr);
	double t1 = clock();
	printf("cerff: %.3f Mcalls/sec\n", n/((t1-t0)/CLOCKS_PER_SEC)/1000000);
  }
  {
	double re, im, rer, imr;

	re =  0.5, im = 0.5;
	cerf(re, im, &rer, &imr);
	printf("cerf (%21.14e,%21.14e) = (%21.14e, %21.14e)\n", re, im, rer, imr);
	cerfc(re, im, &rer, &imr);
	printf("cerfc(%21.14e,%21.14e) = (%21.14e, %21.14e)\n", re, im, rer, imr);

	re = -0.5, im = 0.5;
	cerf(re, im, &rer, &imr);
	printf("cerf (%21.14e,%21.14e) = (%21.14e, %21.14e)\n", re, im, rer, imr);
	cerfc(re, im, &rer, &imr);
	printf("cerfc(%21.14e,%21.14e) = (%21.14e, %21.14e)\n", re, im, rer, imr);

	double t0 = clock();
	for (int i=0; i < n; i++) cerf(re, im, &rer, &imr);
	double t1 = clock();
	printf("cerf: %.3f Mcalls/sec\n", n/((t1-t0)/CLOCKS_PER_SEC)/1000000);
  }
}
