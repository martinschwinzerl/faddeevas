#ifndef FADDEEVAS_CERNLIB_REVISED_C_H__
#define FADDEEVAS_CERNLIB_REVISED_C_H__

#if !defined( CERRF_NO_SYSTEM_INCLUDES )
#if !defined( __cplusplus )
    #include <assert.h>
    #include <math.h>
    #include <stdbool.h>
    #include <stddef.h>
#else /* defined( __cplusplus ) */
    #include <cassert>
    #include <cmath>
    #include <cstddef>
#endif /* !defined( __cplusplus ) */
#endif /* !defined( CERRF_NO_SYSTEM_INCLUDES ) */

#if !defined( CERRF_STATIC )
    #if !defined( _GPUCODE )
        #define CERRF_STATIC static
    #else /* !defined( _GPUCODE ) */
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

#if !defined( CERRF_ASSERT )
    #if !defined( _GPUCODE )
        #define CERRF_ASSERT( cond ) assert( ( cond ) )
    #else /* !defined( _GPUCODE ) */
        #define CERRF_ASSERT( cond )
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( CERRF_ASSERT ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( CERRF_TWO_OVER_SQRT_PI )
    #define CERRF_TWO_OVER_SQRT_PI 1.1283791670955125739
#endif /* !defined( CERRF_TWO_OVER_SQRT_PI ) */

#if !defined( CERRF_X_LIMIT )
    #define CERRF_X_LIMIT 5.33
#endif /* !defined( CERRF_X_LIMIT ) */

#if !defined( CERRF_Y_LIMIT )
    #define CERRF_Y_LIMIT 4.29
#endif /* !defined( CERRF_Y_LIMIT ) */

#if !defined( CERRF_H0 )
    #define CERRF_H0 1.6
#endif /* !defined( CERRF_H0 ) */

#if !defined( CERRF_NU_0 )
    #define CERRF_NU_0 10
#endif /* !defined( CERRF_NU_0 ) */

#if !defined( CERRF_N0 )
    #define CERRF_N0 7
#endif /* !defined( CERRF_N0 ) */

#if !defined( CERRF_NU_1 )
    #define CERRF_NU_1 21
#endif /* !defined( CERRF_NU_1 ) */

#if !defined( CERRF_N1 )
    #define CERRF_N1 23
#endif /* !defined( CERRF_N1 ) */

#if !defined( CERRF_GAUSS_HERMITE_NU )
    #define CERRF_GAUSS_HERMITE_NU 9
#endif /* !defined( CERRF_GAUSS_HERMITE_NU ) */

#if !defined( CERRF_DOUBLE_EPS )
    #define  CERRF_DOUBLE_EPS 2.22e-16
#endif /* !defined( CERRF_DOUBLE_EPS ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

CERRF_STATIC CERRF_FN void cerrf_rev( double x, double y,
    double* __restrict__ out_x, double* __restrict__ out_y );

#if !defined( _GPUCODE )

CERRF_EXTERN CERRF_FN void cerrf_rev_ext( double x, double y,
    double* __restrict__ out_x, double* __restrict__ out_y );

#endif /* !defined( _GPUCODE ) */

/* ************************************************************************* */

CERRF_INLINE void cerrf_rev( double x, double y,
    double* __restrict__ out_x, double* __restrict__ out_y )
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

    int nu = ( int )CERRF_GAUSS_HERMITE_NU;
    int N  = 0;

    bool z_is_in_r0 = false;
    bool use_taylor_sum = false;
    bool do_taylor_sum_step = false;

    CERRF_ASSERT( out_x != NULL );
    CERRF_ASSERT( out_y != NULL );

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

        CERRF_ASSERT( fabs( h ) > ( double )CERRF_DOUBLE_EPS );
        CERRF_ASSERT( ( ( double )1.0 / h ) > ( double )CERRF_DOUBLE_EPS );
    }

    Ry = ( double )0.0;
    Rx = ( y > ( double )CERRF_DOUBLE_EPS )
       ? ( double )0.0 : exp( -x * x ) / ( double )CERRF_TWO_OVER_SQRT_PI;

    xl = ( z_is_in_r0 ) ? pow( h, ( double )( 1 - N ) ) : ( double )0.0;
    xh = ( z_is_in_r0 ) ? y + ( double )0.5 / h : y;
    yh = x;

    use_taylor_sum = ( z_is_in_r0 ) && ( xl > ( double )CERRF_DOUBLE_EPS );

    for( int n = nu ; n > 0 ; n-- )
    {
        Wx     = xh + n * Rx;
        Wy     = yh - n * Ry;
        temp   = Wx * Wx + Wy * Wy;
        Rx     = ( double )0.5 * Wx / temp;
        Ry     = ( double )0.5 * Wy / temp;

        temp   = xl + Sx;
        do_taylor_sum_step = ( use_taylor_sum ) && ( n <= N );
        xl    *= ( do_taylor_sum_step ) ? h : ( double )1.0;

        factor = ( double )( do_taylor_sum_step );
        Sx     = ( factor ) * ( Rx * temp - Ry * Sy );
        Sy     = ( factor ) * ( Ry * temp + Rx * Sy );
    }

    /* Wx, Wy ... result for z|Q1 = |x| + i |y| ... in first quadrant! */
    Wx = ( double )CERRF_TWO_OVER_SQRT_PI * ( ( use_taylor_sum ) ? Sx : Rx );
    Wy = ( double )CERRF_TWO_OVER_SQRT_PI * ( ( use_taylor_sum ) ? Sy : Ry );

    if( sign_y < ( double )0.0 )  /* Quadrants 3 & 4 */
    {
        factor = ( double )2.0 * exp( y * y - x * x );
        temp = ( double )2.0 * x * y;

        Wx = factor * cos( temp ) - Wx;
        Wy = factor * sin( temp ) + Wy;
    }

    *out_x = Wx;
    *out_y = sign_x * Wy;
}


#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* FADDEEVAS_CERNLIB_REVISED_C_H__ */
