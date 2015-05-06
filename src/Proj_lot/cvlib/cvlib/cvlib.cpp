// cvlib.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "cvlib.h"
#include "definitions.h"
#include "setError\setError.h"
#include "errordef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/core/core_c.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <atlstr.h>
//#include <strsafe.h>

using namespace cv;
using namespace std;

/*! \file cvlib.cpp
	\brief Plik z funkcjami na potrzeby wytworzenia biblioteki cvlib.dll dla LabView
	\details Dostêpne s¹ nastêpuj¹ce funkcje:<br/>
	retCode LV_Sobel(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc);<br/>
	funkcja dla filtru Sobel-a<br/>
    retCode LV_Scharr(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc);<br/>
	funkcja dla filtru Scharr-a<br/>
    retCode LV_Otsu(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,char *errDesc);<br/>
	funkcja dla segmentacji Otsu<br/>
    retCode LV_Mix(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,char *errDesc);<br/>
	funkcja dla dedykowanej segmentacji Mix<br/>
	retCode getOutSize(char *plik,UINT16* rows,UINT16 *cols,char *errDesc);<br/>
	funkcja pobieraj¹ca wielkoœæ pliku<br/>
    retCode getOut_resize(int rows,int cols,int procx,int procy,int *outx, int *outy, char *errDesc);<br/>
	funkcja zwracj¹ca rozmiar wierszy oraz kolumn przed wykonaniem operacji zmiany rozmiaru<br/>
    retCode LV_resize(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int procx,int procy,char *errDesc);<br/>
	funckcja, która zmienia rozmiar obrazu<br/>
	\author LM
*/




// Function header
void thresh_callback(int, void* );

/* @function boxes */
void boxes(char *plik)
{
  Mat src; Mat src_gray;
  int thresh = 178;
  int max_thresh = 255;
  RNG rng(12345);
  // Load source image and convert it to gray
  src = imread( plik, 1 );

  // Convert image to gray and blur it
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  // Create Window
  char* source_window = "Source";
  namedWindow( source_window, WINDOW_AUTOSIZE );
  imshow( source_window, src );

  Mat threshold_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  // Detect edges using Threshold
  threshold( src_gray, threshold_output, thresh, 255, THRESH_BINARY );
  // Find contours
  findContours( threshold_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );

  // Find the rotated rectangles and ellipses for each contour
  vector<RotatedRect> minRect( contours.size() );
  vector<RotatedRect> minEllipse( contours.size() );

  for( unsigned int i = 0; i < contours.size(); i++ )
     { minRect[i] = minAreaRect( Mat(contours[i]) );
       if( contours[i].size() > 5 )
         { minEllipse[i] = fitEllipse( Mat(contours[i]) ); }
     }

  // Draw contours + rotated rects + ellipses
  Mat drawing = Mat::zeros( threshold_output.size(), CV_8UC3 );
  for( unsigned int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       // contour
       drawContours( drawing, contours, i, color, 1, 8, vector<Vec4i>(), 0, Point() );
       // ellipse
       ellipse( drawing, minEllipse[i], color, 2, 8 );
       // rotated rectangle
       Point2f rect_points[4]; minRect[i].points( rect_points );
       for( int j = 0; j < 4; j++ )
          line( drawing, rect_points[j], rect_points[(j+1)%4], color, 1, 8 );
     }

  // Show in a window
  namedWindow( "Contours", WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );

  //createTrackbar( " Threshold:", "Source", &thresh, max_thresh, thresh_callback );
  //thresh_callback( 0, 0 );
  
}

/** @function getOutSize
	\brief funkcja ma zwróciæ iloœæ wierszy i kolumn dla pliku graficznego
	\param [in] plik - nazwa pliku werjœciowego
	\param [out] rows - zwraca iloœæ wierszy w pliku graficznym
	\param [out] cols - zwraca iloœæ kolumn w pliku graficznym
	\return zwraca typ retCode, LV_OK - powodzenie, LV_FAIL - nieudane dzia³anie, brak wyniku
	\author LM
*/
retCode getOutSize(char *plik,UINT16* rows,UINT16 *cols,char *errDesc)
{
  try
  {
	Mat obraz = imread(plik);
	if(obraz.empty()) return setError::throwError("cvlib.dll::Bledny plik graficzny." , &errDesc);
	*rows = obraz.rows;
	*cols = obraz.cols;

  }catch(Exception &e)
  {
	  std::string tekst = "cvlib.dll::";
	  std::string tekst1 = e.what();
	  std::string tekst2 = tekst + tekst1;
	  return setError::throwError(tekst2.c_str() , &errDesc);
  }
  return LV_OK;
}


/** @function LV_Sobel
	\brief funkcja generuje filtr Sobela z obrazu wejœciowego na obraz wyjœciowy
	\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
	\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
	\param [in] dx - zmienna dx np.1
	\param [in] dy - zmienna dy np.0
	\param [out] errDesc - wskaŸnik na tablicê znaków - opis przekazywanego b³êdu 
	\return zwraca typ retCode, LV_OK - powodzenie, LV_FAIL - nieudane dzia³anie, brak wyniku
	\author LM
*/
retCode LV_Sobel(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc)
{
  //byte *dane3 = new byte[rows * cols];
  //UINT16 *uptr = (UINT16*)dane3;
  //memcpy(dane3,src1.data,src1.total() * src1.elemSize());
  
  /*
  CString string;
  string.LoadStringW(IDS_LVMIX_ERROR1);
  cout << "Load String: " << string.GetString() << "\n";
  */
  
  try
  {
   Mat obraz = Mat(rows,cols,CV_8UC3,inp).clone();
   Mat obraz1;
   Sobel(obraz, obraz1, CV_32F, dx, dy, 3 /*CV_SCHARR*/);
   obraz1.convertTo(obraz1,CV_8UC3);
   memcpy(out,obraz1.data,obraz1.total() * obraz1.elemSize());
  }catch(Exception &e)
  {
	  //return IDS_LVMIX_ERROR1;
	  
	  std::string tekst = "cvlib.dll::";
	  std::string tekst1 = e.what();
	  std::string tekst2 = tekst + tekst1; 
	  return setError::throwError(tekst2.c_str() , &errDesc);
	  
  }
  return LV_OK;
  //return 0;
}

/** @function LV_Scharr
	\brief funkcja generuje filtr Scharr-a z obrazu wejœciowego na obraz wyjœciowy
	\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
	\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
	\param [in] dx - zmienna dx np.1
	\param [in] dy - zmienna dy np.0
	\param [out] errDesc - wskaŸnik na tablicê znaków - opis przekazywanego b³êdu 
	\return zwraca typ retCode, LV_OK - powodzenie, LV_FAIL - nieudane dzia³anie, brak wyniku
	\author LM
*/
retCode LV_Scharr(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc)
{
  try
  {
  Mat obraz = Mat(rows,cols,CV_8UC3,inp).clone();
  Mat obraz1;
  Scharr(obraz, obraz1, CV_32F, dx, dy, 3 /*CV_SCHARR*/);
  obraz1.convertTo(obraz1,CV_8UC3);
  memcpy(out,obraz1.data,obraz1.total() * obraz1.elemSize());
  }catch(Exception &e)
  {
	  std::string tekst = "cvlib.dll::";
	  std::string tekst1 = e.what();
	  std::string tekst2 = tekst + tekst1;
	  return setError::throwError(tekst2.c_str() , &errDesc);
  }
  return LV_OK;
}


/** @function LV_Sobel
	\brief funkcja generuje segmentacjê(progowanie) Otsu z obrazu wejœciowego na obraz wyjœciowy
	\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
	\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
	\param [out] errDesc - wskaŸnik na tablicê znaków - opis przekazywanego b³êdu 
	\return zwraca typ retCode, LV_OK - powodzenie, LV_FAIL - nieudane dzia³anie, brak wyniku
	\author LM
*/
retCode LV_Otsu(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,char *errDesc)
{
  try
  {
	Mat obraz = Mat(rows,cols,CV_8UC3,inp).clone();
	Mat obraz1,obraz2,obraz3;
	
	cvtColor( obraz, obraz1, CV_RGB2GRAY );
	threshold(obraz1, obraz2, 0, 255, THRESH_BINARY | THRESH_OTSU);
	cvtColor(obraz2,obraz3,CV_GRAY2RGB);
	//cout << "Info z LV_Watershed: obraz3.total = " << obraz3.total() << " obraz3.elemSize = " << obraz3.elemSize() << "\n";

	//memcpy(out,obraz2.data,obraz2.total() * obraz2.elemSize());
	memcpy(out,obraz3.data,obraz3.total() * obraz3.elemSize());

  }catch(Exception &e)
  {
	  std::string tekst = "cvlib.dll::";
	  std::string tekst1 = e.what();
	  std::string tekst2 = tekst + tekst1;
	  return setError::throwError(tekst2.c_str() , &errDesc);
  }
  return LV_OK;


}

// operacja mieszana: rozjaœnianie + rozmywanie typy medianowego + segmentacja
/** @function LV_Mix
	\brief funkcja generuje dedykowan¹ segmentacjê z obrazu wejœciowego na obraz wyjœciowy
	\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [in] rows - ilosc wierszy w obrazie wejœciowym i wyjœciowym
	\param [in] cols - ilosc wierszy w obrazie wejœciowym i wyjœciowym
	\param [out] errDesc - wskaŸnik na tablicê znaków - opis przekazywanego b³êdu 
	\return zwraca typ retCode, LV_OK - powodzenie, LV_FAIL - nieudane dzia³anie, brak wyniku
	\author LM
*/
retCode LV_Mix(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,char *errDesc)
{
  try
  {
    Mat image = Mat(rows,cols,CV_8UC3,inp).clone();

	double alpha; /*< Simple contrast control */  
    int beta;  /*< Simple brightness control */
	Mat new_image = Mat::zeros( image.size(), image.type() );
	alpha = 1.17;
    beta = 12;

     // Do the operation new_image(i,j) = alpha*image(i,j) + beta
    for( int y = 0; y < image.rows; y++ )
       { for( int x = 0; x < image.cols; x++ )
           { for( int c = 0; c < 3; c++ )
              {
      new_image.at<Vec3b>(y,x)[c] =
         saturate_cast<uchar>( alpha*( image.at<Vec3b>(y,x)[c] ) + beta );
             }
           }
       }
   Mat new_image1;
   int MAX_KERNEL_LENGTH = 5;
   for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
      { medianBlur ( new_image, new_image1, i ); }

   Mat new_image2;
   threshold(new_image1,new_image2,216,255,3);
   memcpy(out,new_image2.data,new_image2.total() * new_image2.elemSize());
     
  }catch(Exception &e)
  {
	  std::string tekst = "cvlib.dll::";
	  std::string tekst1 = e.what();
	  std::string tekst2 = tekst + tekst1;
	  return setError::throwError(tekst2.c_str() , &errDesc);
  }
  return LV_OK;

}

//badanie wielkosci
// parametry: wejscie
//			  rows - iloœæ wierszy (os Y)
//			  cols - iloœæ kolumn (os X)
//            procx - ile procent zmienic w osi X
//			  procy - ile procent zmienic w osi y
// parametry: wyjscie
//			  outx - wielkosc wyjsciowa w osi x
//			  outy - wielkosc wyjsciowy w osi y
/** @function getOut_resize
	\brief funkcja generuje wielkoœæ obrazu (x,y) przed wykonaniem funkcji LV_Resize
	\param [in] rows - ilosc wierszy w obrazie wejœciowym
	\param [in] cols - ilosc wierszy w obrazie wejœciowym
	\param [in] procx - procentowy wskaŸnik zmiany obrazu wzd³ó¿ osi X np. 150 oznacza powiêkszenie o 50%
	\param [in] procy - procentowy wskaŸnik zmiany obrazu wzd³ó¿ osi Y np. 150 oznacza powiêkszenie o 50%
	\param [out] outx - iloœæ wierszy wzd³ó¿ osi X w obrazie docelowym
	\param [out] outy - iloœæ wierszy wzd³ó¿ osi Y w obrazie docelowym
	\param [out] errDesc - wskaŸnik na tablicê znaków - opis przekazywanego b³êdu 
	\return zwraca typ retCode, LV_OK - powodzenie, LV_FAIL - nieudane dzia³anie, brak wyniku
	\author LM
*/
retCode getOut_resize(int rows,int cols,int procx,int procy,int *outx, int *outy, char *errDesc)
{
 try
 {
  double px = (double)procx;
  double py = (double)procy;

  int x = (int)( (px/100) * cols);
  int y = (int)( (py/100) * rows); 

  *outx = x;
  *outy = y;

 }catch(Exception &e)
  {
	  std::string tekst = "cvlib.dll::";
	  std::string tekst1 = e.what();
	  std::string tekst2 = tekst + tekst1;
	  return setError::throwError(tekst2.c_str() , &errDesc);
  }
  return LV_OK;
}

//powiazana z getOut_resize, ktora zwraca ilosc wierszy w pionie i w poziomie
/** @function LV_resize
	\brief funkcja generuje powiêkszony obraz z obrazu wejœciowego na obraz wyjœciowy, konieczne uprzednie u¿ycie getOut_resize w celu uzyskania wielkoœci X,Y docelowego obrazu
	\param [in] inp - wskaŸnik na obraz wejœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [out] out - wskaŸnik na obraz wyjœciowy (musi byæ zarezerwowany przed u¿yciem funkcji)
	\param [in] rows - ilosc wierszy w obrazie wejœciowym
	\param [in] cols - ilosc wierszy w obrazie wejœciowym
	\param [in] procx - procentowy wskaŸnik zmiany obrazu wzd³ó¿ osi X np. 150 oznacza powiêkszenie o 50%
	\param [in] procy - procentowy wskaŸnik zmiany obrazu wzd³ó¿ osi Y np. 150 oznacza powiêkszenie o 50%
	\param [out] errDesc - wskaŸnik na tablicê znaków - opis przekazywanego b³êdu 
	\return zwraca typ retCode, LV_OK - powodzenie, LV_FAIL - nieudane dzia³anie, brak wyniku
	\author LM
*/

retCode LV_resize(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int procx,int procy,char *errDesc)
{
 try
 {
  double px = (double)procx;
  double py = (double)procy;

  int x = (int)( (px/100) * cols);
  int y = (int)( (py/100) * rows); 

  Mat obraz = Mat(rows,cols,CV_8UC3,inp).clone();
  Mat obraz1;
  resize(obraz,obraz1,Size(x,y));
  //cout << "Wielkosc X,Y wg obliczen z LV_resize: X=" << x << " Y=" << y << "\n";
  //cout << "Wielkosc X,Y po resize z LV_resize: X=" << obraz1.cols << " Y=" << obraz1.rows << "\n";
  //cout << "LV_Resize: obraz.elemSize = " << obraz.elemSize() << " obraz1.elemSize = " << obraz1.elemSize() << "\n";

  memcpy(out,obraz1.data,x * y * obraz1.elemSize());


  }catch(Exception &e)
  {
	  std::string tekst = "cvlib.dll::";
	  std::string tekst1 = e.what();
	  std::string tekst2 = tekst + tekst1;
	  return setError::throwError(tekst2.c_str() , &errDesc);
  }
  return LV_OK;
}

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CcvlibApp

BEGIN_MESSAGE_MAP(CcvlibApp, CWinApp)
END_MESSAGE_MAP()


// CcvlibApp construction

CcvlibApp::CcvlibApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
//	cout << "Wchodze do biblioteki cvlib.dll\n";
}


// The one and only CcvlibApp object

CcvlibApp theApp;


// CcvlibApp initialization

BOOL CcvlibApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}
