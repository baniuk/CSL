#include "LV_WeldDetectApprox/C_LineInterp.h"

/**
* Podstawowy konstruktor - nie powinien być używany
*/
C_LineInterp::C_LineInterp() : C_Line()
{
	typ_interpolacji = SPLINE;
	image = NULL;
	im_size[0] = im_size[1] = im_size[2] = 0;
	N = getNumOfElements();
	Np = 0;
	interpolated_data = NULL;
	x = NULL;
	y = NULL;
	rtg = NULL;
}
/**
* Tworzy obiekt Intepolacji, dołączony do określonego obrazka (trzeba konwertować z C_Matrix_Container
* \param[in] type Typ interpolacji
* \param[in] _P0 punkt poczatkowy
* \param[in] _P1 punkt końcowy lini interpolacji
* \param[in] _image wskaźnik do obrazu na którym będzie intepolaowana linia
* \param[in] _size tablica z wymiarami obrazu [rows,cols,z]
*/
C_LineInterp::C_LineInterp( APPROX_TYPE type,const C_Point &_P0, const C_Point &_P1, const double *const _image, const unsigned int _size[]  )
{
	ManualConstructor( type,_P0,_P1,_image,_size);
	interpolated_data = NULL;
	x = NULL;
	y = NULL;
	Np = 0;
	image = NULL;
	rtg = _image;
}
/**
* Tworzy oniekt Intepolacji, dołączony do określonego obrazka (trzeba konwertować z C_Matrix_Container
* \param[in] type Typ interpolacji
* \param[in] _a współczynnik kierunkowy prostej interpolacyjnej
* \param[in] _b wyraz wolny
* \param[in] _czy_pion czy prosta jest pionowa czy nie
* \param[in] _image wskaźnik do obrazu na którym będzie intepolaowana linia
* \param[in] _size tablica z wymiarami obrazu [rows,cols,z]
*/
C_LineInterp::C_LineInterp( APPROX_TYPE type,const double &_a, const double &_b, const KIERUNEK_PROSTEJ &_czy_pion, const double *const _image, const unsigned int _size[]  ) :
	C_Line(_a,_b,_czy_pion),
	typ_interpolacji(type),
	Np(0)
{
	// kopiowanie tablicy z rozmiarami danych
	memcpy_s(im_size,sizeof(im_size),_size,3*sizeof(unsigned int));
	// wypełanianie ilosci ementów danych wejsciowych (obrazu)
	N = getNumOfElements();
	interpolated_data = NULL;
	x = NULL;
	y = NULL;
	image = NULL;
	rtg = _image;
}

C_LineInterp::~C_LineInterp()
{
	SAFE_DELETE(image);
	SAFE_DELETE(interpolated_data);
	SAFE_DELETE(x);
	SAFE_DELETE(y);
}
/**
* Zwraca wartości interpolowane z obrazu pomiędzy punktami leżącymi na linii. Wartoci interpolowane zapisane są w interpolated_data.
* współrzędne dla których była inteprolacja równierz zapisywane są w x i y
* \param[in] _P0 punkt początkowy
* \param[in] _P1 punkt końcowy
* \param[in] _Np ilość punktów pomiędzy <P0;P1>
* \return Jeśli P0 i P1 nie leżą na linii to zwraca false i wartości w _out są nieokreślone
* \warning Funkcja modyfikuje tablice image
*/
bool C_LineInterp::getPointsOnLine( const C_Point &_P0, const C_Point &_P1, unsigned int _Np )
{
	bool ret;
	if(!isPointOnLine(_P0))
		return false;
	if(!isPointOnLine(_P1))
		return false;
	// tworzenie bufora z danymi tymczasowymi dla InterpolatedValue
	image = new float[N];
	// kopiowanie danych z zewnatrz do bufora
	for (unsigned int a=0;a<N;a++)
		image[a] = (float)rtg[a];
	int Error = SamplesToCoefficients(image, im_size[1], im_size[0], 2);
	if(Error)
	{
		_RPT0(_CRT_ERROR,"Error in C_LineApprox::getPointsOnLine->SamplesToCoefficients");
		return false;
	}
	// wypeninie lini P0 P1 punktami równo rozłożonymi
	Np = _Np;
	SafeAllocateTab();
	ret = C_Line::getPointsOnLine(_P0,_P1,x,y,Np);	// tu musi być wowołana funkcja z klasy podrzędnej
	if(ret==false)
	{
		SAFE_DELETE(image);
		return false;	// punkty nie na linii
	}
	switch(typ_interpolacji)
	{
	case SPLINE:
		for(unsigned int a=0;a<Np;a++) { // po wszystkich punktach
			interpolated_data[a] = (double)InterpolatedValue(image,
				im_size[1],
				im_size[0],
				x[a],
				y[a],
				2);
		}

		break;
	default:
		_RPT0(_CRT_ERROR,"Error in C_LineApprox::getPointsOnLine->SamplesToCoefficients - wrong type");
	}
	SAFE_DELETE(image);
	return true;
}
/**
* Oblicza rozmiar obrazu wejściowego. Rozmiar ten jest dany za pomocą tablicy [rows cols z]. Funkcja zwraca ilość elementów w tej tablicy.
* Takie podejście jest potzrebne ponieważ funkcja inteprolująca wymaga rozmiarów x i y obrazu (przyjmuje dane w forma,cie linowym zgodnym z C_Matrix_Container::data
* \return Ilość elementów w obrazu wejściowego
*/
unsigned int C_LineInterp::getNumOfElements() const
{
	unsigned int n=1;
	for(int a=0;a<3;a++)
		if(0!=im_size[a])
			n*=im_size[a];
	return n;
}
/**
* Funkcja sprawdza czy nie ma poprzedniej tablicy w przypadku gdy kilka razy wywoła się funkcję GetPointsOLine
*/
void C_LineInterp::SafeAllocateTab()
{
	if(interpolated_data!=NULL)
		SAFE_DELETE(interpolated_data);
	interpolated_data = new double[Np];
	if(NULL!=x)
		SAFE_DELETE(x);
	x = new double[Np];
	if(NULL!=y)
		SAFE_DELETE(y);
	y = new double[Np];
}

inline void C_LineInterp::DataCopy( double *src,double *dest )
{
	memcpy_s(dest,Np*sizeof(double),src,Np*sizeof(double));
}
/**
* Ustawia linieinterpolacji przy pomocy dwóch punktów. Funkcja ta inicjaklizuje także cały obiekt. Powinna być używana w przypadku użycia domyślnego konstruktora.
* \param[in] type Typ interpolacji
* \param[in] P0 punkt poczatkowy
* \param[in] P1 punkt końcowy lini interpolacji
* \param[in] _image wskaźnik do obrazu na którym będzie intepolaowana linia
* \param[in] _size tablica z wymiarami obrazu [rows,cols,z]
*/
void C_LineInterp::ManualConstructor( APPROX_TYPE type,const C_Point &P0, const C_Point &P1, const double *const _image, const unsigned int _size[] )
{
	typ_interpolacji = type;
	getLine2Points(P0,P1);	// inicjalizacja obieku Line
	// kopiowanie tablicy z rozmiarami danych
	memcpy_s(im_size,sizeof(im_size),_size,3*sizeof(unsigned int));
	// wypełanianie ilosci ementów obrzy wejściowego
	N = getNumOfElements();
	rtg = _image;
}