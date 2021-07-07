#ifndef FADDEEVAS_OPENCL_COMMON_BENCHMARK_ITEM_H__
#define FADDEEVAS_OPENCL_COMMON_BENCHMARK_ITEM_H__

#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <memory>

#include "common/definitions.h"
#include "toml/toml.hpp"

namespace faddeevas
{
    struct InitArgumentBase
    {
        typedef CERRF_REAL_TYPE real_type;

        virtual void init( real_type* in_begin, real_type* in_end )
        {
            CERRF_ASSERT( in_begin != nullptr );
            CERRF_ASSERT( in_end   != nullptr );

            while( in_begin != in_end ) *in_begin++ = real_type{ 0. };
        }
    };

    struct BenchmarkItem
    {
        std::string init_x_config = std::string{};
        std::string init_y_config = std::string{};

        std::unique_ptr< InitArgumentBase > init_x_arg =
            std::unique_ptr< InitArgumentBase >{};

        std::unique_ptr< InitArgumentBase > init_y_arg =
            std::unique_ptr< InitArgumentBase >{};

        int num_evaluations = 0;
        int num_repetitions = 0;
        int workgroup_size  = 0;
    };

    struct BenchmarkRun
    {
        BenchmarkRun( toml::table const& config );

        BenchmarkRun( BenchmarkRun const& ) = default;
        BenchmarkRun( BenchmarkRun&& ) = default;

        BenchmarkRun& operator=( BenchmarkRun const& ) = default;
        BenchmarkRun& operator=( BenchmarkRun&& ) = default;

        virtual ~BenchmarkRun() = default;

        int platform_id = 0;
        int device_id   = 0;

        std::string path_to_kernel   = std::string{};
        std::string kernel_file_name = std::string{};
        std::string compile_options  = std::string{};

        std::vector< BenchmarkItem > items;
    };


}

#endif /* FADDEEVAS_OPENCL_COMMON_BENCHMARK_ITEM_H__ */
