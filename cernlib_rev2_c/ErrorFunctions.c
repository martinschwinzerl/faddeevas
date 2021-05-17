/////////////////////////////////////////////////////////////////////////////
//
// FILE NAME
//   ErrorFunctions.c
//
//   02/19/2015, 08/18/2015, 05/12/2021
//
// AUTHORS
//   Hannes Bartosik, Adrian Oeftiger
//
// REVISIONS & REVISING AUTHORS
//   rev 1      05/12/2021  by Martin Schwinzerl
//              remove Rx Ry arrays, eliminate branches
//
// DESCRIPTION
//   Error functions
//
/////////////////////////////////////////////////////////////////////////////

#include "ErrorFunctions.h"

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

double power_n_ext( double const x, unsigned int const n )
{
    return power_n( x, n );
}

void cerrf_rev2_ext( double const x, double const y,
    double* restrict out_x, double* restrict out_y )
{
    cerrf_rev2( x, y, out_x, out_y );
}

