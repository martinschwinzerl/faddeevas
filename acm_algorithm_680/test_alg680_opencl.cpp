#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <CL/cl2.hpp>

int main( int const argc, char* argv[] )
{
    double const XLIM = double{ 6.3 };
    double const YLIM = double{ 4.4 };

    int platform_id = 1;
    int device_id = 0;

    int NUM_ARGUMENTS = 50 * 1024;

    /* ********************************************************************* */

    if( argc >= 2 )
    {
        platform_id = std::atoi( argv[ 1 ] );

        if( argc >= 3 )
        {
            device_id = std::atoi( argv[ 2 ] );

            if( argc >= 4 )
            {
                NUM_ARGUMENTS = std::atoi( argv[ 3 ] );
            }
        }
    }
    else
    {
        std::cout << "Usage: " << argv[ 0 ]
                  << " [PLATFORM_ID [DEVICE_ID [NUM_ARGUMENTS]]]"
                  << "\r\n" << std::endl;

        return 0;
    }


    /* ********************************************************************* */

    std::mt19937_64 prng( 20210527 );

    std::uniform_real_distribution< double > x_uniform_dist(
        -std::sqrt( double{ 2.0 } ) * XLIM, std::sqrt( double{ 2.0 } ) * XLIM );

    std::uniform_real_distribution< double > y_uniform_dist(
        -std::sqrt( double{ 2.0 } ) * YLIM, std::sqrt( double{ 2.0 } ) * YLIM );

    std::vector< double > x_uniform( NUM_ARGUMENTS, double{ 0.0 } );
    std::vector< double > y_uniform( NUM_ARGUMENTS, double{ 0.0 } );

    for( int ii = 0 ; ii < NUM_ARGUMENTS ; ++ii )
    {
        x_uniform[ ii ] = x_uniform_dist( prng );
        y_uniform[ ii ] = y_uniform_dist( prng );
    }

    std::vector< double > x_result( NUM_ARGUMENTS, double{ 0.0 } );
    std::vector< double > y_result( NUM_ARGUMENTS, double{ 0.0 } );

    /* --------------------------------------------------------------------- */

    std::vector< cl::Platform > platforms;
    cl::Platform::get( &platforms );

    assert( !platforms.empty() );
    assert( platforms.size() > platform_id );

    std::vector< cl::Device > devices;
    platforms[ platform_id ].getDevices( CL_DEVICE_TYPE_ALL, &devices );

    assert( !devices.empty() );
    assert( devices.size() > device_id );
    cl::Device device = devices[ device_id ];

    cl::Context ctx( device );
    cl::CommandQueue queue( ctx, device, CL_QUEUE_PROFILING_ENABLE );

    std::string kernel_src;
    std::ifstream in_kernel( "./wofz.cl" );

    if( in_kernel.is_open() )
    {
        std::ostringstream a2str;
        a2str << in_kernel.rdbuf();
        kernel_src = a2str.str();
    }

    std::string const kernel_compile_options =
        "-I.. -D_GPUCODE=1 -DCERRF_NO_SYSTEM_INCLUDES=1 -s./wofz.cl -g";

    cl::Program program( ctx, kernel_src );
    ::cl_int ret = program.build( kernel_compile_options.c_str() );

    assert( ret == CL_SUCCESS );
    cl::Kernel kernel( program, "eval_wofz" );

    /* --------------------------------------------------------------------- */

    cl::Buffer in_x_arg( ctx, CL_MEM_READ_WRITE, sizeof( double ) * NUM_ARGUMENTS, nullptr );
    cl::Buffer in_y_arg( ctx, CL_MEM_READ_WRITE, sizeof( double ) * NUM_ARGUMENTS, nullptr );

    cl::Buffer out_x_arg( ctx, CL_MEM_READ_WRITE, sizeof( double ) * NUM_ARGUMENTS, nullptr );
    cl::Buffer out_y_arg( ctx, CL_MEM_READ_WRITE, sizeof( double ) * NUM_ARGUMENTS, nullptr );

    ret = queue.enqueueWriteBuffer( in_x_arg, CL_TRUE, std::size_t{ 0 },
        x_uniform.size() * sizeof( double ), x_uniform.data() );

    assert( ret == CL_SUCCESS );

    ret = queue.enqueueWriteBuffer( in_y_arg, CL_TRUE, std::size_t{ 0 },
        y_uniform.size() * sizeof( double ), y_uniform.data() );

    assert( ret == CL_SUCCESS );

    ::cl_long const nn = NUM_ARGUMENTS;

    kernel.setArg( 0, in_x_arg );
    kernel.setArg( 1, in_y_arg );
    kernel.setArg( 2, out_x_arg );
    kernel.setArg( 3, out_y_arg );
    kernel.setArg( 4, nn );

    cl::Event ev;

    std::cout << "Starting kernel" << "\r\n";

    ret = queue.enqueueNDRangeKernel(
        kernel, cl::NullRange, NUM_ARGUMENTS, cl::NullRange, nullptr, &ev );
    assert( ret == CL_SUCCESS );

    queue.flush();
    ev.wait();

    std::cout << "finished!" << std::endl;

    ret = queue.enqueueReadBuffer( out_x_arg, CL_TRUE, std::size_t{ 0 },
        x_result.size() * sizeof( double ), x_result.data() );

    assert( ret == CL_SUCCESS );

    ret = queue.enqueueReadBuffer( out_y_arg, CL_TRUE, std::size_t{ 0 },
        y_result.size() * sizeof( double ), y_result.data() );

    assert( ret == CL_SUCCESS );

    return 0;
}
