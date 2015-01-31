#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/core/core_c.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <strsafe.h>
#include "definitions.h"


typedef retCode (*LV_Sobel)(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc);
typedef retCode (*LV_Scharr)(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc);
typedef retCode (*LV_Otsu)(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,char *errDesc);

typedef retCode (*getOutSize)(char *plik,UINT16* rows,UINT16 *cols,char *errDesc);
typedef retCode (*getOut_resize)(int rows,int cols,int procx,int procy,int *outx, int *outy, char *errDesc);
typedef retCode (*LV_resize)(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int procx,int procy,char *errDesc);

using namespace cv;
using namespace std;


/** @function main */
int main( int argc, char** argv )
{
  Mat src;
 if(argc < 2) { std::cout << argv[0] << " [nazwa_pliku_graficznego]\n"; return (-1); }
 src = imread(argv[1]); // Read the file

 if(src.empty()) { cout << "Bledny plik graficzny.\n"; return (-1); }

 namedWindow( "Oryginal", WINDOW_AUTOSIZE ); 
 imshow( "Oryginal", src );

 byte *dst = new byte[src.total() * src.elemSize()];
 byte *dst1 = new byte[src.total() * src.elemSize()];
 byte *dst2 = new byte[src.total() * src.elemSize()];
 
 HINSTANCE hDLL;               // Handle to DLL
 LV_Sobel lpfnDllFunc1;    // Function pointer
 LV_Scharr lpfnDllFunc2;    // Function pointer
 LV_Otsu lpfnDllFunc3;    // Function pointer
 retCode powrot;



hDLL = LoadLibraryW((LPCWSTR)L"cvlib.dll");
if (hDLL != NULL)
{
   
   //funkcja LV_Sobel
   lpfnDllFunc1 = (LV_Sobel)GetProcAddress(hDLL,"LV_Sobel");
   if (!lpfnDllFunc1)
   {
      // handle the error
      std::cout << "BLAD LADOWANIA FUNKCJI LV_Sobel Z biblioteki DLL cvlib.dll";
	  FreeLibrary(hDLL);
	  return -1;
   }
   else
   {
        // call the function
	  char blad[2000];
	  
      powrot = lpfnDllFunc1((UINT16*)src.data,(UINT16*)dst,src.rows,src.cols,1,0,blad);
	  if(powrot==LV_FAIL)
	  {
	    cerr << "Blad wykonywania siê funkcji LV_Sobel:\n";
		cerr << blad << "\n\n";
		return(-1);
	  }

	  
	  Mat wynik = Mat(src.rows,src.cols,CV_8UC3,dst).clone();
	  namedWindow( "Sobel", WINDOW_AUTOSIZE ); 
      imshow( "Sobel", wynik );

	  

	//  std::cout << "Wynik: " << uReturnVal;
   }

   //funkcja LV_Scharr
   lpfnDllFunc2 = (LV_Scharr)GetProcAddress(hDLL,"LV_Scharr");
   if (!lpfnDllFunc1)
   {
      // handle the error
      std::cout << "BLAD LADOWANIA FUNKCJI LV_Scharr Z biblioteki DLL cvlib.dll";
	  FreeLibrary(hDLL);
	  return -1;
   }
   else
   {
        // call the function
	  char blad[2000];
      powrot = lpfnDllFunc2((UINT16*)src.data,(UINT16*)dst1,src.rows,src.cols,0,1,blad);
	  if(powrot==LV_FAIL)
	  {
	    cerr << "Blad wykonywania siê funkcji LV_Scharr:\n";
		cerr << blad << "\n\n";
		return(-1);
	  }
	  
	  Mat wynik1 = Mat(src.rows,src.cols,CV_8UC3,dst1).clone();
	  namedWindow( "Scharr", WINDOW_AUTOSIZE ); 
      imshow( "Scharr", wynik1 );


	//  std::cout << "Wynik: " << uReturnVal;
   }

   lpfnDllFunc3 = (LV_Otsu)GetProcAddress(hDLL,"LV_Otsu");
   if (!lpfnDllFunc3)
   {
      // handle the error
      std::cout << "BLAD LADOWANIA FUNKCJI LV_Otsu Z biblioteki DLL cvlib.dll";
	  FreeLibrary(hDLL);
	  return -1;
   }
   else
   {
        // call the function
	  char blad[2000];
      powrot = lpfnDllFunc3((UINT16*)src.data,(UINT16*)dst2,src.rows,src.cols,blad);
	  if(powrot==LV_FAIL)
	  {
	    cerr << "Blad wykonywania siê funkcji LV_Otsu:\n";
		cerr << blad << "\n\n";
		return(-1);
	  }
	  
	  Mat wynik2 = Mat(src.rows,src.cols,CV_8UC3,dst2).clone();
	  namedWindow( "Otsu", WINDOW_AUTOSIZE ); 
      imshow( "Otsu", wynik2 );


	//  std::cout << "Wynik: " << uReturnVal;
   }

   //pomiar wielkosci pliku graficznego
   getOutSize lpfnDllFunc4a;
   UINT16 wiersze,kolumny;
   lpfnDllFunc4a = (getOutSize)GetProcAddress(hDLL,"getOutSize");
   if (!lpfnDllFunc4a)
   {
      // handle the error
      std::cout << "BLAD LADOWANIA FUNKCJI getOutSize Z biblioteki DLL cvlib.dll";
	  FreeLibrary(hDLL);
	  return -1;
   }else
   {
	   char blad[2000];
	   powrot = lpfnDllFunc4a(argv[1],&wiersze,&kolumny,blad);
	   if(powrot==LV_FAIL)
	   {
	    cerr << "Blad wykonywania siê funkcji getOutSize:\n";
		cerr << blad << "\n\n";
		return(-1);
	   }
   }


   getOut_resize lpfnDllFunc4;    // Function pointer
   int resizex = 250,resizey = 250;
   int wynx,wyny;
   lpfnDllFunc4 = (getOut_resize)GetProcAddress(hDLL,"getOut_resize");
   if (!lpfnDllFunc4)
   {
      // handle the error
      std::cout << "BLAD LADOWANIA FUNKCJI getOut_resize Z biblioteki DLL cvlib.dll";
	  FreeLibrary(hDLL);
	  return -1;
   }
   else
   {
	  char blad[2000];
      //do zmiennych wynx, wyny przypisywany jest rozmiar nowego obrazu	  
	  powrot = lpfnDllFunc4(wiersze,kolumny,resizex,resizey,&wynx,&wyny,blad);
	  if(powrot==LV_FAIL)
	  {
	    cerr << "Blad wykonywania siê funkcji getOut_resize:\n";
		cerr << blad << "\n\n";
		return(-1);
	  }
	  //cout << "Wynik getOut_resize: procentx = " << resizex << " procenty = " << resizey << "procenty = " << resizey << " X = " << wynx << " Y = " << wyny << "\n";

   }

   


   LV_resize lpfnDllFunc5;    // Function pointer
   lpfnDllFunc5 = (LV_resize)GetProcAddress(hDLL,"LV_resize");
   byte* dst3 = new byte[wynx * wyny * src.elemSize()];
   //cout << "Main: src.elemSize = " << src.elemSize() ;
   if (!lpfnDllFunc5)
   {
      // handle the error
      std::cout << "BLAD LADOWANIA FUNKCJI getOut_resize Z biblioteki DLL cvlib.dll";
	  FreeLibrary(hDLL);
	  return -1;
   }
   else
   {
	   char blad[2000];
	   powrot = lpfnDllFunc5((UINT16*)src.data,(UINT16*)dst3,src.rows,src.cols,resizex,resizey,blad);
	   if(powrot==LV_FAIL)
	   {
	     cerr << "Blad wykonywania siê funkcji LV_resize:\n";
	     cerr << blad << "\n\n";
	 	 return(-1);
	   }
	  Mat wynik_resize = Mat(wyny,wynx,CV_8UC3,dst3).clone();
	  
	  namedWindow( "Resize", WINDOW_AUTOSIZE ); 
      imshow( "Resize", wynik_resize );

   }

    waitKey(0);
	destroyWindow("Resize");
	
	//waitKey(0);
	delete dst3;

}else
 {
	 std::cout << "Blad ladowania pliku DLL.\n";
	 std::cout << GetLastError() << "\n";
 } 


//testy inne

Mat testowy;

cvtColor(src,testowy,CV_RGB2GRAY);
namedWindow( "Testowy", WINDOW_AUTOSIZE ); 
imshow( "Testowy", testowy );


// testy resize
/*
Mat wielkosc;
double procx=150,procy=150;
int x,y;
x = (int)( (procx/100) * src.cols);
y = (int)( (procy/100) * src.rows);
resize(src,wielkosc,Size(x,y));

cout << "Wielkosc przed resize, x = " << src.cols << " y = " << src.rows << "\n";
cout << "Wielkosc po resize, x = " << x << " y = " << y << "\n";
cout << "Wielkosc po resize (z Mat), x = " << wielkosc.cols << " y = " << wielkosc.rows << "\n";

namedWindow( "Resize1", WINDOW_AUTOSIZE ); 
imshow( "Resize1", wielkosc );
waitKey(0);
*/

//Testowanie watersegmentation
/*
class WatershedSegmenter{
private:
    cv::Mat markers;
public:
    void setMarkers(cv::Mat& markerImage)
    {
        markerImage.convertTo(markers, CV_32S);
    }

    cv::Mat process(cv::Mat &image)
    {
        cv::watershed(image, markers);
        markers.convertTo(markers,CV_8U);
        return markers;
    }
};

    cv::Mat image = cv::imread(argv[1]);
    cv::Mat blank(image.size(),CV_8U,cv::Scalar(0xFF));
    cv::Mat dest;
    imshow("originalimage", image);

    // Create markers image
    cv::Mat markers(image.size(),CV_8U,cv::Scalar(-1));
    //Rect(topleftcornerX, topleftcornerY, width, height);
    //top rectangle
    markers(Rect(0,0,image.cols, 5)) = Scalar::all(1);
    //bottom rectangle
    markers(Rect(0,image.rows-5,image.cols, 5)) = Scalar::all(1);
    //left rectangle
    markers(Rect(0,0,5,image.rows)) = Scalar::all(1);
    //right rectangle
    markers(Rect(image.cols-5,0,5,image.rows)) = Scalar::all(1);
    //centre rectangle
    int centreW = image.cols/4;
    int centreH = image.rows/4;
    markers(Rect((image.cols/2)-(centreW/2),(image.rows/2)-(centreH/2), centreW, centreH)) = Scalar::all(2);
    markers.convertTo(markers,CV_BGR2GRAY);
    imshow("markers", markers);

    //Create watershed segmentation object
    WatershedSegmenter segmenter;
    segmenter.setMarkers(markers);
    cv::Mat wshedMask = segmenter.process(image);
    cv::Mat mask;
    convertScaleAbs(wshedMask, mask, 1, 0);
    double thresh = threshold(mask, mask, 1, 255, THRESH_BINARY);
    bitwise_and(image, image, dest, mask);
    dest.convertTo(dest,CV_8U);

    imshow("final_result", dest);

waitKey(0);
*/
destroyWindow("Otsu");
destroyWindow("Scharr");
destroyWindow("Sobel");
destroyWindow("Oryginal");

delete dst; delete dst1; delete dst2; 
return(0);

}

