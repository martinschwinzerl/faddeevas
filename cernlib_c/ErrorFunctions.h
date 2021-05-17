#ifndef FADDEEVAS_CERNLIB_C_H__
#define FADDEEVAS_CERNLIB_C_H__

#if !defined( CERRF_NO_SYSTEM_INCLUDES )
#if !defined( __cplusplus )
    #include <stdbool.h>
    #include <stdlib.h>
#else
    #include <cstdlib>
#endif /* C++ */
#endif /* !defined( CERRF_NO_SYSTEM_INCLUDES ) */

#if !defined( CERRF_STATIC )
    #if !defined( _GPUCODE )
        #define CERRF_STATIC static
    #else  /* !defined( _GPUCODE ) */
        #define CERRF_STATIC
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( CERRF_STATIC ) */

#if !defined( CERRF_EXTERN )
    #if !defined( _GPUCODE )
        #define CERRF_EXTERN extern
    #else /* !defined( _GPUCODE ) */
        #define CERRF_EXTERN
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( CERRF_EXTERN ) */

#if !defined( CERRF_FN )
    #define CERRF_FN
#endif /* !defined( CERRF_FN ) */

#if !defined( CERRF_INLINE )
    #define CERRF_INLINE inline
#endif /* !defined( CERRF_INLINE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* C++ */

CERRF_STATIC CERRF_FN void cerrf( double in_real, double in_imag,
    double* out_real, double* out_imag );


CERRF_INLINE void cerrf( double in_real, double in_imag,
    double* out_real, double* out_imag )
{
	/**
	this function calculates the double precision complex error function based on the
	algorithm of the FORTRAN function written at CERN by K. Koelbig, Program C335, 1970.

	See also M. Bassetti and G.A. Erskine, "Closed expression for the electric field of a
	two-dimensional Gaussian charge density", CERN-ISR-TH/80-06;
	*/

	int n, nc, nu;
	double const cfactor = ( double )1.12837916709551;
	double const xLim = 5.33;
	double const yLim = 4.29;

    double h, q, Saux, Sx, Sy, Tn, Tx, Ty, Wx, Wy, xh, xl, x, yh, y;
	double Rx [33];
	double Ry [33];


	x = fabs(in_real);
	y = fabs(in_imag);

	if (y < yLim && x < xLim){
		q = (1.0 - y / yLim) * sqrt(1.0 - (x / xLim) * (x / xLim));
		h  = 1.0 / (3.2 * q);
		nc = 7 + (int) (23.0 * q);
		xl = pow(h, (double) (1 - nc));
		xh = y + 0.5 / h;
		yh = x;
		nu = 10 + (int) (21.0 * q);
		Rx[nu] = 0.;
		Ry[nu] = 0.;
		for (n = nu; n > 0; n--){
			Tx = xh + n * Rx[n];
			Ty = yh - n * Ry[n];
			Tn = Tx*Tx + Ty*Ty;
			Rx[n-1] = 0.5 * Tx / Tn;
			Ry[n-1] = 0.5 * Ty / Tn;
			}
		Sx = 0.;
		Sy = 0.;
		for (n = nc; n>0; n--){
			Saux = Sx + xl;
			Sx = Rx[n-1] * Saux - Ry[n-1] * Sy;
			Sy = Rx[n-1] * Sy + Ry[n-1] * Saux;
			xl = h * xl;
		};
		Wx = cfactor * Sx;
		Wy = cfactor * Sy;
	}
	else{
		xh = y;
		yh = x;
		Rx[0] = 0.;
		Ry[0] = 0.;
		for (n = 9; n>0; n--){
			Tx = xh + n * Rx[0];
			Ty = yh - n * Ry[0];
			Tn = Tx * Tx + Ty * Ty;
			Rx[0] = 0.5 * Tx / Tn;
			Ry[0] = 0.5 * Ty / Tn;
		};
		Wx = cfactor * Rx[0];
		Wy = cfactor * Ry[0];
	}
	if (y == 0.) {Wx = exp(-x * x);}
	if (in_imag < 0.){
		Wx =   2.0 * exp(y * y - x * x) * cos(2.0 * x * y) - Wx;
		Wy = - 2.0 * exp(y * y - x * x) * sin(2.0 * x * y) - Wy;
		if (in_real > 0.) {Wy = -Wy;}
	}
	else if (in_real < 0.) {Wy = -Wy;}

	*out_real = Wx;
	*out_imag = Wy;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* C++ */
#endif /* FADDEEVAS_CERNLIB_C_H__ */
