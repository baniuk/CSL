/**
 * \file PCA.cpp
 * \brief Implementation of PCA rutine based on Lapack
 * \author PB
 * \date 2015/02/03
 */
#include "LV_Features/PCA.h"
#include <f2c.h>
#include <blaswrap.h>
#include <clapack.h>

void PCA(double* a,integer Na,integer LDA,double *D)
{
	char uplo = 'U';		// Upper triangle of A is stored
	double *E = new double[Na-1];	// The off-diagonal elements of the tridiagonal matrix T: E(i) = A(i,i+1) if UPLO = 'U', E(i) = A(i+1,i) if UPLO = 'L'.
	double *TAU = new double[Na-1];	// The scalar factors of the elementary reflectors
	double *WORK_dsytrd;
	double worktmp;
	integer LWORK = -1;
	integer INFO;
	char compz = 'V';		// Compute eigenvalues and eigenvectors of the tridiagonal matrix.  Z is initialized to the identity matrix. 
	integer LDZ = Na;
	double *Z = a;
	double *WORK_dsteqr = new double[2*Na-2];

	dsytrd_(&uplo, &Na, a, &LDA, D, E, TAU, &worktmp, &LWORK, &INFO);
	
	LWORK = (integer)worktmp;
	WORK_dsytrd = new double[LWORK];
	dsytrd_(&uplo, &Na, a, &LDA, D, E, TAU, WORK_dsytrd, &LWORK, &INFO);
	dorgtr_(&uplo, &Na, a, &LDA, TAU, WORK_dsytrd, &LWORK, &INFO);

	dsteqr_(&compz, &Na, D, E, Z, &LDZ, WORK_dsteqr, &INFO);

	SAFE_DELETE(E);
	SAFE_DELETE(TAU);
	SAFE_DELETE(WORK_dsytrd);
	SAFE_DELETE(WORK_dsteqr);
}