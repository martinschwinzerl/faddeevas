#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "ErrorFunctions.h"

int main( int argc, char* argv[] )
{
    typedef double real_type;

    if( argc < 3 )
    {
        std::cout << "Usage: " << argv[ 0 ]
                  << "path_to_abscissa_file path_to_output_file\r\n"
                  << std::endl;

        return 0;
    }

    std::string const path_to_abscissa_file = std::string{ argv[ 1 ] };
    std::string const path_to_output_file   = std::string{ argv[ 2 ] };

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
    out_data << nreal << "\r\n" << nimag << "\r\n";

    out_data.precision( 20 );

    for( std::size_t ii = 0u ; ii < nreal ; ++ii )
    {
        real_type const x = xx[ ii ];
        std::cout << "ii = "
                  << std::setw( 10 ) << ii + 1u << " / "
                  << std::setw( 10 ) << nreal
                  << std::endl;

        for( real_type const y : yy )
        {
            real_type wz_re = real_type{ 0. };
            real_type wz_im = real_type{ 0. };

            ::cerrf_rev2( x, y, &wz_re, &wz_im );

            out_data << std::scientific
                     << std::setw( 40 ) << x
                     << std::setw( 40 ) << y
                     << std::setw( 40 ) << wz_re << std::setw( 40 ) << wz_im
                     << std::fixed << "\r\n";
        }
    }

    out_data.flush();

    return 0;
}

