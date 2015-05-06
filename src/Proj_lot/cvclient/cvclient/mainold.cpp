#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/types_c.h"
#include "opencv2/core/core_c.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <atlstr.h>
#include <strsafe.h>
//#include <stdint.h>
#include "definitions.h"
#include "errordef.h"

typedef retCode (*LV_Sobel)(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc);
typedef retCode (*LV_Scharr)(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int dx, int dy,char *errDesc);
typedef retCode (*LV_Otsu)(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,char *errDesc);
typedef retCode (*LV_Mix)(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,char *errDesc);

typedef retCode (*getOutSize)(char *plik,UINT16* rows,UINT16 *cols,char *errDesc);
typedef retCode (*getOut_resize)(int rows,int cols,int procx,int procy,int *outx, int *outy, char *errDesc);
typedef retCode (*LV_resize)(UINT16* inp,UINT16* out,UINT16 rows,UINT16 cols,int procx,int procy,char *errDesc);

using namespace cv;
using namespace std;

/*! \file mainold.cpp
	\brief Klient, który wykorzystuje bibliotekê cvlib.dll do celów demonstracyjnych zgodnie z zasadami wykorzystywanymi przez LabView
	\details Opis szczecgó³owy u¿ycia (po komplikacji do cvclient.exe):<br/>
	SPOSOBY WYWO£ANIA PROGRAMU (WYŒWIETLA OBRAZ ORYGINALNY + OBRAZ PRZEKSZTA£CONY):<BR/>
	U¿ycie filtru Sobel-a<BR/>
    cvclient <plik_obrazu> LV_Sobel dx dy<BR/>
    gdzie:<BR/>
    <plik_obrazu> np. WSK.tif<BR/>
    LV_Sobel - wpisujemy dla filtru Sobel-a<BR/>
    dx - zmienna dx np. 1<BR/>
    dy - zmienna dy np. 0<BR/><BR/>

    Przyk³adowe wywo³anie:<BR/>
    cvclient WSK.tif LV_Sobel 1 0<BR/><BR/>
	
	U¿ycie filtru Scharr-a<BR/>
    cvclient <plik_obrazu> LV_Scharr dx dy<BR/>
    gdzie:<BR/>
    <plik_obrazu> np. WSK.tif<BR/>
    LV_Scharr - wpisujemy dla filtru Scharr-a<BR/>
    dx - zmienna dx np. 1<BR/>
    dy - zmienna dy np. 0<BR/><BR/><BR/>
    Przyk³adowe wywo³anie:<BR/>
    cvclient WSK.tif LV_Scharr 1 0<BR/><BR/>

    U¿ycie thresholding Otsu<BR/>
    cvclient <plik_obrazu> LV_Otsu<BR/>
    gdzie:<BR/>
    <plik_obrazu> np. WSK.tif<BR/>
    LV_Otsu - wpisujemy dla thresholding Otsu<BR/><BR/>
    Przyk³adowe wywo³anie:<BR/>
    cvclient WSK.tif LV_Otsu<BR/><BR/>
	
    U¿ycie dedykowanej segmentacji Mix<BR/>
    cvclient <plik_obrazu> LV_Mix<BR/>
    gdzie:<BR/>
    <plik_obrazu> np. WSK.tif<BR/>
    LV_Mix - wpisujemy dla dedykowanej segmentacji Mix<BR/><BR/>
    Przyk³adowe wywo³anie:<BR/>
    cvclient WSK.tif LV_Mix<BR/><BR/>
	
    Zmiana rozmiaru obrazu<BR/>
    cvclient <plik_obrazu> LV_Resize procx procy<BR/>
    gdzie:<BR/>
    <plik_obrazu> np. WSK.tif<BR/>
    LV_Resize - wpisujemy dla zmiany rozmiaru<BR/>
    procx - procentowy wymiar dla osi x np. 150<BR/>
    procy - procentowy wymiar dla osi y np. 150<BR/><BR/>

    Przyk³adowe wywo³anie (powiekszenie o 50%):<BR/>
    cvclient WSK.tif LV_Resize 150 150<BR/><BR/>
	
	\author LM
	\see cvlib.cpp
*/




void LV_Sobel_desc(char* prog)
{
	cout << "\nU¿ycie filtru Sobel-a\n";
	cout << prog << " <plik_obrazu>" << " LV_Sobel" << " dx" << " dy\n";
	cout << "gdzie:\n";
	cout << "<plik_obrazu> np. WSK.tif\n";
	cout << "LV_Sobel - wpisujemy dla filtru Sobel-a\n";
	cout << "dx - zmienna dx np. 1\n";
	cout << "dy - zmienna dy np. 0\n\n";
	cout << "Przyk³adowe wywo³anie:\n";
	cout << prog << " WSK.tif" << " LV_Sobel" << " 1" << " 0\n\n";
	cout << "";

}

void LV_Scharr_desc(char* prog)
{
	cout << "\nU¿ycie filtru Scharr-a\n";
	cout << prog << " <plik_obrazu>" << " LV_Scharr" << " dx" << " dy\n";
	cout << "gdzie:\n";
	cout << "<plik_obrazu> np. WSK.tif\n";
	cout << "LV_Scharr - wpisujemy dla filtru Scharr-a\n";
	cout << "dx - zmienna dx np. 1\n";
	cout << "dy - zmienna dy np. 0\n\n";
	cout << "Przyk³adowe wywo³anie:\n";
	cout << prog << " WSK.tif" << " LV_Scharr" << " 1" << " 0\n\n";
}

void LV_Otsu_desc(char* prog)
{
	cout << "\nU¿ycie thresholding Otsu\n";
	cout << prog << " <plik_obrazu>" << " LV_Otsu" << "\n";
	cout << "gdzie:\n";
	cout << "<plik_obrazu> np. WSK.tif\n";
	cout << "LV_Otsu - wpisujemy dla thresholding Otsu\n";
	cout << "Przyk³adowe wywo³anie:\n";
	cout << prog << " WSK.tif" << " LV_Otsu" << " \n\n";
}

void LV_Mix_desc(char* prog)
{
	cout << "\nU¿ycie dedykowanej segmentacji Mix\n";
	cout << prog << " <plik_obrazu>" << " LV_Mix" << "\n";
	cout << "gdzie:\n";
	cout << "<plik_obrazu> np. WSK.tif\n";
	cout << "LV_Mix - wpisujemy dla dedykowanej segmentacji Mix\n";
	cout << "Przyk³adowe wywo³anie:\n";
	cout << prog << " WSK.tif" << " LV_Mix" << "\n\n";
}

void LV_Resize_desc(char* prog)
{
	cout << "\n Zmiana rozmiaru obrazu\n";
	cout << prog << " <plik_obrazu>" << " LV_Resize" << " procx" << " procy\n";
	cout << "gdzie:\n";
	cout << "<plik_obrazu> np. WSK.tif\n";
	cout << "LV_Resize - wpisujemy dla zmiany rozmiaru\n";
	cout << "procx - procentowy wymiar dla osi x np. 150\n";
	cout << "procy - procentowy wymiar dla osi y np. 150 \n\n";
	cout << "Przyk³adowe wywo³anie (powiekszenie o 50%):\n";
	cout << prog << " WSK.tif" << " LV_Resize" << " 150" << " 150\n\n";

}



void all_desc(char *prog)
{
	cout << "SPOSOBY WYWO£ANIA PROGRAMU (WYŒWIETLA OBRAZ ORYGINALNY + OBRAZ PRZEKSZTA£CONY):\n";
	LV_Sobel_desc(prog);
    LV_Scharr_desc(prog);
	LV_Otsu_desc(prog);
	LV_Mix_desc(prog);
	LV_Resize_desc(prog);

}


/** @function main */
int mainold( int argc, char** argv )
{
/*
DWORD dw1 = GetTickCount();
Sleep(1000);
DWORD dw2 = GetTickCount();
cout<<"Time difference is "<<(dw2-dw1)<<" milliSeconds"<<endl;
*/
 
 CString string;
 string.LoadStringA(IDS_LVMIX_ERROR1);
 //string.LoadStringA(101);
 cout << "Load String: " << string.GetString() << "\n";
 cout << "IDS_LVMIX_ERROR1: " << IDS_LVMIX_ERROR1 << "\n";

	Mat src;
 if(argc < 3) { all_desc(argv[0]); return (-1); }
 src = imread(argv[1]); // Read the file
 
 if(src.empty()) { cout << "Bledny plik graficzny.\n"; return (-1); }

 cout << "Rozmiar obraz, wiersze: " << src.rows << " kolumny: " << src.cols << endl;

 //namedWindow( "Oryginal", WINDOW_AUTOSIZE ); 
 //imshow( "Oryginal", src );

 byte *dst = new byte[src.total() * src.elemSize()];
 byte *dst1 = new byte[src.total() * src.elemSize()];
 byte *dst2 = new byte[src.total() * src.elemSize()];

 byte *dstmix = new byte[src.total() * src.elemSize()];
 
 HINSTANCE hDLL;               // Handle to DLL
 LV_Sobel lpfnDllFunc1;    // Function pointer
 LV_Scharr lpfnDllFunc2;    // Function pointer
 LV_Otsu lpfnDllFunc3;    // Function pointer
 retCode powrot;
 //uint32_t powrot1;


 
hDLL = LoadLibraryW((LPCWSTR)L"cvlib.dll");
if (hDLL != NULL)
{
   
  if(strcmp(argv[2],"LV_Sobel")==0)
  {

	if(argc<5) { cout << "Zbyt ma³a liczba argumentów.\n"; LV_Sobel_desc(argv[0]); }
	else
	{
		int dx = atoi(argv[3]);
		int dy = atoi(argv[4]);
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
	  powrot = lpfnDllFunc1((UINT16*)src.data,(UINT16*)dst,src.rows,src.cols,dx,dy,blad);
      //powrot = lpfnDllFunc1((UINT16*)src.data,(UINT16*)dst,src.rows,src.cols,1,0,blad);
	  if(powrot==LV_FAIL)
	  {
	    cerr << "Blad wykonywania siê funkcji LV_Sobel:\n";
		cerr << blad << "\n\n";
		return(-1);
	  }
	  namedWindow( "Oryginal", WINDOW_AUTOSIZE ); 
      imshow( "Oryginal", src );
	  
	  Mat wynik = Mat(src.rows,src.cols,CV_8UC3,dst).clone();
	  namedWindow( "Sobel", WINDOW_AUTOSIZE ); 
      imshow( "Sobel", wynik );
	//  std::cout << "Wynik: " << uReturnVal;
   }
	}//else
  }//Koniec If dla LV_Sobel

   //funkcja LV_Scharr
  if(strcmp(argv[2],"LV_Scharr")==0)
  {

	if(argc<5) { cout << "Zbyt ma³a liczba argumentów.\n"; LV_Scharr_desc(argv[0]); }
	else
	{
		int dx = atoi(argv[3]);
	    int dy = atoi(argv[4]);
   
        lpfnDllFunc2 = (LV_Scharr)GetProcAddress(hDLL,"LV_Scharr");
   if (!lpfnDllFunc2)
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
	  DWORD dw1 = GetTickCount();
      powrot = lpfnDllFunc2((UINT16*)src.data,(UINT16*)dst1,src.rows,src.cols,dx,dy,blad);
	  DWORD dw2 = GetTickCount();
      cout<<"LV_Scharr czas: "<<(dw2-dw1)<<" milliSeconds"<<endl;
	  //powrot = lpfnDllFunc2((UINT16*)src.data,(UINT16*)dst1,src.rows,src.cols,0,1,blad);
	  if(powrot==LV_FAIL)
	  {
	    cerr << "Blad wykonywania siê funkcji LV_Scharr:\n";
		cerr << blad << "\n\n";
		return(-1);
	  }

	  namedWindow( "Oryginal", WINDOW_AUTOSIZE ); 
      imshow( "Oryginal", src );
	  
	  Mat wynik1 = Mat(src.rows,src.cols,CV_8UC3,dst1).clone();
	  namedWindow( "Scharr", WINDOW_AUTOSIZE ); 
      imshow( "Scharr", wynik1 );

	//  std::cout << "Wynik: " << uReturnVal;
   }

   }//else
  }//Koniec If dla LV_Scharr


  if(strcmp(argv[2],"LV_Otsu")==0)
  {

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
      DWORD dw1 = GetTickCount();
	  powrot = lpfnDllFunc3((UINT16*)src.data,(UINT16*)dst2,src.rows,src.cols,blad);
	  DWORD dw2 = GetTickCount();
      cout<<"LV_Otsu czas: "<<(dw2-dw1)<<" milliSeconds"<<endl;
	  if(powrot==LV_FAIL)
	  {
	    cerr << "Blad wykonywania siê funkcji LV_Otsu:\n";
		cerr << blad << "\n\n";
		return(-1);
	  }

	  namedWindow( "Oryginal", WINDOW_AUTOSIZE ); 
      imshow( "Oryginal", src );
	  
	  Mat wynik2 = Mat(src.rows,src.cols,CV_8UC3,dst2).clone();
	  namedWindow( "Otsu", WINDOW_AUTOSIZE ); 
      imshow( "Otsu", wynik2 );
	//  std::cout << "Wynik: " << uReturnVal;
   }
  } //koniec Otsu

  if(strcmp(argv[2],"LV_Mix")==0)
  {

   // wyprobowanie metody LV_Mix
   LV_Mix lpfnDllFunc3a;
   lpfnDllFunc3a = (LV_Mix)GetProcAddress(hDLL,"LV_Mix");
   if (!lpfnDllFunc3a)
   {
      // handle the error
      std::cout << "BLAD LADOWANIA FUNKCJI LV_Mix Z biblioteki DLL cvlib.dll";
	  FreeLibrary(hDLL);
	  return -1;
   }
   else
   {
        // call the function
	  char blad[2000];
	  DWORD dw1 = GetTickCount();
      powrot = lpfnDllFunc3a((UINT16*)src.data,(UINT16*)dstmix,src.rows,src.cols,blad);
	  DWORD dw2 = GetTickCount();
      cout<<"LV_Mix czas: "<<(dw2-dw1)<<" milliSeconds"<<endl;
	  if(powrot>0)
	  {
	    cerr << "Blad wykonywania siê funkcji LV_Mix:\n";
		cerr << blad << "\n\n";
		return(-1);
	  }

	  namedWindow( "Oryginal", WINDOW_AUTOSIZE ); 
      imshow( "Oryginal", src );
	  
	  Mat wynikmix = Mat(src.rows,src.cols,CV_8UC3,dstmix).clone();
	  namedWindow( "Mix", WINDOW_AUTOSIZE ); 
      imshow( "Mix", wynikmix );
	  
	//  std::cout << "Wynik: " << uReturnVal;
   }

  }//koniec Mix


  //funkcja resize
  if(strcmp(argv[2],"LV_Resize")==0)
  {

	if(argc<5) { cout << "Zbyt ma³a liczba argumentów.\n"; LV_Resize_desc(argv[0]); }
	else
	{
	

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
   int resizex = atoi(argv[3]);
   int resizey = atoi(argv[4]);
   //int resizex = 250,resizey = 250;
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
	   DWORD dw1 = GetTickCount();
	   powrot = lpfnDllFunc5((UINT16*)src.data,(UINT16*)dst3,src.rows,src.cols,resizex,resizey,blad);
	   DWORD dw2 = GetTickCount();
       cout<<"LV_Resize czas: "<<(dw2-dw1)<<" milliSeconds"<<endl;
	   if(powrot==LV_FAIL)
	   {
	     cerr << "Blad wykonywania siê funkcji LV_resize:\n";
	     cerr << blad << "\n\n";
	 	 return(-1);
	   }
	  Mat wynik_resize = Mat(wyny,wynx,CV_8UC3,dst3).clone();
	  
	  namedWindow( "Oryginal", WINDOW_AUTOSIZE ); 
      imshow( "Oryginal", src );

	  namedWindow( "Resize", WINDOW_AUTOSIZE ); 
      imshow( "Resize", wynik_resize );

   }

    waitKey(0);
	destroyWindow("Resize");
	
	//waitKey(0);
	delete dst3;
	} //koniec else
  } //koniec Resize



}else
 {
	 std::cout << "Blad ladowania pliku DLL.\n";
	 std::cout << GetLastError() << "\n";
 } 


//testy inne
/*
Mat testowy,testowy1;

cvtColor(src,testowy,CV_RGB2GRAY);
//watershed(testowy,testowy1);
cv::threshold(testowy, testowy1, 150, 255, THRESH_BINARY);
namedWindow( "Testowy", WINDOW_AUTOSIZE ); 
imshow( "Testowy", testowy1 );
*/



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
waitKey(0);
destroyWindow("Otsu");
destroyWindow("Scharr");
destroyWindow("Sobel");
destroyWindow("Oryginal");
destroyWindow("Mix");



delete dst; delete dst1; delete dst2; delete dstmix;
return(0);

}

