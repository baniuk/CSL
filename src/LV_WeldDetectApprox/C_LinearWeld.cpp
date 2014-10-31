/**
* \file    C_LinearWeld.cpp
* \brief	Implementuje dekecje spawów liniowych
* \author  PB
* \date    2012/03/01
* \version 1.0
*/

#include "LV_WeldDetectApprox\C_LinearWeld.h"
#include "LV_WeldDetectApprox\ParamEstimation.h"

C_LinearWeld::C_LinearWeld( const Matrix_Container *_rtg ) : C_WeldlineDetect(_rtg)
{
	interp_lines = new C_CircBuff<C_LineInterp>;
	approx_results = new C_CircBuff<C_LineWeldApprox>;
	recalculated_approx_data = new C_CircBuff<double>;
	lineOK = new vector<bool>;
	weldPos = new vector<C_WeldPos>;
}

C_LinearWeld::~C_LinearWeld()
{
	SAFE_DELETE(_w);
	SAFE_DELETE(interp_lines);
	SAFE_DELETE(approx_results);
	SAFE_DELETE(recalculated_approx_data);
	SAFE_DELETE(lineOK);
	SAFE_DELETE(weldPos);
	_RPT0(_CRT_WARN,"\tEntering C_LinearWeld::~C_LinearWeld\n");
}
/**
* Ustawia środowisko, tworzy potrzebne tablice.
* Funkcja musi być wywołana po konstruktorze aby ustawić potrzebne parametry.
* \param[in] _k ilość linii branych do wygeneroania następnej - wielkosć bufora
* \param[in] _StartPoint punkt startowy - kolumna obrazka w tym przypadku (skłądowa x)
*/
void C_LinearWeld::SetProcedureParameters(unsigned int _k, C_Point _StartPoint)
{
	_RPT0(_CRT_WARN,"\tEntering C_LinearWeld::SetProcedureParameters");
	k = _k;
	_ASSERT(!(_StartPoint.getX()<1) ||
		!(_StartPoint.getX()>rtg->_cols-1)); // punkt poza obrazem
	P0.setPoint(_StartPoint.getX(),0); // dół obrazka
	P1.setPoint(_StartPoint.getX(),rtg->_rows-1);	// góra obrazka
	// tworzenie buforów na przechowanie danych
	if(k>0)
	{
		_RPT1(_CRT_WARN,"\t\tk = %d",k);
		approx_results->BuffInit(k);
		interp_lines->BuffInit(k);
		recalculated_approx_data->BuffInit(k);
	}
	_RPT5(_CRT_WARN,"\t\tk=%.3lf, P0[%.1lf;%.1lf] P1[%.1lf;%.1lf]",k,P0.getX(),P0.getY(),P1.getX(),P1.getY());
	_RPT0(_CRT_WARN,"\tLeaving C_LinearWeld::SetProcedureParameters\n");
}
/**
* Uruchamia właściwy proces wykrywnia spawu.
* \param[in] step Krok z jakimjest wykrywaie spawu. Bufor zawsze jest ypełniany z krokiem 1
* \param[in] ile Ile linii ma być aproxymowanych, jesli 0 to do końca spawu
* \param[in] weld_edge Ile procent wysokości spawu to brzeg, domyślnie to warość \c WELD_EDGE
* \return OK jeśli udało się zakończyć, BLAD jeśli wystapił błąd. BLAD jest zwracany jesli nie uda sie stworzyc bufora lub krok było równy 0
*/
bool C_LinearWeld::Start(unsigned int step,unsigned int ile, double weld_edge=WELD_EDGE)
{
	this->weld_edge = weld_edge;
	// bierząca pozycja spawu w przestrzeni obrazka
	bool liniaok = OK;	// czy aproxymacja bierzacej lini zakończyła się sukcesem. Jeśli tak to została ona włączona do bufora i treba go przeliczyć. Jesli nie to nie ma takiej potrzeby
	unsigned int ile_done=0;	// ile linii zostało już zaproxymowanych, liczą sięwszystkie nawet te złe
	C_WeldPos currentPos;
	C_LineInterp *obj;	// obiekt tymczasowy do łatwiejszego adresowania
	C_LineWeldApprox *app;
	const double *y;	// dane x do aproxymacji
	double *pre;	// wskaźnik na daną w buforze precalculated_approx_data
	_RPT0(_CRT_WARN,"\tEntering C_LinearWeld::Start");
	bool ret=OK;
	int iter;
	float* coef = NULL;
	// wypełnianie bufora w zależności od punktu startowego podanego w SetProcedureParameters()
	ret = fillBuffor();
	if(BLAD==ret)
		return ret;
	// w P0P1 jest już następny punkt bo został wygenerowany w fillBuffor()
	// jesli ile jest 0 to nie uwzględniamy tego warunku stopu. ile jest ustawiane na wartość max to zawsze bedzie warunek spełniony
	if(0==ile) ile = UINT_MAX;
	while(OK==ret && ile_done<ile)
	{
		// generowanie nast paramerów na podstawie bufora wypełniane są zmienne _p, _ub, _lb, _w
		if(liniaok)	// przeliczamy nowe parametry jesli była zmiana w buforze
			evalNextParams();
		// generowanie linii itp
		obj = interp_lines->AddObject();	// dodaje nową linię
		// ustawiam parametry interpolacji - P0 lezy na dole obrazu, P1 na górze, linia pionowa
		_RPT4(_CRT_WARN,"\t\tInput: P0[%.1lf;%.1lf] P1[%.1lf;%.1lf]",P0.getX(),P0.getY(),P1.getX(),P1.getY());
		obj->ManualConstructor(SPLINE,P0,P1,rtg->data,rtgsize);
		// wykonuje interpolację - biorę tyle punktów ile jest rzędów w obrazie + punkty końcowe. Wyniki są zapamiętywane w klasie i dostępne poprzez getInterpolated
		obj->getPointsOnLine(P0,P1,(rtg->_rows+1)/4,&coef);
		// aproksymacja - dodaje obiekt aprox
		app = approx_results->AddObject();
		if(obj->getjest_pion()==PIONOWA) // sprawdzam bo jak jest pionowa to aproxymacja jest w funkcji y a jeśli nie to x
			app->ManualConstructor(typeGaussLin,obj->getInterpolated_data(),obj->getInterpolated_Y(),obj->getSizeofInterpData());
		else
			_RPT0(_CRT_ASSERT,"C_LinearWeld::fillBuffor()->linia nie jest pionowa"); // to nie powinno byc nigdy wykonene w tej wersji
		// aproxymacja - parametry obliczone przez evalNextParams()
		app->setApproxParmas(_p,_w,_ub,_lb,NULL);
		// aproxymacja
		/// \todo dodać tu sprawdzanie czy zwraca poprawną ilość iteracji
		iter = app->getLineApprox(150);
		_RPT1(_CRT_WARN,"\t\tITER: %d",iter);
#ifdef _DEBUG
		const double *pdeb;pdeb = app->getApproxParams_p();
		_RPT5(_CRT_WARN,"\t\tRES: A=%.2lf B=%.2lf C=%.2lf D=%.2lf E=%.2lf",pdeb[A],pdeb[B],pdeb[C],pdeb[D],pdeb[E]);
		pdeb = app->getApproxParams_ub();
		_RPT5(_CRT_WARN,"\t\tUB: A=%.2lf B=%.2lf C=%.2lf D=%.2lf E=%.2lf",pdeb[A],pdeb[B],pdeb[C],pdeb[D],pdeb[E]);
		pdeb = app->getApproxParams_lb();
		_RPT5(_CRT_WARN,"\t\tLB: A=%.2lf B=%.2lf C=%.2lf D=%.2lf E=%.2lf",pdeb[A],pdeb[B],pdeb[C],pdeb[D],pdeb[E]);
#endif
		// sprawdzam powodzenie interpolacji danej linii
		if(BLAD==czyAccept(app,obj))
		{
			liniaok = BLAD;	// nie dodaliśmy nowej linii
			approx_results->DelObject();
			interp_lines->DelObject();
			lineOK->push_back(liniaok);	// te wektory zawierają już info o liniach bufora
			currentPos.Clear();	// kasuje wszystko bo ten wpis nie ważny
			weldPos->push_back(currentPos);
		} else {
			liniaok = OK;	// dodlaiśmy nowa linię
			lineOK->push_back(liniaok);	// linia ok
			pre = recalculated_approx_data->AddObject(obj->getSizeofInterpData());	// przeliczanie danych -dodawan etylko dla dobrych linii, wiec nie ma potrzeby kasownaia dla złych
			y = obj->getInterpolated_Y();
			app->evalApproxFcnVec(y,pre,obj->getSizeofInterpData());
			evalWeldPos(app,obj,pre,currentPos);	// wypełniam currentPos właściwymi danymo
			weldPos->push_back(currentPos);
		}
		// generowanie nast punktu start (zwrocone z  blad oznacza koniec spawu i wtedy tu przerywamy)
		ile_done++;
		ret = evalNextStartPoint(step);
		if(!((int)P0.getX()%10))
			std::cout<<P0.getX()<<"\n";
	}
	_RPT0(_CRT_WARN,"\tLeaving C_LinearWeld::Start\n");
	SAFE_DELETE(coef);
	return OK; // zwracamy ok normalnie, BLAD jest zwracany jesli nie uda sie stworzyc bufora
}
/**
* Oblicza jedną linię dla spawu i zwraca pozycje brzegów i środka. Sprawdza poprwność aproksymacji
* oraz nie bierze pod uwagę buforów. Linia obliczana dla bierzących punktów (tych zdefinoowanych w klasie).
* Można je zmieniać poprzez evalNextStartPoint. Ta funkcja wymaga zainicjalizowanej klasy jak w normalnym przypadku.
* \param[out] weldpos Struktura z położeniem spawu dla jednego punktu
* \return OK jeśli aproxymacja dobra, BLAD jeśli nie
*/
bool C_LinearWeld::getOneApproxLine(C_WeldPos &weldpos)
{
	_RPT0(_CRT_WARN,"\tEntering C_LinearWeld::getOneApproxLine");
	C_LineInterp *obj = NULL;	// obiekt tymczasowy do łatwiejszego adresowania
	C_LineWeldApprox *app = NULL;
	float* coef = NULL;
	double *pre;	// wskaźnik na daną w buforze precalculated_approx_data
	const double *y;	// dane x do aproxymacji

	bool ret;
	int iter;
	C_WeldPos wp;

	obj = new C_LineInterp;
	obj->ManualConstructor(SPLINE,P0,P1,rtg->data,rtgsize);
	// wykonuje interpolację - biorę tyle punktów ile jest rzędów w obrazie + punkty końcowe. Wyniki są zapamiętywane w klasie i dostępne poprzez getInterpolated
	obj->getPointsOnLine(P0,P1,rtg->_rows+1,&coef);

	app = new C_LineWeldApprox;
	app->ManualConstructor(typeGaussLin,obj->getInterpolated_data(),obj->getInterpolated_Y(),obj->getSizeofInterpData());
	// aproxymacja - parametry domyślne
	app->setApproxParmas(NULL,NULL,NULL,NULL,NULL);
	// aproxymacja
	iter = app->getLineApprox(200);
	_RPT1(_CRT_WARN,"\t\tITER: %d",iter);
	double sr = app->getInfo(stopreason);
	_RPT1(_CRT_WARN,"\t\tSTOPREASON: %lf",sr);

	pre = recalculated_approx_data->AddObject(obj->getSizeofInterpData());	// przeliczanie danych
	y = obj->getInterpolated_Y();
	app->evalApproxFcnVec(y,pre,obj->getSizeofInterpData());
	evalWeldPos(app,obj,pre,weldpos);	// wypełniam currentPos właściwymi danymo

	ret = czyAccept(app,obj);

	SAFE_DELETE(app);
	SAFE_DELETE(obj);
	SAFE_DELETE(coef);
	_RPT0(_CRT_WARN,"\tLeaving C_LinearWeld::getOneApproxLine\n");
	return(ret);
}
/**
* Procedura wypełnia bufory kołowe.
* Dokonuje interpolacji k kolejnych linii obrazka oraz ich aproxymacji. Zapisuje obiekty w buforze kołowym. Dodatkowo także zapisuje dane w weldPos oraz lineOK. Dzięki temu te zienne zawsze przechowują informacje o wszystkich obrobionych liniach, nawet tych niepoprawnych.\n
* W tej funkcji wypełniany jest takze bufor recalculated_approx_data.
* \return OK jeśli udało sięwypełnić, BLAD jeśli wystapił błąd
*/
bool C_LinearWeld::fillBuffor()
{
	_RPT0(_CRT_WARN,"\tEntering C_LinearWeld::fillBuffor");
	// bierząca pozycja spawu w przestrzeni obrazka
	C_WeldPos currentPos;
	// interpolacja k kolejnych linii zacynając od startowej - poruszam się po kolumnach
	C_LineInterp *obj;	// obiekt tymczasowy do łatwiejszego adresowania
	C_LineWeldApprox *app;
	bool ret_evalnextparam = OK; // jeśli false to koniec obrazka
	const double *y;	// dane x do aproxymacji
	double *pre;	// wskaźnik na daną w buforze precalculated_approx_data
	float* coef=NULL;
	while(!interp_lines->Czy_pelny() && interp_lines->getNumElem()>-1 && ret_evalnextparam==OK)	// dopuki bufor nie jest pełny i jednocześnie jest zainicjowany
	{
		obj = interp_lines->AddObject();	// dodaje nową linię
		// ustawiam parametry interpolacji - P0 lezy na dole obrazu, P1 na górze, linia pionowa
		_RPT4(_CRT_WARN,"\t\tInput: P0[%.1lf;%.1lf] P1[%.1lf;%.1lf]",P0.getX(),P0.getY(),P1.getX(),P1.getY());
		obj->ManualConstructor(SPLINE,P0,P1,rtg->data,rtgsize);
		// wykonuje interpolację - biorę tyle punktów ile jest rzędów w obrazie + punkty końcowe. Wyniki są zapamiętywane w klasie i dostępne poprzez getInterpolated
		obj->getPointsOnLine(P0,P1,rtg->_rows+1,&coef);
		// aproksymacja - dodaje obiekt aprox
		app = approx_results->AddObject();
		// konstruktor manualne
		if(obj->getjest_pion()==PIONOWA) // sprawdzam bo jak jest pionowa to aproxymacja jest w funkcji y a jeśli nie to x
			app->ManualConstructor(typeGaussLin,obj->getInterpolated_data(),obj->getInterpolated_Y(),obj->getSizeofInterpData());
		else{
			_RPTF0(_CRT_ASSERT,"C_LinearWeld::fillBuffor()->linia nie jest pionowa");
			app->ManualConstructor(typeGaussLin,obj->getInterpolated_data(),obj->getInterpolated_X(),obj->getSizeofInterpData()); // to nie
			// powinno byc nigdy wykonene w tej wersji
		}
		// aproxymacja - parametry domyślne
		app->setApproxParmas(NULL,NULL,NULL,NULL,NULL);
		// aproxymacja
		app->getLineApprox(100);
		// sprawdzam powodzenie interpolacji
#ifdef _DEBUG
		const double *pdeb;pdeb = app->getApproxParams_p();
		_RPT5(_CRT_WARN,"\t\tRES: A=%.2lf B=%.2lf C=%.2lf D=%.2lf E=%.2lf",pdeb[A],pdeb[B],pdeb[C],pdeb[D],pdeb[E]);
		pdeb = app->getApproxParams_ub();
		_RPT5(_CRT_WARN,"\t\tUB: A=%.2lf B=%.2lf C=%.2lf D=%.2lf E=%.2lf",pdeb[A],pdeb[B],pdeb[C],pdeb[D],pdeb[E]);
		pdeb = app->getApproxParams_lb();
		_RPT5(_CRT_WARN,"\t\tLB: A=%.2lf B=%.2lf C=%.2lf D=%.2lf E=%.2lf",pdeb[A],pdeb[B],pdeb[C],pdeb[D],pdeb[E]);
#endif
		// sprawdzam poprawność danych
		if(BLAD==czyAccept(app,obj))
		{
			approx_results->DelObject();
			interp_lines->DelObject();
			lineOK->push_back(BLAD);
			currentPos.Clear();
			weldPos->push_back(currentPos);	// wartości domyślne
		} else {
			lineOK->push_back(OK);	// linia ok
			pre = recalculated_approx_data->AddObject(obj->getSizeofInterpData());	// przeliczanie danych
			y = obj->getInterpolated_Y();
			app->evalApproxFcnVec(y,pre,obj->getSizeofInterpData());
			evalWeldPos(app,obj,pre,currentPos);	// wypełniam currentPos właściwymi danymo
			weldPos->push_back(currentPos);
		}
		// generuje następne punkty, w buforze zawsze krok 1
		ret_evalnextparam = evalNextStartPoint(1);
	}
	_RPT0(_CRT_WARN,"\tLeaving C_LinearWeld::fillBuffor\n");
	SAFE_DELETE(coef);
	return ret_evalnextparam;
}
/**
* Generuje zestaw parametrów startowych do obliczenia kolejenj aproxymacji. Obraz jest
* interpolowany na linii P0P1 a następnie ten profil będzie podlegał aproxymacji. Każde wywołanie funkcji
* powoduje wygenerowanie następnego zestawu parametrów.
* \param[in] step krok z jakim przesuwamy się. Załozenie jest że krok dotyczy tylko osi x
* \return BLAD jeśli nie można wygenerowac kolejnych parametrów (na przykłąd koniec obrazka)
* \warning Funkcja modyfikuje pola P0 i P1
*
*/
bool C_LinearWeld::evalNextStartPoint(unsigned int step)
{
	_RPT0(_CRT_WARN,"\tEntering C_LinearWeld::evalNextStartPoint");
	// generowanie nowych współrzędnych dla linii inteprolacyjnej - do paproxymacji profilu
	//	_ASSERT(step!=0);
	if(P0.getX()>=rtg->_cols-1 || 0==step)	// jeśli jesteśmy na ostatniej kolumnie to nie można wygenerowac kolejnej
		return BLAD;
	C_Point delta(step,0);	// krok 1 po x
	_RPT4(_CRT_WARN,"\t\tInput: P0[%.1lf;%.1lf] P1[%.1lf;%.1lf]",P0.getX(),P0.getY(),P1.getX(),P1.getY());
	P0+=delta;
	P1+=delta;
	_RPT4(_CRT_WARN,"\t\tOutput: P0[%.1lf;%.1lf] P1[%.1lf;%.1lf]",P0.getX(),P0.getY(),P1.getX(),P1.getY());
	_RPT0(_CRT_WARN,"\tLeaving C_LinearWeld::evalNextStartPoint\n");
	return OK;
}
/**
* Generuje parametry aproksymacji: współczynniki startowe p, ub, lb oraz wagi. Na podstawie struktur buforowych approx_results i interp_lines.Obliczone parametry zwraca na zewnątrz. W kolejnej moga one zostać przekazane do klasy C_LineWeldApprox, która robi sobie ich lokalną kopię.Funkcja inicalizuje tablcę wag, ale jednorazowo. Założenie jest ze do obiektu nie można podłączyć innego obrazka więc ilość elementów interpolowanych nie zmieni się.
* \return OK jesli w porzadku
*/
bool C_LinearWeld::evalNextParams()
{
	_RPT0(_CRT_WARN,"\tEntering C_LinearWeld::evalNextParams");
#ifdef _DEBUG
	if(approx_results->getNumElem()<=0)
		_RPT0(_CRT_ASSERT,"C_LinearWeld::evalNextParams->pusty bufor");
#endif
	/// \warning Jeśli bufor nie pełny to może zajść rozbierzność pomiędzy buforami, tzn w różnych buforach kołowych może być różna ilość danych. Rozmiar danch tez ma znaczneie przy innych spawach niz liniowe. Trzeba pilnowac zeby zawsze tyle smo punktów było
	int num_el = approx_results->getNumElem(); // wielkość bufora
	int num_points = interp_lines->GetFirstInitialized()->getSizeofInterpData();
#ifdef _DEBUG
	int num_elrec = recalculated_approx_data->getNumElem(); // wielkość bufora
	_ASSERT(num_el==num_elrec); // powinny być tego samemgo rozmiaru te bufory
#endif
	//	C_Matrix_Container a(1,num_el);
	//	C_Matrix_Container b(1,num_el);
	//	C_Matrix_Container c(1,num_el);
	//	C_Matrix_Container d(1,num_el);
	//	C_Matrix_Container e(1,num_el);
	vector<double> a;
	vector<double> b;
	vector<double> c;
	vector<double> d;
	vector<double> e;
	//	C_Image_Container waga;	// pomocniczy do skalowania wag
	const double *p_par;	// parametry z bufora lub wektor wag
	// meidana z p - poszczególne elementy tego wektora z całego bufora są zbierane do jednego wektora
	_RPT1(_CRT_WARN,"\t\tSizebuff: %d",num_el);
	_RPT1(_CRT_WARN,"\t\tNumInterpElem: %d",num_points);
	// inicjalizacja wektora wag (globalny) inicjalizowany tylko raz
	_RPT1(_CRT_WARN,"\t\t_w = %p:",_w);
	if(NULL==_w)
	{
		_RPT0(_CRT_WARN,"\t\t_w initialized");
		_w = new double[num_points];
	}
	unsigned int l;
	for (int la=l=0;la<num_el;la++)
	{
		p_par = approx_results->GetObject(la)->getApproxParams_p(); if(NULL==p_par) continue;
		a.push_back(p_par[A]);
		b.push_back(p_par[B]);
		c.push_back(p_par[C]);
		d.push_back(p_par[D]);
		e.push_back(p_par[E]);
		l++; // do tego assert poniżej
	}
	_ASSERT(l==num_el);	// jeden element był NULL i mediana moze być fałszywa bo nie wszystkie elementy wypełnione
	_p[A] = getMedian<double>(a);
	_p[B] = getMedian<double>(b);
	_p[C] = getMedian<double>(c);
	_p[D] = getMedian<double>(d);
	_p[E] = getMedian<double>(e);

	// sprawdzanie czy parametry ub i lb nie są takie same (dla 0 moga być)

	/// \bug Dla parametru ujemnego może być że ub<lb. Poprawione poprzez dodanie fabs do parametrów.

	_ub[A] = _p[A] + fabs(_p[A])*0.3; if(0==_ub[A]) _ub[A] = 0.2;
	_ub[B] = _p[B] + fabs(_p[B])*0.3; if(0==_ub[B]) _ub[B] = 0.2;
	_ub[C] = _p[C] + fabs(_p[C])*0.2; if(0==_ub[C]) _ub[C] = 0.1;
	_ub[D] = _p[D] + fabs(_p[D])*0.3; if(0==_ub[D]) _ub[D] = 0.2;
	_ub[E] = _p[E] + fabs(_p[E])*0.3; if(0==_ub[E]) _ub[E] = 0.2;

	_lb[A] = _p[A] - fabs(_p[A])*0.3; if(0==_lb[A]) _lb[A] = -0.2;
	_lb[B] = _p[B] - fabs(_p[B])*0.3; if(0==_lb[B]) _lb[B] = -0.2;
	_lb[C] = _p[C] - fabs(_p[C])*0.2; if(0==_lb[C]) _lb[C] = -0.1;
	_lb[D] = _p[D] - fabs(_p[D])*0.3; if(0==_lb[D]) _lb[D] = -0.2;
	_lb[E] = _p[E] - fabs(_p[E])*0.3; if(0==_lb[E]) _lb[E] = -0.2;

	// wagi
	// wypełnienie zerami

	for(int ld=0;ld<num_points;++ld)	// dzielenie oprzez ilosc kazdej warotsci
		_w[ld] = 0.0;
	unsigned int real_num_el = 0;	// rzeczywista ilosc linii w buforze - gdy niektóre nie będą zainicjalizowane
	for(int la=0;la<num_el;la++)	// po liniach w buforze
	{
		p_par = recalculated_approx_data->GetObject(la); if(NULL==p_par) continue; // biore dane z la linii w buforze - to s a wartości z aproxymacji wypełnione w fillbufor i start na bierząco z innymi buforami razem
		real_num_el++;
		for(int ld=0;ld<num_points;ld++)
			_w[ld]+=p_par[ld];	// dodaje do bufora wag
	}
	for(int ld=0;ld<num_points;ld++)	// dzielenie oprzez ilosc kazdej warotsci
		_w[ld]/=real_num_el;

	// skalowanie wag do zakresu 01
	/// \todo Tu można przyspieszyć znacznie wykonując te operacje w miejscu - funkcja albo metoda statyczna lub stl
	/// \verbatim
	//	waga.AllocateData(1,num_points);
	//	waga.CopyfromTab(_w,num_points);
	//	waga.Normalize(0,1);
	/// \endverbatim
	// kopiowanie spowrotem
	//	memcpy_s(_w,num_points*sizeof(double),waga.data,waga.GetNumofElements()*sizeof(double));
	_RPT0(_CRT_WARN,"\tLeaving C_LinearWeld::evalNextParams\n");
	return OK;
}
/**
* Funkcja spawdza czy uzyskana interpolacja może być zaakceptowana.
* \param[in] _approx Wskaźnik do obiektu z aproksymacją linii
* \param[in] _interp Wskaźnik do obietu z interpolacją danych
* \return OK jeśli dane są akceptowalne, BLAD jeśli nie
*/
bool C_LinearWeld::czyAccept( const C_LineWeldApprox *_approx, const C_LineInterp *_interp )
{
	_RPT0(_CRT_WARN,"\tEntering C_LinearWeld::czyAccept");
	_RPT1(_CRT_WARN,"\t\terr=%.3e",_approx->getInfo(err));
	if(7==_approx->getInfo(stopreason)){
		_RPT0(_CRT_WARN,"\t\t Deleted: reason");
		return BLAD;
	}else // zbieram przydatne parametry
		if(_approx->getInfo(err)>MAX_ERROR_LEVEL){
			_RPT0(_CRT_WARN,"\t\t Deleted: error");
			return BLAD;
		}
		_RPT0(_CRT_WARN,"\tLeaving C_LinearWeld::czyAccept\n");
		return OK;
}
/**
* Oblicza pozycję spawu. Wersja używająca przeliczonych wartości funkcji aproxymacyjnej
* \param[in] _approx Wskaźnik do obiektu z aproksymacją linii
* \param[in] _interp Wskaźnik do obietu z interpolacją danych
* \param[in] _pre przeliczone dane z aproxymacji - celem przyspieszenia
* \param[out] _weldPos Dane o pozycji spawu
* \warning Dla inne,go przypdku aproxymacji należy sprwdzać czy prosta intepolacyjna była pionowa i odpowiednio brać dane x albo y do evaluacji wartości w klasie C_LineWeldApprox. Funkcja zakłąda ze dane _approx oraz _interp są spójne, tzn dotyczą tej samej linii obrazu
*/
void C_LinearWeld::evalWeldPos( const C_LineWeldApprox *_approx, const C_LineInterp *_interp,const double *_pre, C_WeldPos &_weldPos)
{
	_RPT0(_CRT_WARN,"\tEntering C_LinearWeld::evalWeldPos");
	//	double *evaldata = new double[_interp->getSizeofInterpData()]; // tablica na dane obliczone dla krzywej aproxymacyjnej
	unsigned int *indexy = new unsigned int[_interp->getSizeofInterpData()]; // tablica na indexy
	unsigned int l,licznik;
	const double *p;	// parametry aproxymacji
	double pos;
	const double *x,*y;	// wskazniki na wektory x i y dla których została wykonan interpolacja i aproxymacja (współrzędne obrazu)
	double max_el,max_lin;	// wartosc maksymalna funkcji aproxymującej

	x = _interp->getInterpolated_X();
	y = _interp->getInterpolated_Y();
	// 	_approx->evalApproxFcnVec(y,evaldata,_interp->getSizeofInterpData());
	for(l=0,max_el = _pre[0];l<_interp->getSizeofInterpData();++l)
		if(_pre[l]>max_el)
			max_el = _pre[l];	// w max_el wartość maxymalna
	// wartość maxymalna nie jest od zera ale ma jakiś liniowy trend dodany - trzeba to uwzględnić. Dlatego liczona jest wartość funkcji liniowej skojarzonej z gaussem i dopiero róznica jest brana jako wysokość piku. Wszystko liczone jest względem punktu maximum, więc dla dużego tendu może być błędne
	_RPT1(_CRT_WARN,"\t\tmax_el: %.1lf",max_el);
	// znajdowanie indeksów z wartością max
	for (l=licznik=0;l<_interp->getSizeofInterpData();++l)
		if(_pre[l]==max_el)
			indexy[licznik++] = l;	// w indexy pozycje elementów maksymalnych (jeśli więcej niż 1 to liczymy średnią)
	pos = 0.0;
	for(l=0;l<licznik;++l)	// po wszyskich pozycjach el. maksymalnych
		pos+=(double)indexy[l];
	pos/=licznik;	// w pos pozycja środka, uśredniona jeśli było więcej maximów
	pos = floor(pos+0.5);	// zaokraglona do całkowitej
	_RPT1(_CRT_WARN,"\t\tmax_el_pos: %d",(int)pos);
	_weldPos.S.setPoint(x[(int)pos],y[(int)pos]); // ustawiam pozycję środka na wyjściu
	_RPT2(_CRT_WARN,"\t\t_weldPos.S.setPoint(%.1lf,%.1lf])",x[(int)pos],y[(int)pos]);

	p = _approx->getApproxParams_p();
	max_lin = y[(int)pos]*p[D]+p[E]; // wartość trendu dla pozycji max
	_RPT1(_CRT_WARN,"\t\tmax_lin = %lf.1",max_lin);

	// górna granica od środka do końca
	licznik = 0;
	for(l=(unsigned int)pos;l<_interp->getSizeofInterpData();++l)
		if(_pre[l]<max_lin+(max_el-max_lin)*weld_edge)	{	// procent wysokości piku + przesunięcie liniowe
			indexy[licznik++] = l;	// pierwszy element to pozycja górnej granicy
			break;	// nie ma potrzeby analizowania pozostałych el
		}
		/// \warning Może się zdażyć ze nie bedzie w ifie i wtedy wartość indexy niezdefiniowana, wtedy przyjmuje ostatni i pierwszy element. Tak się zdaża gdy aproxymowane są złe dane i funkcja aproxymująca jest zbyt szeoka, tzn obeajmuje cały obraz i nie daje rady zmaleć do żądanego zakresu.
		if(0==licznik)
			indexy[0] = _interp->getSizeofInterpData()-1;// ostatni element
		_weldPos.G.setPoint(x[indexy[0]],y[indexy[0]]); // ustawiam pozycję góry na wyjściu
		_RPT2(_CRT_WARN,"\t\t_weldPos.G.setPoint(%.1lf,%.1lf])",x[indexy[0]],y[indexy[0]]);

		// dolna granica do środka
		licznik = 0;
		for(l=(unsigned int)pos+1;l>0;--l) // +1aby uniknąć błędu z przekręceniem się zakresu!!
			if(_pre[l-1]<max_lin+(max_el-max_lin)*weld_edge)	{
				indexy[licznik++] = l-1;	// pierwszy element to pozycja górnej granicy
				break;	// nie ma potrzeby analizowania pozostałych el
			}
			/**
			* \warning - w tym kodzie występuje bardzo ciekawy błąd:
			* \code
			licznik = 0;
			for(l=(unsigned int)pos;l>=0;--l)
			if(_pre[l]<max_lin+(max_el-max_lin)*WELD_EDGE)	{
			indexy[licznik++] = l;	// pierwszy element to pozycja górnej granicy
			break;	// nie ma potrzeby analizowania pozostałych el
			}
			* \endcode
			* l jest zdefinoowane jako uint i biorąc pod uwagę kolejnosc działania for to dla l=1 zostanie
			* wykonane pętla, następnie l będzie zmniejszone o 1, sprawdzony warunek (będzie na tak) i dalej
			* wykona się petla, zmiejszy się l o 1 i tu następuje przekręcenie zakresu bo l jest uint!! a warunek cięgle będzie
			* spełniony bo l>0
			*/

			if(0==licznik)
				indexy[0] = 0;// pierwszy element
			_weldPos.D.setPoint(x[indexy[0]],y[indexy[0]]); // ustawiam pozycję środka na wyjściu
			_RPT2(_CRT_WARN,"\t\t_weldPos.D.setPoint(%.1lf,%.1lf])",x[indexy[0]],y[indexy[0]]);

			_RPT1(_CRT_WARN,"\t\tmaxlin: %.3lf",max_lin);
			_RPT2(_CRT_WARN,"\t\tG: [%.1lf,%.1lf]",_weldPos.G.getX(),_weldPos.G.getY());
			_RPT2(_CRT_WARN,"\t\tS: [%.1lf,%.1lf]",_weldPos.S.getX(),_weldPos.S.getY());
			_RPT2(_CRT_WARN,"\t\tD: [%.1lf,%.1lf]",_weldPos.D.getX(),_weldPos.D.getY());

			//	SAFE_DELETE(evaldata);
			SAFE_DELETE(indexy);
			_RPT0(_CRT_WARN,"\tLeaving C_LinearWeld::evalWeldPos\n");
}
/** \example WeldDetecApprox_example.cpp
* Przykład użycia klasy
*/
