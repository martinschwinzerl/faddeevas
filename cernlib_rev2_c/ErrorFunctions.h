#ifndef FADDEEVAS_CERNLIB_REVISED_C_H__
#define FADDEEVAS_CERNLIB_REVISED_C_H__

#if !defined( CERRF_NO_SYSTEM_INCLUDES )
#if !defined( __cplusplus )
    #include <assert.h>
    #include <stdbool.h>
    #include <stddef.h>
    #include <math.h>
#else /* defined( __cplusplus ) */
    #include <cassert>
    #include <cstddef>
    #include <cmath>
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

#if !defined( CERRF_SQRT_TWO )
    #define CERRF_SQRT_TWO 1.4142135623730950488
#endif /* !defined( CERRF_SQRT_TWO ) */

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

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */


CERRF_STATIC CERRF_FN double power_n( double x, unsigned int n );
CERRF_STATIC CERRF_FN void cerrf_rev2( double x, double y,
    double* __restrict__ out_x, double* __restrict__ out_y );

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE )

CERRF_EXTERN double power_n_ext( double const x, unsigned int const n );

CERRF_EXTERN void cerrf_rev2_ext( double const x, double const y,
    double* __restrict__ out_x, double* __restrict__ out_y );

#endif /* !defined( _GPUCODE ) */

/* ************************************************************************* */

CERRF_INLINE double power_n( double x, unsigned int n )
{
    double x_n = x;

    unsigned int const n_div_16 = n >> 4u;
    unsigned int const n_mod_16 = n - ( n_div_16 << 4u );
    CERRF_ASSERT( n < 128u );
    CERRF_ASSERT( n_div_16 * 16u + n_mod_16 == n );
    CERRF_ASSERT( ( sqrt( x * x ) > ( double )CERRF_DOUBLE_EPS ) || ( n > 0u ) );

    switch( n_mod_16 )
    {
        case  0: { x_n = ( double )1.0; break; }
        case  1: { break; }
        case  2: { x_n *= x;                                       break; }
        case  3: { x_n *= x * x;                                   break; }
        case  4: { x_n *= x;     x_n *= x_n;                       break; }
        case  5: { x_n *= x;     x_n *= x_n * x;                   break; }
        case  6: { x_n *= x * x; x_n *= x_n;                       break; }
        case  7: { x_n *= x * x; x_n *= x_n * x;                   break; }
        case  8: { x_n *= x;     x_n *= x_n;     x_n *= x_n;       break; }
        case  9: { x_n *= x * x; x_n *= x_n * x_n;                 break; }
        case 10: { x_n *= x * x; x_n *= x_n * x_n * x;             break; }
        case 11: { x_n *= x;     x_n *= x_n * x; x_n *= x_n * x;   break; }
        case 12: { x_n *= x * x; x_n *= x_n;     x_n *= x_n;       break; }
        case 13: { x_n *= x * x; x_n *= x_n;     x_n *= x_n * x;   break; }
        case 14: { x_n *= x * x; x_n *= x_n * x; x_n *= x_n;       break; }
        case 15: { x_n *= x;     x_n *= x_n * x; x_n *= x_n * x_n; break; }

        default:
        {
            CERRF_ASSERT( n > 15u );
            x_n = ( double )0.0;
        }
    };

    if( n_div_16 > 0u ) { x *= x; x *= x; x *= x; x *= x; }

    switch( n_div_16 )
    {
        case  0: { x_n  = ( n_mod_16 != 0u ) ? x_n : ( double )1.0; break; }
        case  1: { x_n *= x;                                        break; }
        case  2: { x   *= x; x_n *= x;                              break; }
        case  3: { x_n *= x * x * x;                                break; }
        case  4: { x   *= x; x *= x; x_n *= x;                      break; }
        case  5: { x_n *= x; x *= x; x *= x; x_n *= x;              break; }
        case  6: { x   *= x * x; x *= x; x_n *= x;                  break; }
        case  7: { x_n *= x; x *= x * x; x *= x; x_n *= x;          break; }
        default:
        {
            CERRF_ASSERT( n < 128u );
            CERRF_ASSERT( n > 0u );
            x_n = ( double )0.0;
        }
    };

    return x_n;
}

CERRF_INLINE void cerrf_rev2( double x, double y,
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

    double inv_h2   = ( double )1.0;
    double temp     = y * sign_y;
    double y_plus_h = temp;

    double Rx, Ry, Sx, Sy, Wx, Wy, h2_n, factor;

    int nu = ( int )CERRF_GAUSS_HERMITE_NU;
    int N  = 0;

    bool z_is_in_r0, use_taylor_sum, do_taylor_step;
    CERRF_ASSERT( ( out_x != NULL ) && ( out_y != NULL ) );
    Ry = Sx = Sy = h2_n = ( double )0.0;

    y  = temp;
	x *= sign_x;

    z_is_in_r0 = ( ( y < ( double )CERRF_Y_LIMIT ) &&
                   ( x < ( double )CERRF_X_LIMIT ) );

	if( z_is_in_r0 )
    {
        temp = x / ( double )CERRF_X_LIMIT;
        temp = ( ( double )1.0 - y / ( double )CERRF_Y_LIMIT ) *
               sqrt( ( double )1.0 - temp * temp );


        nu   = ( y > ( double )CERRF_DOUBLE_EPS )
             ? ( int )CERRF_NU_0 + ( int )( ( double )CERRF_NU_1 * temp )
             : ( int )0;

        N    = ( int )CERRF_N0 + ( int )( ( double )CERRF_N1 * temp );
        h2_n = ( double )2.0 * ( double )CERRF_H0 * temp;

        CERRF_ASSERT( h2_n > ( double )CERRF_DOUBLE_EPS );
        inv_h2 = ( double )1.0 / h2_n;
        CERRF_ASSERT( inv_h2 > ( double )CERRF_DOUBLE_EPS );
        y_plus_h += ( double )0.5 * h2_n;
        h2_n = power_n( h2_n, N - 1 );
    }

    Rx = ( y > ( double )CERRF_DOUBLE_EPS )
       ? ( double )0.0
       : exp( -x * x ) / ( double )CERRF_TWO_OVER_SQRT_PI;

    use_taylor_sum = ( z_is_in_r0 ) && ( h2_n > ( double )CERRF_DOUBLE_EPS );

    for( int n = nu ; n > 0 ; n-- )
    {
        Wx     = y_plus_h + n * Rx;
        Wy     = x - n * Ry;
        temp   = Wx * Wx + Wy * Wy;
        Rx     = ( double )0.5 * Wx / temp;
        Ry     = ( double )0.5 * Wy / temp;

        if( ( use_taylor_sum ) && ( n <= N ) )
        {
            temp   = h2_n + Sx;
            h2_n   = h2_n * inv_h2;
            Sx     = Rx * temp - Ry * Sy;
            Sy     = Ry * temp + Rx * Sy;
        }
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

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */
#endif /* FADDEEVAS_CERNLIB_REVISED_C_H__ */
