#ifndef KOD_H
#define KOD_H
#include"Interval.h"

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <complex>
#include <cmath>

typedef std::complex<long double> Complex;
typedef std::vector<Complex> cplxvector;
typedef std::vector<cplxvector> cplxmatrix;

typedef interval_arithmetic::Interval<long double> inter;
typedef std::complex<inter> Complexp;
typedef std::vector<Complexp> cplxvectorp;
typedef std::vector<cplxvectorp> cplxmatrixp;

void complexmatrix(int n, cplxmatrix& a, cplxvector& x, int& st);
void complexmatrixp(int n, cplxmatrixp& a, cplxvectorp& x, int& st);

#endif // KOD_H
