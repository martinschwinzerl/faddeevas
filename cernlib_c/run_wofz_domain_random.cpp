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
#include "cernlib_c/ErrorFunctions.h"

int main( int argc, char* argv[] )
{
    typedef CERRF_REAL_TYPE real_type;
    std::size_t NUM_EVALUATIONS = std::size_t{ 1000 };

    std::string path_to_abscissa_file;
    std::mt19937_64 prng( std::mt19937_64::result_type{ 20210725 } );

    if( argc >= 2 )
    {
        path_to_abscissa_file = std::string{ argv[ 1 ] };

        if( argc >= 3 )
        {
            NUM_EVALUATIONS = static_cast< std::size_t >(
                std::atoi( argv[ 2 ] ) );
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

    std::vector< std::pair< std::size_t, std::size_t > > rand_indices;
    rand_indices.clear();
    rand_indices.reserve( NUM_EVALUATIONS * nreal * nimag );

    for( std::size_t jj = 0u ; jj < nimag ; ++jj )
    {
        for( std::size_t ii = 0u ; ii < nreal ; ++ii )
        {
            for( std::size_t kk = 0u ; kk < NUM_EVALUATIONS ; ++kk )
            {
                rand_indices.emplace_back( jj, ii );
            }
        }
    }

    std::shuffle( rand_indices.begin(), rand_indices.end(), prng );
    std::vector< double > out_re( nreal * nimag,  double{ 0.0 } );
    std::vector< double > out_im( nreal * nimag,  double{ 0.0 } );

    for( auto const& idx : rand_indices )
    {
        std::size_t const out_idx = idx.second + idx.first * nimag;
        ::cerrf( xx[ idx.second ], yy[ idx.first ], &out_re[ out_idx ], &out_im[ out_idx ] );
    }

    return 0;
}

