#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <fstream>
#include <exception>

typedef int (*generuj_klasy)(double *dane,long rows,long cols,int *wynik);
typedef int (*generuj_klasy_plik)(char *nazwa,int *wynik);

using namespace std;

/*! \file main.cpp
	\brief Klient, który wykorzystuje bibliotekê dll_rulproj.dll do celów demonstracyjnych zgodnie z zasadami, które mog¹ zostaæ wykorzystywanymi przez LabView
	\details Opis szczegó³owy u¿ycia (po komplikacji do dlltest.exe):<br/>
	SPOSOBY WYWO£ANIA PROGRAMU (wyœwietla na stadardowe wyjœcie (ekran) wynik klasyfikacji):<BR/>
	dlltest wynik<BR/>
	Wyœwietla wynik klasyfikacji z tablicy jednowymiarowej (w programie tablica zostaje za³adowana z pliku dane/nspawy_probki.tab)<BR/><BR/>
	Przyk³adowe wywo³anie:<BR/>
	dlltest wynik<BR/><BR/>

	dlltest [plik_z_danymi.tab]<BR/>
	Wyœwietla wynik klasyfikacji z pliku podanego jako pierwszy argument<BR/><BR/>

    Przyk³adowe wywo³anie:<BR/>
    dlltest dane/nspawy_probki.tab<BR/><BR/>
	
	\author LM
	\see dll_rulproj.cpp
*/  

	

void opis()
{
	cout << "SPOSOBY WYWO£ANIA PROGRAMU (wyœwietla na stadardowe wyjœcie (ekran) wynik klasyfikacji):\n";
	cout << "dlltest wynik\n";
	cout << "Wyœwietla wynik klasyfikacji z tablicy jednowymiarowej (w programie tablica zostaje za³adowana z pliku dane/nspawy_probki.tab)\n\n";
	cout << "Przyk³adowe wywo³anie:\n";
	cout << "dlltest wynik\n\n";
	cout << "dlltest [plik_z_danymi.tab]\n";
	cout << "Wyœwietla wynik klasyfikacji z pliku podanego jako pierwszy argument\n\n";
	cout << "Przyk³adowe wywo³anie:\n";
    cout << "dlltest dane/nspawy_probki.tab\n\n";
}

int main( int argc, char** argv )
{
  HINSTANCE hDLL;               // Handle to DLL
  generuj_klasy lpfnDllFunc1;    // Function pointer
  generuj_klasy_plik lpfnDllFunc2;    // Function pointer
 
  hDLL = LoadLibraryW((LPCWSTR)L"dll_rulproj.dll");

  if(argc < 2) 
  { 
	opis();
	return (-1);
  }


  lpfnDllFunc1 = (generuj_klasy)GetProcAddress(hDLL,"generuj_klasy");
  lpfnDllFunc2 = (generuj_klasy_plik)GetProcAddress(hDLL,"generuj_klasy_plik");

  if (hDLL != NULL)
  {
    if (!lpfnDllFunc1)
    {
      // handle the error
      std::cout << "BLAD LADOWANIA FUNKCJI generuj_klasy Z biblioteki DLL dll_rulproj.dll";
	  FreeLibrary(hDLL);
	  return -1;
    }
    else
    {
		long rows=5,cols=80;
		int out[1600];


		// uzycie funkcji z klasyfikacj¹ z tablicy jednowymiarowej
		if(strcmp(argv[1],"wynik") == 0)
		{
		//uruchomienie funkcji
		char *name = "dane/nspawy_probki.tab";

		ifstream in(name);
		if(!in.good()) { cout << "[dlltest wynik] Brak pliku: " << name << "\n"; return (-1); }
		in >> cols;
        in >> rows;
 
         double *dane = new double[cols*rows];

         //ladowanie danych
         long i,j;
         for(i=0 ; i<rows ; i++)
          for(j=0 ; j<cols ; j++) 
           in >> dane[i*cols + j];
 
         in.close();

		 int powrot = lpfnDllFunc1(dane, rows, cols, out);

		 for(i=0 ; i < rows ; i++)
             cout << out[i] << endl;

		 delete[] dane;
	   } else // uzcyie funkcji z klasyfikacja z pliku (parametr wywolania programu)
		{
			char *name = argv[1];
			ifstream in(name);
			if(!in.good()) { cout << "Brak pliku: " << name << "\n"; return (-1); }
			in >> cols;
            in >> rows;
  			int powrot = lpfnDllFunc2(name, out);
			
			for(long i=0 ; i < rows ; i++)
             cout << out[i] << endl;

	    }
  	}
  
  
  }else
     {
	   cout << "B³¹d ³adowania biblioteki generuj_klasy z biblioteki DLL dll_rulproj.dll \n";
     }

  return EXIT_SUCCESS;

}
