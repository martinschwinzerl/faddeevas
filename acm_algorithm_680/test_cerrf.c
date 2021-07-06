#include <assert.h>
#include <stdbool.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "ErrorFunctions.h"

int main()
{
    double x = ( double )3.0;
    double y = ( double )3.9;

    double out_x = ( double )0.0;
    double out_y = ( double )0.0;

    wofz_alg680( x, y, &out_x, &out_y );
	printf( "in: wofz_alg680( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );

    x = -x;
    wofz_alg680( x, y, &out_x, &out_y );
	printf( "in: wofz_alg680( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );

    y = -y;
    wofz_alg680( x, y, &out_x, &out_y );
	printf( "in: wofz_alg680( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );

    x = -x;
    wofz_alg680( x, y, &out_x, &out_y );
	printf( "in: wofz_alg680( %+f + i * %+f ) = %+30.18f %+30.18f * i\r\n",
               x, y, out_x, out_y );

	fflush( stdout );
	return 0;
}

