#ifndef FADDEEVAS_CERNLIB_REVISED_C_H__
#define FADDEEVAS_CERNLIB_REVISED_C_H__

#if !defined( __cplusplus )
    #include <stddef.h>
#else /* defined( __cplusplus ) */
    #include <cstddef>
#endif /* !defined( __cplusplus ) */

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

#if defined( __cplusplus )
extern "C" {
#endif /* defined( __cplusplus ) */

extern void cerrf_rev(
    double x, double y,
    double* __restrict__ out_x, double* __restrict__ out_y );

#if defined( __cplusplus )
}
#endif /* defined( __cplusplus ) */
#endif /* FADDEEVAS_CERNLIB_REVISED_C_H__ */
