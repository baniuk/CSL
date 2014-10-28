/**
* \file   CV_WeldPostProcess.cpp
* \brief	Definitions for basic OpenCV based method related to WeldDetection
* \author  PB
* \date    2014/10/25
*/

#include "LV_WeldDetectApprox/CV_WeldPostProcess.h"

/**
* \brief Wype³nia kszta³t spawu
* \details
* \param[in]
* \param[out]
d
* \retval \c retCode
* \return
* \author PB
* \date 2014/10/28
* \warning
*/void fillWeldShape(UINT16** data, unsigned int& rows, unsigned int& cols)
{
}

/**
* \brief Konvertuje obiekt \c cv::Mat do surowego wskaŸnika
* \details Allokuje pamiêæ, któr¹ caller musi zwolniæ
* \param[in] image Obraz wejœciowy
* \param[out] p_raw WskaŸnik do obrazu wyjœciowego allokowanego przez funkcjê
* \param[out] rows liczba wierszy obrazów
* \param[out] cols liczba kolumn obrazów
* \retval \c retCode
* \return LV_FAIL if image bigger than UINT16 on any dimmension
* \author PB
* \date 2014/10/28
* \warning Mximum image dimmensions less than UINT16
*/
retCode getRawPointer(const cv::Mat& image, unique_ptr<UINT16[]>& p_raw, UINT16& rows, UINT16& cols)
{
	unsigned int _rows, _cols;
	_rows = image.rows;
	_cols = image.cols;
	if (_rows>USHRT_MAX || _cols>USHRT_MAX)
		return LV_FAIL;
	else
	{
		rows = _rows;
		cols = _cols;
	}
	p_raw.reset(new UINT16[rows*cols]);
	MatConstIterator_<UINT16> it, end;
	size_t i=0;
	for(it = image.begin<UINT16>(), end = image.end<UINT16>(); it!=end; ++it )
	{
		p_raw[i++] = (UINT16)(*it);
	}
	return LV_OK;
}