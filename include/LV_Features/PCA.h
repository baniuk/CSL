/**
 * \file PCA.h
 * \brief Defines Lapack based function used in Features.cpp
 * \author PB
 * \date 2015/02/03
 */
#ifndef PCA_h__
#define PCA_h__

#include <stddef.h>
typedef long int integer;

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

/// Evaluates PCA rutine
void PCA(double* a, integer Na, integer LDA, double *D);

#endif // PCA_h__
