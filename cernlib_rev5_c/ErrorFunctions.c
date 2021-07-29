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

void cerrf_rev3_ext( CERRF_REAL_TYPE const x, CERRF_REAL_TYPE const y,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_x,
    CERRF_RESULT_DEC CERRF_REAL_TYPE* CERRF_RESTRICT out_y ) CERRF_NOEXCEPT
{
    cerrf_rev3( x, y, out_x, out_y );
}

