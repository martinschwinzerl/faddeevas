/////////////////////////////////////////////////////////////////////////////
//
// FILE NAME
//   ErrorFunctions.c
//
//   02/19/2015, 08/18/2015, 05/12/2021
//
// AUTHORS
//   Hannes Bartosik, Adrian Oeftiger
//
// REVISIONS & REVISING AUTHORS
//   rev 1      05/12/2021  by Martin Schwinzerl
//              remove Rx Ry arrays, eliminate branches
//
// DESCRIPTION
//   Error functions
//
/////////////////////////////////////////////////////////////////////////////

#include "ErrorFunctions.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>

void cerrf_rev(
    double x, double y,
    double* restrict out_x, double* restrict out_y )
{
    /**
    this function calculates the double precision complex error function based on the
    algorithm of the FORTRAN function written at CERN by K. Koelbig, Program C335, 1970.

    See also M. Bassetti and G.A. Erskine, "Closed expression for the electric field of a
    two-dimensional Gaussian charge density", CERN-ISR-TH/80-06;
    */

    double const sign_x = ( double )( x >= ( double )0.0 ) -
                          ( double )( x <  ( double )0.0 );

    double const sign_y = ( double )( y >= ( double )0.0 ) -
                          ( double )( y <  ( double )0.0 );

    double Rx, Ry, Sx, Sy, temp, Wx, Wy, xh, xl, yh;
    double factor = ( double )0.0;
    double h = ( double )0.0;

    int nu = 0;
    int N  = 0;

    bool z_is_in_r0 = false;
    bool taylor_sum_enabled = false;
    bool do_taylor_sum_step = false;

    assert( out_x != NULL );
    assert( out_y != NULL );

	x *= sign_x;
    y *= sign_y;

    z_is_in_r0 = ( ( y < ( double )CERRF_Y_LIMIT ) &&
                   ( x < ( double )CERRF_X_LIMIT ) );

	if( z_is_in_r0 )
    {
        temp = x / ( double )CERRF_X_LIMIT;
        double const q = ( ( double )1.0 - y / ( double )CERRF_Y_LIMIT ) *
            sqrt( ( double )1.0 - temp * temp );

        nu = ( y > ( double )CERRF_DOUBLE_EPS )
            ? ( int )CERRF_NU_0 + ( int )( ( double )CERRF_NU_1 * q )
            : ( int )0;

        N  = ( int )CERRF_N0   + ( int )( ( double )CERRF_N1   * q );
        h  = ( double )1.0 / ( ( double )2.0 * ( double )CERRF_H0 * q );
        Sx = Sy = ( double )0.0;

        assert( fabs( h ) > ( double )CERRF_DOUBLE_EPS );
        assert( ( ( double )1.0 / h ) > ( double )CERRF_DOUBLE_EPS );
    }

    Ry = ( double )0.0;
    Rx = ( y > ( double )CERRF_DOUBLE_EPS )
       ? ( double )0.0 : exp( -x * x ) / ( double )CERRF_TWO_OVER_SQRT_PI;

    xl = ( z_is_in_r0 ) ? pow( h, ( double )( 1 - N ) ) : ( double )0.0;
    xh = ( z_is_in_r0 ) ? y + ( double )0.5 / h : y;
    yh = x;

    taylor_sum_enabled = ( z_is_in_r0 ) && ( xl > ( double )CERRF_DOUBLE_EPS );

    for( int n = nu ; n > 0 ; n-- )
    {
        Wx     = xh + n * Rx;
        Wy     = yh - n * Ry;
        temp   = Wx * Wx + Wy * Wy;
        Rx     = ( double )0.5 * Wx / temp;
        Ry     = ( double )0.5 * Wy / temp;

        temp   = xl + Sx;
        do_taylor_sum_step = ( taylor_sum_enabled ) && ( n <= N );
        xl    *= ( do_taylor_sum_step ) ? h : ( double )1.0;

        factor = ( double )( do_taylor_sum_step );
        Sx     = ( factor ) * ( Rx * temp - Ry * Sy );
        Sy     = ( factor ) * ( Ry * temp + Rx * Sy );
    }

    Wx = ( double )CERRF_TWO_OVER_SQRT_PI * ( ( taylor_sum_enabled ) ? Sx : Rx );
    Wy = ( double )CERRF_TWO_OVER_SQRT_PI * ( ( taylor_sum_enabled ) ? Sy : Ry );

    if( sign_y > ( double )0.0 ) /* Quadrants 1 & 2 */
    {
        *out_x = Wx;
        *out_y = sign_x * Wy;
    }
    else  /* Quadrants 3 & 4 */
    {
        factor = ( double )2.0 * exp( y * y - x * x );
        temp = ( double )2.0 * x * y;

        *out_x = factor * cos( temp ) - Wx;
        *out_y = sign_x * factor * sin( temp ) - Wy;
    }
}
