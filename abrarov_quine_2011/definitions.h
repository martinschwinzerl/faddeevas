#ifndef CERRF_ABRAROV_QUINE_2011_DEFINITIONS_H__
#define CERRF_ABRAROV_QUINE_2011_DEFINITIONS_H__

#if !defined( CERRF_NO_INCLUDES )
    #include "common/definitions.h"
#endif /* !defined( CERRF_NO_INCLUDES ) */

#if !defined( CERRF_TAYLOR_COEFF_DEC )
    #if defined( _GPUCODE )
        #if defined( __OPENCL_C_VERSION__ )
            #define CERRF_TAYLOR_COEFF_DEC __global
        #else
            #define CERRF_TAYLOR_COEFF_DEC
        #endif
    #else
        #define CERRF_TAYLOR_COEFF_DEC
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( CERRF_TAYLOR_COEFF_DEC ) */

#if !defined( CERRF_FOURIER_COEFF_DEC )
    #if defined( _GPUCODE )
        #if defined( __OPENCL_C_VERSION__ )
            #define CERRF_FOURIER_COEFF_DEC __global
        #else
            #define CERRF_FOURIER_COEFF_DEC
        #endif
    #else
        #define CERRF_FOURIER_COEFF_DEC
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( CERRF_FOURIER_COEFF_DEC ) */


#if !defined( CERRF_RESULT_DEC )
    #if defined( _GPUCODE )
        #if defined( __OPENCL_C_VERSION__ )
            #define CERRF_RESULT_DEC __private
        #else
            #define CERRF_RESULT_DEC
        #endif
    #else
        #define CERRF_RESULT_DEC
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( CERRF_RESULT_DEC ) */

/* - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#if !defined( CERRF_INV_TWO_SQRT_PI )
    #define CERRF_INV_TWO_SQRT_PI 0.28209479177387814347403972578
#endif /* !defined( CERRF_INV_TWO_SQRT_PI ) */

#if !defined( CERRF_SQRT_TWO )
    #define CERRF_SQRT_TWO 1.4142135623730950488
#endif /* !defined( CERRF_SQRT_TWO ) */

#if !defined( CERRF_N_FOURIER )
    #define CERRF_N_FOURIER 24
#endif /* !defined( CERRF_N_FOURIER ) */

#if !defined( CERRF_N_TAYLOR )
    #define CERRF_N_TAYLOR 6
#endif /* !defined( CERRF_N_TAYLOR ) */

/* CERRF_NUM_TAYLOR_COMPONENTS */
#if !defined( CERRF_NUM_TAYLOR_COMPONENTS )
    #define CERRF_NUM_TAYLOR_COMPONENTS 21
#endif /* !defined( CERRF_NUM_TAYLOR_COMPONENTS ) */

/* CERRF_NUM_TAYLOR_COEFF = 2 * ( 1 + CERRF_N_FOURIER ) * CERRF_N_TAYLOR */

#if !defined( CERRF_NUM_TAYLOR_COEFF )
    #define CERRF_NUM_TAYLOR_COEFF 288
#endif /* !defined( CERRF_NUM_TAYLOR_COEFF ) */

#if !defined( CERRF_TM )
    #define CERRF_TM 12.0
#endif /* !defined( CERRF_TM ) */

#if !defined( CERRF_PI_OVER_TM )
    #define CERRF_PI_OVER_TM 0.261799387799149436538553615273291907016430783281258818414578716
#endif /* !defined( CERRF_PI_OVER_TM ) */

#if !defined( CERRF_TM_OVER_PI )
    #define CERRF_TM_OVER_PI 3.819718634205488058453210320940344688827031497770954769944016257
#endif /* !defined( CERRF_TM_OVER_PI ) */

#if !defined( CERRF_TM_SQU )
    #define CERRF_TM_SQU 144.0
#endif /* !defined( CERRF_TM_SQU ) */

#if !defined( CERRF_MIN_POLE_DIST )
    #define CERRF_MIN_POLE_DIST 3e-3
#endif /* !defined( CERRF_MIN_POLE_DIST ) */

#if !defined( CERRF_MIN_POLE_DIST_SQU )
    #define CERRF_MIN_POLE_DIST_SQU 9e-6
#endif /* !defined( CERRF_MIN_POLE_DIST_SQU ) */

/* CERRF_MAX_X_FOR_POLE:
 *  if |x| > N_FOURIER * ( pi / tm ) + MIN_POLE_DIST,
 *  then we will not hit a pole */
#if !defined( CERRF_MAX_X_FOR_POLE )
    #define CERRF_MAX_X_FOR_POLE 6.024385919380437040449183196420878916776737296799061466113435469
#endif /* !defined( CERRF_MAX_X_FOR_POLE ) */

#endif /* CERRF_ABRAROV_QUINE_2011_DEFINITIONS_H__ */
