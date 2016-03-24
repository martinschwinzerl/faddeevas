// Translated from C++ to C for SixTrack and MAD-X
// Author: Laurent Deniau, BE/ABP, laurent.deniau@cern.ch
// Date  : 2016.01.13

// implementation of complex erf and erfc (see erfc.h)

// compilation as shared lib:
// gcc -std=c99 -W -Wall -Wextra -pedantic -O3 -ffast-math -ftree-vectorize -fPIC -shared erfc.c -o liberfc.so

// compilation options:
// - fast   implementation: -DFAST_IMPL
// - sincos implementation: -std=gnu99 -DSINCOS

#include <math.h>
#include <tgmath.h>
#include <complex.h>
#include <stdbool.h>
#include <assert.h>

#include "erfc.h"

#undef  T
#define T float
#include "erfc.tc"

#undef  T
#define T double
#include "erfc.tc"
