#ifndef CERRF_FADDEEVAS_HELPER_FUNCTIONS_H__
#define CERRF_FADDEEVAS_HELPER_FUNCTIONS_H__

#if !defined( CERRF_NO_INCLUDES )
#include "common/definitions.h"
#endif /* !defined( CERRF_NO_INCLUDES ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
extern "C" {
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */

CERRF_STATIC CERRF_FN CERRF_REAL_TYPE power_n(
    CERRF_REAL_TYPE x, unsigned int n ) CERRF_NOEXCEPT;

#if !defined( _GPUCODE )

CERRF_EXTERN CERRF_HOST_FN CERRF_REAL_TYPE power_n_ext(
    CERRF_REAL_TYPE x, unsigned int n ) CERRF_NOEXCEPT;

#endif /* !defined( _GPUCODE ) */

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */


///////////////////////////////////////////////////////////////////////////////

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C" {
#endif /* C++, Host */

CERRF_INLINE CERRF_REAL_TYPE power_n(
    CERRF_REAL_TYPE x, unsigned int n ) CERRF_NOEXCEPT
{
    typedef CERRF_REAL_TYPE real_type;

    real_type x_n = x;

    unsigned int const n_div_16 = n >> 4u;
    unsigned int const n_mod_16 = n - ( n_div_16 << 4u );
    CERRF_ASSERT( n_div_16 * 16u + n_mod_16 == n );
    CERRF_ASSERT( ( sqrt( x * x ) > ( real_type )CERRF_REAL_EPS) || ( n > 0u ) );

    switch( n_mod_16 )
    {
        case  0: { x_n = ( real_type )1.0; break; }
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
            x_n = ( real_type )0.0;
        }
    };

    if( n_div_16 > 0u ){ x *= x; x *= x; x *= x; x *= x; }

    switch( n_div_16 )
    {
        case  0: { x_n  = ( n_mod_16 != 0u ) ? x_n : ( real_type )1.0; break; }
        case  1: { x_n *= x;                                           break; }
        case  2: { x   *= x; x_n *= x;                                 break; }
        case  3: { x_n *= x * x * x;                                   break; }
        case  4: { x   *= x; x *= x; x_n *= x;                         break; }
        case  5: { x_n *= x; x *= x; x *= x; x_n *= x;                 break; }
        case  6: { x   *= x * x; x *= x; x_n *= x;                     break; }
        case  7: { x_n *= x; x *= x * x; x *= x; x_n *= x;             break; }
        case  8: { x *= x; x *= x; x*= x; x_n *= x;                    break; }
        case  9: { x *= x * x; x *= x * x; x_n *= x;                   break; }
        case 10: { x_n *= x; x *= x * x; x *= x * x; x_n *= x;         break; }
        case 11: { x_n *= x * x; x *= x * x; x *= x * x; x_n *= x;     break; }
        case 12: { x *= x; x *= x; x_n *= x; x *= x; x_n *= x;         break; }
        case 13: { x_n *= x; x *= x; x *= x; x_n *= x; x *= x;
                   x_n *= x; break; }

        case 14: { x_n *= x * x; x *= x; x *= x; x_n *= x; x *= x;
                   x_n *= x; break; }

        case 15: { x *= x * x; x_n *= x * x; x *= x * x; x_n *= x;    break; }

        default:
        {
            unsigned int ii = 0u;
            unsigned int nn = n_div_16 % 16u;

            CERRF_ASSERT( n_div_16 >= 16u );

            for( ; ii < nn ; ++ii ) x_n *= x;

            CERRF_ASSERT( ( n_div_16 - nn ) % 16u == 0u );

            x *= x; x *= x; x *= x; x *= x;
            nn = ( n_div_16 - nn ) >> 4u;

            for( ii = 0u ; ii < nn ; ++ii ) x_n *= x;
        }
    };

    return x_n;
}

#if defined( __cplusplus ) && !defined( _GPUCODE )
}
#endif /* defined( __cplusplus ) && !defined( _GPUCODE ) */
#endif /* CERRF_FADDEEVAS_HELPER_FUNCTIONS_H__ */
