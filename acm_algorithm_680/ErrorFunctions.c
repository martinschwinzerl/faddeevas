#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>

#include "acm_algorithm_680/ErrorFunctions.h"


int wofz_alg680_ext(
    CERRF_REAL_TYPE const in_x, CERRF_REAL_TYPE const in_y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT
{
    return wofz_alg680( in_x, in_y, out_x, out_y );
}
