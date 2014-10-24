/**
* \file ParamEstimation.cpp
* \brief Estimates parameters for C_LineWeldApprox::setDefaultParams
* \author PB
* \date 2014/10/24
*/

#include "LV_WeldDetectApprox/ParamEstimation.h"
#include "LV_WeldDetectApprox/C_Matrix_Container.h"

using namespace std;
/**
* \brief Calculates initial parameters for C_LineWeldApprox::setDefaultParams method
* \details Basing on original image it calculates \c A and \E parameters using median value for start column and its maximum. Assumes that most of data on
* colums belongs to background and thus median returns these values.
* \param[in] data input image
* \param[in] cols number of columns of input image
* \param[in] rows number of rows of input image
* \param[in] start_column column of \c data which \A and \E will be evaluated for
* \param[out] A parameter \c A of Gauss
* \param[out] E parameter \c E of linera function
* \retval \c void
* \author PB
* \date 2014/10/24
* \see C_LineWeldApprox::setDefaultParams
*/
void ParamEstimation(const double* data, unsigned int cols, unsigned int rows, unsigned int start_column, double& A, double& E )
{
	vector<double> column; // kolumna obrazu
	size_t i;
	// wycinanie kolumny - dane u³o¿one rzedami
	for(i = start_column; i < rows*cols; i+=cols)
		column.push_back(data[i]);

	// maksimum
	auto biggest = max_element(column.cbegin(),column.cend());
	// parameter A - amplituda
	A = *biggest;
	// mediana
	double median = getMedian(column);
	E = median;
	A-=median;
}

/**
* \brief Evaluates median on vector of doubles
* \param[in] input vector to evaluate median from
* \return Median value
* \retval \c double
* \author PB
* \date 2014/10/24
* \todo Move in future to separate library of maths methods
*/
double getMedian(vector<double>& input)
{
	double median;
	size_t size = input.size();

	sort(input.begin(), input.end());

	if (size  % 2 == 0)
	{
		median = (input[size / 2 - 1] + input[size / 2]) / 2;
	}
	else
	{
		median = input[size / 2];
	}

	return median;
}