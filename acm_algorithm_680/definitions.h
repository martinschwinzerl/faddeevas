#ifndef CERRF_ALG680_POPPE_WIJERS_DEFINITIONS_H__
#define CERRF_ALG680_POPPE_WIJERS_DEFINITIONS_H__

#if !defined( CERRF_NO_INCLUDES )
#include "common/definitions.h"
#endif /* !defined( CERRF_NO_INCLUDES ) */

#if !defined( CERRF_X_LIMIT )
    #define CERRF_X_LIMIT 6.3
#endif /* !defined( CERRF_X_LIMIT ) */

#if !defined( CERRF_Y_LIMIT )
    #define CERRF_Y_LIMIT 4.4
#endif /* !defined( CERRF_Y_LIMIT ) */

#if !defined( CERRF_TWO_OVER_SQRT_PI )
    #define CERRF_TWO_OVER_SQRT_PI 1.1283791670955125739
#endif /* !defined( CERRF_TWO_OVER_SQRT_PI ) */

#if !defined( CERRF_SQRT_TWO )
    #define CERRF_SQRT_TWO 1.4142135623730950488
#endif /* !defined( CERRF_SQRT_TWO ) */

#if !defined( CERRF_DOUBLE_EPS )
    #define  CERRF_REAL_EPS 2.22044604925031e-16
#endif /* !defined( CERRF_DOUBLE_EPS ) */

#if !defined( CERRF_REAL_MIN )
    #define CERRF_REAL_MIN 2.22507385850720e-308
#endif /* !defined( CERRF_REAL_MIN ) */

#if !defined( CERRF_REAL_MAX )
    #define CERRF_REAL_MAX 1.79769313486232e+308
#endif /* !defined( CERRF_REAL_MAX ) */

#if !defined( CERRF_XY_ABS_OVERFLOW_LIMIT )
    #define CERRF_XY_ABS_OVERFLOW_LIMIT 1.6814159916986475e-8
#endif /* !defined( CERRF_XY_ABS_OVERFLOW_LIMIT ) */

#if !defined( CERRF_REAL_MAX_X )
    /* sqrt( CERRF_REAL_MAX_X / CERRF_X_LIMIT ) = 5.34179854210932e+153 */
    /* choosen 5e153 to be on the safe side */
    #define CERRF_REAL_MAX_X 5.0e153
#endif /* !defined( CERRF_REAL_MAX_X ) */

#if !defined( CERRF_REAL_MAX_Y )
    /* sqrt( CERRF_REAL_MAX_Y / CERRF_Y_LIMIT ) = 6.39192163249533e+153 */
    /* choosen 6e153 to be on the safe side */
    #define CERRF_REAL_MAX_Y 6.0e153
#endif /* !defined( CERRF_REAL_MAX_Y ) */

#if !defined( CERRF_MAX_REAL_MAX_EXP )
    /* ln( CERRF_REAL_MAX ) - ln( 2.0 ) */
    #define CERRF_MAX_REAL_MAX_EXP 709.089565712824
#endif /* !defined( CERRF_MAX_REAL_MAX_EXP ) */

#if !defined( CERRF_MAX_REAL_GONIOMETRIC_ARG )
    #define CERRF_MAX_REAL_GONIOMETRIC_ARG 3.53711887601422e+15
#endif /* !defined( CERRF_MAX_REAL_GONIOMETRIC_ARG ) */

#if !defined( CERRF_QRHO_SQU_POWER_SERIES_LIMIT )
    #define CERRF_QRHO_SQU_POWER_SERIES_LIMIT 0.0852640
#endif /* !defined( CERRF_QRHO_SQU_POWER_SERIES_LIMIT ) */

#if !defined( CERRF_QRHO_SQU_CONTINUED_FRACTION_LIMIT )
    #define CERRF_QRHO_SQU_CONTINUED_FRACTION_LIMIT 1.0
#endif /* !defined( CERRF_QRHO_SQU_CONTINUED_FRACTION_LIMIT ) */

#if !defined( CERRF_QRHO_C0 )
    #define CERRF_QRHO_C0 1.0
#endif /* !defined( CERRF_QRHO_C0 ) */

#if !defined( CERRF_QRHO_C1 )
    #define CERRF_QRHO_C1 0.85
#endif /* !defined( CERRF_QRHO_C1 ) */

#if !defined( CERRF_N0 )
    #define CERRF_N0 6.5
#endif /* !defined( CERRF_N0 ) */

#if !defined( CERRF_N1 )
    #define CERRF_N1 72.0
#endif /* !defined( CERRF_N1 ) */

#if !defined( CERRF_H1 )
    #define CERRF_H1 1.88
#endif /* !defined( CERRF_H1 ) */

#if !defined( CERRF_KAPN0 )
    #define CERRF_KAPN0 7.5
#endif /* !defined( CERRF_KAPN0 ) */

#if !defined( CERRF_KAPN1 )
    #define CERRF_KAPN1 34.0
#endif /* !defined( CERRF_KAPN1 ) */

#if !defined( CERRF_NU0_CONT_FRACTION )
    #define CERRF_NU0_CONT_FRACTION 3.0
#endif /* !defined( CERRF_NU0_CONT_FRACTION ) */

#if !defined( CERRF_NU1_CONT_FRACTION )
    #define CERRF_NU1_CONT_FRACTION 1442.0
#endif /* !defined( CERRF_NU1_CONT_FRACTION ) */

#if !defined( CERRF_NU2_CONT_FRACTION )
    #define CERRF_NU2_CONT_FRACTION 77
#endif /* !defined( CERRF_NU2_CONT_FRACTION ) */

#if !defined( CERRF_NU3_CONT_FRACTION )
    #define CERRF_NU3_CONT_FRACTION 26
#endif /* !defined( CERRF_NU3_CONT_FRACTION ) */

#if !defined( CERRF_NU0 )
    #define CERRF_NU0 16.5
#endif /* !defined( CERRF_NU0 ) */

#if !defined( CERRF_NU1 )
    #define CERRF_NU1 26.0
#endif /* !defined( CERRF_NU1 ) */

#if !defined( CERRF_TWO_H_LIMIT )
    #define CERRF_TWO_H_LIMIT 0.25
#endif /* CERRF_TWO_H_LIMIT */

#endif /* CERRF_ALG680_POPPE_WIJERS_DEFINITIONS_H__ */
