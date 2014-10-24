/**
* \file ParamEstimation.h
* \brief Header for Param estimation methods
* \author PB
* \date 2014/10/24
*/

#ifndef ParamEstimation_h__
#define ParamEstimation_h__

#include <vector>
#include <algorithm>

/// Estimates initial parameters for weld detection using input image
void ParamEstimation(const double* data, unsigned int cols, unsigned int rows, unsigned int start_column, double& A, double& E);
/// Evaluates median on vector
double getMedian(std::vector<double>& input);
#endif // ParamEstimation_h__