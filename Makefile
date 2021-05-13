### Makefile for the C and Fortran implementations

CC = gcc
CFLAGS = -std=c99 -W -Wall -Wextra -pedantic -O3 -ffast-math -ftree-vectorize -fPIC
LDFLAGS = -shared
F2PY = f2py
F2PYFLAGS = --opt="-O3 -ffast-math -ftree-vectorize"


.PHONY: all cernlib_c cernlib_rev_c cernlib_f90

all: cernlib_c cernlib_rev_c cernlib_f90 root_improvement root_improvement_fast root_improvement_sincos

cernlib_c:
	@echo "cernlib_c";
	$(CC) $(CFLAGS) $(LDFLAGS) cernlib_c/ErrorFunctions.c -o cernlib_c/wofz.so -lm

cernlib_rev_c:
	@echo "*** cernlib_rev_c ***";
	$(CC) $(CFLAGS) $(LDFLAGS) cernlib_rev_c/ErrorFunctions.c -o cernlib_rev_c/wofz_rev.so -lm

cernlib_f90:
	$(F2PY) $(F2PYFLAGS) -m wwerf -c cernlib_f90/erfr.f90; mv `ls -1 ./wwerf*.so` ./cernlib_f90/ ; cp `ls -1 ./cernlib_f90/wwerf*.so` ./cernlib_f90/wwerf.so

root_improvement:
	$(CC) $(CFLAGS) $(LDFLAGS) cernlib_root_adapted/erfc.c -o cernlib_root_adapted/liberfc.so

root_improvement_fast:
	$(CC) $(CFLAGS) $(LDFLAGS) cernlib_root_adapted/erfc.c -o cernlib_root_adapted/liberfc_fast.so -DFAST_IMPL

root_improvement_sincos:
	$(CC) $(CFLAGS) $(LDFLAGS) cernlib_root_adapted/erfc.c -o cernlib_root_adapted/liberfc_sincos.so -DSINCOS




clean:
	rm -f cernlib_c/*.so cernlib_f90/*.so cernlib_root_adapted/*.so
	rm -f cernlib_rev_c/*.so

