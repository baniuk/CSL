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
template<typename T>
void ParamEstimation(const T* data, unsigned int cols, unsigned int rows, unsigned int start_column, T& A, T& E )
{
	vector<T> column; // kolumna obrazu
	size_t i;
	// wycinanie kolumny - dane u³o¿one rzedami
	for(i = start_column; i < rows*cols; i+=cols)
		column.push_back(data[i]);

	// maksimum
	auto biggest = max_element(column.cbegin(),column.cend());
	// parameter A - amplituda
	A = *biggest;
	// mediana
	T median = getMedian(column);
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
template<typename T>
T getMedian(vector<T>& input)
{
	T median;
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
#endif // ParamEstimation_h__