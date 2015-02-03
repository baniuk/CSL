/**
* \file    LV_Features.h
* \brief	Headers and definitions for LV_Features.dll
* \author  PB
* \date    2015/02/03
* \todo Finish and move definitions here
*/

#ifndef LV_Features_h__
#define LV_Features_h__

#include <inttypes.h>
#include "LV_Features/C_Matrix_Container.h"
#include "LV_Features/C_Image_Container.h"
#include "LV_Features/PCA.h"
#include "definitions.h"

void  func(void *data);
void cov(C_Matrix_Container* X, C_Matrix_Container* Y);
unsigned int unique(C_Matrix_Container* input, C_Matrix_Container* licznosc);
BOOL isintable(double* tab, double val, unsigned int tab_size);
void RemoveVal(C_Matrix_Container* input, double val);
void GetMinMax(double* data, double& min, double& max, unsigned int ile);
void CutImage(C_Image_Container*im, C_Image_Container *out, double *xc, double *yc, unsigned int ile);
BOOL MatrixMulti(C_Matrix_Container* in1, C_Matrix_Container* in2, C_Matrix_Container* out);

void PB_feat1(unsigned int current_flaw, unsigned int current_flaw_offset, C_Image_Container *res, C_Matrix_Container *x_coord, C_Matrix_Container *y_coord, unsigned int current_flaw_size, double* out1, double* out2, double* out6, double* out7_1, double* out7_2, double* out7_3, double* out7_4, double* out7_5, double* out8, double* out9);
void PB_feat2(unsigned int current_flaw, unsigned int current_flaw_offset, C_Image_Container *res, C_Image_Container *org, C_Matrix_Container *x_coord, C_Matrix_Container *y_coord, unsigned int current_flaw_size,
	double Mout[]);
void PB_texture(unsigned int current_flaw, unsigned int current_flaw_offset, C_Image_Container *org, C_Matrix_Container *x_coord, C_Matrix_Container *y_coord, unsigned int current_flaw_size, double* out1, double* out2);
double PB_stdcirc(C_Image_Container *in, double gx, double gy);
double PB_getIndexNumber(C_Image_Container *res);
void featuresMC(C_Image_Container* BwIm, C_Image_Container* BwPer, double Area, double Perimeter, double* Cx, double* Cy, double *Width, double *Length, double *Elongation, double *Rectangulity, double *Compactness, double *Iacf);

unsigned long LN_Area(C_Image_Container*);
double LN_Perimeter(C_Image_Container *in, C_Image_Container *out);
double LN_wspMal(double A, double p);
double LN_wspBB(C_Image_Container *in, double A, double Gx, double Gy);
double LN_wspDan(C_Image_Container *in, double A);
double LN_wspHar(C_Image_Container *in, double gx, double gy, double ilePikseli);
void LN_morf(C_Matrix_Container* F, int M[3][3], bool bit);
void LN_CenterOfGravity(C_Image_Container *in, double A, double *Gx, double *Gy);

uint32_t Features(C_Image_Container& original, C_Image_Container& indexed, C_Image_Container& bw,
	C_Matrix_Container& out,
	char NUMOFPROC,
	char deb);

#endif // LV_Features_h__


