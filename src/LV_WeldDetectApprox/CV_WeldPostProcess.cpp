/**
* \file   CV_WeldPostProcess.cpp
* \brief	Definitions for basic OpenCV based method related to WeldDetection
* \author  PB
* \date    2014/10/25
*/

#include "LV_WeldDetectApprox/CV_WeldPostProcess.h"

/**
* \brief Fills shape of the weld line
* \details Basing on data returned from weld detection procedure performs filling the weld shape defined as set of edge points.
* \param[in] _weldpos Vector of \c C_WeldPos classes contianing positions of upper, lower and middle point of weld in single column of image
* \param[in] _lineOK Vector validating data in \c _weldpos
* \param[out] image Image of weld. This struct must be initialized outside of the \c fillWeldShape and have proper size equal to size of the radiogram
* \retval \c void
* \author PB
* \date 2014/10/30
* \exception Can throw std::invalid_argument if input image is empty
*/
void fillWeldShape(const vector<C_WeldPos>* _weldpos, const std::vector<bool>* _lineOK, cv::Mat& image)
{
	if(image.empty())
	{
		_RPT0(_CRT_ASSERT, "Input image is empty - it must be allocated first");
		throw std::invalid_argument("Input image is empty - it must be allocated first");
	}

	bool data;
	C_WeldPos wp;
	vector<cv::Point> weldShape;	// zarys spawu
	unsigned int ncols, nrows;

	ncols = image.cols;
	nrows = image.rows;

	// pierwszy punkt x=0, y=yG
	wp = _weldpos->at(0);
	weldShape.push_back(Point(0, static_cast<int>(wp.G.getY())));
	for(size_t l=0;l<_lineOK->size();++l)
	{
		data = _lineOK->at(l);
		if(data)				// dobra linia
		{
			wp = _weldpos->at(l);
			// punkty po kolei
			weldShape.push_back(Point(static_cast<int>(wp.G.getX()),static_cast<int>(wp.G.getY())));		// punkty górne (zgodnie ze wskazówkami zegara
		}
	}
	// ostatni na górze
	weldShape.push_back(Point(ncols-1, static_cast<int>(wp.G.getY())));
	// punkty dolne od ty³u
	// pierwszy punkt na dole od prawej x=ncols-1, y=yD
	wp = _weldpos->at(_lineOK->size()-1);
	weldShape.push_back(Point(ncols-1, static_cast<int>(wp.D.getY())));
	for(long l=_lineOK->size()-1; l>=0; --l)
	{
		data = _lineOK->at(l);
		if(data)
		{
			wp = _weldpos->at(l);
			weldShape.push_back(Point(static_cast<int>(wp.D.getX()), static_cast<int>(wp.D.getY())));
		}
	}
	// ostatni po lewej na dole
	weldShape.push_back(Point(0, static_cast<int>(wp.D.getY())));
	vector<vector<Point>> fillContAll;
	fillContAll.push_back(weldShape);
	cv::fillPoly( image, fillContAll, cv::Scalar(65535));
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