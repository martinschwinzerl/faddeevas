#include <algorithm>
#include <cassert>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <chrono>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "common/definitions.h"
#include "cernlib_c/ErrorFunctions.h"

CERRF_REAL_TYPE gz( CERRF_REAL_TYPE const x, CERRF_REAL_TYPE const y,
                    CERRF_REAL_TYPE const x0, CERRF_REAL_TYPE const y0
) CERRF_NOEXCEPT
{
    typedef CERRF_REAL_TYPE real_type;

    #if defined( __cplusplus )
    using std::sqrt;
    #endif /* defined( __cplusplus ) */

    real_type const xrel = x / x0;
    real_type const yrel = y / y0;

    CERRF_ASSERT( x0   >  ( real_type )0.0 );
    CERRF_ASSERT( y0   >  ( real_type )0.0 );
    CERRF_ASSERT( x    >= ( real_type )0.0 );
    CERRF_ASSERT( y    >= ( real_type )0.0 );
    CERRF_ASSERT( x    <= x0 );
    CERRF_ASSERT( y    <= y0 );

    return ( ( real_type )1.0 - yrel ) * sqrt( ( real_type )1.0 - xrel * xrel );
}

int main( int argc, char* argv[] )
{
    typedef CERRF_REAL_TYPE real_type;

    std::size_t const CHUNK_SIZE = std::size_t{ 10 };
    std::size_t NUM_REPETITIONS  = std::size_t{ 40 };
    std::size_t NUM_EVALUATIONS  = std::size_t{ 1000 };

    std::string path_to_abscissa_file;
    std::string path_to_output_file;

    real_type const x0 = real_type{ 5.33 };
    real_type const y0 = real_type{ 4.29 };

    real_type const N0 = real_type{ 7 };
    real_type const N1 = real_type{ 23 };

    real_type const NU_0 = real_type{ 10 };
    real_type const NU_1 = real_type{ 21 };

    real_type const K    = real_type{ 9 };

    if( argc >= 3 )
    {
        path_to_abscissa_file = std::string{ argv[ 1 ] };
        path_to_output_file   = std::string{ argv[ 2 ] };

        if( argc >= 4 )
        {
            NUM_EVALUATIONS = static_cast< std::size_t >(
                std::atoi( argv[ 3 ] ) );

            if( argc >= 5 )
            {
                NUM_REPETITIONS = static_cast< std::size_t >(
                    std::atoi( argv[ 4 ] ) );
            }
        }
    }
    else
    {
        std::cout << "Usage: " << argv[ 0 ]
                  << "path_to_abscissa_file path_to_output_file\r\n"
                  << std::endl;

        return 0;
    }

    std::size_t n_chunks = NUM_EVALUATIONS / CHUNK_SIZE;
    if( n_chunks * CHUNK_SIZE < NUM_EVALUATIONS ) ++n_chunks;
    NUM_EVALUATIONS = n_chunks * CHUNK_SIZE;

    std::size_t nreal = std::size_t{ 0 };
    std::size_t nimag = std::size_t{ 0 };


    std::ifstream in_absc( path_to_abscissa_file );
    if( !in_absc.is_open() ) return 0;

    in_absc >> nreal;
    in_absc >> nimag;

    if( ( nreal == std::size_t{ 0 } ) && ( nimag == std::size_t{ 0 } ) )
    {
        return 0;
    }

    std::vector< real_type > xx( nreal, real_type{ 0.0 } );
    std::vector< real_type > yy( nimag, real_type{ 0.0 } );

    xx.clear();
    yy.clear();

    for( std::size_t ii = std::size_t{ 0 } ; ii < nreal ; ++ii )
    {
        if( !in_absc.is_open() ) break;

        real_type temp;
        in_absc >> temp;

        if( ( !xx.empty() ) && ( xx.back() >= temp ) ) break;

        xx.push_back( temp );
    }

    if( xx.size() != nreal ) return 0;

    for( std::size_t ii = std::size_t{ 0 } ; ii < nreal ; ++ii )
    {
        if( !in_absc.is_open() ) break;

        real_type temp;
        in_absc >> temp;

        if( ( !yy.empty() ) && ( yy.back() >= temp ) ) break;

        yy.push_back( temp );
    }

    if( yy.size() != nimag ) return 0;

    std::vector< double > out_re( NUM_EVALUATIONS,  double{ 0.0 } );
    std::vector< double > out_im( NUM_EVALUATIONS,  double{ 0.0 } );
    std::vector< double > timings( NUM_REPETITIONS, double{ 0.0 } );

    std::ofstream out_data( path_to_output_file );

    out_data.precision( 10 );
    out_data << "#" << std::setw( 19 ) << "in_re"
             << std::setw( 20 ) << "in_im"
             << std::setw( 20 ) << "gz"
             << std::setw(  6 ) << "N"
             << std::setw(  6 ) << "nu"
             << std::setw( 20 ) << "out_re"
             << std::setw( 20 ) << "out_im"
             << std::setw(  8 ) << "num_evaluations"
             << std::setw(  8 ) << "num_repetitions"
             << std::setw( 15 ) << "median_t_run"
             << std::setw( 15 ) << "min_t_run"
             << std::setw( 15 ) << "max_t_run"
             << std::setw( 15 ) << "t_run_10_perc"
             << std::setw( 15 ) << "t_run_90 perc\r\n";


    for( std::size_t ii = 0u ; ii < nreal ; ++ii )
    {
        real_type const x = xx[ ii ];

        std::cout << "ii = "
                  << std::setw( 10 ) << ii + 1u << " / "
                  << std::setw( 10 ) << nreal
                  << std::endl;

        for( std::size_t jj = 0u ; jj < nimag ; ++jj )
        {
            real_type const y = yy[ jj ];

            real_type const g = ( x <= x0 && y <= y0 )
                ? gz( x, y, x0, y0 ) : real_type{ 1.0 };

            int const N  = ( x <= x0 && y <= y0 )
                ? static_cast< int >( std::floor( N0 + N1 * g ) )
                : int{ 0 };

            int const NU = ( x <= x0 && y <= y0 )
                ? static_cast< int >( std::floor( NU_0 + NU_1 * g ) )
                : static_cast< int >( K );

            std::fill( timings.begin(), timings.end(), real_type{ 0.0 } );

            for( std::size_t ll = 0u ; ll < NUM_REPETITIONS ; ++ll )
            {
                std::fill( out_re.begin(), out_re.end(), real_type{ 0.0 } );
                std::fill( out_im.begin(), out_im.end(), real_type{ 0.0 } );
                real_type t = real_type{ 0.0 };
                real_type num_evals = real_type{ 0.0 };

                for( std::size_t kk = 0u ; kk < n_chunks ; ++kk )
                {
                    std::size_t nn = kk * CHUNK_SIZE;
                    auto start = std::chrono::high_resolution_clock::now();

                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );
                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );
                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );
                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );
                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );
                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );
                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );
                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );
                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );
                    ::cerrf( x, y, &out_re[ nn ], &out_im[ nn++ ] );

                    auto stop = std::chrono::high_resolution_clock::now();

                    std::chrono::duration< double, std::micro > const diff =
                        stop - start;

                    t += diff.count();
                    num_evals += real_type{ 10.0 };
                }

                timings[ ll ] = t / num_evals;
            }

            std::sort( timings.begin(), timings.end() );

            out_data.precision( 10 );

            out_data << std::scientific
                     << std::setw( 20 ) << x << " "
                     << std::setw( 20 ) << y << " "
                     << std::setw( 20 ) << g << " "
                     << std::setw(  6 ) << N << " "
                     << std::setw(  6 ) << NU << " "
                     << std::setw( 20 ) << out_re[ 0 ] << " "
                     << std::setw( 20 ) << out_im[ 0 ] << " "
                     << std::setw(  8 ) << NUM_EVALUATIONS << " "
                     << std::setw(  8 ) << NUM_REPETITIONS << " ";

            out_data.precision( 6 );
            out_data << std::fixed
                     << std::setw( 15 ) << timings[ timings.size() >> 1 ] << " "
                     << std::setw( 15 ) << timings.front() << " "
                     << std::setw( 15 ) << timings.back() << " "
                     << std::setw( 15 ) << timings[ static_cast< int >( 0.1 * timings.size() + 0.5 ) ] << " "
                     << std::setw( 15 ) << timings[ static_cast< int >( 0.9 * timings.size() + 0.5 ) ] << "\r\n";
        }
    }

    return 0;
}

