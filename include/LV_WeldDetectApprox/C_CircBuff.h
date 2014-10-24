/**
* \file    C_CircBuff.h
* \brief	Bufor kołowy
* \author  PB
* \date    2012/03/01
*/
#ifndef C_CircBuff_h__
#define C_CircBuff_h__

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

/**
* Klasa obsługująca bufor kołowy. Umożliwia realziację bufora kołowego ale przy indeksowaniu liniowym. Dane są dopisuwane na kolejne
* miejsce zraz za oststnio dopisanym. T jest typem obiektu a S rozmiarem bufora. Bepośrednio po zapisaniu elementu do bufora można go skasować. Funkcja getNumElements() zwraca ilość elementów w buforze kompatybilną z funkcją GetObject, dzięki czemu można ją adresować za pomocą pętli. Generalnie bufor działa w następujący sposób - dopóki nie zostanie cały zapisany to Czy_pelny zawsze zwraca false. Jeśli zostanie cały zapisany ale jeden ostatni zostanie skasowany to terz zwórci false. Po pirwszym przepełnieniu funkcja zawsze zwrca true. Tak samo getNumElements - po przepełnieniu zwraca pojemność bufora.
* \warning Nie jest zalecane wielokrotne kasowanie pod rząd wielu elementow. Powinno kasować się tylko ostatni.
* Przykłady użycia w pliku TESTS.cpp w C_WeldlineDetet_TESTS.\n
* Kolejność używania:\n
* \li Stworzyć obiekt używając konstruktora bezparametrowego
* \li Dodać obiekty używając AddObject, która zwrca adres nowododanego obiektu
* \li Po każdej tej instrukcji można odwołać się do tego obiektu lub go skasować
* \todo przemyslec czy funkcje informujące o ilosc zapisanych elementów mają sens? Bo jesli jeden kasujemy to bufor nie jest pełny ale nie wiemy który jest póstu, więc to klient powinien sprawdzać (getElem zwraca NULL). Pozostawić jedynie funkcję która wykrywa pierwsze wypełnienie bufora. Generalnie jest dobrze, te funkcjie powinny zostać ale wazny jest spsoób ich działania.
*/
template<class T> class C_CircBuff
{
public:
	C_CircBuff();
	~C_CircBuff();
	/// inicjalizuje dynamicznie bufor
	void BuffInit(unsigned int _S);
	/// dodaje obiekt typu T do bufora na kolejną pozycję
	T *AddObject();
	/// dodaje obiekt typu T do bufora na kolejną pozycję. Umożliwia podanie rozmiaru obiektu
	T *AddObject(unsigned int siz);
	/// zwraca odres obiektu na pozycji n
	T *GetObject(unsigned int _n);
	/// zwraca true jeśli bufor pełny
	bool Czy_pelny() const;
	/// kasuje ostatnio dodany obiekt
	void DelObject();
	/// zwraca ilość elementów w buforze
	int getNumElem();
	/// zwraca pierwszy zainicjalizowany
	T *GetFirstInitialized();
private:
	/// tablica zawierająca obiekty w buforze kołowym
	T **buff;
	/// ostatni dodany obiekt - index - liniowy od 0 do N moze byc
	unsigned int last;
	/// rozmiar bufora
	unsigned int S;
	/// ostatnio dodany index przy uwzglęnieniu cyrkularności
	int ostatni;
	/// ilosc zapisów
	unsigned int ile;
};
/**
* Zwraca ilość zapisanych elementów w buforze.
* \return Ilość elementów. Jesli bufor pełny to zwraca jego pojemność, jeśli nie pełny to ilość zapisanych elementów. Jeśli choc raz bufor przy zapisie dojdzie do konca to jest uwazany zap pełny.
*/
template<class T>
int C_CircBuff<T>::getNumElem()
{
	if(NULL==buff )
		return -1;
	if( ostatni<0)
		return 0;
	if(Czy_pelny())
		return S;
	else
		return (unsigned int)(ostatni+1);	// rozmiar zwraca a nie index
}

template<class T>
void C_CircBuff<T>::DelObject()
{
	_ASSERT(buff!=NULL);	// bez inicjalizacji
	_ASSERT(ostatni>=0);	// nie ma nic dodane ale jest zainicjalizowane
	SAFE_DELETE(buff[ostatni]);
	last = ostatni;
	ile--;
}

/**
* Ta funkcja musi być wywołana jako pierwsza
* \param _S Rozmiar bufora
*/
template<class T>
void C_CircBuff<T>::BuffInit( unsigned int _S )
{
#ifdef _DEBUG
	if(0==_S)
		_RPT0(_CRT_ERROR,"void C_CircBuff<T>::BuffInit->Wrong size");
#endif
	S = _S;
	buff = new T *[S];
	for(unsigned int a=0;a<S;a++)
		buff[a] = NULL;
}

/**
* Funkcja zwraca element na pozycji n. Jeśli n jest większe ood rozmiaru bufora to
* zwracany jest element na pozycji po przekręceniu się bufora
* \warning Istnieje mozliwosc pobrania pozycji niezainicjalizowanej
*/
template<class T>
T * C_CircBuff<T>::GetObject( unsigned int _n )
{
	_ASSERT(buff!=NULL);
#ifdef _DEBUG
	if(NULL==buff[_n%S])
		_RPT1(_CRT_WARN,"\t\tAccess to empty element %d",_n);
#endif
	//	_ASSERT(buff[_n%S]!=NULL);
	return buff[_n%S];
}
/**
* Funkcja zwraca pierwszy zaincjalizowany obiekt z bufora
* \return Zwraca pierwszy obiekt zainicjalizowany lub NULL jesli nie znajdzie takiego
*/
template<class T>
T * C_CircBuff<T>::GetFirstInitialized()
{
	unsigned int l=0;
	for(l=0;l<S;l++)
		if(buff[l]!=NULL)
			return buff[l];
	_ASSERT(buff[l]);
	return NULL;
}
/**
* \return Funkcja zwraca adres nowododanego obiektu
*/
template<class T>
T * C_CircBuff<T>::AddObject()
{
	_ASSERT(buff!=NULL);
	if(last>S-1) {last = 0;}
	SAFE_DELETE(buff[last]);	// kasownaie tego co tam jest na nowej pozycji
	buff[last] = new T;
	ostatni = (int)last;
	ile++;
	return GetObject(last++);
}
/**
* \return Funkcja zwraca adres nowododanego obiektu. Umożliwia przekazanie rozmiaru tworzonego obiektu
*/
template<class T>
T * C_CircBuff<T>::AddObject(unsigned int siz)
{
	_ASSERT(buff!=NULL);
	if(last>S-1) {last = 0;}
	SAFE_DELETE(buff[last]);	// kasownaie tego co tam jest na nowej pozycji
	buff[last] = new T[siz];
	ostatni = (int)last;
	ile++;
	return GetObject(last++);
}
template<class T>
bool C_CircBuff<T>::Czy_pelny() const
{
	if(ile>=S)
		return true;	// więcej zapisów niz miejsca
	else
		return false;
}

template<class T>
C_CircBuff<T>::~C_CircBuff()
{
	for(unsigned int a=0;a<S;a++)
		SAFE_DELETE(buff[a]);
	SAFE_DELETE(buff);
}

template<class T>
C_CircBuff<T>::C_CircBuff()
{
	buff = NULL;
	last = 0;	// do ustawienia
	S = 0;
	ile = 0;
	ostatni = -1;
}

#endif // C_CircBuff_h__