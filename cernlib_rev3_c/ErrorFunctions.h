#ifndef FADDEEVAS_CERNLIB_REV3__C_H__
#define FADDEEVAS_CERNLIB_REV3__C_H__

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

#if !defined( CERRF_NO_INCLUDES )
    #include "common/definitions.h"
    #include "common/helper_functions.h"
    #include "cernlib_rev2_c/definitions.h"
#endif /* !defined( CERRF_NO_INCLUDES ) */

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */


CERRF_STATIC CERRF_FN void cerrf_rev3(
    CERRF_REAL_TYPE x, CERRF_REAL_TYPE y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT;

CERRF_STATIC CERRF_FN int wofz_cernlib_rev3(
    CERRF_REAL_TYPE x, CERRF_REAL_TYPE y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT;

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE )

CERRF_EXTERN void cerrf_rev3_ext(
    CERRF_REAL_TYPE const x, CERRF_REAL_TYPE const y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

/* ************************************************************************* */

CERRF_INLINE void cerrf_rev3( CERRF_REAL_TYPE x, CERRF_REAL_TYPE y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT
{
    typedef CERRF_REAL_TYPE real_type;

    /**
    this function calculates the real_type precision complex error function based on the
    algorithm of the FORTRAN function written at CERN by K. Koelbig, Program C335, 1970.

    See also M. Bassetti and G.A. Erskine, "Closed expression for the electric field of a
    two-dimensional Gaussian charge density", CERN-ISR-TH/80-06;
    */

    real_type const sign_x = ( real_type )( x >= ( real_type )0.0 ) -
                             ( real_type )( x <  ( real_type )0.0 );

    real_type const sign_y = ( real_type )( y >= ( real_type )0.0 ) -
                             ( real_type )( y <  ( real_type )0.0 );

    real_type inv_h2   = ( real_type )1.0;
    real_type temp     = y * sign_y;
    real_type y_plus_h = temp;

    real_type Rx, Ry, Sx, Sy, Wx, Wy, inv_Wsqu, h2_n;

    int nu = ( int )CERRF_GAUSS_HERMITE_NU;
    int n  = 0;
    int N  = 0;

    bool z_is_in_r0, use_taylor_sum;
    CERRF_ASSERT( ( out_x != NULL ) && ( out_y != NULL ) );
    Ry = Sx = Sy = h2_n = ( real_type )0.0;

    y  = temp;
	x *= sign_x;

    z_is_in_r0 = ( ( y < ( real_type )CERRF_Y_LIMIT ) &&
                   ( x < ( real_type )CERRF_X_LIMIT ) );

    if( z_is_in_r0 )
    {
        temp = x / ( real_type )CERRF_X_LIMIT;
        temp = ( ( real_type )1.0 - y / ( real_type )CERRF_Y_LIMIT ) *
               sqrt( ( real_type )1.0 - temp * temp );

        nu   = ( y > ( real_type )CERRF_REAL_EPS )
             ? ( int )CERRF_NU_0 + ( int )( ( real_type )CERRF_NU_1 * temp )
             : ( int )0;

        N    = ( int )CERRF_N0 + ( int )( ( real_type )CERRF_N1 * temp );
        h2_n = ( real_type )CERRF_H0 * temp;
        y_plus_h += h2_n;
        h2_n *= ( real_type )2.0;

        CERRF_ASSERT( h2_n > ( real_type )CERRF_REAL_EPS );
        inv_h2 = ( real_type )1.0 / h2_n;
        CERRF_ASSERT( inv_h2 > ( real_type )CERRF_REAL_EPS );
        h2_n = power_n( h2_n, N - 1 );
    }

    Rx = ( y > ( real_type )CERRF_REAL_EPS )
       ? ( real_type )0.0
       : exp( -x * x ) / ( real_type )CERRF_TWO_OVER_SQRT_PI;

    use_taylor_sum = ( z_is_in_r0 ) && ( h2_n > ( real_type )CERRF_REAL_EPS );
    n = nu;

    for( ; n > N ; --n )
    {
        Wx       = y_plus_h + ( real_type )n * Rx;
        temp     = Wx * Wx;
        Wy       = x - ( real_type )n * Ry;
        temp    += Wy * Wy;
        inv_Wsqu = ( real_type )0.5 / temp;
        Rx       = Wx * inv_Wsqu;
        Ry       = Wy * inv_Wsqu;
    }

    #if !defined( _GPUCODE )
    if( !use_taylor_sum )
    {
        Wx = ( real_type )CERRF_TWO_OVER_SQRT_PI * Sx;
        Wy = ( real_type )CERRF_TWO_OVER_SQRT_PI * Sy;
    }
    else
    #else
    if( use_taylor_sum )
    #endif
    {
        for( ; n > 0 ; --n )
        {
            Wx       = y_plus_h + ( real_type )n * Rx;
            temp     = Wx * Wx;
            Wy       = x - ( real_type )n * Ry;
            temp    += Wy * Wy;
            inv_Wsqu = ( real_type )0.5 / temp;
            Rx       = Wx * inv_Wsqu;
            Ry       = Wy * inv_Wsqu;

            temp   = h2_n + Sx;
            h2_n  *= inv_h2;
            Sx     = Rx * temp - Ry * Sy;
            Sy     = Ry * temp + Rx * Sy;
        }

        Wx = ( real_type )CERRF_TWO_OVER_SQRT_PI * Sx;
        Wy = ( real_type )CERRF_TWO_OVER_SQRT_PI * Sy;
    }

    if( sign_y < ( real_type )0.0 )  /* Quadrants 3 & 4 */
    {
        real_type const factor = ( real_type )2.0 * exp( y * y - x * x );
        temp = ( real_type )2.0 * x * y;

        Wx = factor * cos( temp ) - Wx;
        Wy = factor * sin( temp ) + Wy;
    }

    *out_x = Wx;
    *out_y = sign_x * Wy;
}

CERRF_INLINE int wofz_cernlib_rev2(
    CERRF_REAL_TYPE x, CERRF_REAL_TYPE y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT
{
    cerrf_rev3( x, y, out_x, out_y );
    return 0;
}

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */
#endif /* FADDEEVAS_CERNLIB_REV3__C_H__ */
