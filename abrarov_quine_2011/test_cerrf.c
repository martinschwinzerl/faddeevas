#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "coefficients.h"
#include "ErrorFunctions.h"

int main()
{
    double x = ( double )CERRF_PI / ( double )CERRF_TM;
    double y = ( double )1e-3;

    double out_x = ( double )0.0;
    double out_y = ( double )0.0;

    wofz_abrarov_quine( x, y, &out_x, &out_y,
                        &CERRF_FOURIER_COEFF[ 0 ],
                        &CERRF_TAYLOR_COEFF[ 0 ] );
	printf( "in: wofz_abrarov_quine( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );

    x = ( double )CERRF_PI / ( double )CERRF_TM;
    y = ( double )sqrt( 2.0 ) * 1e-3;

    out_x = ( double )0.0;
    out_y = ( double )0.0;

    wofz_abrarov_quine( x, y, &out_x, &out_y,
                        &CERRF_FOURIER_COEFF[ 0 ],
                        &CERRF_TAYLOR_COEFF[ 0 ] );
	printf( "in: wofz_abrarov_quine( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );

    x = ( double )1.0;
    y = ( double )1.0;

    out_x = ( double )0.0;
    out_y = ( double )0.0;

    wofz_abrarov_quine( x, y, &out_x, &out_y,
                        &CERRF_FOURIER_COEFF[ 0 ],
                        &CERRF_TAYLOR_COEFF[ 0 ] );
	printf( "in: wofz_abrarov_quine( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );

/*
    x = -x;
    cerrf_abrarov_quine( x, y, &out_x, &out_y );
	printf( "in: cerrf_alg680( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );

    y = -y;
    cerrf_abrarov_quine( x, y, &out_x, &out_y );
	printf( "in: cerrf_alg680( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );

    x = -x;
    cerrf_abrarov_quine( x, y, &out_x, &out_y );
	printf( "in: cerrf_alg680( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );
*/

	fflush( stdout );
	return 0;
}

