/**
* \file   CV_WeldPostProcess.cpp
* \brief	Definitions for basic OpenCV based method related to WeldDetection
* \author  PB
* \date    2014/10/25
*/

#include "LV_WeldDetectApprox/CV_WeldPostProcess.h"

/**
* \brief Wype�nia kszta�t spawu
* \details
* \param[in]
* \param[out]
d
* \retval \c retCode
* \return
* \author PB
* \date 2014/10/28
* \warning
*/
void fillWeldShape(const vector<C_WeldPos>* _weldpos, const std::vector<bool>* _lineOK, UINT16 nrows, UINT16 ncols)
{
	bool data;
	C_WeldPos wp;
	vector<cv::Point> weldShape;	// zarys spawu

	Mat image(nrows,ncols, CV_16U, Scalar(0)); // obraz wynikowy z wype�nionym spawem

	for(size_t l=0;l<_lineOK->size();++l)
	{
		data = _lineOK->at(l);
		if(data)				// dobra linia
		{
			wp = _weldpos->at(l);
			// punkty po kolei
			weldShape.push_back(Point(wp.G.getX(), wp.G.getY()));		// punkty g�rne (zgodnie ze wskaz�wkami zegara
		}
	}
	// punkty dolne od ty�u
	for(size_t l=_lineOK->size()-1; l>=0; --l)
	{
		data = _lineOK->at(l);
		if(data)
		{
			wp = _weldpos->at(l);
			weldShape.push_back(Point(wp.D.getX(), wp.D.getY()));
		}
	}

	vector<vector<Point>> fillContAll;
	fillContAll.push_back(weldShape);
	cv::fillPoly( image, fillContAll, cv::Scalar(65535));
	cv::imwrite("filled_weld.png", image);
}

/**
* \brief Konvertuje obiekt \c cv::Mat do surowego wska�nika
* \details Allokuje pami��, kt�r� caller musi zwolni�
* \param[in] image Obraz wej�ciowy
* \param[out] p_raw Wska�nik do obrazu wyj�ciowego allokowanego przez funkcj�
* \param[out] rows liczba wierszy obraz�w
* \param[out] cols liczba kolumn obraz�w
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