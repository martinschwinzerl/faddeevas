#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <utility>

#include "common/definitions.h"
#include "cernlib_rev2_c/ErrorFunctions.h"

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
    typedef std::chrono::steady_clock clock_type;

    std::size_t NUM_EVALUATIONS = std::size_t{ 500 };

    std::string path_to_abscissa_file;
    std::string path_to_output_file;
    std::mt19937_64 prng( std::mt19937_64::result_type{ 20210725 } );

    real_type const x0 = real_type{ CERRF_X_LIMIT };
    real_type const y0 = real_type{ CERRF_Y_LIMIT };

    real_type const N0 = real_type{ CERRF_N0 };
    real_type const N1 = real_type{ CERRF_N1 };

    real_type const NU_0 = real_type{ CERRF_NU_0 };
    real_type const NU_1 = real_type{ CERRF_NU_1 };

    real_type const K    = real_type{ CERRF_GAUSS_HERMITE_NU };

    if( argc >= 3 )
    {
        path_to_abscissa_file = std::string{ argv[ 1 ] };
        path_to_output_file   = std::string{ argv[ 2 ] };

        if( argc >= 4 )
        {
            NUM_EVALUATIONS = static_cast< std::size_t >(
                std::atoi( argv[ 3 ] ) );
        }
    }
    else
    {
        std::cout << "Usage: " << argv[ 0 ]
                  << "path_to_abscissa_file path_to_output_file\r\n"
                  << std::endl;

        return 0;
    }

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

    for( std::size_t ii = std::size_t{ 0 } ; ii < nimag ; ++ii )
    {
        if( !in_absc.is_open() ) break;

        real_type temp;
        in_absc >> temp;

        if( ( !yy.empty() ) && ( yy.back() >= temp ) ) break;

        yy.push_back( temp );
    }

    if( yy.size() != nimag ) return 0;

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

    std::vector< std::vector< double > > timings;
    timings.clear();
    timings.reserve( nreal * nimag );

    std::vector< std::pair< std::size_t, std::size_t > > rand_indices;
    rand_indices.clear();
    rand_indices.reserve( NUM_EVALUATIONS * nreal * nimag );

    for( std::size_t jj = 0u ; jj < nimag ; ++jj )
    {
        for( std::size_t ii = 0u ; ii < nreal ; ++ii )
        {
            timings.emplace_back( NUM_EVALUATIONS, double{ 0.0 } );
            timings.back().clear();

            for( std::size_t kk = 0u ; kk < NUM_EVALUATIONS ; ++kk )
            {
                rand_indices.emplace_back( jj, ii );
            }
        }
    }

    std::shuffle( rand_indices.begin(), rand_indices.end(), prng );
    std::vector< double > out_re( nreal * nimag,  double{ 0.0 } );
    std::vector< double > out_im( nreal * nimag,  double{ 0.0 } );

    std::size_t const nn = rand_indices.size();

    std::size_t const one_percent_of_nn = static_cast< std::size_t >(
        std::floor( double{ 0.01 } * nn + double{ 0.5 } ) );

    auto start_chunk = clock_type::now();

    for( std::size_t kk = 0u ; kk < nn ; ++kk )
    {
        auto const idx = rand_indices[ kk ];
        std::size_t const ii = idx.second;
        std::size_t const jj = idx.first;
        std::size_t const out_idx = ii + jj * nreal;

        real_type const x = xx[ ii ];
        real_type const y = yy[ jj ];

        auto const start = clock_type::now();
        ::cerrf_rev2( x, y, &out_re[ out_idx ], &out_im[ out_idx ] );
        auto const stop = clock_type::now();

        std::chrono::duration< double, std::micro > const t_elapsed =
            stop - start;

        timings[ out_idx ].push_back( t_elapsed.count() );

        if( ( kk > 0u ) && ( ( kk % one_percent_of_nn ) == 0u ) )
        {
            auto const stop_chunk = clock_type::now();
            std::chrono::duration< double, std::ratio< 1 > >
                const t_elapsed_chunk = stop_chunk - start_chunk;

            std::cout << "Evaluated " << std::setw( 20 ) << kk + 1
                      << " / " << std::setw( 20 ) << nn
                      << " ( " << std::setw( 4 )
                      << kk / one_percent_of_nn << "% ) : "
                      << t_elapsed_chunk.count() << " sec" << std::endl;

            start_chunk = clock_type::now();
        }
    }

    for( std::size_t jj = 0u ; jj < nimag ; ++jj )
    {
        real_type const y = yy[ jj ];

        for( std::size_t ii = 0u ; ii < nreal ; ++ii )
        {
            real_type const x = xx[ ii ];
            real_type const g = ( x <= x0 && y <= y0 )
                ? gz( x, y, x0, y0 ) : real_type{ 1.0 };

            int const N  = ( x <= x0 && y <= y0 )
                ? static_cast< int >( std::floor( N0 + N1 * g ) )
                : int{ 0 };

            int const NU = ( x <= x0 && y <= y0 )
                ? static_cast< int >( std::floor( NU_0 + NU_1 * g ) )
                : static_cast< int >( CERRF_GAUSS_HERMITE_NU );

            std::size_t const out_idx = ii + jj * nreal;

            out_data.precision( 10 );

            out_data << std::scientific
                     << std::setw( 20 ) << x << " "
                     << std::setw( 19 ) << y << " "
                     << std::setw( 19 ) << g << " "
                     << std::setw(  5 ) << N << " "
                     << std::setw(  5 ) << NU << " "
                     << std::setw( 19 ) << out_re[ out_idx ] << " "
                     << std::setw( 19 ) << out_im[ out_idx ] << " "
                     << std::setw(  7 ) << NUM_EVALUATIONS << " "
                     << std::setw(  7 ) << 1 << " ";

            std::size_t const num_evals = timings[ out_idx ].size();

            std::size_t const median_idx = num_evals >> 1;
            std::size_t const perc10_idx = static_cast< std::size_t >(
                std::floor( double{ 0.1 } * num_evals + double{ 0.5 } ) );

            std::size_t const perc90_idx = static_cast< std::size_t >(
                std::floor( double{ 0.9 } * num_evals + double{ 0.5 } ) );

            std::sort( timings[ out_idx ].begin(), timings[ out_idx ].end() );
            out_data.precision( 6 );
            out_data << std::fixed
                     << std::setw( 14 ) << timings[ out_idx ][ median_idx ] << " "
                     << std::setw( 14 ) << timings[ out_idx ].front() << " "
                     << std::setw( 14 ) << timings[ out_idx ].back() << " "
                     << std::setw( 14 ) << timings[ out_idx ][ perc10_idx ] << " "
                     << std::setw( 14 ) << timings[ out_idx ][ perc90_idx ] << "\r\n";
        }
    }

    return 0;
}

