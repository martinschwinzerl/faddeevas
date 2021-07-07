#ifndef CERRF_FADDEEVAS_COMMON_DEFINITIONS_H__
#define CERRF_FADDEEVAS_COMMON_DEFINITIONS_H__

#if !defined( CERRF_NO_SYSTEM_INCLUDES )
    #include <assert.h>
    #include <math.h>
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

#if !defined( CERRF_HOST_FN )
    #if defined( __CUDACC__ )
        #define CERRF_HOST_FN __host__
    #else
        #define CERRF_HOST_FN
    #endif
#endif

#if !defined( CERRF_DEVICE_FN )
    #if defined( __CUDACC__ )
        #define CERRF_DEVICE_FN __device__
    #else
        #define CERRF_DEVICE_FN
    #endif
#endif

#if !defined( CERRF_FN )
    #if defined( __CUDACC__ )
        #define CERRF_FN __host__ __device__
    #else
        #define CERRF_FN
    #endif /* CUDA */
#endif /* !defined( CERRF_FN ) */

#if !defined( CERRF_NOEXCEPT )
    #if !defined( _GPUCODE ) && defined( __cplusplus )
        #define CERRF_NOEXCEPT noexcept
    #else /* !defined( _GPUCODE ) && C++ */
        #define CERRF_NOEXCEPT
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( CERRF_NOEXCEPT ) */


#if !defined( CERRF_INLINE )
    #define CERRF_INLINE inline
#endif /* !defined( CERRF_INLINE ) */

#if !defined( CERRF_RESTRICT )
    #if defined( _GPUCODE )
        #if defined( __OPENCL_C_VERSION__ )
            #define CERRF_RESTRICT restrict
        #endif
    #else /* !defined( _GPUCODE ) */
        #if defined( __cplusplus )
            #define CERRF_RESTRICT __restrict__
        #else
            #define CERRF_RESTRICT restrict
        #endif /* defined( __cplusplus ) */
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( CERRF_RESTRICT ) */

#if !defined( CERRF_ASSERT )
    #if !defined( _GPUCODE )
        #define CERRF_ASSERT( cond ) assert( ( cond ) )
    #else /* !defined( _GPUCODE ) */
        #define CERRF_ASSERT( cond )
    #endif /* !defined( _GPUCODE ) */
#endif /* !defined( CERRF_ASSERT ) */

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

#if !defined( CERRF_REAL_TYPE )
    #define CERRF_REAL_TYPE double
#endif /* CERRF_REAL_TYPE */

#if !defined( CERRF_DOUBLE_EPS )
    #define  CERRF_REAL_EPS 2.22044604925031e-16
#endif /* !defined( CERRF_DOUBLE_EPS ) */

#if !defined( CERRF_REAL_MIN )
    #define CERRF_REAL_MIN 2.22507385850720e-308
#endif /* !defined( CERRF_REAL_MIN ) */

#if !defined( CERRF_REAL_MAX )
    #define CERRF_REAL_MAX 1.79769313486232e+308
#endif /* !defined( CERRF_REAL_MAX ) */

#if !defined( CERRF_PI )
    #define CERRF_PI 3.141592653589793238462643383279502884197169399375105820974944592
#endif /* !defined( CERRF_PI ) */

#if !defined( CERRF_SQRT_PI )
    #define CERRF_SQRT_PI 1.77245385090551602729816748334114518279754945612238712821380779
#endif /* !defined( CERRF_SQRT_PI ) */

#endif /* CERRF_FADDEEVAS_COMMON_DEFINITIONS_H__*/
