#ifndef FADDEEVAS_CERNLIB_REV4_C_H__
#define FADDEEVAS_CERNLIB_REV4_C_H__

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
    #include "cernlib_rev4_c/definitions.h"
#endif /* !defined( CERRF_NO_INCLUDES ) */

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */


CERRF_STATIC CERRF_FN void cerrf_rev4(
    CERRF_REAL_TYPE x, CERRF_REAL_TYPE y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT;

CERRF_STATIC CERRF_FN int wofz_cernlib_rev4(
    CERRF_REAL_TYPE x, CERRF_REAL_TYPE y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT;

/* ------------------------------------------------------------------------- */

#if !defined( _GPUCODE )

CERRF_EXTERN void cerrf_rev4_ext(
    CERRF_REAL_TYPE const x, CERRF_REAL_TYPE const y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

/* ************************************************************************* */

void cerrf_rev4( CERRF_REAL_TYPE x, CERRF_REAL_TYPE y,
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

    real_type Rx, Ry, Sx, Sy, Wx, Wy, h2_n;

    int nu = ( int )CERRF_GAUSS_HERMITE_NU;
    int N  = 0;
    bool use_taylor_sum = false;

    #if defined( __cplusplus )
    using std::sqrt;
    using std::floor;
    using std::exp;
    using std::cos;
    using std::sin;
    #endif /* defined( __cplusplus ) */

    CERRF_ASSERT( ( out_x != NULL ) && ( out_y != NULL ) );
    Rx = Ry = Sx = Sy = h2_n = ( real_type )0.0;

    y  = temp;
	x *= sign_x;

	if( ( y < ( real_type )CERRF_Y_LIMIT ) &&
        ( x < ( real_type )CERRF_X_LIMIT ) )
    {
        temp  = x / ( real_type )CERRF_X_LIMIT;
        temp  = sqrt( ( real_type )1.0 - temp * temp );
        temp *= ( ( real_type )1.0 - y / ( real_type )CERRF_Y_LIMIT );

        N     = ( int )floor( ( real_type )CERRF_N0   + ( real_type )CERRF_N1   * temp );
        nu    = ( int )floor( ( real_type )CERRF_NU_0 + ( real_type )CERRF_NU_1 * temp );

        temp *= ( real_type )CERRF_H0;
        y_plus_h += temp;

        h2_n  = temp;
        h2_n *= ( real_type )2.0;
        use_taylor_sum = ( bool )( h2_n > ( real_type )CERRF_REAL_EPS );

        CERRF_ASSERT( h2_n > ( real_type )CERRF_REAL_EPS );
        inv_h2 = ( real_type )1.0 / h2_n;
        CERRF_ASSERT( inv_h2 > ( real_type )CERRF_REAL_EPS );
        h2_n = power_n( h2_n, N - 1 );
    }

    if( y < ( real_type )CERRF_REAL_EPS )
    {
        Rx = exp( -x * x ) / ( real_type )CERRF_TWO_OVER_SQRT_PI;
        nu = 0;
    }

    if( !use_taylor_sum )
    {
        for( int n = nu ; n > 0 ; --n )
        {
            Wx       = y_plus_h + n * Rx;
            Wy       = x - n * Ry;
            temp     = Wx * Wx + Wy * Wy;
            Rx       = ( real_type )0.5 * Wx;
            Rx      /= temp;
            Ry       = ( real_type )0.5 * Wy;
            Ry      /= temp;
        }

        Wx = ( real_type )CERRF_TWO_OVER_SQRT_PI * Rx;
        Wy = ( real_type )CERRF_TWO_OVER_SQRT_PI * Ry;
    }
    else
    {
        for( int n = nu ; n > N ; --n )
        {
            Wx       = y_plus_h + n * Rx;
            Wy       = x - n * Ry;
            temp     = Wx * Wx + Wy * Wy;
            Rx       = ( real_type )0.5 * Wx;
            Rx      /= temp;
            Ry       = ( real_type )0.5 * Wy;
            Ry      /= temp;
        }

        for( int n = N ; n > 0 ; --n )
        {
            Wx       = y_plus_h + n * Rx;
            Wy       = x - n * Ry;
            temp     = Wx * Wx + Wy * Wy;
            Rx       = ( real_type )0.5 * Wx;
            Rx      /= temp;
            Ry       = ( real_type )0.5 * Wy;
            Ry      /= temp;

            Wx       = h2_n + Sx;
            h2_n    *= inv_h2;
            Sx       = Rx * Wx - Ry * Sy;
            Sy       = Ry * Wx + Rx * Sy;
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

CERRF_INLINE int wofz_cernlib_rev4(
    CERRF_REAL_TYPE x, CERRF_REAL_TYPE y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT
{
    cerrf_rev4( x, y, out_x, out_y );
    return 0;
}

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */
#endif /* FADDEEVAS_CERNLIB_REV4_C_H__ */
