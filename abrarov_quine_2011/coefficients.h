#ifndef CERRF_ABRAROV_QUINE_2011_COEFFICIENTS_ABZ_H__
#define CERRF_ABRAROV_QUINE_2011_COEFFICIENTS_ABZ_H__

#if !defined( CERRF_NO_SYSTEM_INCLUDES )
    #include <stddef.h>
    #include <stdlib.h>
#endif /* !defined( CERRF_NO_SYSTEM_INCLUDES ) */

#include "definitions.h"

#if !defined( _GPUCODE ) && defined( __cplusplus )
extern "C"  {
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

CERRF_EXTERN CERRF_REAL_TYPE const CERRF_FOURIER_COEFF[ CERRF_N_FOURIER ];
CERRF_EXTERN CERRF_REAL_TYPE const CERRF_TAYLOR_COEFF[ CERRF_NUM_TAYLOR_COEFF ];

#if !defined( _GPUCODE ) && defined( __cplusplus )
}
#endif /* !defined( _GPUCODE ) && defined( __cplusplus ) */

#endif /* CERRF_ABRAROV_QUINE_2011_COEFFICIENTS_ABZ_H__ */
