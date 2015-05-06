//#include "stdafx.h"
#include <stdint.h>

extern "C" __declspec(dllexport) UINT16 CV_brightness(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, double alpha, int beta);
extern "C" __declspec(dllexport) UINT16 CV_convolve(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype);
extern "C" __declspec(dllexport) UINT16 CV_morphpology(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int operation, int kerneltype, int kernsize);
extern "C" __declspec(dllexport) UINT16 CV_watershed(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols);
extern "C" __declspec(dllexport) UINT16 CV_erosion(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype, int kernelsize);
extern "C" __declspec(dllexport) UINT16 CV_dilation(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int kerneltype, int kernelsize);
extern "C" __declspec(dllexport) UINT16 CV_smooth(UINT16* inp, UINT16* out, UINT16 rows, UINT16 cols, int type, int kernellength);
