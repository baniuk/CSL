#include "stdafx.h"
#include "rulinter.hpp"

using namespace std;

/*! \file rulinter.cpp
    \brief Plik z klas¹ RulInter tworz¹c¹ bibliotekê dll_rulproj.dll dla LabView niezbêdn¹ dla klasyfikacji wad po³¹czeñ spawalniczych
    \details Dostêpne s¹ nastêpuj¹ce metody:<br/>
	RulInter::RulInter(long wyb)<br/>
	Konstruktor klasy z wyborem sposobu wykonywania klasyfikacji<br/>
	RulInter::~RulInter()<br/>
	Destruktor klasy zwalniaj¹cy alokowan¹ pamiêæ<br/>
	void RulInter::configuration()<br/>
	Metoda konfiguruj¹ca przypisanie poszczególnych kolumn struktury wewnêtrznej do kolumn oznaczonych jako X1,X2 itd.<br/>
	void RulInter::alocDane(long wys,long szer)<br/>
	Metoda do alokacji wewnêtrznej struktury<br/>
	void RulInter::dealocDane(long wys,long szer)<br/>
	Metoda do zwalniania pamiêci zajmowanej przez wewnêtrzn¹ strukturê<br/>
	int RulInter::loadFile(char *name)<br/>
	Metoda ³aduj¹ca dane z zewnêtrznego pliku<br/>
	void RulInter::show()<br/>
	Metoda pomocnicza do prezentacji wybranych danych<br/>
	double RulInter::map(long w, long k)<br/>
	Metoda mapuj¹ca kolumnê strukury wed³ug wartoœci zmiennej np.X3 (dla metody configuration())<br/>
	void RulInter::transform(double *dane1,long row, long col)<br/>
	Metoda transformuj¹ca p³ask¹ strukturê na tablicê dwuwymiarow¹<br/>
	void RulInter::induct(int *out,long opt)<br/>
	Metoda do klasyfikacji z wykorzystaniem indukowanych regu³<br/>
	void RulInter::WyswietlRule()<br/>
	Metoda pomocnicza do wyœwietlania regu³<br/>
    void RulInter::RSS(double *in, long row, long col, int *out,C_Error *err)<br/>
	Metoda do generowania wyników klasyfikacji<br/>
	void RulInter::TestLogic()<br/>
	Metoda pomocnicza do testowania logiki dla wewnêtrznej struktury<br/>
	void RulInter::showWierszdane()<br/>
	Metoda pomocnicza do wyœwietlania wiersza danych<br/>
	void RulInter::ZapiszRule4()<br/>
	Metoda dla regu³ momentowych jednoatrybutowych<br/>
	void RulInter::ZapiszRule1()<br/>
	Metoda dla regu³ niemomentowych<br/><br/>
	\author LM
	\see rulinter.hpp
*/

/*! \class RulInter
	\brief Plik z klas¹ RulInter tworz¹c¹ bibliotekê dll_rulproj.dll dla LabView niezbêdn¹ dla klasyfikacji wad po³¹czeñ spawalniczych
	\details Dostêpne s¹ nastêpuj¹ce metody:<br/>
	RulInter::RulInter(long wyb)<br/>
	Konstruktor klasy z wyborem sposobu wykonywania klasyfikacji<br/>
	RulInter::~RulInter()<br/>
	Destruktor klasy zwalniaj¹cy alokowan¹ pamiêæ<br/>
	void RulInter::configuration()<br/>
	Metoda konfiguruj¹ca przypisanie poszczególnych kolumn struktury wewnêtrznej do kolumn oznaczonych jako X1,X2 itd.<br/>
	void RulInter::alocDane(long wys,long szer)<br/>
	Metoda do alokacji wewnêtrznej struktury<br/>
	void RulInter::dealocDane(long wys,long szer)<br/>
	Metoda do zwalniania pamiêci zajmowanej przez wewnêtrzn¹ strukturê<br/>
	int RulInter::loadFile(char *name)<br/>
	Metoda ³aduj¹ca dane z zewnêtrznego pliku<br/>
	void RulInter::show()<br/>
	Metoda pomocnicza do prezentacji wybranych danych<br/>
	double RulInter::map(long w, long k)<br/>
	Metoda mapuj¹ca kolumnê strukury wed³ug wartoœci zmiennej np.X3 (dla metody configuration())<br/>
	void RulInter::transform(double *dane1,long row, long col)<br/>
	Metoda transformuj¹ca p³ask¹ strukturê na tablicê dwuwymiarow¹<br/>
	void RulInter::induct(int *out,long opt)<br/>
	Metoda do klasyfikacji z wykorzystaniem indukowanych regu³<br/>
	void RulInter::WyswietlRule()<br/>
	Metoda pomocnicza do wyœwietlania regu³<br/>
    void RulInter::RSS(double *in, long row, long col, int *out,C_Error *err)<br/>
	Metoda do generowania wyników klasyfikacji<br/>
	void RulInter::TestLogic()<br/>
	Metoda pomocnicza do testowania logiki dla wewnêtrznej struktury<br/>
	void RulInter::showWierszdane()<br/>
	Metoda pomocnicza do wyœwietlania wiersza danych<br/>
	void RulInter::ZapiszRule4()<br/>
	Metoda dla regu³ momentowych jednoatrybutowych<br/>
	void RulInter::ZapiszRule1()<br/>
	Metoda dla regu³ niemomentowych<br/><br/>
	\author LM
	\see rulinter.hpp
*/

/** \brief Konstruktor klasy z wyborem sposobu wykonywania klasyfikacji
	\param [in] wyb - wybór rodzaju u¿ywanych regu³: 1 - regu³y momentowe jednoatrybutowe, 2 - regu³y niemomentowe 
	\author LM
*/
RulInter::RulInter(long wyb)
{
 X3=0; X4=1; X5=2; X6=3; X7=4; X8=5; X9=6;
 X10=7; X11=8; X12=9; X13=10; X14=11; X15=12; X16=13; X17=14; X18=15; X19=16;
 X20=17; X21=18; X22=19; X23=20; X24=21; X25=22; X26=23; X27=24; X28=25; X29=26;
 X30=27; X31=28; X32=29; X33=30; X34=31; X35=32; 
 X40=33; X43=34; X44=35; 
 X52=36; X53=37; X54=38; X55=39; X56=40; X57=41; X58=42; X59=43;
 X60=44; X61=45; X62=46; X63=47; X64=48; X65=49; X66=50; X67=51; X68=52; X69=53;
 X70=54; X71=55; X72=56; X73=57; X74=58; X75=59;
 
 dlugosc = 150; 
 check1 = false;
 if(wyb == 4) dl_inx = 22; else if(wyb == 1) dl_inx= 112;; //ilosc regul
// cout << "Ilosc regul: " << dl_inx << endl;
 wybor = wyb; //wybor rodzaju regul, 4 - reguly momentowe jednoatrybutowe, 1 - reguly niemomentowe

  if(wybor == 4)
  {
    ZapiszRule4();
  } //koniec  if(wybor == 4)
  if(wybor == 1)
  {
    ZapiszRule1();           
  } //koniec wybor == 1
 
}

/** \brief Destruktor klasy zwalniaj¹cy alokowan¹ pamiêæ
	\author LM
*/
RulInter::~RulInter()
{
  if(check1 == true) dealocDane(wier,kol);
}

/** \brief  S³u¿y do przypisania faktycznego parametru do indeksu przekazywanej tablicy 
	np. parametrowi X3 odpowiada na przyk³ad wyd³u¿enie i wskazuje na indeks 0 danych, dlatego jest zapis X3=0
	\author LM
*/
void RulInter::configuration()
{
 X3=0; X4=1; X5=2; X6=3; X7=4; X8=5; X9=6;
 X10=7; X11=8; X12=9; X13=10; X14=11; X15=12; X16=13; X17=14; X18=15; X19=16;
 X20=17; X21=18; X22=19; X23=20; X24=21; X25=22; X26=23; X27=24; X28=25; X29=26;
 X30=27; X31=28; X32=29; X33=30; X34=31; X35=32; 
 X40=33; X43=34; X44=35; 
 X52=36; X53=37; X54=38; X55=39; X56=40; X57=41; X58=42; X59=43;
 X60=44; X61=45; X62=46; X63=47; X64=48; X65=49; X66=50; X67=51; X68=52; X69=53;
 X70=54; X71=55; X72=56; X73=57; X74=58; X75=59;
}


/** \brief Metoda do alokacji wewnêtrznej struktury
	\param [in] wys - iloœæ kolumn dla alokowanej strukturzy wewnêtrznej
	\param [in] szer - iloœæ wierszy dla alokowanej strukturzy wewnêtrznej
	\author LM
*/
void RulInter::alocDane(long wys,long szer)
{
 long i;
 long szer1 = szer + 1;
 dane = new double*[wys];
 for(i = 0 ; i < wys ; i++)
    dane[i] = new double[szer1];                            
 check1 = true;
}

/** \brief Metoda do dealokacji wewnêtrznej struktury danych
	\param [in] wys - iloœæ kolumn dla dealokowanej strukturzy wewnêtrznej
	\param [in] szer - iloœæ wierszy dla dealokowanej strukturzy wewnêtrznej
	\author LM
*/
void RulInter::dealocDane(long wys,long szer)
{
 long i;
 for(i = 0 ; i < wys ; i++)
  delete[] dane[i];
 delete[] dane;                              
}


/** \brief Metoda ³aduj¹ca dane z zewnêtrznego pliku
	\param [in] name - nazwa pliku (okreœlona struktura) z którego ³adowane s¹ dane
	\return wartosc 1 oznacza prawid³owe zakoñczenie metody
	\author LM
*/
int RulInter::loadFile(char *name)
{
 if(check1 == true) dealocDane(wier,kol);
 ifstream in(name);
 in >> kol;
 in >> wier;
 
 alocDane(wier,kol);
 //ladowanie danych
 long i,j;
  for(j=0 ; j<wier ; j++) 
   for(i=0 ; i<kol ; i++)
    in >> dane[j][i];
 
 in.close();
 return 1;
}

/** \brief Metoda pomocnicza do prezentacji wybranych danych
	\author LM
*/
void RulInter::show()
{
 cout << kol << " | " << wier << endl;
 cout << "Dane:" << endl;
 
 long i;
 
 cout << endl << "1szy rz¹d:" << endl;
 for(i = 0 ; i< kol ; i++)
   cout << dane[0][i] << " ";
   
 cout << endl << "2gi rz¹d:" << endl;
 for(i = 0 ; i< kol ; i++)
   cout << dane[1][i] << " ";

 
 long last = wier - 1;  
 cout << endl << "Ostatni rz¹d:" << endl;
 for(i = 0 ; i< kol ; i++)
   cout << dane[last][i] << " ";
   
   cout << endl;
 
}

/** \brief Metoda mapuj¹ca kolumnê strukury wed³ug wartoœci zmiennej np.X3 (dla metody configuration())
	\param [in] w - numer wiersza w strukturze wewnêtrznej
	\param [in] k - numer kolumny mapowanej w strukturze wewnêtrznej np. k=1 odpowiada X1
	\return zwraca wartoœæ struktury zawartej w wierszu w oraz kolumnie k np. k=1 odpowiada X1
	\author LM
*/
double RulInter::map(long w, long k)
{
  switch(k)
  {
   case 1: return dane[w][X1];
   case 2: return dane[w][X2];
   case 3: return dane[w][X3];
   case 4: return dane[w][X4];
   case 5: return dane[w][X5];
   case 6: return dane[w][X6];
   case 7: return dane[w][X7];
   case 8: return dane[w][X8];
   case 9: return dane[w][X9];
   case 10: return dane[w][X10];
   case 11: return dane[w][X11];
   case 12: return dane[w][X12];
   case 13: return dane[w][X13];
   case 14: return dane[w][X14];
   case 15: return dane[w][X15];
   case 16: return dane[w][X16];
   case 17: return dane[w][X17];
   case 18: return dane[w][X18];
   case 19: return dane[w][X19];
   case 20: return dane[w][X20];
   case 21: return dane[w][X21];
   case 22: return dane[w][X22];
   case 23: return dane[w][X23];
   case 24: return dane[w][X24];
   case 25: return dane[w][X25];
   case 26: return dane[w][X26];
   case 27: return dane[w][X27];
   case 28: return dane[w][X28];
   case 29: return dane[w][X29];
   case 30: return dane[w][X30];
   case 31: return dane[w][X31];
   case 32: return dane[w][X32];
   case 33: return dane[w][X33];
   case 34: return dane[w][X34];
   case 35: return dane[w][X35];
   case 36: return dane[w][X36];
   case 37: return dane[w][X37];
   case 38: return dane[w][X38];
   case 39: return dane[w][X39];
   case 40: return dane[w][X40];
   case 41: return dane[w][X41]/10000;
   case 42: return dane[w][X42]/10000;
   case 43: return dane[w][X43];
   case 44: return dane[w][X44];
   case 45: return dane[w][X45]/10000;
   case 46: return dane[w][X46]/1000000;
   case 47: return dane[w][X47]/10000;
   case 48: return dane[w][X48]/10000000;
   case 49: return dane[w][X49]/100000;
   case 50: return dane[w][X50]/100000000;
   case 51: return dane[w][X51]/100000;
   case 52: return dane[w][X52];
   case 53: return dane[w][X53];
   case 54: return dane[w][X54];
   case 55: return dane[w][X55];
   case 56: return dane[w][X56];
   case 57: return dane[w][X57];
   case 58: return dane[w][X58];
   case 59: return dane[w][X59];
   case 60: return dane[w][X60];
   case 61: return dane[w][X61];
   case 62: return dane[w][X62];
   case 63: return dane[w][X63];
   case 64: return dane[w][X64];
   case 65: return dane[w][X65];
   case 66: return dane[w][X66];
   case 67: return dane[w][X67];
   case 68: return dane[w][X68];
   case 69: return dane[w][X69];
   case 70: return dane[w][X70];
   case 71: return dane[w][X71];
   case 72: return dane[w][X72];
   case 73: return dane[w][X73];
   case 74: return dane[w][X74];
   case 75: return dane[w][X75];
   case 76: return dane[w][X76];
   case 77: return dane[w][X77];
   case 78: return dane[w][X78];
   case 79: return dane[w][X79];
  } //koniec case
 return -1;
}

/** \brief Metoda transformuj¹ca p³ask¹ strukturê na wewnêtrzn¹ tablicê dwuwymiarow¹
	\param [in] dane1 - wskaŸnik na jednowymiarow¹ strukturê wejœciow¹ (tablica dwuwymiarowa zapisana w jedym wymiarze)
	\param [in] row - iloœæ wierszy w danych wejœciowych - dane1
	\param [in] col - iloœæ komlumn w danych wejœciowych - dane1
	\author LM
*/
void RulInter::transform(double *dane1,long row, long col)
{
 long rows = row;
 long cols = col;
 
 if(check1 == true) dealocDane(rows,cols);
 alocDane(rows,cols);

 wier = rows;
 kol = cols;
 
 long i,j;
   for(i=0 ; i<rows ; i++)
      for(j=0 ; j<cols ; j++) 
          dane[i][j] = dane1[i*cols + j];
 
}

/** \brief Metoda pomocnicza do wyœwietlania regu³
	\author LM
*/
void RulInter::WyswietlRule()
{
 long i,j;
 long idx=0;

//dla kazdej reguly
for(idx = 0 ; idx < dl_inx ; idx++)
{
 //petla zewnetrzna dla regul sekcja OR
 for(j=0 ; j<dl_reg[idx]; j++)
 {
   // dla kazdej reguly
   cout << "Regula nr " << j << endl;
   cout << "X" << rul[idx][j][0] << " = " << endl;
   // j - numer reguly, i - numery przedzialow wartosci
   for(i=2 ; i<=(rul[idx][j][1] + 1) ; i+=2)
   {
     if(rul[idx][j][i] != rul[idx][j][i+1])
        cout << "(" << rul[idx][j][i] << "," << rul[idx][j][i+1] << ")"; // nierowne wartosci
     else
        cout << "(" << rul[idx][j][i] << ")";
        
     if(i != rul[idx][j][1]) cout << " lub ";
   }
 
 }//koniec petli for zewnetrznej - j
}//koniec petli idx

}


/** \brief Metoda do klasyfikacji z wykorzystaniem indukowanych regu³
	\param [out] out - wskaŸnik na jednowymiarow¹ tablicê z wynikami klasyfikacji (alokacja na zewn¹trz)
	\param [in] opt - opcja rozwi¹zywania konfliktów w regu³ach (kilka regu³ wskazuje na ró¿ne klasy)
	opt = 1 - przypisanie klasy wed³ug kolejnoœci regu³ (pierwsza napotkana regu³a przypisuje wartoœæ klasy)
	opt = 2 - Simple Voting - klasa jest wybrana, je¿eli najwiêcej regu³ na ni¹ wskazuje (wiêcej ni¿ na pozosta³e klasy)
	\author LM
*/
void RulInter::induct(int *out,long opt)
{
 long i,j,idx,k,d1,i1;
 long xx; //numer biezacej zmiennej np. 40 dla X40
 double wartosc; //biezaca wartosc w danych
 bool logtmp;
 bool koncowa; 
 long klasy[6]; // zmienna na potrzeby Simple Voting klasy[1] - ilosc klas dla regul
 
   //zerowanie wynikow
   for(k=0 ; k<wier ; k++)
     out[k] = -1;
   //zerowanie klas
   for(i1=0 ; i1<=5 ; i1++) klasy[i1]=0;
 
  //petla zewnetrzna dla wiersza danych wejsciowych
  for(d1=0 ; d1<wier ; d1++)
  {
             
     //petla zewnetrzna dla numeru reguly
     for(idx= 0 ; idx< dl_inx ; idx++)
     {


      if(opt == 1) //opcja opt = 1
      {
        //jezeli klasa jest juz ustawiona to idziemy dalej
         if(out[d1] != -1) break;
         
      }else if(opt == 2) // Simple Voting
      {
            
      
      }
    
      //inicjalizacja tablicy     
       for(k=0 ; k<dlugosc ; k++)
            logic[k] = false;
      
      //petla zewnetrzna dla AND
      for(j=0 ; j< dl_reg[idx] ; j++)
      {     
        xx = (long)rul[idx][j][0];
        wartosc = map(d1,xx);
       // cout << "X40 = " << wartosc << "xx = " << xx << " dane[d1][X40] = " << dane[d1][X40] << "d1 = " << d1 <<endl;
        //petla wewnetrzna dla OR
        logtmp = false;
        for(i=2 ; i<=(rul[idx][j][1]+1) ; i+=2)
        {
          //czy przedzial dolny i gorny sa takie same
          if(rul[idx][j][i] != rul[idx][j][i+1])
          {
            //old logic
            //logtmp = (wartosc > rul[idx][j][i] && wartosc <= rul[idx][j][i+1]);
            //new logic
            logtmp = (wartosc >= rul[idx][j][i] && wartosc < rul[idx][j][i+1]);
          }
          else
          {
            logtmp = (wartosc == rul[idx][j][i]);
          }
           //uaktualnienie zmiennej logic[i] 
           logic[j] = logic[j] || logtmp;
           //jezeli jest juz true dla operacji OR nie ma sensu kontynuacja petli
           /*if(logic[j]  && (d1==32) /*&& (idx==13) nr reguly )
            {
              cout << "Informacja o trafieniu dla wiersza danych: " << (d1+1)  << " Regula: " << (idx+1) << endl;
              cout << "X" << rul[idx][j][0] << " = " << wartosc << " klasa = " << (long)dec[idx] << " dolny = " << rul[idx][j][i] << " gorny = " << rul[idx][j][i+1] <<endl;
            }*/
           if(logic[j]) break;
           
           
         }// koniec petli for dla i
       }// koniec dla j
      
        //ustalenie wartosci koncowej dla reguly
        koncowa = logic[0];
        for(k=0 ; k<dl_reg[idx] ; k++)
          koncowa = (koncowa && logic[k]);

        if(opt == 1) //opt = 1
        {
          if(koncowa) out[d1] = (long)dec[idx]; // else out[d1]=-1;
          //jezeli regula trafila nie ma sensu kontynuwac
          if(koncowa) break;
        }else if(opt == 2) // Simple Voting
        {
          //ustawienie ilosci klas
          if(koncowa) klasy[dec[idx]]++;    
        }
          

     } //koniec petli idx
      
      //ustawienie numeru klasy

      if(opt == 2) // Simple Voting
      {
        long ktora_klasa;
        
        //zmieniami kod uwzgledniajacy kolejnosc klas tj.1,3,5,2,4
        ktora_klasa=1;
        if(klasy[3]>=klasy[ktora_klasa]) ktora_klasa=3;
        if(klasy[5]>=klasy[ktora_klasa]) ktora_klasa=5;
        if(klasy[2]>=klasy[ktora_klasa]) ktora_klasa=2;
        if(klasy[4]>=klasy[ktora_klasa]) ktora_klasa=4;
        
        
        //zmieniami kod uwzgledniajacy kolejnosc klas tj.5,4,3,2,1
        /*
        ktora_klasa=5;
        if(klasy[4]>klasy[ktora_klasa]) ktora_klasa=4;
        if(klasy[3]>klasy[ktora_klasa]) ktora_klasa=3;
        if(klasy[2]>klasy[ktora_klasa]) ktora_klasa=2;
        if(klasy[1]>klasy[ktora_klasa]) ktora_klasa=1;
        */
        
        //zmieniami kod uwzgledniajacy kolejnosc klas tj.4,2,5,3,1
        /*
        ktora_klasa=4;
        if(klasy[2]>klasy[ktora_klasa]) ktora_klasa=2;
        if(klasy[5]>klasy[ktora_klasa]) ktora_klasa=5;
        if(klasy[3]>klasy[ktora_klasa]) ktora_klasa=3;
        if(klasy[1]>klasy[ktora_klasa]) ktora_klasa=1;
        */
        
        /*ktora_klasa = 1;
        for(i1=2 ; i1<=5 ; i1++)       
        {
          if(klasy[i1] > klasy[ktora_klasa]) ktora_klasa=i1;
        }

        //ustawienie ostatecznej klasy*/

        if(klasy[ktora_klasa]<=0) ktora_klasa = -1;        
        out[d1] = ktora_klasa;
        //cout << "Wiersz nr " << d1+1 << ": k[1]= " <<klasy[1] <<" k[2]= " <<klasy[2] << " k[3]= " << klasy[3] << " k[4]= " << klasy[4] << " k[5]= " << klasy[5] << " ktora_klasa= " << ktora_klasa <<endl;
        //zerowanie numerow klas
        for(i1=0 ; i1<=5 ; i1++) klasy[i1]=0;
      }
     
 } //koniec petli d1 dla danych

}//koniec metody induct


/** \brief Metoda do generowania wyników klasyfikacji
	\param [in] in - wskaŸnik na jednowymiarow¹ tablicê z danymi wejœciowymi do klasyfikacji (dwuwymiarowa tablica zapisana w jedym wymiarze)
	\param [in] row - iloœæ wierszy w tablicy wejœciowej
	\param [in] col - iloœæ kolumn w tablicy wejœciowej
	\param [out] out - wskaŸnik na jednowymiarow¹ tablicê z wynikami klasyfikacji (alokacja na zewn¹trz)
	\param [out] err - wskaŸnik klasê C_Error z opisem b³êdu wykonania (obecnie nie jest wykorzystywana)
	\author LM
*/
void RulInter::RSS(double *in, long row, long col, int *out,C_Error *err)
{
    transform(in,row,col);
    //2 oznacza simple voting
    induct(out,2);
}//koniec RSS


/** @method RulInter::TestLogic
	\brief Metoda pomocnicza do testowania logiki dla wewnêtrznej struktury
	\author LM
*/
void RulInter::TestLogic()
{
 bool log=false,tmplog;    
 double dd[2];
 double wartosc = 223.22;
 dd[0] = 123.23;
 dd[1] = 223.23;
 
 cout << endl << "Test logic:" << endl;
 tmplog = (wartosc >= dd[0] && wartosc < dd[1]);
 log = (log || tmplog);
 cout << tmplog << endl;
 cout << endl << "End test logic." << endl;
 
 cout << "dane[0][0] = " << dane[0][0] << endl;
 cout << "dane[1][0] = " << dane[1][0] << endl;
 cout << "dane[2][0] = " << dane[2][0] << endl;
 cout << "dane[3][0] = " << dane[3][0] << endl;
 
 cout << "dane[0][0] = " << dane[0][0] << endl;
 cout << "dane[0][1] = " << dane[0][1] << endl;
 cout << "dane[0][2] = " << dane[0][2] << endl;
 cout << "dane[0][3] = " << dane[0][3] << endl;
 
 cout << "dane[0][wier-3] = " << dane[0][wier-3] << endl;
 cout << "dane[0][wier-2] = " << dane[0][wier-2] << endl;
 cout << "dane[0][wier-1] = " << dane[0][wier-1] << endl;
 
 cout << "dane[0][0] = " << dane[0][0] << endl;
 cout << "dane[0][1] = " << dane[0][1] << endl;
 cout << "dane[0][2] = " << dane[0][2] << endl;
 cout << "dane[0][3] = " << dane[0][3] << endl;

 
 cout << "dane[wier-1][kol-1] = " << dane[wier-1][kol-1] << endl;
 cout << "map[0][X3] = " << map(0,3) << endl;

 cout << "dane[wier-1][60] = " << dane[wier-1][60] << endl; 
  cout << "dane[wier-1][X67] = " << dane[wier-1][X67] << endl; 
 cout << "map[wier-1][X75] = " << map(wier-1,75) << endl;
 
 cout << "map[0][X40] = " << map(0,40) << endl;
 cout << "map[1][X40] = " << map(1,40) << endl;
 cout << "map[wier-2][X40] = " << map(wier-2,40) << endl;
 cout << "map[wier-1][X40] = " << map(wier-1,40) << endl;
}

/** \brief Metoda pomocnicza do wyœwietlania wiersza danych
	\author LM
*/
void RulInter::showWierszdane()
{
 long i=0;
 cout << "Pierwszy wiersz danych :" << endl;

/* X3=0; X4=1; X5=2; X6=3; X7=4; X8=5; X9=6;
 X10=7; X11=8; X12=9; X13=10; X14=11; X15=12; X16=13; X17=14; X18=15; X19=16;
 X20=17; X21=18; X22=19; X23=20; X24=21; X25=22; X26=23; X27=24; X28=25; X29=26;
 X30=27; X31=28; X32=29; X33=30; X34=31; X35=32; 
 X40=33; X43=34; X44=35; 
 X52=36; X53=37; X54=38; X55=39; X56=40; X57=41; X58=42; X59=43;
 X60=44; X61=45; X62=46; X63=47; X64=48; X65=49; X66=50; X67=51; X68=52; X69=53;
 X70=54; X71=55; X72=56; X73=57; X74=58; X75=59; 
 */
 /*
 cout << "X3=" << map(i,3) << " X4=" << map(i,4) << " X5=" << map(i,5) << " X6=" << map(i,6) << " X7=" << map(i,7) << " X8=" << map(i,8) << " X9=" << map(i,9);
 cout << "X10=" << map(i,10) << " X11=" << map(i,11) << " X12=" << map(i,12) << " X13=" << map(i,13) << " X14=" << map(i,14) << " X15=" << map(i,15) << " X16=" << map(i,16) << " X17=" << map(i,17) << " X18=" << map(i,18) << " X19=" << map(i,19) << endl;
 cout << "X20=" << map(i,20) << " X21=" << map(i,21) << " X22=" << map(i,22) << " X23=" << map(i,23) << " X24=" << map(i,24) << " X25=" << map(i,25) << " X26=" << map(i,26) << " X27=" << map(i,27) << " X28=" << map(i,28) << " X29=" << map(i,29) << endl;     
 cout << "X30=" << map(i,30) << " X31=" << map(i,31) << " X32=" << map(i,32) << " X33=" << map(i,33) << " X34=" << map(i,34) << " X35=" << map(i,35) << endl;
 cout << "X40=" << map(i,40) << " X43=" << map(i,43) << " X44=" << map(i,44) << endl;
 cout << "X52=" << map(i,52) << " X53=" << map(i,53) << " X54=" << map(i,54) << " X55=" << map(i,55) << " X56=" << map(i,56) << " X57=" << map(i,57) << " X58=" << map(i,58) << " X59=" << map(i,59) << endl;
 cout << "X60=" << map(i,60) << " X61=" << map(i,61) << " X62=" << map(i,62) << " X63=" << map(i,63) << " X64=" << map(i,64) << " X65=" << map(i,65) << " X66=" << map(i,66) << " X67=" << map(i,67) << " X68=" << map(i,68) << " X69=" << map(i,69) << endl;           
 cout << "X70=" << map(i,70) << " X71=" << map(i,71) << " X72=" << map(i,72) << " X73=" << map(i,73) << " X74=" << map(i,74) << " X75=" << map(i,75) << endl;
 */
 
 cout << "X40=" << map(i,40) << " X43=" << map(i,43) << " X54=" << map(i,54) << " X57=" << map(i,57) << " X66=" << map(i,66) << endl;
 i = 1;
 cout << "Drugi wiersz danych :" << endl;
 cout << "X40=" << map(i,40) << " X43=" << map(i,43) << " X54=" << map(i,54) << " X57=" << map(i,57) << " X66=" << map(i,66) << endl;
 cout << "Wiersz 24 :" << endl; i=23;
 cout << "X40=" << map(i,40) << " X43=" << map(i,43) << " X54=" << map(i,54) << " X57=" << map(i,57) << " X66=" << map(i,66) << endl;
 cout << "Wiersz 519 :" << endl; i=518;
 cout << "X40=" << map(i,40) << " X43=" << map(i,43) << " X54=" << map(i,54) << " X57=" << map(i,57) << " X66=" << map(i,66) << endl;
 
}

/** \brief Metoda dla regu³ momentowych jednoatrybutowych
	\author LM
*/
void RulInter::ZapiszRule4()
{
 double min = -DBL_MAX;
 double max = DBL_MAX;


// 1. Regula
// 1. sekcja AND 1 reguly.
rul[0][0][0]=40; rul[0][0][1]=368; 
rul[0][0][2]=20334.5; rul[0][0][3]=21550.5; rul[0][0][4]=55756.0; rul[0][0][5]=58048.0; rul[0][0][6]=47732.0; rul[0][0][7]=48867.5; 
rul[0][0][8]=678695.0; rul[0][0][9]=683362.0; rul[0][0][10]=146757.0; rul[0][0][11]=148010.0; rul[0][0][12]=225831.0; rul[0][0][13]=227967.0; 
rul[0][0][14]=53467.5; rul[0][0][15]=54037.0; rul[0][0][16]=1.00615E7; rul[0][0][17]=1.08019E7; rul[0][0][18]=26787.0; rul[0][0][19]=27742.0; 
rul[0][0][20]=67028.0; rul[0][0][21]=67807.5; rul[0][0][22]=151848.0; rul[0][0][23]=152626.0; rul[0][0][24]=1163850.0; rul[0][0][25]=1172580.0; 
rul[0][0][26]=1.95785E7; rul[0][0][27]=2.22966E7; rul[0][0][28]=68676.0; rul[0][0][29]=69773.5; rul[0][0][30]=2679000.0; rul[0][0][31]=2786820.0; 
rul[0][0][32]=93403.0; rul[0][0][33]=94764.0; rul[0][0][34]=46337.5; rul[0][0][35]=47065.5; rul[0][0][36]=2148850.0; rul[0][0][37]=2166370.0; 
rul[0][0][38]=67958.5; rul[0][0][39]=68483.5; rul[0][0][40]=354224.0; rul[0][0][41]=356073.0; rul[0][0][42]=25672.0; rul[0][0][43]=25898.5; 
rul[0][0][44]=31010.5; rul[0][0][45]=31382.5; rul[0][0][46]=4598350.0; rul[0][0][47]=4717660.0; rul[0][0][48]=95214.5; rul[0][0][49]=95828.0; 
rul[0][0][50]=331796.0; rul[0][0][51]=333272.0; rul[0][0][52]=107162.0; rul[0][0][53]=108303.0; rul[0][0][54]=43346.5; rul[0][0][55]=45126.0; 
rul[0][0][56]=161836.0; rul[0][0][57]=162258.0; rul[0][0][58]=1.59848E7; rul[0][0][59]=1.89741E7; rul[0][0][60]=1.34443E7; rul[0][0][61]=1.4041E7; 
rul[0][0][62]=79378.5; rul[0][0][63]=79933.5; rul[0][0][64]=214534.0; rul[0][0][65]=216409.0; rul[0][0][66]=91987.5; rul[0][0][67]=93250.5; 
rul[0][0][68]=14553.0; rul[0][0][69]=16401.5; rul[0][0][70]=461781.0; rul[0][0][71]=463980.0; rul[0][0][72]=101857.0; rul[0][0][73]=106411.0; 
rul[0][0][74]=1914310.0; rul[0][0][75]=1919670.0; rul[0][0][76]=27975.5; rul[0][0][77]=29499.5; rul[0][0][78]=312558.0; rul[0][0][79]=312842.0; 
rul[0][0][80]=207473.0; rul[0][0][81]=213331.0; rul[0][0][82]=823286.0; rul[0][0][83]=826603.0; rul[0][0][84]=447871.0; rul[0][0][85]=449528.0; 
rul[0][0][86]=963467.0; rul[0][0][87]=965601.0; rul[0][0][88]=100950.0; rul[0][0][89]=101243.0; rul[0][0][90]=8073130.0; rul[0][0][91]=8405610.0; 
rul[0][0][92]=83549.5; rul[0][0][93]=83778.0; rul[0][0][94]=1046580.0; rul[0][0][95]=1058470.0; rul[0][0][96]=29732.0; rul[0][0][97]=29927.0; 
rul[0][0][98]=30709.5; rul[0][0][99]=30789.0; rul[0][0][100]=125796.0; rul[0][0][101]=127392.0; rul[0][0][102]=565961.0; rul[0][0][103]=568526.0; 
rul[0][0][104]=1339010.0; rul[0][0][105]=1345090.0; rul[0][0][106]=36950.0; rul[0][0][107]=37056.5; rul[0][0][108]=184746.0; rul[0][0][109]=185140.0; 
rul[0][0][110]=1980050.0; rul[0][0][111]=1983860.0; rul[0][0][112]=253182.0; rul[0][0][113]=253431.0; rul[0][0][114]=1891610.0; rul[0][0][115]=1902650.0; 
rul[0][0][116]=88167.5; rul[0][0][117]=89237.0; rul[0][0][118]=664551.0; rul[0][0][119]=665854.0; rul[0][0][120]=365355.0; rul[0][0][121]=366559.0; 
rul[0][0][122]=255083.0; rul[0][0][123]=256144.0; rul[0][0][124]=269023.0; rul[0][0][125]=269543.0; rul[0][0][126]=798267.0; rul[0][0][127]=799981.0; 
rul[0][0][128]=4200550.0; rul[0][0][129]=4222870.0; rul[0][0][130]=51546.5; rul[0][0][131]=51763.0; rul[0][0][132]=188662.0; rul[0][0][133]=189187.0; 
rul[0][0][134]=932348.0; rul[0][0][135]=936087.0; rul[0][0][136]=85301.5; rul[0][0][137]=86344.5; rul[0][0][138]=551884.0; rul[0][0][139]=554371.0; 
rul[0][0][140]=214011.0; rul[0][0][141]=214064.0; rul[0][0][142]=508056.0; rul[0][0][143]=510805.0; rul[0][0][144]=371528.0; rul[0][0][145]=372767.0; 
rul[0][0][146]=2106930.0; rul[0][0][147]=2112240.0; rul[0][0][148]=2419460.0; rul[0][0][149]=2470940.0; rul[0][0][150]=197452.0; rul[0][0][151]=197765.0; 
rul[0][0][152]=233376.0; rul[0][0][153]=235604.0; rul[0][0][154]=173851.0; rul[0][0][155]=175491.0; rul[0][0][156]=705513.0; rul[0][0][157]=707793.0; 
rul[0][0][158]=746330.0; rul[0][0][159]=747108.0; rul[0][0][160]=1829890.0; rul[0][0][161]=1841020.0; rul[0][0][162]=812262.0; rul[0][0][163]=813158.0; 
rul[0][0][164]=76473.0; rul[0][0][165]=77088.5; rul[0][0][166]=6516100.0; rul[0][0][167]=6554360.0; rul[0][0][168]=81816.0; rul[0][0][169]=82373.5; 
rul[0][0][170]=min; rul[0][0][171]=8368.5; rul[0][0][172]=97380.5; rul[0][0][173]=97506.0; rul[0][0][174]=396968.0; rul[0][0][175]=397455.0; 
rul[0][0][176]=2519980.0; rul[0][0][177]=2533150.0; rul[0][0][178]=30296.5; rul[0][0][179]=30608.5; rul[0][0][180]=610675.0; rul[0][0][181]=611401.0; 
rul[0][0][182]=1078240.0; rul[0][0][183]=1080150.0; rul[0][0][184]=66319.0; rul[0][0][185]=66652.0; rul[0][0][186]=1.54049E7; rul[0][0][187]=1.57249E7; 
rul[0][0][188]=45502.0; rul[0][0][189]=46134.0; rul[0][0][190]=219026.0; rul[0][0][191]=220212.0; rul[0][0][192]=36711.0; rul[0][0][193]=36801.0; 
rul[0][0][194]=5047400.0; rul[0][0][195]=5080130.0; rul[0][0][196]=647731.0; rul[0][0][197]=648425.0; rul[0][0][198]=488800.0; rul[0][0][199]=490361.0; 
rul[0][0][200]=726555.0; rul[0][0][201]=729945.0; rul[0][0][202]=1068140.0; rul[0][0][203]=1070340.0; rul[0][0][204]=122667.0; rul[0][0][205]=122980.0; 
rul[0][0][206]=465336.0; rul[0][0][207]=465814.0; rul[0][0][208]=1216090.0; rul[0][0][209]=1223220.0; rul[0][0][210]=473291.0; rul[0][0][211]=473518.0; 
rul[0][0][212]=294603.0; rul[0][0][213]=295887.0; rul[0][0][214]=64585.0; rul[0][0][215]=64775.0; rul[0][0][216]=877514.0; rul[0][0][217]=883734.0; 
rul[0][0][218]=52104.0; rul[0][0][219]=52483.5; rul[0][0][220]=54944.5; rul[0][0][221]=55347.5; rul[0][0][222]=186817.0; rul[0][0][223]=187429.0; 
rul[0][0][224]=89622.0; rul[0][0][225]=90152.5; rul[0][0][226]=591138.0; rul[0][0][227]=591177.0; rul[0][0][228]=16782.0; rul[0][0][229]=17042.5; 
rul[0][0][230]=127844.0; rul[0][0][231]=128234.0; rul[0][0][232]=2345620.0; rul[0][0][233]=2398090.0; rul[0][0][234]=249886.0; rul[0][0][235]=250357.0; 
rul[0][0][236]=9410910.0; rul[0][0][237]=9725410.0; rul[0][0][238]=159261.0; rul[0][0][239]=160130.0; rul[0][0][240]=1247010.0; rul[0][0][241]=1256660.0; 
rul[0][0][242]=70746.5; rul[0][0][243]=71987.5; rul[0][0][244]=1351590.0; rul[0][0][245]=1357250.0; rul[0][0][246]=1300350.0; rul[0][0][247]=1306890.0; 
rul[0][0][248]=3170410.0; rul[0][0][249]=3180480.0; rul[0][0][250]=473816.0; rul[0][0][251]=476455.0; rul[0][0][252]=375991.0; rul[0][0][253]=378158.0; 
rul[0][0][254]=153792.0; rul[0][0][255]=155306.0; rul[0][0][256]=787971.0; rul[0][0][257]=789054.0; rul[0][0][258]=170931.0; rul[0][0][259]=172698.0; 
rul[0][0][260]=512450.0; rul[0][0][261]=512741.0; rul[0][0][262]=6899520.0; rul[0][0][263]=7148850.0; rul[0][0][264]=383706.0; rul[0][0][265]=383855.0; 
rul[0][0][266]=2474640.0; rul[0][0][267]=2513850.0; rul[0][0][268]=264986.0; rul[0][0][269]=265837.0; rul[0][0][270]=1861330.0; rul[0][0][271]=1874360.0; 
rul[0][0][272]=169657.0; rul[0][0][273]=170379.0; rul[0][0][274]=378841.0; rul[0][0][275]=379153.0; rul[0][0][276]=236257.0; rul[0][0][277]=236743.0; 
rul[0][0][278]=339787.0; rul[0][0][279]=341018.0; rul[0][0][280]=369341.0; rul[0][0][281]=370183.0; rul[0][0][282]=61123.0; rul[0][0][283]=61490.0; 
rul[0][0][284]=856070.0; rul[0][0][285]=857169.0; rul[0][0][286]=64181.5; rul[0][0][287]=64256.5; rul[0][0][288]=397843.0; rul[0][0][289]=400622.0; 
rul[0][0][290]=899181.0; rul[0][0][291]=901407.0; rul[0][0][292]=7512910.0; rul[0][0][293]=7917980.0; rul[0][0][294]=634452.0; rul[0][0][295]=635465.0; 
rul[0][0][296]=223459.0; rul[0][0][297]=223917.0; rul[0][0][298]=156715.0; rul[0][0][299]=157076.0; rul[0][0][300]=779815.0; rul[0][0][301]=780773.0; 
rul[0][0][302]=134815.0; rul[0][0][303]=135122.0; rul[0][0][304]=5493580.0; rul[0][0][305]=5529250.0; rul[0][0][306]=99776.0; rul[0][0][307]=100431.0; 
rul[0][0][308]=902110.0; rul[0][0][309]=902955.0; rul[0][0][310]=19780.0; rul[0][0][311]=20210.5; rul[0][0][312]=621613.0; rul[0][0][313]=622029.0; 
rul[0][0][314]=4421330.0; rul[0][0][315]=4531320.0; rul[0][0][316]=1.11859E7; rul[0][0][317]=1.28758E7; rul[0][0][318]=32887.5; rul[0][0][319]=34101.0; 
rul[0][0][320]=806710.0; rul[0][0][321]=808764.0; rul[0][0][322]=1741900.0; rul[0][0][323]=1767120.0; rul[0][0][324]=248107.0; rul[0][0][325]=248897.0; 
rul[0][0][326]=258579.0; rul[0][0][327]=261269.0; rul[0][0][328]=121997.0; rul[0][0][329]=122107.0; rul[0][0][330]=5336300.0; rul[0][0][331]=5449100.0; 
rul[0][0][332]=2579480.0; rul[0][0][333]=2607790.0; rul[0][0][334]=26003.0; rul[0][0][335]=26108.0; rul[0][0][336]=501905.0; rul[0][0][337]=506220.0; 
rul[0][0][338]=118110.0; rul[0][0][339]=118556.0; rul[0][0][340]=514825.0; rul[0][0][341]=516849.0; rul[0][0][342]=17299.5; rul[0][0][343]=17377.5; 
rul[0][0][344]=53235.0; rul[0][0][345]=53310.0; rul[0][0][346]=1332090.0; rul[0][0][347]=1335930.0; rul[0][0][348]=521391.0; rul[0][0][349]=523885.0; 
rul[0][0][350]=796812.0; rul[0][0][351]=797519.0; rul[0][0][352]=41542.0; rul[0][0][353]=42020.0; rul[0][0][354]=2924990.0; rul[0][0][355]=2933420.0; 
rul[0][0][356]=83975.0; rul[0][0][357]=84556.0; rul[0][0][358]=427878.0; rul[0][0][359]=429592.0; rul[0][0][360]=820249.0; rul[0][0][361]=820499.0; 
rul[0][0][362]=1474970.0; rul[0][0][363]=1478280.0; rul[0][0][364]=803382.0; rul[0][0][365]=805271.0; rul[0][0][366]=547327.0; rul[0][0][367]=547725.0; 
rul[0][0][368]=591525.0; rul[0][0][369]=597530.0; 
dl_reg[0]=1;
dec[0]=4; 
// 1. Koniec reguly
// 2. Regula
// 1. sekcja AND 2 reguly.
rul[1][0][0]=40; rul[1][0][1]=380; 
rul[1][0][2]=600700.0; rul[1][0][3]=608382.0; rul[1][0][4]=325879.0; rul[1][0][5]=329994.0; rul[1][0][6]=1288970.0; rul[1][0][7]=1300350.0; 
rul[1][0][8]=691824.0; rul[1][0][9]=695804.0; rul[1][0][10]=711847.0; rul[1][0][11]=726555.0; rul[1][0][12]=289274.0; rul[1][0][13]=290224.0; 
rul[1][0][14]=292224.0; rul[1][0][15]=293325.0; rul[1][0][16]=297790.0; rul[1][0][17]=305348.0; rul[1][0][18]=200991.0; rul[1][0][19]=204546.0; 
rul[1][0][20]=181464.0; rul[1][0][21]=182530.0; rul[1][0][22]=994089.0; rul[1][0][23]=1000760.0; rul[1][0][24]=306300.0; rul[1][0][25]=312558.0; 
rul[1][0][26]=167094.0; rul[1][0][27]=169072.0; rul[1][0][28]=119684.0; rul[1][0][29]=121305.0; rul[1][0][30]=857169.0; rul[1][0][31]=870247.0; 
rul[1][0][32]=490361.0; rul[1][0][33]=491806.0; rul[1][0][34]=429942.0; rul[1][0][35]=433857.0; rul[1][0][36]=112109.0; rul[1][0][37]=113201.0; 
rul[1][0][38]=417293.0; rul[1][0][39]=419209.0; rul[1][0][40]=960298.0; rul[1][0][41]=963467.0; rul[1][0][42]=3908890.0; rul[1][0][43]=3913580.0; 
rul[1][0][44]=316574.0; rul[1][0][45]=319941.0; rul[1][0][46]=1947820.0; rul[1][0][47]=1960710.0; rul[1][0][48]=185140.0; rul[1][0][49]=186452.0; 
rul[1][0][50]=669930.0; rul[1][0][51]=674950.0; rul[1][0][52]=813158.0; rul[1][0][53]=820249.0; rul[1][0][54]=684442.0; rul[1][0][55]=690142.0; 
rul[1][0][56]=2565660.0; rul[1][0][57]=2579480.0; rul[1][0][58]=350428.0; rul[1][0][59]=351013.0; rul[1][0][60]=1142980.0; rul[1][0][61]=1158210.0; 
rul[1][0][62]=2607790.0; rul[1][0][63]=2679000.0; rul[1][0][64]=379153.0; rul[1][0][65]=381153.0; rul[1][0][66]=96118.5; rul[1][0][67]=96668.5; 
rul[1][0][68]=281004.0; rul[1][0][69]=282585.0; rul[1][0][70]=1319940.0; rul[1][0][71]=1332090.0; rul[1][0][72]=295887.0; rul[1][0][73]=297292.0; 
rul[1][0][74]=659889.0; rul[1][0][75]=662056.0; rul[1][0][76]=177784.0; rul[1][0][77]=180181.0; rul[1][0][78]=385808.0; rul[1][0][79]=394703.0; 
rul[1][0][80]=461066.0; rul[1][0][81]=461781.0; rul[1][0][82]=276974.0; rul[1][0][83]=278644.0; rul[1][0][84]=472135.0; rul[1][0][85]=473291.0; 
rul[1][0][86]=759467.0; rul[1][0][87]=764255.0; rul[1][0][88]=463980.0; rul[1][0][89]=465336.0; rul[1][0][90]=496291.0; rul[1][0][91]=498334.0; 
rul[1][0][92]=2067380.0; rul[1][0][93]=2093610.0; rul[1][0][94]=250357.0; rul[1][0][95]=252115.0; rul[1][0][96]=487680.0; rul[1][0][97]=488800.0; 
rul[1][0][98]=499090.0; rul[1][0][99]=501905.0; rul[1][0][100]=204817.0; rul[1][0][101]=206699.0; rul[1][0][102]=334868.0; rul[1][0][103]=337056.0; 
rul[1][0][104]=476455.0; rul[1][0][105]=483057.0; rul[1][0][106]=547725.0; rul[1][0][107]=551884.0; rul[1][0][108]=849395.0; rul[1][0][109]=854029.0; 
rul[1][0][110]=249368.0; rul[1][0][111]=249886.0; rul[1][0][112]=936087.0; rul[1][0][113]=951923.0; rul[1][0][114]=374335.0; rul[1][0][115]=374944.0; 
rul[1][0][116]=657127.0; rul[1][0][117]=658288.0; rul[1][0][118]=333272.0; rul[1][0][119]=333709.0; rul[1][0][120]=976998.0; rul[1][0][121]=979322.0; 
rul[1][0][122]=368049.0; rul[1][0][123]=369341.0; rul[1][0][124]=187429.0; rul[1][0][125]=188070.0; rul[1][0][126]=1116390.0; rul[1][0][127]=1126200.0; 
rul[1][0][128]=1398480.0; rul[1][0][129]=1400420.0; rul[1][0][130]=117312.0; rul[1][0][131]=117640.0; rul[1][0][132]=71987.5; rul[1][0][133]=72188.0; 
rul[1][0][134]=176578.0; rul[1][0][135]=177005.0; rul[1][0][136]=129074.0; rul[1][0][137]=129593.0; rul[1][0][138]=568526.0; rul[1][0][139]=571160.0; 
rul[1][0][140]=5598620.0; rul[1][0][141]=5650720.0; rul[1][0][142]=197765.0; rul[1][0][143]=200223.0; rul[1][0][144]=664439.0; rul[1][0][145]=664551.0; 
rul[1][0][146]=635465.0; rul[1][0][147]=636914.0; rul[1][0][148]=214064.0; rul[1][0][149]=214534.0; rul[1][0][150]=572318.0; rul[1][0][151]=572799.0; 
rul[1][0][152]=799981.0; rul[1][0][153]=801700.0; rul[1][0][154]=144202.0; rul[1][0][155]=145445.0; rul[1][0][156]=2854850.0; rul[1][0][157]=2878350.0; 
rul[1][0][158]=1306890.0; rul[1][0][159]=1313560.0; rul[1][0][160]=151480.0; rul[1][0][161]=151848.0; rul[1][0][162]=1983860.0; rul[1][0][163]=1995050.0; 
rul[1][0][164]=1191130.0; rul[1][0][165]=1204240.0; rul[1][0][166]=166072.0; rul[1][0][167]=166269.0; rul[1][0][168]=744221.0; rul[1][0][169]=745067.0; 
rul[1][0][170]=554371.0; rul[1][0][171]=559288.0; rul[1][0][172]=395174.0; rul[1][0][173]=395802.0; rul[1][0][174]=106592.0; rul[1][0][175]=106685.0; 
rul[1][0][176]=453471.0; rul[1][0][177]=455077.0; rul[1][0][178]=4962520.0; rul[1][0][179]=5033530.0; rul[1][0][180]=847092.0; rul[1][0][181]=848429.0; 
rul[1][0][182]=1537840.0; rul[1][0][183]=1543820.0; rul[1][0][184]=74835.5; rul[1][0][185]=75782.0; rul[1][0][186]=797519.0; rul[1][0][187]=798267.0; 
rul[1][0][188]=268177.0; rul[1][0][189]=269023.0; rul[1][0][190]=372767.0; rul[1][0][191]=373403.0; rul[1][0][192]=442841.0; rul[1][0][193]=446262.0; 
rul[1][0][194]=3043840.0; rul[1][0][195]=3084160.0; rul[1][0][196]=1084320.0; rul[1][0][197]=1093280.0; rul[1][0][198]=1596300.0; rul[1][0][199]=1622040.0; 
rul[1][0][200]=130595.0; rul[1][0][201]=132102.0; rul[1][0][202]=3188350.0; rul[1][0][203]=3281120.0; rul[1][0][204]=247417.0; rul[1][0][205]=248107.0; 
rul[1][0][206]=157076.0; rul[1][0][207]=157582.0; rul[1][0][208]=3153790.0; rul[1][0][209]=3170410.0; rul[1][0][210]=78589.5; rul[1][0][211]=79378.5; 
rul[1][0][212]=63781.0; rul[1][0][213]=64181.5; rul[1][0][214]=640499.0; rul[1][0][215]=641663.0; rul[1][0][216]=1707040.0; rul[1][0][217]=1712020.0; 
rul[1][0][218]=396435.0; rul[1][0][219]=396968.0; rul[1][0][220]=2975170.0; rul[1][0][221]=3042090.0; rul[1][0][222]=331319.0; rul[1][0][223]=331796.0; 
rul[1][0][224]=256144.0; rul[1][0][225]=256210.0; rul[1][0][226]=243248.0; rul[1][0][227]=245312.0; rul[1][0][228]=1072650.0; rul[1][0][229]=1078240.0; 
rul[1][0][230]=905388.0; rul[1][0][231]=907150.0; rul[1][0][232]=622029.0; rul[1][0][233]=626014.0; rul[1][0][234]=73599.0; rul[1][0][235]=73804.5; 
rul[1][0][236]=345433.0; rul[1][0][237]=346788.0; rul[1][0][238]=2145790.0; rul[1][0][239]=2148850.0; rul[1][0][240]=2112240.0; rul[1][0][241]=2129740.0; 
rul[1][0][242]=2398090.0; rul[1][0][243]=2419460.0; rul[1][0][244]=512741.0; rul[1][0][245]=514825.0; rul[1][0][246]=562439.0; rul[1][0][247]=565961.0; 
rul[1][0][248]=465814.0; rul[1][0][249]=466102.0; rul[1][0][250]=320668.0; rul[1][0][251]=322970.0; rul[1][0][252]=836036.0; rul[1][0][253]=846001.0; 
rul[1][0][254]=352105.0; rul[1][0][255]=352304.0; rul[1][0][256]=516849.0; rul[1][0][257]=518830.0; rul[1][0][258]=1482600.0; rul[1][0][259]=1513690.0; 
rul[1][0][260]=1972180.0; rul[1][0][261]=1980050.0; rul[1][0][262]=158260.0; rul[1][0][263]=158469.0; rul[1][0][264]=193683.0; rul[1][0][265]=195225.0; 
rul[1][0][266]=965601.0; rul[1][0][267]=968790.0; rul[1][0][268]=419469.0; rul[1][0][269]=423711.0; rul[1][0][270]=400622.0; rul[1][0][271]=404543.0; 
rul[1][0][272]=338885.0; rul[1][0][273]=339787.0; rul[1][0][274]=224539.0; rul[1][0][275]=225831.0; rul[1][0][276]=195623.0; rul[1][0][277]=196908.0; 
rul[1][0][278]=83201.5; rul[1][0][279]=83549.5; rul[1][0][280]=582835.0; rul[1][0][281]=586924.0; rul[1][0][282]=617581.0; rul[1][0][283]=620240.0; 
rul[1][0][284]=1159770.0; rul[1][0][285]=1163850.0; rul[1][0][286]=632784.0; rul[1][0][287]=634452.0; rul[1][0][288]=1402480.0; rul[1][0][289]=1433570.0; 
rul[1][0][290]=411752.0; rul[1][0][291]=413935.0; rul[1][0][292]=359510.0; rul[1][0][293]=361436.0; rul[1][0][294]=451718.0; rul[1][0][295]=452791.0; 
rul[1][0][296]=5143760.0; rul[1][0][297]=5185730.0; rul[1][0][298]=777290.0; rul[1][0][299]=779815.0; rul[1][0][300]=160130.0; rul[1][0][301]=160657.0; 
rul[1][0][302]=138789.0; rul[1][0][303]=140146.0; rul[1][0][304]=3586570.0; rul[1][0][305]=3657340.0; rul[1][0][306]=1623110.0; rul[1][0][307]=1628650.0; 
rul[1][0][308]=1070340.0; rul[1][0][309]=1072130.0; rul[1][0][310]=707793.0; rul[1][0][311]=709292.0; rul[1][0][312]=247023.0; rul[1][0][313]=247243.0; 
rul[1][0][314]=129926.0; rul[1][0][315]=130418.0; rul[1][0][316]=239473.0; rul[1][0][317]=242112.0; rul[1][0][318]=598432.0; rul[1][0][319]=598736.0; 
rul[1][0][320]=1723440.0; rul[1][0][321]=1741900.0; rul[1][0][322]=611401.0; rul[1][0][323]=615392.0; rul[1][0][324]=69773.5; rul[1][0][325]=69891.0; 
rul[1][0][326]=1269580.0; rul[1][0][327]=1271030.0; rul[1][0][328]=370183.0; rul[1][0][329]=371528.0; rul[1][0][330]=901407.0; rul[1][0][331]=902110.0; 
rul[1][0][332]=237009.0; rul[1][0][333]=238388.0; rul[1][0][334]=424152.0; rul[1][0][335]=426121.0; rul[1][0][336]=50406.0; rul[1][0][337]=51015.0; 
rul[1][0][338]=272634.0; rul[1][0][339]=273353.0; rul[1][0][340]=510805.0; rul[1][0][341]=512450.0; rul[1][0][342]=93250.5; rul[1][0][343]=93403.0; 
rul[1][0][344]=1256660.0; rul[1][0][345]=1262900.0; rul[1][0][346]=118908.0; rul[1][0][347]=119320.0; rul[1][0][348]=192235.0; rul[1][0][349]=192499.0; 
rul[1][0][350]=108836.0; rul[1][0][351]=111597.0; rul[1][0][352]=918148.0; rul[1][0][353]=920881.0; rul[1][0][354]=1277050.0; rul[1][0][355]=1278950.0; 
rul[1][0][356]=449528.0; rul[1][0][357]=450637.0; rul[1][0][358]=216409.0; rul[1][0][359]=216987.0; rul[1][0][360]=887211.0; rul[1][0][361]=889922.0; 
rul[1][0][362]=170379.0; rul[1][0][363]=170845.0; rul[1][0][364]=230907.0; rul[1][0][365]=231800.0; rul[1][0][366]=284763.0; rul[1][0][367]=287261.0; 
rul[1][0][368]=348544.0; rul[1][0][369]=349262.0; rul[1][0][370]=578674.0; rul[1][0][371]=579817.0; rul[1][0][372]=2533150.0; rul[1][0][373]=2551400.0; 
rul[1][0][374]=47065.5; rul[1][0][375]=47581.0; rul[1][0][376]=540381.0; rul[1][0][377]=540708.0; rul[1][0][378]=747108.0; rul[1][0][379]=748479.0; 
rul[1][0][380]=89237.0; rul[1][0][381]=89622.0; 
dl_reg[1]=1;
dec[1]=2; 
// 2. Koniec reguly
// 3. Regula
// 1. sekcja AND 3 reguly.
rul[2][0][0]=40; rul[2][0][1]=64; 
rul[2][0][2]=1.4041E7; rul[2][0][3]=1.54049E7; rul[2][0][4]=9271780.0; rul[2][0][5]=9410910.0; rul[2][0][6]=4.42338E7; rul[2][0][7]=max; 
rul[2][0][8]=351535.0; rul[2][0][9]=351809.0; rul[2][0][10]=466102.0; rul[2][0][11]=466519.0; rul[2][0][12]=1.89741E7; rul[2][0][13]=1.95785E7; 
rul[2][0][14]=1785040.0; rul[2][0][15]=1786420.0; rul[2][0][16]=3.23919E7; rul[2][0][17]=3.79541E7; rul[2][0][18]=41398.0; rul[2][0][19]=41542.0; 
rul[2][0][20]=426121.0; rul[2][0][21]=427878.0; rul[2][0][22]=1654690.0; rul[2][0][23]=1660020.0; rul[2][0][24]=357555.0; rul[2][0][25]=359510.0; 
rul[2][0][26]=2129740.0; rul[2][0][27]=2145790.0; rul[2][0][28]=118556.0; rul[2][0][29]=118908.0; rul[2][0][30]=52483.5; rul[2][0][31]=53070.0; 
rul[2][0][32]=128782.0; rul[2][0][33]=129074.0; rul[2][0][34]=160657.0; rul[2][0][35]=161221.0; rul[2][0][36]=49469.5; rul[2][0][37]=49589.0; 
rul[2][0][38]=3361990.0; rul[2][0][39]=3375610.0; rul[2][0][40]=4222870.0; rul[2][0][41]=4361000.0; rul[2][0][42]=1.28758E7; rul[2][0][43]=1.34443E7; 
rul[2][0][44]=97222.0; rul[2][0][45]=97380.5; rul[2][0][46]=3913580.0; rul[2][0][47]=3933310.0; rul[2][0][48]=81059.0; rul[2][0][49]=81218.0; 
rul[2][0][50]=2.22966E7; rul[2][0][51]=2.55771E7; rul[2][0][52]=62031.0; rul[2][0][53]=62827.5; rul[2][0][54]=4391230.0; rul[2][0][55]=4421330.0; 
rul[2][0][56]=3885350.0; rul[2][0][57]=3908890.0; rul[2][0][58]=5529250.0; rul[2][0][59]=5598620.0; rul[2][0][60]=9725410.0; rul[2][0][61]=1.00615E7; 
rul[2][0][62]=197142.0; rul[2][0][63]=197452.0; rul[2][0][64]=36462.5; rul[2][0][65]=36629.0; 
dl_reg[2]=1;
dec[2]=5; 
// 3. Koniec reguly
// 4. Regula
// 1. sekcja AND 4 reguly.
rul[3][0][0]=40; rul[3][0][1]=344; 
rul[3][0][2]=69891.0; rul[3][0][3]=70746.5; rul[3][0][4]=8368.5; rul[3][0][5]=11552.0; rul[3][0][6]=106685.0; rul[3][0][7]=107162.0; 
rul[3][0][8]=1004890.0; rul[3][0][9]=1017690.0; rul[3][0][10]=662056.0; rul[3][0][11]=664439.0; rul[3][0][12]=49144.0; rul[3][0][13]=49469.5; 
rul[3][0][14]=1177500.0; rul[3][0][15]=1191130.0; rul[3][0][16]=2203040.0; rul[3][0][17]=2223950.0; rul[3][0][18]=780773.0; rul[3][0][19]=784299.0; 
rul[3][0][20]=3982490.0; rul[3][0][21]=4128450.0; rul[3][0][22]=1080150.0; rul[3][0][23]=1084320.0; rul[3][0][24]=2933420.0; rul[3][0][25]=2975170.0; 
rul[3][0][26]=64775.0; rul[3][0][27]=65492.0; rul[3][0][28]=26108.0; rul[3][0][29]=26787.0; rul[3][0][30]=12738.0; rul[3][0][31]=14553.0; 
rul[3][0][32]=22139.5; rul[3][0][33]=24340.5; rul[3][0][34]=54037.0; rul[3][0][35]=54944.5; rul[3][0][36]=140357.0; rul[3][0][37]=144202.0; 
rul[3][0][38]=870247.0; rul[3][0][39]=877514.0; rul[3][0][40]=2234160.0; rul[3][0][41]=2255950.0; rul[3][0][42]=60251.5; rul[3][0][43]=61123.0; 
rul[3][0][44]=5185730.0; rul[3][0][45]=5336300.0; rul[3][0][46]=6001950.0; rul[3][0][47]=6516100.0; rul[3][0][48]=180181.0; rul[3][0][49]=181464.0; 
rul[3][0][50]=641663.0; rul[3][0][51]=645692.0; rul[3][0][52]=381153.0; rul[3][0][53]=383258.0; rul[3][0][54]=735583.0; rul[3][0][55]=737436.0; 
rul[3][0][56]=72737.5; rul[3][0][57]=73411.5; rul[3][0][58]=135426.0; rul[3][0][59]=138789.0; rul[3][0][60]=42020.0; rul[3][0][61]=43346.5; 
rul[3][0][62]=65866.0; rul[3][0][63]=66125.0; rul[3][0][64]=579817.0; rul[3][0][65]=582835.0; rul[3][0][66]=808764.0; rul[3][0][67]=810765.0; 
rul[3][0][68]=176126.0; rul[3][0][69]=176578.0; rul[3][0][70]=330703.0; rul[3][0][71]=331250.0; rul[3][0][72]=793550.0; rul[3][0][73]=796812.0; 
rul[3][0][74]=378158.0; rul[3][0][75]=378841.0; rul[3][0][76]=40425.5; rul[3][0][77]=40586.0; rul[3][0][78]=125446.0; rul[3][0][79]=125485.0; 
rul[3][0][80]=170845.0; rul[3][0][81]=170931.0; rul[3][0][82]=441492.0; rul[3][0][83]=442841.0; rul[3][0][84]=287261.0; rul[3][0][85]=289274.0; 
rul[3][0][86]=350124.0; rul[3][0][87]=350428.0; rul[3][0][88]=1767120.0; rul[3][0][89]=1785040.0; rul[3][0][90]=98874.5; rul[3][0][91]=99150.5; 
rul[3][0][92]=1874360.0; rul[3][0][93]=1885590.0; rul[3][0][94]=333709.0; rul[3][0][95]=334868.0; rul[3][0][96]=2513850.0; rul[3][0][97]=2519980.0; 
rul[3][0][98]=3817990.0; rul[3][0][99]=3845400.0; rul[3][0][100]=216987.0; rul[3][0][101]=218400.0; rul[3][0][102]=87170.0; rul[3][0][103]=87343.0; 
rul[3][0][104]=16401.5; rul[3][0][105]=16782.0; rul[3][0][106]=1960710.0; rul[3][0][107]=1972180.0; rul[3][0][108]=1844500.0; rul[3][0][109]=1861330.0; 
rul[3][0][110]=1095660.0; rul[3][0][111]=1096510.0; rul[3][0][112]=902955.0; rul[3][0][113]=905388.0; rul[3][0][114]=119320.0; rul[3][0][115]=119684.0; 
rul[3][0][116]=571160.0; rul[3][0][117]=572318.0; rul[3][0][118]=658288.0; rul[3][0][119]=659382.0; rul[3][0][120]=729945.0; rul[3][0][121]=730584.0; 
rul[3][0][122]=483057.0; rul[3][0][123]=487680.0; rul[3][0][124]=1478280.0; rul[3][0][125]=1482600.0; rul[3][0][126]=64256.5; rul[3][0][127]=64585.0; 
rul[3][0][128]=45126.0; rul[3][0][129]=45383.5; rul[3][0][130]=745067.0; rul[3][0][131]=746330.0; rul[3][0][132]=242112.0; rul[3][0][133]=243248.0; 
rul[3][0][134]=218784.0; rul[3][0][135]=219026.0; rul[3][0][136]=1712020.0; rul[3][0][137]=1723440.0; rul[3][0][138]=82373.5; rul[3][0][139]=82739.0; 
rul[3][0][140]=1335930.0; rul[3][0][141]=1339010.0; rul[3][0][142]=117640.0; rul[3][0][143]=118110.0; rul[3][0][144]=62827.5; rul[3][0][145]=63781.0; 
rul[3][0][146]=58048.0; rul[3][0][147]=58292.5; rul[3][0][148]=1108130.0; rul[3][0][149]=1116390.0; rul[3][0][150]=99357.5; rul[3][0][151]=99776.0; 
rul[3][0][152]=811364.0; rul[3][0][153]=811881.0; rul[3][0][154]=122980.0; rul[3][0][155]=123073.0; rul[3][0][156]=1204240.0; rul[3][0][157]=1216090.0; 
rul[3][0][158]=29499.5; rul[3][0][159]=29732.0; rul[3][0][160]=1265310.0; rul[3][0][161]=1268200.0; rul[3][0][162]=124585.0; rul[3][0][163]=125337.0; 
rul[3][0][164]=267164.0; rul[3][0][165]=267668.0; rul[3][0][166]=4382910.0; rul[3][0][167]=4391230.0; rul[3][0][168]=3042090.0; rul[3][0][169]=3043840.0; 
rul[3][0][170]=1313560.0; rul[3][0][171]=1314940.0; rul[3][0][172]=25540.0; rul[3][0][173]=25672.0; rul[3][0][174]=1628650.0; rul[3][0][175]=1652520.0; 
rul[3][0][176]=4531320.0; rul[3][0][177]=4598350.0; rul[3][0][178]=1789640.0; rul[3][0][179]=1800020.0; rul[3][0][180]=667579.0; rul[3][0][181]=669930.0; 
rul[3][0][182]=659594.0; rul[3][0][183]=659889.0; rul[3][0][184]=37557.0; rul[3][0][185]=39143.0; rul[3][0][186]=101243.0; rul[3][0][187]=101857.0; 
rul[3][0][188]=2166370.0; rul[3][0][189]=2187330.0; rul[3][0][190]=7349530.0; rul[3][0][191]=7389630.0; rul[3][0][192]=25898.5; rul[3][0][193]=26003.0; 
rul[3][0][194]=191070.0; rul[3][0][195]=192235.0; rul[3][0][196]=1815390.0; rul[3][0][197]=1824450.0; rul[3][0][198]=1524740.0; rul[3][0][199]=1532080.0; 
rul[3][0][200]=756385.0; rul[3][0][201]=759467.0; rul[3][0][202]=620240.0; rul[3][0][203]=621613.0; rul[3][0][204]=1471970.0; rul[3][0][205]=1474970.0; 
rul[3][0][206]=648425.0; rul[3][0][207]=650438.0; rul[3][0][208]=220212.0; rul[3][0][209]=220438.0; rul[3][0][210]=446598.0; rul[3][0][211]=447871.0; 
rul[3][0][212]=366559.0; rul[3][0][213]=368049.0; rul[3][0][214]=4161440.0; rul[3][0][215]=4200550.0; rul[3][0][216]=855768.0; rul[3][0][217]=856070.0; 
rul[3][0][218]=122107.0; rul[3][0][219]=122172.0; rul[3][0][220]=127392.0; rul[3][0][221]=127578.0; rul[3][0][222]=982002.0; rul[3][0][223]=983604.0; 
rul[3][0][224]=186452.0; rul[3][0][225]=186817.0; rul[3][0][226]=732049.0; rul[3][0][227]=734596.0; rul[3][0][228]=374944.0; rul[3][0][229]=375991.0; 
rul[3][0][230]=312842.0; rul[3][0][231]=313446.0; rul[3][0][232]=1622040.0; rul[3][0][233]=1623110.0; rul[3][0][234]=78262.0; rul[3][0][235]=78589.5; 
rul[3][0][236]=1902650.0; rul[3][0][237]=1914310.0; rul[3][0][238]=3281120.0; rul[3][0][239]=3361990.0; rul[3][0][240]=1664010.0; rul[3][0][241]=1670010.0; 
rul[3][0][242]=2786820.0; rul[3][0][243]=2809040.0; rul[3][0][244]=764255.0; rul[3][0][245]=767297.0; rul[3][0][246]=30608.5; rul[3][0][247]=30709.5; 
rul[3][0][248]=1388020.0; rul[3][0][249]=1398480.0; rul[3][0][250]=373403.0; rul[3][0][251]=373624.0; rul[3][0][252]=337056.0; rul[3][0][253]=337770.0; 
rul[3][0][254]=149780.0; rul[3][0][255]=150613.0; rul[3][0][256]=20210.5; rul[3][0][257]=20334.5; rul[3][0][258]=1040530.0; rul[3][0][259]=1046580.0; 
rul[3][0][260]=5449100.0; rul[3][0][261]=5493580.0; rul[3][0][262]=58496.5; rul[3][0][263]=59539.5; rul[3][0][264]=1357250.0; rul[3][0][265]=1375320.0; 
rul[3][0][266]=968790.0; rul[3][0][267]=974215.0; rul[3][0][268]=1158660.0; rul[3][0][269]=1159770.0; rul[3][0][270]=1567300.0; rul[3][0][271]=1583130.0; 
rul[3][0][272]=97506.0; rul[3][0][273]=98515.0; rul[3][0][274]=115473.0; rul[3][0][275]=116431.0; rul[3][0][276]=1029430.0; rul[3][0][277]=1032560.0; 
rul[3][0][278]=496024.0; rul[3][0][279]=496291.0; rul[3][0][280]=133615.0; rul[3][0][281]=134109.0; rul[3][0][282]=111597.0; rul[3][0][283]=112109.0; 
rul[3][0][284]=586924.0; rul[3][0][285]=591138.0; rul[3][0][286]=433857.0; rul[3][0][287]=436346.0; rul[3][0][288]=893148.0; rul[3][0][289]=899181.0; 
rul[3][0][290]=152626.0; rul[3][0][291]=153792.0; rul[3][0][292]=3529790.0; rul[3][0][293]=3586570.0; rul[3][0][294]=35078.5; rul[3][0][295]=35515.5; 
rul[3][0][296]=95828.0; rul[3][0][297]=96118.5; rul[3][0][298]=293325.0; rul[3][0][299]=294603.0; rul[3][0][300]=17231.0; rul[3][0][301]=17299.5; 
rul[3][0][302]=29927.0; rul[3][0][303]=30296.5; rul[3][0][304]=1093280.0; rul[3][0][305]=1094980.0; rul[3][0][306]=263800.0; rul[3][0][307]=264986.0; 
rul[3][0][308]=17042.5; rul[3][0][309]=17120.0; rul[3][0][310]=506220.0; rul[3][0][311]=508056.0; rul[3][0][312]=17377.5; rul[3][0][313]=18727.5; 
rul[3][0][314]=466519.0; rul[3][0][315]=467048.0; rul[3][0][316]=96668.5; rul[3][0][317]=97116.5; rul[3][0][318]=128234.0; rul[3][0][319]=128567.0; 
rul[3][0][320]=3.79541E7; rul[3][0][321]=4.42338E7; rul[3][0][322]=3092830.0; rul[3][0][323]=3121080.0; rul[3][0][324]=883734.0; rul[3][0][325]=887211.0; 
rul[3][0][326]=83778.0; rul[3][0][327]=83975.0; rul[3][0][328]=608382.0; rul[3][0][329]=609326.0; rul[3][0][330]=491806.0; rul[3][0][331]=493224.0; 
rul[3][0][332]=786366.0; rul[3][0][333]=786841.0; rul[3][0][334]=238388.0; rul[3][0][335]=239230.0; rul[3][0][336]=47581.0; rul[3][0][337]=47732.0; 
rul[3][0][338]=429592.0; rul[3][0][339]=429942.0; rul[3][0][340]=36801.0; rul[3][0][341]=36950.0; rul[3][0][342]=353632.0; rul[3][0][343]=354224.0; 
rul[3][0][344]=227967.0; rul[3][0][345]=228880.0; 
dl_reg[3]=1;
dec[3]=3; 
// 4. Koniec reguly
// 5. Regula
// 1. sekcja AND 5 reguly.
rul[4][0][0]=40; rul[4][0][1]=70; 
rul[4][0][2]=282585.0; rul[4][0][3]=284763.0; rul[4][0][4]=195396.0; rul[4][0][5]=195623.0; rul[4][0][6]=146218.0; rul[4][0][7]=146757.0; 
rul[4][0][8]=889922.0; rul[4][0][9]=893148.0; rul[4][0][10]=166269.0; rul[4][0][11]=166465.0; rul[4][0][12]=1532080.0; rul[4][0][13]=1537840.0; 
rul[4][0][14]=1703700.0; rul[4][0][15]=1707040.0; rul[4][0][16]=730584.0; rul[4][0][17]=730830.0; rul[4][0][18]=172698.0; rul[4][0][19]=173851.0; 
rul[4][0][20]=94764.0; rul[4][0][21]=95048.0; rul[4][0][22]=213331.0; rul[4][0][23]=214011.0; rul[4][0][24]=1660020.0; rul[4][0][25]=1664010.0; 
rul[4][0][26]=446262.0; rul[4][0][27]=446598.0; rul[4][0][28]=235604.0; rul[4][0][29]=235756.0; rul[4][0][30]=90152.5; rul[4][0][31]=90695.0; 
rul[4][0][32]=1999960.0; rul[4][0][33]=2007060.0; rul[4][0][34]=423711.0; rul[4][0][35]=424152.0; rul[4][0][36]=751815.0; rul[4][0][37]=756385.0; 
rul[4][0][38]=352384.0; rul[4][0][39]=352865.0; rul[4][0][40]=1513690.0; rul[4][0][41]=1524740.0; rul[4][0][42]=324595.0; rul[4][0][43]=325788.0; 
rul[4][0][44]=636914.0; rul[4][0][45]=640250.0; rul[4][0][46]=609326.0; rul[4][0][47]=610675.0; rul[4][0][48]=543589.0; rul[4][0][49]=545548.0; 
rul[4][0][50]=351809.0; rul[4][0][51]=352105.0; rul[4][0][52]=528643.0; rul[4][0][53]=531052.0; rul[4][0][54]=675986.0; rul[4][0][55]=676826.0; 
rul[4][0][56]=3787070.0; rul[4][0][57]=3817990.0; rul[4][0][58]=457964.0; rul[4][0][59]=460614.0; rul[4][0][60]=130418.0; rul[4][0][61]=130593.0; 
rul[4][0][62]=2878350.0; rul[4][0][63]=2901590.0; rul[4][0][64]=319941.0; rul[4][0][65]=320668.0; rul[4][0][66]=220438.0; rul[4][0][67]=220657.0; 
rul[4][0][68]=789054.0; rul[4][0][69]=790795.0; rul[4][0][70]=276203.0; rul[4][0][71]=276974.0; 
dl_reg[4]=1;
dec[4]=1; 
// 5. Koniec reguly
// 6. Regula
// 1. sekcja AND 6 reguly.
rul[5][0][0]=43; rul[5][0][1]=374; 
rul[5][0][2]=3.01226; rul[5][0][3]=3.0239; rul[5][0][4]=3.48224; rul[5][0][5]=3.50451; rul[5][0][6]=4.00286; rul[5][0][7]=4.01432; 
rul[5][0][8]=23.1066; rul[5][0][9]=23.4192; rul[5][0][10]=14.1517; rul[5][0][11]=14.2174; rul[5][0][12]=42.6996; rul[5][0][13]=42.912; 
rul[5][0][14]=14.2871; rul[5][0][15]=14.3477; rul[5][0][16]=34.097; rul[5][0][17]=34.6133; rul[5][0][18]=3.24669; rul[5][0][19]=3.43035; 
rul[5][0][20]=30.3987; rul[5][0][21]=30.9184; rul[5][0][22]=94.9198; rul[5][0][23]=105.803; rul[5][0][24]=3.01062; rul[5][0][25]=3.01172; 
rul[5][0][26]=63.0272; rul[5][0][27]=64.8221; rul[5][0][28]=8.59291; rul[5][0][29]=8.63949; rul[5][0][30]=5.71057; rul[5][0][31]=5.71838; 
rul[5][0][32]=20.8167; rul[5][0][33]=20.9311; rul[5][0][34]=20.2317; rul[5][0][35]=20.2824; rul[5][0][36]=6.80128; rul[5][0][37]=6.82147; 
rul[5][0][38]=5.67683; rul[5][0][39]=5.69707; rul[5][0][40]=10.1505; rul[5][0][41]=10.1593; rul[5][0][42]=16.9149; rul[5][0][43]=17.0439; 
rul[5][0][44]=9.56097; rul[5][0][45]=9.62728; rul[5][0][46]=3.46663; rul[5][0][47]=3.47821; rul[5][0][48]=7.87438; rul[5][0][49]=7.91663; 
rul[5][0][50]=3.99776; rul[5][0][51]=4.00098; rul[5][0][52]=51.9874; rul[5][0][53]=53.0122; rul[5][0][54]=7.44863; rul[5][0][55]=7.4767; 
rul[5][0][56]=25.9986; rul[5][0][57]=26.0684; rul[5][0][58]=227.738; rul[5][0][59]=234.209; rul[5][0][60]=8.90293; rul[5][0][61]=8.93369; 
rul[5][0][62]=133.744; rul[5][0][63]=137.552; rul[5][0][64]=7.02466; rul[5][0][65]=7.02862; rul[5][0][66]=4.96118; rul[5][0][67]=4.97178; 
rul[5][0][68]=4.98176; rul[5][0][69]=5.02686; rul[5][0][70]=87.6315; rul[5][0][71]=90.2622; rul[5][0][72]=90.5107; rul[5][0][73]=91.4856; 
rul[5][0][74]=4.33675; rul[5][0][75]=4.35548; rul[5][0][76]=47.0403; rul[5][0][77]=47.9607; rul[5][0][78]=4.7939; rul[5][0][79]=4.82039; 
rul[5][0][80]=5.27943; rul[5][0][81]=5.30013; rul[5][0][82]=5.79781; rul[5][0][83]=5.8041; rul[5][0][84]=28.6361; rul[5][0][85]=28.6536; 
rul[5][0][86]=8.07421; rul[5][0][87]=8.09549; rul[5][0][88]=8.45601; rul[5][0][89]=8.4578; rul[5][0][90]=7.60944; rul[5][0][91]=7.62001; 
rul[5][0][92]=12.3862; rul[5][0][93]=12.407; rul[5][0][94]=26.7549; rul[5][0][95]=26.951; rul[5][0][96]=2.98316; rul[5][0][97]=2.98479; 
rul[5][0][98]=14.0731; rul[5][0][99]=14.0816; rul[5][0][100]=17.5632; rul[5][0][101]=17.5756; rul[5][0][102]=3.00627; rul[5][0][103]=3.00948; 
rul[5][0][104]=5.13136; rul[5][0][105]=5.14844; rul[5][0][106]=7.03005; rul[5][0][107]=7.04325; rul[5][0][108]=6.8761; rul[5][0][109]=6.87731; 
rul[5][0][110]=9.3396; rul[5][0][111]=9.3833; rul[5][0][112]=21.6485; rul[5][0][113]=21.7768; rul[5][0][114]=14.8978; rul[5][0][115]=14.9265; 
rul[5][0][116]=4.56635; rul[5][0][117]=4.58431; rul[5][0][118]=28.5453; rul[5][0][119]=28.5983; rul[5][0][120]=5.22201; rul[5][0][121]=5.24483; 
rul[5][0][122]=6.63162; rul[5][0][123]=6.63577; rul[5][0][124]=4.50783; rul[5][0][125]=4.50825; rul[5][0][126]=10.5787; rul[5][0][127]=10.5939; 
rul[5][0][128]=10.7786; rul[5][0][129]=10.7915; rul[5][0][130]=17.9116; rul[5][0][131]=17.9226; rul[5][0][132]=15.383; rul[5][0][133]=15.4491; 
rul[5][0][134]=18.5917; rul[5][0][135]=18.6277; rul[5][0][136]=5.57709; rul[5][0][137]=5.58236; rul[5][0][138]=19.0774; rul[5][0][139]=19.1556; 
rul[5][0][140]=5.46185; rul[5][0][141]=5.50568; rul[5][0][142]=21.4826; rul[5][0][143]=21.4983; rul[5][0][144]=8.74515; rul[5][0][145]=8.76938; 
rul[5][0][146]=12.0917; rul[5][0][147]=12.1011; rul[5][0][148]=5.8099; rul[5][0][149]=5.81694; rul[5][0][150]=35.0097; rul[5][0][151]=35.2683; 
rul[5][0][152]=5.97851; rul[5][0][153]=6.00082; rul[5][0][154]=13.2269; rul[5][0][155]=13.2485; rul[5][0][156]=6.64131; rul[5][0][157]=6.65076; 
rul[5][0][158]=33.1707; rul[5][0][159]=33.4568; rul[5][0][160]=42.2543; rul[5][0][161]=42.2637; rul[5][0][162]=11.7614; rul[5][0][163]=11.7706; 
rul[5][0][164]=13.3144; rul[5][0][165]=13.3448; rul[5][0][166]=83.4703; rul[5][0][167]=85.5294; rul[5][0][168]=12.1312; rul[5][0][169]=12.1432; 
rul[5][0][170]=21.1675; rul[5][0][171]=21.2693; rul[5][0][172]=10.3175; rul[5][0][173]=10.3439; rul[5][0][174]=3.8787; rul[5][0][175]=3.90277; 
rul[5][0][176]=6.61335; rul[5][0][177]=6.63064; rul[5][0][178]=8.22327; rul[5][0][179]=8.24273; rul[5][0][180]=40.8333; rul[5][0][181]=41.8239; 
rul[5][0][182]=9.4857; rul[5][0][183]=9.49486; rul[5][0][184]=11.9466; rul[5][0][185]=11.9622; rul[5][0][186]=243.971; rul[5][0][187]=251.269; 
rul[5][0][188]=7.17329; rul[5][0][189]=7.20303; rul[5][0][190]=7.67018; rul[5][0][191]=7.68342; rul[5][0][192]=2.9648; rul[5][0][193]=2.9698; 
rul[5][0][194]=4.38473; rul[5][0][195]=4.39515; rul[5][0][196]=25.3252; rul[5][0][197]=25.3424; rul[5][0][198]=46.4188; rul[5][0][199]=46.6299; 
rul[5][0][200]=30.2162; rul[5][0][201]=30.2501; rul[5][0][202]=8.19648; rul[5][0][203]=8.21208; rul[5][0][204]=3.98565; rul[5][0][205]=3.99198; 
rul[5][0][206]=9.71898; rul[5][0][207]=9.73318; rul[5][0][208]=27.5115; rul[5][0][209]=27.5162; rul[5][0][210]=4.50261; rul[5][0][211]=4.50638; 
rul[5][0][212]=20.7607; rul[5][0][213]=20.7808; rul[5][0][214]=10.693; rul[5][0][215]=10.6966; rul[5][0][216]=7.12423; rul[5][0][217]=7.13593; 
rul[5][0][218]=13.8373; rul[5][0][219]=13.8806; rul[5][0][220]=9.97507; rul[5][0][221]=9.99953; rul[5][0][222]=15.0357; rul[5][0][223]=15.0507; 
rul[5][0][224]=57.8979; rul[5][0][225]=58.1299; rul[5][0][226]=146.125; rul[5][0][227]=149.984; rul[5][0][228]=2.99647; rul[5][0][229]=2.99952; 
rul[5][0][230]=26.5107; rul[5][0][231]=26.5777; rul[5][0][232]=4.49387; rul[5][0][233]=4.4999; rul[5][0][234]=36.2835; rul[5][0][235]=36.3436; 
rul[5][0][236]=4.17451; rul[5][0][237]=4.17763; rul[5][0][238]=2.99985; rul[5][0][239]=3.00269; rul[5][0][240]=8.50134; rul[5][0][241]=8.50831; 
rul[5][0][242]=22.5177; rul[5][0][243]=22.5892; rul[5][0][244]=24.1926; rul[5][0][245]=24.2395; rul[5][0][246]=10.4938; rul[5][0][247]=10.5018; 
rul[5][0][248]=7.64427; rul[5][0][249]=7.65767; rul[5][0][250]=319.432; rul[5][0][251]=336.53; rul[5][0][252]=6.75378; rul[5][0][253]=6.77254; 
rul[5][0][254]=6.02075; rul[5][0][255]=6.02874; rul[5][0][256]=45.9782; rul[5][0][257]=46.2047; rul[5][0][258]=44.6662; rul[5][0][259]=45.1351; 
rul[5][0][260]=10.2611; rul[5][0][261]=10.2763; rul[5][0][262]=75.359; rul[5][0][263]=76.4302; rul[5][0][264]=5.75863; rul[5][0][265]=5.7796; 
rul[5][0][266]=26.4135; rul[5][0][267]=26.4669; rul[5][0][268]=10.2902; rul[5][0][269]=10.3055; rul[5][0][270]=6.32154; rul[5][0][271]=6.33104; 
rul[5][0][272]=128.209; rul[5][0][273]=131.724; rul[5][0][274]=20.6647; rul[5][0][275]=20.6951; rul[5][0][276]=55.249; rul[5][0][277]=55.4047; 
rul[5][0][278]=38.3424; rul[5][0][279]=38.5014; rul[5][0][280]=6.982; rul[5][0][281]=6.98577; rul[5][0][282]=14.2456; rul[5][0][283]=14.2531; 
rul[5][0][284]=15.2909; rul[5][0][285]=15.3241; rul[5][0][286]=8.40457; rul[5][0][287]=8.41346; rul[5][0][288]=5.69968; rul[5][0][289]=5.70481; 
rul[5][0][290]=25.1088; rul[5][0][291]=25.1283; rul[5][0][292]=38.7497; rul[5][0][293]=39.3465; rul[5][0][294]=6.94092; rul[5][0][295]=6.95739; 
rul[5][0][296]=58.3882; rul[5][0][297]=58.7512; rul[5][0][298]=4.85151; rul[5][0][299]=4.87785; rul[5][0][300]=79.3451; rul[5][0][301]=82.0156; 
rul[5][0][302]=9.49746; rul[5][0][303]=9.50334; rul[5][0][304]=15.5642; rul[5][0][305]=15.6411; rul[5][0][306]=2.98946; rul[5][0][307]=2.99028; 
rul[5][0][308]=10.0698; rul[5][0][309]=10.0761; rul[5][0][310]=8.7246; rul[5][0][311]=8.73729; rul[5][0][312]=4.0928; rul[5][0][313]=4.11218; 
rul[5][0][314]=12.303; rul[5][0][315]=12.311; rul[5][0][316]=21.5236; rul[5][0][317]=21.5637; rul[5][0][318]=3.5046; rul[5][0][319]=3.50515; 
rul[5][0][320]=65.3561; rul[5][0][321]=65.8179; rul[5][0][322]=21.1128; rul[5][0][323]=21.1553; rul[5][0][324]=11.9111; rul[5][0][325]=11.9221; 
rul[5][0][326]=3.00418; rul[5][0][327]=3.00553; rul[5][0][328]=27.7373; rul[5][0][329]=27.7865; rul[5][0][330]=31.8118; rul[5][0][331]=31.9535; 
rul[5][0][332]=48.6251; rul[5][0][333]=49.0226; rul[5][0][334]=5.19756; rul[5][0][335]=5.20987; rul[5][0][336]=5.40869; rul[5][0][337]=5.4194; 
rul[5][0][338]=140.904; rul[5][0][339]=143.758; rul[5][0][340]=18.6512; rul[5][0][341]=18.6671; rul[5][0][342]=2.99174; rul[5][0][343]=2.99536; 
rul[5][0][344]=15.3471; rul[5][0][345]=15.3687; rul[5][0][346]=23.5225; rul[5][0][347]=23.6723; rul[5][0][348]=6.39209; rul[5][0][349]=6.40655; 
rul[5][0][350]=13.7126; rul[5][0][351]=13.7163; rul[5][0][352]=23.8933; rul[5][0][353]=24.0799; rul[5][0][354]=8.38843; rul[5][0][355]=8.38912; 
rul[5][0][356]=3.0247; rul[5][0][357]=3.06291; rul[5][0][358]=7.76735; rul[5][0][359]=7.78193; rul[5][0][360]=14.0497; rul[5][0][361]=14.0608; 
rul[5][0][362]=36.6836; rul[5][0][363]=37.1544; rul[5][0][364]=7.49409; rul[5][0][365]=7.49596; rul[5][0][366]=7.34251; rul[5][0][367]=7.36108; 
rul[5][0][368]=6.4809; rul[5][0][369]=6.52292; rul[5][0][370]=27.5303; rul[5][0][371]=27.5557; rul[5][0][372]=6.65905; rul[5][0][373]=6.66576; 
rul[5][0][374]=46.812; rul[5][0][375]=46.8839; 
dl_reg[5]=1;
dec[5]=4; 
// 6. Koniec reguly
// 7. Regula
// 1. sekcja AND 7 reguly.
rul[6][0][0]=43; rul[6][0][1]=378; 
rul[6][0][2]=14.9265; rul[6][0][3]=15.0224; rul[6][0][4]=13.7265; rul[6][0][5]=13.7908; rul[6][0][6]=15.6411; rul[6][0][7]=15.7733; 
rul[6][0][8]=9.62728; rul[6][0][9]=9.67126; rul[6][0][10]=18.1958; rul[6][0][11]=18.4347; rul[6][0][12]=13.7002; rul[6][0][13]=13.7126; 
rul[6][0][14]=13.5134; rul[6][0][15]=13.6795; rul[6][0][16]=7.42851; rul[6][0][17]=7.44863; rul[6][0][18]=9.2525; rul[6][0][19]=9.28368; 
rul[6][0][20]=11.5578; rul[6][0][21]=11.6134; rul[6][0][22]=22.263; rul[6][0][23]=22.4224; rul[6][0][24]=9.83396; rul[6][0][25]=9.89504; 
rul[6][0][26]=16.2692; rul[6][0][27]=16.3933; rul[6][0][28]=10.1008; rul[6][0][29]=10.1505; rul[6][0][30]=9.28537; rul[6][0][31]=9.31701; 
rul[6][0][32]=18.8154; rul[6][0][33]=18.8723; rul[6][0][34]=35.5079; rul[6][0][35]=35.8785; rul[6][0][36]=12.9063; rul[6][0][37]=12.9417; 
rul[6][0][38]=10.9906; rul[6][0][39]=11.0867; rul[6][0][40]=27.1766; rul[6][0][41]=27.5115; rul[6][0][42]=17.3536; rul[6][0][43]=17.5273; 
rul[6][0][44]=15.9837; rul[6][0][45]=15.999; rul[6][0][46]=7.56587; rul[6][0][47]=7.60944; rul[6][0][48]=6.90351; rul[6][0][49]=6.94092; 
rul[6][0][50]=15.4491; rul[6][0][51]=15.5642; rul[6][0][52]=32.4642; rul[6][0][53]=32.7874; rul[6][0][54]=17.5756; rul[6][0][55]=17.6062; 
rul[6][0][56]=16.0036; rul[6][0][57]=16.0574; rul[6][0][58]=17.2217; rul[6][0][59]=17.2901; rul[6][0][60]=24.0799; rul[6][0][61]=24.1926; 
rul[6][0][62]=21.4729; rul[6][0][63]=21.4826; rul[6][0][64]=24.4449; rul[6][0][65]=24.5672; rul[6][0][66]=6.54183; rul[6][0][67]=6.56738; 
rul[6][0][68]=5.39775; rul[6][0][69]=5.40627; rul[6][0][70]=16.1249; rul[6][0][71]=16.2099; rul[6][0][72]=12.8206; rul[6][0][73]=12.865; 
rul[6][0][74]=25.4526; rul[6][0][75]=25.9986; rul[6][0][76]=11.9783; rul[6][0][77]=12.0621; rul[6][0][78]=18.0758; rul[6][0][79]=18.1428; 
rul[6][0][80]=9.50334; rul[6][0][81]=9.56097; rul[6][0][82]=46.2047; rul[6][0][83]=46.4188; rul[6][0][84]=7.94503; rul[6][0][85]=7.99217; 
rul[6][0][86]=10.0302; rul[6][0][87]=10.0569; rul[6][0][88]=7.81449; rul[6][0][89]=7.85518; rul[6][0][90]=9.41744; rul[6][0][91]=9.44583; 
rul[6][0][92]=12.467; rul[6][0][93]=12.6038; rul[6][0][94]=12.1459; rul[6][0][95]=12.1702; rul[6][0][96]=10.7172; rul[6][0][97]=10.7786; 
rul[6][0][98]=53.0122; rul[6][0][99]=53.5956; rul[6][0][100]=7.02862; rul[6][0][101]=7.03005; rul[6][0][102]=6.14506; rul[6][0][103]=6.15555; 
rul[6][0][104]=11.6292; rul[6][0][105]=11.6843; rul[6][0][106]=16.7318; rul[6][0][107]=16.766; rul[6][0][108]=25.2845; rul[6][0][109]=25.3001; 
rul[6][0][110]=6.82147; rul[6][0][111]=6.8761; rul[6][0][112]=6.28993; rul[6][0][113]=6.31807; rul[6][0][114]=5.73852; rul[6][0][115]=5.75087; 
rul[6][0][116]=5.30013; rul[6][0][117]=5.32149; rul[6][0][118]=6.03143; rul[6][0][119]=6.04988; rul[6][0][120]=58.7512; rul[6][0][121]=60.3298; 
rul[6][0][122]=11.2058; rul[6][0][123]=11.2475; rul[6][0][124]=34.7565; rul[6][0][125]=34.8602; rul[6][0][126]=6.69557; rul[6][0][127]=6.70203; 
rul[6][0][128]=26.1901; rul[6][0][129]=26.308; rul[6][0][130]=6.65076; rul[6][0][131]=6.65905; rul[6][0][132]=10.8234; rul[6][0][133]=10.8522; 
rul[6][0][134]=9.3188; rul[6][0][135]=9.3396; rul[6][0][136]=9.6786; rul[6][0][137]=9.69584; rul[6][0][138]=5.51845; rul[6][0][139]=5.53278; 
rul[6][0][140]=8.24273; rul[6][0][141]=8.30125; rul[6][0][142]=25.1283; rul[6][0][143]=25.2034; rul[6][0][144]=28.5983; rul[6][0][145]=28.6361; 
rul[6][0][146]=8.66031; rul[6][0][147]=8.70596; rul[6][0][148]=7.78193; rul[6][0][149]=7.80087; rul[6][0][150]=18.7584; rul[6][0][151]=18.788; 
rul[6][0][152]=4.8387; rul[6][0][153]=4.84227; rul[6][0][154]=4.17177; rul[6][0][155]=4.17451; rul[6][0][156]=32.1895; rul[6][0][157]=32.2995; 
rul[6][0][158]=15.8487; rul[6][0][159]=15.8606; rul[6][0][160]=6.88081; rul[6][0][161]=6.9004; rul[6][0][162]=7.49596; rul[6][0][163]=7.51716; 
rul[6][0][164]=6.23424; rul[6][0][165]=6.25824; rul[6][0][166]=11.4468; rul[6][0][167]=11.4791; rul[6][0][168]=13.2043; rul[6][0][169]=13.2269; 
rul[6][0][170]=8.8923; rul[6][0][171]=8.90293; rul[6][0][172]=31.7029; rul[6][0][173]=31.7583; rul[6][0][174]=49.812; rul[6][0][175]=49.9392; 
rul[6][0][176]=36.3436; rul[6][0][177]=36.4569; rul[6][0][178]=6.73021; rul[6][0][179]=6.75378; rul[6][0][180]=13.2705; rul[6][0][181]=13.2829; 
rul[6][0][182]=14.884; rul[6][0][183]=14.8978; rul[6][0][184]=9.16072; rul[6][0][185]=9.16422; rul[6][0][186]=4.53963; rul[6][0][187]=4.55781; 
rul[6][0][188]=50.6073; rul[6][0][189]=51.756; rul[6][0][190]=15.902; rul[6][0][191]=15.9531; rul[6][0][192]=7.04325; rul[6][0][193]=7.06119; 
rul[6][0][194]=5.11409; rul[6][0][195]=5.12048; rul[6][0][196]=11.89; rul[6][0][197]=11.9111; rul[6][0][198]=13.0278; rul[6][0][199]=13.0435; 
rul[6][0][200]=14.3652; rul[6][0][201]=14.4206; rul[6][0][202]=58.1299; rul[6][0][203]=58.3882; rul[6][0][204]=27.5557; rul[6][0][205]=27.6358; 
rul[6][0][206]=46.6299; rul[6][0][207]=46.812; rul[6][0][208]=4.00098; rul[6][0][209]=4.00286; rul[6][0][210]=18.7246; rul[6][0][211]=18.751; 
rul[6][0][212]=18.9039; rul[6][0][213]=18.9105; rul[6][0][214]=65.8179; rul[6][0][215]=66.4694; rul[6][0][216]=12.1806; rul[6][0][217]=12.1954; 
rul[6][0][218]=19.4836; rul[6][0][219]=19.5191; rul[6][0][220]=26.682; rul[6][0][221]=26.7286; rul[6][0][222]=18.5059; rul[6][0][223]=18.5575; 
rul[6][0][224]=11.616; rul[6][0][225]=11.6207; rul[6][0][226]=13.0823; rul[6][0][227]=13.0968; rul[6][0][228]=4.40913; rul[6][0][229]=4.45118; 
rul[6][0][230]=10.23; rul[6][0][231]=10.2611; rul[6][0][232]=19.5863; rul[6][0][233]=19.6198; rul[6][0][234]=38.2165; rul[6][0][235]=38.3424; 
rul[6][0][236]=4.35672; rul[6][0][237]=4.35897; rul[6][0][238]=7.01934; rul[6][0][239]=7.02466; rul[6][0][240]=9.3833; rul[6][0][241]=9.40442; 
rul[6][0][242]=10.0761; rul[6][0][243]=10.0931; rul[6][0][244]=12.0803; rul[6][0][245]=12.0917; rul[6][0][246]=12.4149; rul[6][0][247]=12.4398; 
rul[6][0][248]=45.1351; rul[6][0][249]=45.4444; rul[6][0][250]=32.9426; rul[6][0][251]=33.1512; rul[6][0][252]=10.8924; rul[6][0][253]=10.9359; 
rul[6][0][254]=14.0608; rul[6][0][255]=14.0731; rul[6][0][256]=7.63125; rul[6][0][257]=7.64427; rul[6][0][258]=11.8086; rul[6][0][259]=11.8402; 
rul[6][0][260]=7.08794; rul[6][0][261]=7.11346; rul[6][0][262]=22.5892; rul[6][0][263]=22.6933; rul[6][0][264]=9.06527; rul[6][0][265]=9.11447; 
rul[6][0][266]=41.8239; rul[6][0][267]=42.0006; rul[6][0][268]=44.401; rul[6][0][269]=44.6662; rul[6][0][270]=7.74685; rul[6][0][271]=7.76735; 
rul[6][0][272]=10.8638; rul[6][0][273]=10.8705; rul[6][0][274]=13.4509; rul[6][0][275]=13.4701; rul[6][0][276]=7.13593; rul[6][0][277]=7.17329; 
rul[6][0][278]=39.6224; rul[6][0][279]=39.7641; rul[6][0][280]=19.1556; rul[6][0][281]=19.3577; rul[6][0][282]=14.0816; rul[6][0][283]=14.0925; 
rul[6][0][284]=14.4681; rul[6][0][285]=14.6437; rul[6][0][286]=39.8489; rul[6][0][287]=40.0576; rul[6][0][288]=31.4031; rul[6][0][289]=31.4462; 
rul[6][0][290]=8.12798; rul[6][0][291]=8.13956; rul[6][0][292]=6.60953; rul[6][0][293]=6.61335; rul[6][0][294]=49.2385; rul[6][0][295]=49.3998; 
rul[6][0][296]=15.3241; rul[6][0][297]=15.3471; rul[6][0][298]=17.1748; rul[6][0][299]=17.201; rul[6][0][300]=8.99275; rul[6][0][301]=8.99529; 
rul[6][0][302]=65.0491; rul[6][0][303]=65.3561; rul[6][0][304]=16.4288; rul[6][0][305]=16.4831; rul[6][0][306]=14.454; rul[6][0][307]=14.4558; 
rul[6][0][308]=10.3791; rul[6][0][309]=10.4262; rul[6][0][310]=5.56089; rul[6][0][311]=5.57709; rul[6][0][312]=5.268; rul[6][0][313]=5.27943; 
rul[6][0][314]=10.1593; rul[6][0][315]=10.1772; rul[6][0][316]=10.5252; rul[6][0][317]=10.5787; rul[6][0][318]=25.3073; rul[6][0][319]=25.3252; 
rul[6][0][320]=5.71838; rul[6][0][321]=5.7263; rul[6][0][322]=17.9033; rul[6][0][323]=17.9116; rul[6][0][324]=5.18434; rul[6][0][325]=5.19756; 
rul[6][0][326]=10.365; rul[6][0][327]=10.3716; rul[6][0][328]=7.0106; rul[6][0][329]=7.01247; rul[6][0][330]=6.34421; rul[6][0][331]=6.36808; 
rul[6][0][332]=4.94989; rul[6][0][333]=4.96118; rul[6][0][334]=min; rul[6][0][335]=2.91307; rul[6][0][336]=7.54026; rul[6][0][337]=7.55997; 
rul[6][0][338]=31.0424; rul[6][0][339]=31.1001; rul[6][0][340]=11.7166; rul[6][0][341]=11.7614; rul[6][0][342]=8.0382; rul[6][0][343]=8.05705; 
rul[6][0][344]=4.68302; rul[6][0][345]=4.68647; rul[6][0][346]=20.462; rul[6][0][347]=20.6647; rul[6][0][348]=39.4884; rul[6][0][349]=39.5439; 
rul[6][0][350]=12.1432; rul[6][0][351]=12.1445; rul[6][0][352]=4.17763; rul[6][0][353]=4.18072; rul[6][0][354]=19.0494; rul[6][0][355]=19.0774; 
rul[6][0][356]=10.6743; rul[6][0][357]=10.687; rul[6][0][358]=21.352; rul[6][0][359]=21.4127; rul[6][0][360]=6.67309; rul[6][0][361]=6.67742; 
rul[6][0][362]=15.1248; rul[6][0][363]=15.2049; rul[6][0][364]=20.9943; rul[6][0][365]=21.0541; rul[6][0][366]=8.47507; rul[6][0][367]=8.49417; 
rul[6][0][368]=30.275; rul[6][0][369]=30.3987; rul[6][0][370]=5.58671; rul[6][0][371]=5.58838; rul[6][0][372]=9.74294; rul[6][0][373]=9.76482; 
rul[6][0][374]=12.2602; rul[6][0][375]=12.2948; rul[6][0][376]=10.5018; rul[6][0][377]=10.5144; rul[6][0][378]=3.78032; rul[6][0][379]=3.846; 
dl_reg[6]=1;
dec[6]=2; 
// 7. Koniec reguly
// 8. Regula
// 1. sekcja AND 8 reguly.
rul[7][0][0]=43; rul[7][0][1]=58; 
rul[7][0][2]=614.763; rul[7][0][3]=max; rul[7][0][4]=5.50568; rul[7][0][5]=5.51845; rul[7][0][6]=13.6795; rul[7][0][7]=13.693; 
rul[7][0][8]=57.3754; rul[7][0][9]=57.8979; rul[7][0][10]=396.398; rul[7][0][11]=421.598; rul[7][0][12]=4.36615; rul[7][0][13]=4.37103; 
rul[7][0][14]=12.1445; rul[7][0][15]=12.1459; rul[7][0][16]=38.5014; rul[7][0][17]=38.613; rul[7][0][18]=217.402; rul[7][0][19]=226.28; 
rul[7][0][20]=66.4694; rul[7][0][21]=67.2278; rul[7][0][22]=4.52656; rul[7][0][23]=4.53963; rul[7][0][24]=5.95757; rul[7][0][25]=5.96048; 
rul[7][0][26]=17.201; rul[7][0][27]=17.2217; rul[7][0][28]=234.209; rul[7][0][29]=243.971; rul[7][0][30]=10.5939; rul[7][0][31]=10.6096; 
rul[7][0][32]=5.5908; rul[7][0][33]=5.62997; rul[7][0][34]=6.4355; rul[7][0][35]=6.43788; rul[7][0][36]=49.0226; rul[7][0][37]=49.2385; 
rul[7][0][38]=437.402; rul[7][0][39]=475.1; rul[7][0][40]=76.4302; rul[7][0][41]=77.5492; rul[7][0][42]=6.68788; rul[7][0][43]=6.69557; 
rul[7][0][44]=251.269; rul[7][0][45]=319.432; rul[7][0][46]=6.60009; rul[7][0][47]=6.60896; rul[7][0][48]=85.5294; rul[7][0][49]=85.9961; 
rul[7][0][50]=5.86877; rul[7][0][51]=5.88656; rul[7][0][52]=105.803; rul[7][0][53]=109.526; rul[7][0][54]=67.9432; rul[7][0][55]=68.1373; 
rul[7][0][56]=18.9012; rul[7][0][57]=18.9039; rul[7][0][58]=4.58431; rul[7][0][59]=4.58875; 
dl_reg[7]=1;
dec[7]=5; 
// 8. Koniec reguly
// 9. Regula
// 1. sekcja AND 9 reguly.
rul[8][0][0]=43; rul[8][0][1]=384; 
rul[8][0][2]=28.6536; rul[8][0][3]=28.9723; rul[8][0][4]=8.00365; rul[8][0][5]=8.0382; rul[8][0][6]=24.6412; rul[8][0][7]=24.9379; 
rul[8][0][8]=9.76482; rul[8][0][9]=9.83396; rul[8][0][10]=14.2531; rul[8][0][11]=14.2745; rul[8][0][12]=13.0968; rul[8][0][13]=13.2017; 
rul[8][0][14]=18.5575; rul[8][0][15]=18.5917; rul[8][0][16]=12.327; rul[8][0][17]=12.3553; rul[8][0][18]=40.0576; rul[8][0][19]=40.8333; 
rul[8][0][20]=6.08318; rul[8][0][21]=6.14107; rul[8][0][22]=14.0183; rul[8][0][23]=14.0497; rul[8][0][24]=7.65767; rul[8][0][25]=7.67018; 
rul[8][0][26]=34.6133; rul[8][0][27]=34.7565; rul[8][0][28]=5.03773; rul[8][0][29]=5.0712; rul[8][0][30]=3.90277; rul[8][0][31]=3.97264; 
rul[8][0][32]=4.37103; rul[8][0][33]=4.38473; rul[8][0][34]=2.99028; rul[8][0][35]=2.99174; rul[8][0][36]=55.4047; rul[8][0][37]=56.5029; 
rul[8][0][38]=4.01432; rul[8][0][39]=4.0928; rul[8][0][40]=14.7467; rul[8][0][41]=14.8639; rul[8][0][42]=18.9472; rul[8][0][43]=19.0494; 
rul[8][0][44]=2.9698; rul[8][0][45]=2.98316; rul[8][0][46]=4.47178; rul[8][0][47]=4.48539; rul[8][0][48]=4.87785; rul[8][0][49]=4.89423; 
rul[8][0][50]=9.31701; rul[8][0][51]=9.3188; rul[8][0][52]=25.2034; rul[8][0][53]=25.2845; rul[8][0][54]=50.1092; rul[8][0][55]=50.6073; 
rul[8][0][56]=10.3439; rul[8][0][57]=10.365; rul[8][0][58]=18.751; rul[8][0][59]=18.7584; rul[8][0][60]=6.97223; rul[8][0][61]=6.97738; 
rul[8][0][62]=8.55093; rul[8][0][63]=8.59291; rul[8][0][64]=6.16621; rul[8][0][65]=6.16917; rul[8][0][66]=8.88589; rul[8][0][67]=8.88807; 
rul[8][0][68]=6.42131; rul[8][0][69]=6.43015; rul[8][0][70]=8.84548; rul[8][0][71]=8.87558; rul[8][0][72]=17.6062; rul[8][0][73]=17.6536; 
rul[8][0][74]=2.98479; rul[8][0][75]=2.98946; rul[8][0][76]=29.8381; rul[8][0][77]=30.0509; rul[8][0][78]=46.8839; rul[8][0][79]=47.0403; 
rul[8][0][80]=28.4398; rul[8][0][81]=28.4815; rul[8][0][82]=67.8042; rul[8][0][83]=67.9432; rul[8][0][84]=6.63064; rul[8][0][85]=6.63162; 
rul[8][0][86]=27.7865; rul[8][0][87]=27.846; rul[8][0][88]=12.219; rul[8][0][89]=12.2251; rul[8][0][90]=42.2637; rul[8][0][91]=42.6996; 
rul[8][0][92]=49.3998; rul[8][0][93]=49.6491; rul[8][0][94]=30.2501; rul[8][0][95]=30.275; rul[8][0][96]=27.5162; rul[8][0][97]=27.5303; 
rul[8][0][98]=15.844; rul[8][0][99]=15.8487; rul[8][0][100]=15.7733; rul[8][0][101]=15.8354; rul[8][0][102]=5.54164; rul[8][0][103]=5.54625; 
rul[8][0][104]=2.99536; rul[8][0][105]=2.99647; rul[8][0][106]=11.7764; rul[8][0][107]=11.7897; rul[8][0][108]=10.687; rul[8][0][109]=10.693; 
rul[8][0][110]=3.51098; rul[8][0][111]=3.51786; rul[8][0][112]=18.69; rul[8][0][113]=18.7246; rul[8][0][114]=3.01172; rul[8][0][115]=3.01226; 
rul[8][0][116]=42.2423; rul[8][0][117]=42.2543; rul[8][0][118]=51.756; rul[8][0][119]=51.9874; rul[8][0][120]=35.2683; rul[8][0][121]=35.5079; 
rul[8][0][122]=19.8315; rul[8][0][123]=19.9823; rul[8][0][124]=4.24681; rul[8][0][125]=4.27997; rul[8][0][126]=4.35548; rul[8][0][127]=4.35672; 
rul[8][0][128]=20.2824; rul[8][0][129]=20.2888; rul[8][0][130]=21.4646; rul[8][0][131]=21.4729; rul[8][0][132]=10.1772; rul[8][0][133]=10.1856; 
rul[8][0][134]=14.3477; rul[8][0][135]=14.3652; rul[8][0][136]=44.1536; rul[8][0][137]=44.281; rul[8][0][138]=3.00948; rul[8][0][139]=3.01062; 
rul[8][0][140]=4.49176; rul[8][0][141]=4.49387; rul[8][0][142]=8.09549; rul[8][0][143]=8.11833; rul[8][0][144]=14.2174; rul[8][0][145]=14.2317; 
rul[8][0][146]=10.3716; rul[8][0][147]=10.3791; rul[8][0][148]=14.6437; rul[8][0][149]=14.6602; rul[8][0][150]=3.47821; rul[8][0][151]=3.48224; 
rul[8][0][152]=17.0865; rul[8][0][153]=17.1189; rul[8][0][154]=8.30125; rul[8][0][155]=8.31943; rul[8][0][156]=16.5546; rul[8][0][157]=16.5793; 
rul[8][0][158]=91.914; rul[8][0][159]=94.9198; rul[8][0][160]=29.5716; rul[8][0][161]=29.6729; rul[8][0][162]=5.82669; rul[8][0][163]=5.83362; 
rul[8][0][164]=71.529; rul[8][0][165]=73.6333; rul[8][0][166]=31.7583; rul[8][0][167]=31.8118; rul[8][0][168]=16.7982; rul[8][0][169]=16.897; 
rul[8][0][170]=31.4462; rul[8][0][171]=31.7029; rul[8][0][172]=4.97178; rul[8][0][173]=4.98176; rul[8][0][174]=13.2516; rul[8][0][175]=13.2705; 
rul[8][0][176]=15.8606; rul[8][0][177]=15.902; rul[8][0][178]=19.5496; rul[8][0][179]=19.5863; rul[8][0][180]=23.0643; rul[8][0][181]=23.1066; 
rul[8][0][182]=11.1056; rul[8][0][183]=11.1411; rul[8][0][184]=6.5838; rul[8][0][185]=6.60009; rul[8][0][186]=143.758; rul[8][0][187]=146.125; 
rul[8][0][188]=4.73673; rul[8][0][189]=4.7939; rul[8][0][190]=5.18213; rul[8][0][191]=5.18434; rul[8][0][192]=4.18072; rul[8][0][193]=4.20009; 
rul[8][0][194]=15.999; rul[8][0][195]=16.0036; rul[8][0][196]=14.1226; rul[8][0][197]=14.1517; rul[8][0][198]=3.5939; rul[8][0][199]=3.67549; 
rul[8][0][200]=17.0439; rul[8][0][201]=17.0638; rul[8][0][202]=77.5492; rul[8][0][203]=77.9747; rul[8][0][204]=5.88656; rul[8][0][205]=5.9358; 
rul[8][0][206]=21.6085; rul[8][0][207]=21.6342; rul[8][0][208]=12.311; rul[8][0][209]=12.3189; rul[8][0][210]=8.4578; rul[8][0][211]=8.47507; 
rul[8][0][212]=9.89504; rul[8][0][213]=9.90477; rul[8][0][214]=8.79806; rul[8][0][215]=8.81079; rul[8][0][216]=4.89941; rul[8][0][217]=4.93261; 
rul[8][0][218]=12.2948; rul[8][0][219]=12.303; rul[8][0][220]=15.9731; rul[8][0][221]=15.9837; rul[8][0][222]=7.11346; rul[8][0][223]=7.12423; 
rul[8][0][224]=7.62001; rul[8][0][225]=7.63125; rul[8][0][226]=9.49486; rul[8][0][227]=9.49746; rul[8][0][228]=9.96919; rul[8][0][229]=9.97507; 
rul[8][0][230]=7.86272; rul[8][0][231]=7.87438; rul[8][0][232]=4.55781; rul[8][0][233]=4.56635; rul[8][0][234]=25.3001; rul[8][0][235]=25.3073; 
rul[8][0][236]=11.5482; rul[8][0][237]=11.5578; rul[8][0][238]=4.50825; rul[8][0][239]=4.52656; rul[8][0][240]=12.7627; rul[8][0][241]=12.7869; 
rul[8][0][242]=12.865; rul[8][0][243]=12.9048; rul[8][0][244]=32.0381; rul[8][0][245]=32.1895; rul[8][0][246]=8.76938; rul[8][0][247]=8.79123; 
rul[8][0][248]=7.20303; rul[8][0][249]=7.21778; rul[8][0][250]=7.85518; rul[8][0][251]=7.86112; rul[8][0][252]=10.0931; rul[8][0][253]=10.1008; 
rul[8][0][254]=13.4289; rul[8][0][255]=13.4509; rul[8][0][256]=121.501; rul[8][0][257]=125.232; rul[8][0][258]=5.70481; rul[8][0][259]=5.71057; 
rul[8][0][260]=2.99952; rul[8][0][261]=2.99985; rul[8][0][262]=31.3842; rul[8][0][263]=31.4031; rul[8][0][264]=17.138; rul[8][0][265]=17.1501; 
rul[8][0][266]=26.951; rul[8][0][267]=27.1766; rul[8][0][268]=15.3687; rul[8][0][269]=15.383; rul[8][0][270]=18.788; rul[8][0][271]=18.8154; 
rul[8][0][272]=17.6895; rul[8][0][273]=17.724; rul[8][0][274]=6.53713; rul[8][0][275]=6.54183; rul[8][0][276]=16.766; rul[8][0][277]=16.7861; 
rul[8][0][278]=10.8106; rul[8][0][279]=10.8234; rul[8][0][280]=6.71771; rul[8][0][281]=6.73021; rul[8][0][282]=5.382; rul[8][0][283]=5.39775; 
rul[8][0][284]=6.27145; rul[8][0][285]=6.28993; rul[8][0][286]=3.43035; rul[8][0][287]=3.46663; rul[8][0][288]=6.00082; rul[8][0][289]=6.02075; 
rul[8][0][290]=36.5787; rul[8][0][291]=36.6836; rul[8][0][292]=21.4983; rul[8][0][293]=21.5236; rul[8][0][294]=6.70203; rul[8][0][295]=6.71598; 
rul[8][0][296]=9.11447; rul[8][0][297]=9.16072; rul[8][0][298]=11.1874; rul[8][0][299]=11.2058; rul[8][0][300]=26.1069; rul[8][0][301]=26.1208; 
rul[8][0][302]=7.29567; rul[8][0][303]=7.34251; rul[8][0][304]=33.9864; rul[8][0][305]=34.0445; rul[8][0][306]=6.66576; rul[8][0][307]=6.67309; 
rul[8][0][308]=7.41186; rul[8][0][309]=7.42851; rul[8][0][310]=11.2743; rul[8][0][311]=11.3121; rul[8][0][312]=11.7139; rul[8][0][313]=11.7166; 
rul[8][0][314]=5.20987; rul[8][0][315]=5.22201; rul[8][0][316]=13.7163; rul[8][0][317]=13.7265; rul[8][0][318]=7.80087; rul[8][0][319]=7.81449; 
rul[8][0][320]=7.99217; rul[8][0][321]=7.99945; rul[8][0][322]=10.7915; rul[8][0][323]=10.8099; rul[8][0][324]=21.871; rul[8][0][325]=21.9622; 
rul[8][0][326]=11.8402; rul[8][0][327]=11.8621; rul[8][0][328]=13.9197; rul[8][0][329]=13.9815; rul[8][0][330]=6.77254; rul[8][0][331]=6.78258; 
rul[8][0][332]=5.40627; rul[8][0][333]=5.40869; rul[8][0][334]=17.9226; rul[8][0][335]=17.9685; rul[8][0][336]=4.84435; rul[8][0][337]=4.85151; 
rul[8][0][338]=9.69584; rul[8][0][339]=9.71898; rul[8][0][340]=21.9972; rul[8][0][341]=22.0651; rul[8][0][342]=20.3689; rul[8][0][343]=20.4151; 
rul[8][0][344]=4.50638; rul[8][0][345]=4.50783; rul[8][0][346]=179.74; rul[8][0][347]=185.926; rul[8][0][348]=3.99198; rul[8][0][349]=3.99776; 
rul[8][0][350]=15.0224; rul[8][0][351]=15.0357; rul[8][0][352]=11.9622; rul[8][0][353]=11.9783; rul[8][0][354]=8.37163; rul[8][0][355]=8.3809; 
rul[8][0][356]=21.7768; rul[8][0][357]=21.8248; rul[8][0][358]=14.6902; rul[8][0][359]=14.7135; rul[8][0][360]=5.14844; rul[8][0][361]=5.16567; 
rul[8][0][362]=4.31803; rul[8][0][363]=4.33675; rul[8][0][364]=566.75; rul[8][0][365]=587.915; rul[8][0][366]=12.1702; rul[8][0][367]=12.1806; 
rul[8][0][368]=6.78974; rul[8][0][369]=6.79448; rul[8][0][370]=7.37079; rul[8][0][371]=7.38548; rul[8][0][372]=26.4669; rul[8][0][373]=26.5107; 
rul[8][0][374]=6.87846; rul[8][0][375]=6.88081; rul[8][0][376]=27.6358; rul[8][0][377]=27.7373; rul[8][0][378]=2.91307; rul[8][0][379]=2.9648; 
rul[8][0][380]=42.0006; rul[8][0][381]=42.1526; rul[8][0][382]=8.65861; rul[8][0][383]=8.66031; rul[8][0][384]=56.7944; rul[8][0][385]=57.3754; 
dl_reg[8]=1;
dec[8]=3; 
// 9. Koniec reguly
// 10. Regula
// 1. sekcja AND 10 reguly.
rul[9][0][0]=57; rul[9][0][1]=400; 
rul[9][0][2]=7.748E-6; rul[9][0][3]=8.183E-6; rul[9][0][4]=-3.81618E-4; rul[9][0][5]=-3.71699E-4; rul[9][0][6]=-7.3782E-5; rul[9][0][7]=-7.1777E-5; 
rul[9][0][8]=-2.05035E-5; rul[9][0][9]=-2.0257E-5; rul[9][0][10]=4.994E-6; rul[9][0][11]=5.085E-6; rul[9][0][12]=1.2734E-5; rul[9][0][13]=1.3178E-5; 
rul[9][0][14]=7.15534E-4; rul[9][0][15]=7.30894E-4; rul[9][0][16]=-1.02616E-4; rul[9][0][17]=-1.01699E-4; rul[9][0][18]=0.00110514; rul[9][0][19]=0.00114683; 
rul[9][0][20]=1.9187E-5; rul[9][0][21]=1.9551E-5; rul[9][0][22]=-2.47387E-4; rul[9][0][23]=-2.44013E-4; rul[9][0][24]=-6.12745E-5; rul[9][0][25]=-5.9991E-5; 
rul[9][0][26]=2.18972E-4; rul[9][0][27]=2.2204E-4; rul[9][0][28]=-4.35941E-4; rul[9][0][29]=-4.24632E-4; rul[9][0][30]=4.43565E-5; rul[9][0][31]=4.51685E-5; 
rul[9][0][32]=-1.07818E-4; rul[9][0][33]=-1.06279E-4; rul[9][0][34]=-1.0885E-6; rul[9][0][35]=-1.0505E-6; rul[9][0][36]=-2.87748E-4; rul[9][0][37]=-2.73344E-4; 
rul[9][0][38]=1.17189E-4; rul[9][0][39]=1.21453E-4; rul[9][0][40]=-5.96777E-4; rul[9][0][41]=-5.84939E-4; rul[9][0][42]=-8.4958E-5; rul[9][0][43]=-8.23215E-5; 
rul[9][0][44]=-3.128E-6; rul[9][0][45]=-2.7755E-6; rul[9][0][46]=3.0E-6; rul[9][0][47]=3.133E-6; rul[9][0][48]=6.52085E-5; rul[9][0][49]=6.74795E-5; 
rul[9][0][50]=-7.3555E-6; rul[9][0][51]=-7.282E-6; rul[9][0][52]=-1.60585E-5; rul[9][0][53]=-1.59215E-5; rul[9][0][54]=1.86635E-5; rul[9][0][55]=1.9069E-5; 
rul[9][0][56]=-2.7E-8; rul[9][0][57]=-1.6E-8; rul[9][0][58]=5.4693E-5; rul[9][0][59]=5.5051E-5; rul[9][0][60]=-8.87125E-5; rul[9][0][61]=-8.76465E-5; 
rul[9][0][62]=-4.4565E-6; rul[9][0][63]=-4.187E-6; rul[9][0][64]=-3.62125E-5; rul[9][0][65]=-3.60475E-5; rul[9][0][66]=4.0463E-5; rul[9][0][67]=4.10355E-5; 
rul[9][0][68]=-5.07825E-5; rul[9][0][69]=-5.0626E-5; rul[9][0][70]=3.8222E-5; rul[9][0][71]=3.85345E-5; rul[9][0][72]=1.11975E-5; rul[9][0][73]=1.138E-5; 
rul[9][0][74]=-1.32825E-5; rul[9][0][75]=-1.32195E-5; rul[9][0][76]=-2.2499E-5; rul[9][0][77]=-2.23545E-5; rul[9][0][78]=-5.15625E-5; rul[9][0][79]=-5.1123E-5; 
rul[9][0][80]=-1.23225E-5; rul[9][0][81]=-1.1816E-5; rul[9][0][82]=-1.1182E-5; rul[9][0][83]=-1.06565E-5; rul[9][0][84]=2.11075E-5; rul[9][0][85]=2.1294E-5; 
rul[9][0][86]=2.74735E-5; rul[9][0][87]=2.78555E-5; rul[9][0][88]=-1.7134E-5; rul[9][0][89]=-1.70065E-5; rul[9][0][90]=1.9784E-5; rul[9][0][91]=2.02375E-5; 
rul[9][0][92]=-2.5529E-5; rul[9][0][93]=-2.54575E-5; rul[9][0][94]=-7.2445E-6; rul[9][0][95]=-7.239E-6; rul[9][0][96]=2.3678E-5; rul[9][0][97]=2.3777E-5; 
rul[9][0][98]=1.68535E-5; rul[9][0][99]=1.7146E-5; rul[9][0][100]=5.2988E-5; rul[9][0][101]=5.3512E-5; rul[9][0][102]=8.8165E-6; rul[9][0][103]=8.8485E-6; 
rul[9][0][104]=-2.0792E-5; rul[9][0][105]=-2.067E-5; rul[9][0][106]=-1.14725E-5; rul[9][0][107]=-1.14505E-5; rul[9][0][108]=-4.3215E-5; rul[9][0][109]=-4.2443E-5; 
rul[9][0][110]=6.2943E-5; rul[9][0][111]=6.32665E-5; rul[9][0][112]=-8.397E-6; rul[9][0][113]=-8.344E-6; rul[9][0][114]=1.7229E-5; rul[9][0][115]=1.74275E-5; 
rul[9][0][116]=9.5677E-5; rul[9][0][117]=9.627E-5; rul[9][0][118]=5.356E-6; rul[9][0][119]=5.4535E-6; rul[9][0][120]=1.25615E-5; rul[9][0][121]=1.25885E-5; 
rul[9][0][122]=1.38422E-4; rul[9][0][123]=1.38951E-4; rul[9][0][124]=4.65745E-5; rul[9][0][125]=4.81295E-5; rul[9][0][126]=2.6933E-5; rul[9][0][127]=2.7219E-5; 
rul[9][0][128]=6.8705E-6; rul[9][0][129]=7.048E-6; rul[9][0][130]=2.14428E-4; rul[9][0][131]=2.15866E-4; rul[9][0][132]=5.6855E-6; rul[9][0][133]=5.7205E-6; 
rul[9][0][134]=3.318E-5; rul[9][0][135]=3.3345E-5; rul[9][0][136]=1.1435E-5; rul[9][0][137]=1.1722E-5; rul[9][0][138]=-1.0499E-5; rul[9][0][139]=-1.03165E-5; 
rul[9][0][140]=2.4763E-5; rul[9][0][141]=2.4914E-5; rul[9][0][142]=-1.2145E-6; rul[9][0][143]=-1.193E-6; rul[9][0][144]=-6.7345E-6; rul[9][0][145]=-6.575E-6; 
rul[9][0][146]=1.46341E-4; rul[9][0][147]=1.49773E-4; rul[9][0][148]=-7.9772E-5; rul[9][0][149]=-7.9387E-5; rul[9][0][150]=-7.6713E-5; rul[9][0][151]=-7.51115E-5; 
rul[9][0][152]=6.4022E-5; rul[9][0][153]=6.4183E-5; rul[9][0][154]=2.2207E-5; rul[9][0][155]=2.28215E-5; rul[9][0][156]=4.8345E-6; rul[9][0][157]=4.9125E-6; 
rul[9][0][158]=-5.545E-7; rul[9][0][159]=-5.41E-7; rul[9][0][160]=-6.7548E-5; rul[9][0][161]=-6.70985E-5; rul[9][0][162]=-1.4019E-5; rul[9][0][163]=-1.38375E-5; 
rul[9][0][164]=-2.06873E-4; rul[9][0][165]=-2.0506E-4; rul[9][0][166]=-2.99905E-5; rul[9][0][167]=-2.9001E-5; rul[9][0][168]=-2.8616E-5; rul[9][0][169]=-2.85205E-5; 
rul[9][0][170]=4.24003E-4; rul[9][0][171]=4.27577E-4; rul[9][0][172]=-8.317E-6; rul[9][0][173]=-8.287E-6; rul[9][0][174]=1.71067E-4; rul[9][0][175]=1.72562E-4; 
rul[9][0][176]=1.50218E-4; rul[9][0][177]=1.50613E-4; rul[9][0][178]=1.6479E-5; rul[9][0][179]=1.6544E-5; rul[9][0][180]=-4.5965E-6; rul[9][0][181]=-4.5445E-6; 
rul[9][0][182]=-7.0165E-6; rul[9][0][183]=-6.882E-6; rul[9][0][184]=1.7646E-5; rul[9][0][185]=1.774E-5; rul[9][0][186]=-9.05065E-5; rul[9][0][187]=-8.93475E-5; 
rul[9][0][188]=-2.48482E-4; rul[9][0][189]=-2.47813E-4; rul[9][0][190]=-9.303E-6; rul[9][0][191]=-8.9815E-6; rul[9][0][192]=-9.62565E-5; rul[9][0][193]=-9.4287E-5; 
rul[9][0][194]=7.522E-5; rul[9][0][195]=7.57345E-5; rul[9][0][196]=-1.00055E-5; rul[9][0][197]=-9.927E-6; rul[9][0][198]=-4.6907E-5; rul[9][0][199]=-4.66415E-5; 
rul[9][0][200]=-7.78433E-4; rul[9][0][201]=-7.37652E-4; rul[9][0][202]=-0.00161031; rul[9][0][203]=-0.00150286; rul[9][0][204]=3.65113E-4; rul[9][0][205]=3.66853E-4; 
rul[9][0][206]=-1.98565E-5; rul[9][0][207]=-1.96565E-5; rul[9][0][208]=-4.02E-7; rul[9][0][209]=-3.78E-7; rul[9][0][210]=-1.10256E-4; rul[9][0][211]=-1.09478E-4; 
rul[9][0][212]=-9.35376E-4; rul[9][0][213]=-8.85864E-4; rul[9][0][214]=-1.66205E-5; rul[9][0][215]=-1.6308E-5; rul[9][0][216]=-2.4888E-5; rul[9][0][217]=-2.48575E-5; 
rul[9][0][218]=3.90205E-5; rul[9][0][219]=3.90475E-5; rul[9][0][220]=6.97645E-5; rul[9][0][221]=7.0241E-5; rul[9][0][222]=-5.32965E-5; rul[9][0][223]=-5.21735E-5; 
rul[9][0][224]=-0.00120696; rul[9][0][225]=-0.00118878; rul[9][0][226]=-1.471E-6; rul[9][0][227]=-1.4335E-6; rul[9][0][228]=-1.95354E-4; rul[9][0][229]=-1.91059E-4; 
rul[9][0][230]=-3.8812E-5; rul[9][0][231]=-3.76735E-5; rul[9][0][232]=-5.206E-5; rul[9][0][233]=-5.19195E-5; rul[9][0][234]=5.09294E-4; rul[9][0][235]=5.17066E-4; 
rul[9][0][236]=-4.88775E-5; rul[9][0][237]=-4.83425E-5; rul[9][0][238]=5.1905E-6; rul[9][0][239]=5.2405E-6; rul[9][0][240]=-1.27741E-4; rul[9][0][241]=-1.27201E-4; 
rul[9][0][242]=0.00116571; rul[9][0][243]=0.00116889; rul[9][0][244]=-4.95E-7; rul[9][0][245]=-4.855E-7; rul[9][0][246]=8.4692E-5; rul[9][0][247]=8.5162E-5; 
rul[9][0][248]=-5.7255E-6; rul[9][0][249]=-5.592E-6; rul[9][0][250]=5.1035E-6; rul[9][0][251]=5.135E-6; rul[9][0][252]=4.5786E-5; rul[9][0][253]=4.6131E-5; 
rul[9][0][254]=-5.3666E-5; rul[9][0][255]=-5.35805E-5; rul[9][0][256]=8.97E-6; rul[9][0][257]=9.3575E-6; rul[9][0][258]=2.5029E-5; rul[9][0][259]=2.51165E-5; 
rul[9][0][260]=-2.19515E-5; rul[9][0][261]=-2.1389E-5; rul[9][0][262]=6.34932E-4; rul[9][0][263]=6.3921E-4; rul[9][0][264]=1.4459E-5; rul[9][0][265]=1.47385E-5; 
rul[9][0][266]=-2.16777E-4; rul[9][0][267]=-2.10687E-4; rul[9][0][268]=-0.00185383; rul[9][0][269]=-0.00184867; rul[9][0][270]=-4.675E-7; rul[9][0][271]=-4.3E-7; 
rul[9][0][272]=3.07253E-4; rul[9][0][273]=3.22576E-4; rul[9][0][274]=2.1647E-5; rul[9][0][275]=2.20865E-5; rul[9][0][276]=-1.2885E-5; rul[9][0][277]=-1.25595E-5; 
rul[9][0][278]=-2.30755E-5; rul[9][0][279]=-2.29905E-5; rul[9][0][280]=-4.9175E-6; rul[9][0][281]=-4.885E-6; rul[9][0][282]=0.00320871; rul[9][0][283]=0.00324735; 
rul[9][0][284]=0.00148412; rul[9][0][285]=0.00153243; rul[9][0][286]=2.09163E-4; rul[9][0][287]=2.09697E-4; rul[9][0][288]=8.1325E-5; rul[9][0][289]=8.29895E-5; 
rul[9][0][290]=-9.955E-7; rul[9][0][291]=-9.565E-7; rul[9][0][292]=-8.795E-7; rul[9][0][293]=-8.41E-7; rul[9][0][294]=-1.08E-7; rul[9][0][295]=-7.1E-8; 
rul[9][0][296]=1.1615E-6; rul[9][0][297]=1.206E-6; rul[9][0][298]=-3.08705E-5; rul[9][0][299]=-3.0667E-5; rul[9][0][300]=0.00581319; rul[9][0][301]=0.00592256; 
rul[9][0][302]=-1.97644E-4; rul[9][0][303]=-1.97024E-4; rul[9][0][304]=1.51175E-5; rul[9][0][305]=1.5433E-5; rul[9][0][306]=-8.60365E-5; rul[9][0][307]=-8.56845E-5; 
rul[9][0][308]=1.18105E-5; rul[9][0][309]=1.24755E-5; rul[9][0][310]=-5.72355E-5; rul[9][0][311]=-5.6556E-5; rul[9][0][312]=3.0616E-5; rul[9][0][313]=3.1108E-5; 
rul[9][0][314]=9.20415E-5; rul[9][0][315]=9.23075E-5; rul[9][0][316]=7.32505E-5; rul[9][0][317]=7.47865E-5; rul[9][0][318]=2.97145E-5; rul[9][0][319]=3.02785E-5; 
rul[9][0][320]=-8.71293E-4; rul[9][0][321]=-7.98055E-4; rul[9][0][322]=3.9617E-5; rul[9][0][323]=4.02705E-5; rul[9][0][324]=2.52005E-5; rul[9][0][325]=2.53245E-5; 
rul[9][0][326]=1.13731E-4; rul[9][0][327]=1.14652E-4; rul[9][0][328]=-1.1485E-6; rul[9][0][329]=-1.1125E-6; rul[9][0][330]=-1.304E-6; rul[9][0][331]=-1.2695E-6; 
rul[9][0][332]=0.0036804; rul[9][0][333]=0.00404548; rul[9][0][334]=6.9105E-5; rul[9][0][335]=6.9366E-5; rul[9][0][336]=-1.04809E-4; rul[9][0][337]=-1.03363E-4; 
rul[9][0][338]=2.097E-6; rul[9][0][339]=2.215E-6; rul[9][0][340]=-8.2425E-6; rul[9][0][341]=-7.69E-6; rul[9][0][342]=4.379E-6; rul[9][0][343]=4.4695E-6; 
rul[9][0][344]=9.9528E-5; rul[9][0][345]=9.9886E-5; rul[9][0][346]=-2.4348E-5; rul[9][0][347]=-2.39825E-5; rul[9][0][348]=7.14335E-5; rul[9][0][349]=7.2252E-5; 
rul[9][0][350]=-1.4214E-5; rul[9][0][351]=-1.41775E-5; rul[9][0][352]=7.161E-6; rul[9][0][353]=7.263E-6; rul[9][0][354]=-8.70335E-5; rul[9][0][355]=-8.62935E-5; 
rul[9][0][356]=3.7133E-5; rul[9][0][357]=3.7298E-5; rul[9][0][358]=4.92615E-5; rul[9][0][359]=4.95725E-5; rul[9][0][360]=-1.31987E-4; rul[9][0][361]=-1.31395E-4; 
rul[9][0][362]=2.90074E-4; rul[9][0][363]=2.97074E-4; rul[9][0][364]=3.00391E-4; rul[9][0][365]=3.02766E-4; rul[9][0][366]=4.7965E-6; rul[9][0][367]=4.81E-6; 
rul[9][0][368]=-1.38764E-4; rul[9][0][369]=-1.38505E-4; rul[9][0][370]=-6.0E-9; rul[9][0][371]=7.5E-9; rul[9][0][372]=-1.8663E-5; rul[9][0][373]=-1.83915E-5; 
rul[9][0][374]=-2.59955E-5; rul[9][0][375]=-2.56355E-5; rul[9][0][376]=-9.8181E-5; rul[9][0][377]=-9.64545E-5; rul[9][0][378]=5.9035E-6; rul[9][0][379]=5.9815E-6; 
rul[9][0][380]=3.396E-6; rul[9][0][381]=3.4545E-6; rul[9][0][382]=-5.2025E-6; rul[9][0][383]=-5.133E-6; rul[9][0][384]=-9.4035E-5; rul[9][0][385]=-9.2149E-5; 
rul[9][0][386]=1.07808E-4; rul[9][0][387]=1.09046E-4; rul[9][0][388]=-4.94165E-5; rul[9][0][389]=-4.92865E-5; rul[9][0][390]=-0.00324788; rul[9][0][391]=-0.00321534; 
rul[9][0][392]=-3.245E-7; rul[9][0][393]=-3.09E-7; rul[9][0][394]=-2.849E-5; rul[9][0][395]=-2.8442E-5; rul[9][0][396]=-3.9815E-6; rul[9][0][397]=-3.818E-6; 
rul[9][0][398]=6.55096E-4; rul[9][0][399]=6.88895E-4; rul[9][0][400]=-7.0453E-5; rul[9][0][401]=-6.79775E-5; 
dl_reg[9]=1;
dec[9]=2; 
// 10. Koniec reguly
// 11. Regula
// 1. sekcja AND 11 reguly.
rul[10][0][0]=57; rul[10][0][1]=388; 
rul[10][0][2]=-3.4026E-5; rul[10][0][3]=-3.25195E-5; rul[10][0][4]=-0.0118416; rul[10][0][5]=-0.00693221; rul[10][0][6]=7.5E-9; rul[10][0][7]=7.35E-8; 
rul[10][0][8]=-4.85703E-4; rul[10][0][9]=-4.35941E-4; rul[10][0][10]=2.6965E-6; rul[10][0][11]=2.8805E-6; rul[10][0][12]=-0.0025019; rul[10][0][13]=-0.0022342; 
rul[10][0][14]=1.725E-7; rul[10][0][15]=3.13E-7; rul[10][0][16]=3.48128E-4; rul[10][0][17]=3.65113E-4; rul[10][0][18]=2.3777E-5; rul[10][0][19]=2.4685E-5; 
rul[10][0][20]=9.8185E-6; rul[10][0][21]=9.985E-6; rul[10][0][22]=-0.00592722; rul[10][0][23]=-0.0044699; rul[10][0][24]=1.86707E-4; rul[10][0][25]=1.90132E-4; 
rul[10][0][26]=0.0010379; rul[10][0][27]=0.00110514; rul[10][0][28]=-9.671E-6; rul[10][0][29]=-9.303E-6; rul[10][0][30]=4.18246E-4; rul[10][0][31]=4.24003E-4; 
rul[10][0][32]=0.00119445; rul[10][0][33]=0.0012312; rul[10][0][34]=0.00492331; rul[10][0][35]=0.00555046; rul[10][0][36]=-2.90116E-4; rul[10][0][37]=-2.87748E-4; 
rul[10][0][38]=-1.4335E-6; rul[10][0][39]=-1.379E-6; rul[10][0][40]=6.24862E-4; rul[10][0][41]=6.34932E-4; rul[10][0][42]=6.4183E-5; rul[10][0][43]=6.52085E-5; 
rul[10][0][44]=-4.855E-7; rul[10][0][45]=-4.765E-7; rul[10][0][46]=-7.11615E-5; rul[10][0][47]=-7.0453E-5; rul[10][0][48]=-6.995E-7; rul[10][0][49]=-6.495E-7; 
rul[10][0][50]=-1.9415E-6; rul[10][0][51]=-1.6605E-6; rul[10][0][52]=-3.09E-7; rul[10][0][53]=-2.225E-7; rul[10][0][54]=-9.565E-7; rul[10][0][55]=-9.18E-7; 
rul[10][0][56]=-0.00134034; rul[10][0][57]=-0.00126477; rul[10][0][58]=0.0026591; rul[10][0][59]=0.00276661; rul[10][0][60]=-5.78845E-5; rul[10][0][61]=-5.72355E-5; 
rul[10][0][62]=-3.18939E-4; rul[10][0][63]=-2.98533E-4; rul[10][0][64]=1.73923E-4; rul[10][0][65]=1.76698E-4; rul[10][0][66]=0.0222512; rul[10][0][67]=0.0315873; 
rul[10][0][68]=6.65E-7; rul[10][0][69]=7.87E-7; rul[10][0][70]=-0.0019874; rul[10][0][71]=-0.00188441; rul[10][0][72]=5.89365E-4; rul[10][0][73]=5.95541E-4; 
rul[10][0][74]=-0.00370099; rul[10][0][75]=-0.00324788; rul[10][0][76]=1.10808E-4; rul[10][0][77]=1.13731E-4; rul[10][0][78]=-1.45544E-4; rul[10][0][79]=-1.38764E-4; 
rul[10][0][80]=-1.01699E-4; rul[10][0][81]=-1.01421E-4; rul[10][0][82]=1.80505E-4; rul[10][0][83]=1.81326E-4; rul[10][0][84]=1.6143E-5; rul[10][0][85]=1.6187E-5; 
rul[10][0][86]=2.62805E-5; rul[10][0][87]=2.66385E-5; rul[10][0][88]=1.9551E-5; rul[10][0][89]=1.9784E-5; rul[10][0][90]=-0.22128; rul[10][0][91]=-0.149391008; 
rul[10][0][92]=-0.00182804; rul[10][0][93]=-0.00175605; rul[10][0][94]=6.187E-6; rul[10][0][95]=6.2215E-6; rul[10][0][96]=-0.00642224; rul[10][0][97]=-0.00616151; 
rul[10][0][98]=-8.85864E-4; rul[10][0][99]=-8.71293E-4; rul[10][0][100]=-2.0985E-5; rul[10][0][101]=-2.0889E-5; rul[10][0][102]=-1.2275E-6; rul[10][0][103]=-1.2145E-6; 
rul[10][0][104]=4.10355E-5; rul[10][0][105]=4.2123E-5; rul[10][0][106]=0.00334123; rul[10][0][107]=0.00346682; rul[10][0][108]=4.56835E-5; rul[10][0][109]=4.5786E-5; 
rul[10][0][110]=-1.1125E-6; rul[10][0][111]=-1.0995E-6; rul[10][0][112]=-3.3155E-6; rul[10][0][113]=-3.271E-6; rul[10][0][114]=-5.046E-6; rul[10][0][115]=-5.0405E-6; 
rul[10][0][116]=-5.58875E-5; rul[10][0][117]=-5.5361E-5; rul[10][0][118]=-2.21732E-4; rul[10][0][119]=-2.16777E-4; rul[10][0][120]=1.31636E-4; rul[10][0][121]=1.32315E-4; 
rul[10][0][122]=5.45725E-4; rul[10][0][123]=5.50636E-4; rul[10][0][124]=1.4735E-6; rul[10][0][125]=1.6E-6; rul[10][0][126]=-4.92865E-5; rul[10][0][127]=-4.88775E-5; 
rul[10][0][128]=3.485E-7; rul[10][0][129]=3.715E-7; rul[10][0][130]=-8.23215E-5; rul[10][0][131]=-8.21285E-5; rul[10][0][132]=-2.3546E-4; rul[10][0][133]=-2.34164E-4; 
rul[10][0][134]=-0.00681274; rul[10][0][135]=-0.00663076; rul[10][0][136]=-1.765E-7; rul[10][0][137]=-1.08E-7; rul[10][0][138]=-3.7245E-6; rul[10][0][139]=-3.527E-6; 
rul[10][0][140]=-1.59215E-5; rul[10][0][141]=-1.58755E-5; rul[10][0][142]=4.76023E-4; rul[10][0][143]=4.78209E-4; rul[10][0][144]=-7.282E-6; rul[10][0][145]=-7.254E-6; 
rul[10][0][146]=1.97578E-4; rul[10][0][147]=2.04695E-4; rul[10][0][148]=1.206E-6; rul[10][0][149]=1.3195E-6; rul[10][0][150]=-2.56848E-4; rul[10][0][151]=-2.48482E-4; 
rul[10][0][152]=8.75045E-5; rul[10][0][153]=8.76675E-5; rul[10][0][154]=2.86206E-4; rul[10][0][155]=2.90074E-4; rul[10][0][156]=-4.752E-6; rul[10][0][157]=-4.625E-6; 
rul[10][0][158]=9.82528E-4; rul[10][0][159]=0.00102203; rul[10][0][160]=8.8485E-6; rul[10][0][161]=8.88E-6; rul[10][0][162]=2.83024E-4; rul[10][0][163]=2.84763E-4; 
rul[10][0][164]=-9.83425E-5; rul[10][0][165]=-9.8181E-5; rul[10][0][166]=-5.19195E-5; rul[10][0][167]=-5.15625E-5; rul[10][0][168]=1.027E-5; rul[10][0][169]=1.0342E-5; 
rul[10][0][170]=5.91E-7; rul[10][0][171]=5.99E-7; rul[10][0][172]=1.047E-6; rul[10][0][173]=1.1065E-6; rul[10][0][174]=-2.29343E-4; rul[10][0][175]=-2.24028E-4; 
rul[10][0][176]=1.82264E-4; rul[10][0][177]=1.83926E-4; rul[10][0][178]=2.60608E-4; rul[10][0][179]=2.67497E-4; rul[10][0][180]=6.07385E-5; rul[10][0][181]=6.2416E-5; 
rul[10][0][182]=1.3178E-5; rul[10][0][183]=1.3221E-5; rul[10][0][184]=2.0408E-5; rul[10][0][185]=2.0815E-5; rul[10][0][186]=0.00293938; rul[10][0][187]=0.00313743; 
rul[10][0][188]=9.07875E-5; rul[10][0][189]=9.20415E-5; rul[10][0][190]=0.00146787; rul[10][0][191]=0.00148412; rul[10][0][192]=7.39777E-4; rul[10][0][193]=7.96439E-4; 
rul[10][0][194]=-4.47865E-5; rul[10][0][195]=-4.4342E-5; rul[10][0][196]=-7.98055E-4; rul[10][0][197]=-7.78433E-4; rul[10][0][198]=-1.506E-6; rul[10][0][199]=-1.4995E-6; 
rul[10][0][200]=2.15866E-4; rul[10][0][201]=2.18972E-4; rul[10][0][202]=2.20865E-5; rul[10][0][203]=2.2207E-5; rul[10][0][204]=8.02861E-4; rul[10][0][205]=8.04325E-4; 
rul[10][0][206]=8.5162E-5; rul[10][0][207]=8.59555E-5; rul[10][0][208]=1.656E-6; rul[10][0][209]=1.7185E-6; rul[10][0][210]=-2.00177E-4; rul[10][0][211]=-1.97644E-4; 
rul[10][0][212]=1.57345E-4; rul[10][0][213]=1.60989E-4; rul[10][0][214]=-1.72756E-4; rul[10][0][215]=-1.72208E-4; rul[10][0][216]=3.68585E-5; rul[10][0][217]=3.7133E-5; 
rul[10][0][218]=-5.9735E-6; rul[10][0][219]=-5.947E-6; rul[10][0][220]=-1.54187E-4; rul[10][0][221]=-1.53917E-4; rul[10][0][222]=3.446E-5; rul[10][0][223]=3.5339E-5; 
rul[10][0][224]=-5.15E-7; rul[10][0][225]=-4.95E-7; rul[10][0][226]=4.3417E-5; rul[10][0][227]=4.3845E-5; rul[10][0][228]=3.7298E-5; rul[10][0][229]=3.74895E-5; 
rul[10][0][230]=-1.35932E-4; rul[10][0][231]=-1.31987E-4; rul[10][0][232]=-4.9864E-5; rul[10][0][233]=-4.9651E-5; rul[10][0][234]=-1.29822E-4; rul[10][0][235]=-1.27741E-4; 
rul[10][0][236]=5.8829E-5; rul[10][0][237]=5.92825E-5; rul[10][0][238]=-0.0194256; rul[10][0][239]=-0.0166692; rul[10][0][240]=2.34455E-5; rul[10][0][241]=2.3678E-5; 
rul[10][0][242]=-0.00433735; rul[10][0][243]=-0.00380332; rul[10][0][244]=4.51685E-5; rul[10][0][245]=4.5562E-5; rul[10][0][246]=-7.68E-7; rul[10][0][247]=-7.46E-7; 
rul[10][0][248]=8.9035E-6; rul[10][0][249]=8.915E-6; rul[10][0][250]=1.7146E-5; rul[10][0][251]=1.7229E-5; rul[10][0][252]=0.00775146; rul[10][0][253]=0.0081761; 
rul[10][0][254]=-5.2825E-6; rul[10][0][255]=-5.2025E-6; rul[10][0][256]=-7.2187E-4; rul[10][0][257]=-7.13052E-4; rul[10][0][258]=-0.0134011; rul[10][0][259]=-0.0131559; 
rul[10][0][260]=-8.76465E-5; rul[10][0][261]=-8.70335E-5; rul[10][0][262]=9.76075E-5; rul[10][0][263]=9.9162E-5; rul[10][0][264]=-8.93475E-5; rul[10][0][265]=-8.90605E-5; 
rul[10][0][266]=-1.11136E-4; rul[10][0][267]=-1.10256E-4; rul[10][0][268]=8.18E-7; rul[10][0][269]=8.495E-7; rul[10][0][270]=-5.4054E-5; rul[10][0][271]=-5.3666E-5; 
rul[10][0][272]=-6.29556E-4; rul[10][0][273]=-6.2751E-4; rul[10][0][274]=-3.78E-7; rul[10][0][275]=-3.415E-7; rul[10][0][276]=7.47865E-5; rul[10][0][277]=7.522E-5; 
rul[10][0][278]=-1.01145E-5; rul[10][0][279]=-1.00055E-5; rul[10][0][280]=2.80095E-5; rul[10][0][281]=2.80625E-5; rul[10][0][282]=-5.32012E-4; rul[10][0][283]=-5.28268E-4; 
rul[10][0][284]=5.34124E-4; rul[10][0][285]=5.41344E-4; rul[10][0][286]=-0.00216686; rul[10][0][287]=-0.0021485; rul[10][0][288]=5.7926E-4; rul[10][0][289]=5.83543E-4; 
rul[10][0][290]=-0.00167507; rul[10][0][291]=-0.00166111; rul[10][0][292]=-1.15682E-4; rul[10][0][293]=-1.13134E-4; rul[10][0][294]=0.0505836; rul[10][0][295]=0.0588463; 
rul[10][0][296]=4.46455E-4; rul[10][0][297]=4.50558E-4; rul[10][0][298]=-5.77094E-4; rul[10][0][299]=-5.41031E-4; rul[10][0][300]=0.00681236; rul[10][0][301]=0.00731456; 
rul[10][0][302]=-3.99138E-4; rul[10][0][303]=-3.96736E-4; rul[10][0][304]=-5.575E-7; rul[10][0][305]=-5.545E-7; rul[10][0][306]=7.0241E-5; rul[10][0][307]=7.14335E-5; 
rul[10][0][308]=0.082763; rul[10][0][309]=0.103867; rul[10][0][310]=3.02785E-5; rul[10][0][311]=3.03385E-5; rul[10][0][312]=1.9069E-5; rul[10][0][313]=1.9187E-5; 
rul[10][0][314]=-1.62699E-4; rul[10][0][315]=-1.61536E-4; rul[10][0][316]=3.99356E-4; rul[10][0][317]=4.08544E-4; rul[10][0][318]=-6.513E-6; rul[10][0][319]=-6.477E-6; 
rul[10][0][320]=8.6E-8; rul[10][0][321]=1.435E-7; rul[10][0][322]=-0.0154907; rul[10][0][323]=-0.0140121; rul[10][0][324]=2.7764E-4; rul[10][0][325]=2.80705E-4; 
rul[10][0][326]=0.00236784; rul[10][0][327]=0.0024911; rul[10][0][328]=8.68228E-4; rul[10][0][329]=8.89831E-4; rul[10][0][330]=0.00145395; rul[10][0][331]=0.00146294; 
rul[10][0][332]=-7.397E-6; rul[10][0][333]=-7.3555E-6; rul[10][0][334]=-1.60185E-4; rul[10][0][335]=-1.58765E-4; rul[10][0][336]=2.47458E-4; rul[10][0][337]=2.52068E-4; 
rul[10][0][338]=4.945E-7; rul[10][0][339]=5.2E-7; rul[10][0][340]=-6.00097E-4; rul[10][0][341]=-5.96777E-4; rul[10][0][342]=5.48E-7; rul[10][0][343]=5.74E-7; 
rul[10][0][344]=9.9886E-5; rul[10][0][345]=1.00113E-4; rul[10][0][346]=-5.0626E-5; rul[10][0][347]=-5.03415E-5; rul[10][0][348]=-1.1584E-5; rul[10][0][349]=-1.14725E-5; 
rul[10][0][350]=7.7407E-5; rul[10][0][351]=7.8874E-5; rul[10][0][352]=3.14825E-5; rul[10][0][353]=3.24775E-5; rul[10][0][354]=0.00227173; rul[10][0][355]=0.00232621; 
rul[10][0][356]=-2.68202E-4; rul[10][0][357]=-2.66196E-4; rul[10][0][358]=-1.193E-6; rul[10][0][359]=-1.1485E-6; rul[10][0][360]=0.0019552; rul[10][0][361]=0.0020184; 
rul[10][0][362]=2.28215E-5; rul[10][0][363]=2.32185E-5; rul[10][0][364]=-1.32195E-5; rul[10][0][365]=-1.2885E-5; rul[10][0][366]=-2.061E-6; rul[10][0][367]=-1.9585E-6; 
rul[10][0][368]=1.29868E-4; rul[10][0][369]=1.30451E-4; rul[10][0][370]=-6.40335E-5; rul[10][0][371]=-6.38145E-5; rul[10][0][372]=-1.0505E-6; rul[10][0][373]=-9.955E-7; 
rul[10][0][374]=-1.14505E-5; rul[10][0][375]=-1.1416E-5; rul[10][0][376]=-1.09478E-4; rul[10][0][377]=-1.07818E-4; rul[10][0][378]=-4.2443E-5; rul[10][0][379]=-4.1577E-5; 
rul[10][0][380]=2.2204E-4; rul[10][0][381]=2.29366E-4; rul[10][0][382]=-5.0215E-4; rul[10][0][383]=-4.97735E-4; rul[10][0][384]=-1.75027E-4; rul[10][0][385]=-1.73222E-4; 
rul[10][0][386]=-6.8309E-4; rul[10][0][387]=-6.4482E-4; rul[10][0][388]=-0.0016579; rul[10][0][389]=-0.00164796; 
dl_reg[10]=1;
dec[10]=4; 
// 11. Koniec reguly
// 12. Regula
// 1. sekcja AND 12 reguly.
rul[11][0][0]=57; rul[11][0][1]=372; 
rul[11][0][2]=-8.9815E-6; rul[11][0][3]=-8.7305E-6; rul[11][0][4]=3.39559E-4; rul[11][0][5]=3.48128E-4; rul[11][0][6]=1.03312E-4; rul[11][0][7]=1.07808E-4; 
rul[11][0][8]=4.2123E-5; rul[11][0][9]=4.3417E-5; rul[11][0][10]=-1.96565E-5; rul[11][0][11]=-1.9252E-5; rul[11][0][12]=5.754E-6; rul[11][0][13]=5.9035E-6; 
rul[11][0][14]=1.52785E-4; rul[11][0][15]=1.57345E-4; rul[11][0][16]=1.67122E-4; rul[11][0][17]=1.71067E-4; rul[11][0][18]=2.66385E-5; rul[11][0][19]=2.6933E-5; 
rul[11][0][20]=-1.54565E-5; rul[11][0][21]=-1.50075E-5; rul[11][0][22]=1.55555E-5; rul[11][0][23]=1.58495E-5; rul[11][0][24]=-4.5445E-6; rul[11][0][25]=-4.4565E-6; 
rul[11][0][26]=1.0342E-5; rul[11][0][27]=1.0484E-5; rul[11][0][28]=-3.72865E-5; rul[11][0][29]=-3.70105E-5; rul[11][0][30]=-0.00164796; rul[11][0][31]=-0.00161031; 
rul[11][0][32]=1.6544E-5; rul[11][0][33]=1.68535E-5; rul[11][0][34]=3.4545E-6; rul[11][0][35]=3.621E-6; rul[11][0][36]=-9.64439E-4; rul[11][0][37]=-9.58986E-4; 
rul[11][0][38]=-2.48575E-5; rul[11][0][39]=-2.4348E-5; rul[11][0][40]=0.00414778; rul[11][0][41]=0.00492331; rul[11][0][42]=4.95725E-5; rul[11][0][43]=5.09895E-5; 
rul[11][0][44]=4.29128E-4; rul[11][0][45]=4.32035E-4; rul[11][0][46]=-0.00118878; rul[11][0][47]=-0.00103941; rul[11][0][48]=0.0020184; rul[11][0][49]=0.00227173; 
rul[11][0][50]=2.80625E-5; rul[11][0][51]=2.8549E-5; rul[11][0][52]=9.44E-7; rul[11][0][53]=1.047E-6; rul[11][0][54]=-7.9387E-5; rul[11][0][55]=-7.72835E-5; 
rul[11][0][56]=2.8805E-6; rul[11][0][57]=3.0E-6; rul[11][0][58]=-1.5725E-4; rul[11][0][59]=-1.54187E-4; rul[11][0][60]=7.474E-6; rul[11][0][61]=7.748E-6; 
rul[11][0][62]=6.32665E-5; rul[11][0][63]=6.3959E-5; rul[11][0][64]=-1.76985E-4; rul[11][0][65]=-1.75027E-4; rul[11][0][66]=-6.58505E-5; rul[11][0][67]=-6.45525E-5; 
rul[11][0][68]=-9.39203E-4; rul[11][0][69]=-9.35376E-4; rul[11][0][70]=1.48855E-5; rul[11][0][71]=1.51175E-5; rul[11][0][72]=1.81326E-4; rul[11][0][73]=1.82264E-4; 
rul[11][0][74]=0.00139772; rul[11][0][75]=0.00142415; rul[11][0][76]=-0.00207993; rul[11][0][77]=-0.0019874; rul[11][0][78]=4.08544E-4; rul[11][0][79]=4.18246E-4; 
rul[11][0][80]=1.47385E-5; rul[11][0][81]=1.4801E-5; rul[11][0][82]=-4.4243E-5; rul[11][0][83]=-4.41165E-5; rul[11][0][84]=1.8464E-5; rul[11][0][85]=1.86635E-5; 
rul[11][0][86]=-2.225E-7; rul[11][0][87]=-1.765E-7; rul[11][0][88]=1.14652E-4; rul[11][0][89]=1.16071E-4; rul[11][0][90]=0.0152771; rul[11][0][91]=0.0154208; 
rul[11][0][92]=-5.47755E-5; rul[11][0][93]=-5.4535E-5; rul[11][0][94]=-1.0555E-5; rul[11][0][95]=-1.05175E-5; rul[11][0][96]=2.97074E-4; rul[11][0][97]=3.00391E-4; 
rul[11][0][98]=0.00329257; rul[11][0][99]=0.00334123; rul[11][0][100]=4.6975E-6; rul[11][0][101]=4.7965E-6; rul[11][0][102]=5.2405E-6; rul[11][0][103]=5.356E-6; 
rul[11][0][104]=0.00183071; rul[11][0][105]=0.0019552; rul[11][0][106]=-1.38375E-5; rul[11][0][107]=-1.375E-5; rul[11][0][108]=-9.64545E-5; rul[11][0][109]=-9.62565E-5; 
rul[11][0][110]=-2.29905E-5; rul[11][0][111]=-2.2892E-5; rul[11][0][112]=1.3195E-6; rul[11][0][113]=1.355E-6; rul[11][0][114]=6.665E-6; rul[11][0][115]=6.8705E-6; 
rul[11][0][116]=4.4695E-6; rul[11][0][117]=4.5735E-6; rul[11][0][118]=2.215E-6; rul[11][0][119]=2.2975E-6; rul[11][0][120]=-5.03415E-5; rul[11][0][121]=-5.007E-5; 
rul[11][0][122]=1.428E-6; rul[11][0][123]=1.4735E-6; rul[11][0][124]=-1.37744E-4; rul[11][0][125]=-1.37123E-4; rul[11][0][126]=-0.00188441; rul[11][0][127]=-0.00185383; 
rul[11][0][128]=0.00116889; rul[11][0][129]=0.00119445; rul[11][0][130]=-3.02595E-5; rul[11][0][131]=-2.99905E-5; rul[11][0][132]=2.78555E-5; rul[11][0][133]=2.80095E-5; 
rul[11][0][134]=3.5339E-5; rul[11][0][135]=3.6E-5; rul[11][0][136]=-6.79775E-5; rul[11][0][137]=-6.7548E-5; rul[11][0][138]=8.183E-6; rul[11][0][139]=8.2155E-6; 
rul[11][0][140]=1.24755E-5; rul[11][0][141]=1.25615E-5; rul[11][0][142]=-1.1816E-5; rul[11][0][143]=-1.1584E-5; rul[11][0][144]=-2.5145E-6; rul[11][0][145]=-2.4915E-6; 
rul[11][0][146]=1.774E-5; rul[11][0][147]=1.79375E-5; rul[11][0][148]=2.53245E-5; rul[11][0][149]=2.5514E-5; rul[11][0][150]=-3.9704E-5; rul[11][0][151]=-3.92545E-5; 
rul[11][0][152]=3.826E-6; rul[11][0][153]=3.987E-6; rul[11][0][154]=1.78552E-4; rul[11][0][155]=1.7948E-4; rul[11][0][156]=-6.38145E-5; rul[11][0][157]=-6.3266E-5; 
rul[11][0][158]=-1.51118E-4; rul[11][0][159]=-1.48644E-4; rul[11][0][160]=1.09955E-5; rul[11][0][161]=1.11975E-5; rul[11][0][162]=-2.0889E-5; rul[11][0][163]=-2.0792E-5; 
rul[11][0][164]=-1.53614E-4; rul[11][0][165]=-1.53022E-4; rul[11][0][166]=-1.31395E-4; rul[11][0][167]=-1.3073E-4; rul[11][0][168]=4.605E-7; rul[11][0][169]=4.71E-7; 
rul[11][0][170]=-5.84939E-4; rul[11][0][171]=-5.77094E-4; rul[11][0][172]=6.2215E-6; rul[11][0][173]=6.4745E-6; rul[11][0][174]=-1.81345E-5; rul[11][0][175]=-1.7134E-5; 
rul[11][0][176]=-6.2751E-4; rul[11][0][177]=-6.13282E-4; rul[11][0][178]=-0.00102212; rul[11][0][179]=-0.00102056; rul[11][0][180]=-9.18E-7; rul[11][0][181]=-8.795E-7; 
rul[11][0][182]=5.95541E-4; rul[11][0][183]=6.00329E-4; rul[11][0][184]=0.007552; rul[11][0][185]=0.00775146; rul[11][0][186]=4.5562E-5; rul[11][0][187]=4.56835E-5; 
rul[11][0][188]=1.37155E-4; rul[11][0][189]=1.38422E-4; rul[11][0][190]=0.00232621; rul[11][0][191]=0.00236784; rul[11][0][192]=-5.1123E-5; rul[11][0][193]=-5.07825E-5; 
rul[11][0][194]=-2.28225E-5; rul[11][0][195]=-2.2798E-5; rul[11][0][196]=-0.00100866; rul[11][0][197]=-9.83279E-4; rul[11][0][198]=4.3845E-5; rul[11][0][199]=4.43565E-5; 
rul[11][0][200]=-2.44013E-4; rul[11][0][201]=-2.42437E-4; rul[11][0][202]=1.00113E-4; rul[11][0][203]=1.00995E-4; rul[11][0][204]=8.364E-6; rul[11][0][205]=8.655E-6; 
rul[11][0][206]=0.0081761; rul[11][0][207]=0.00904502; rul[11][0][208]=2.84763E-4; rul[11][0][209]=2.86206E-4; rul[11][0][210]=-0.0816306; rul[11][0][211]=-0.0597263; 
rul[11][0][212]=-1.41775E-5; rul[11][0][213]=-1.4019E-5; rul[11][0][214]=7.30894E-4; rul[11][0][215]=7.39777E-4; rul[11][0][216]=-4.7343E-5; rul[11][0][217]=-4.72755E-5; 
rul[11][0][218]=-4.065E-7; rul[11][0][219]=-4.02E-7; rul[11][0][220]=-6.3725E-6; rul[11][0][221]=-6.321E-6; rul[11][0][222]=3.69573E-4; rul[11][0][223]=3.86504E-4; 
rul[11][0][224]=3.26762E-4; rul[11][0][225]=3.29327E-4; rul[11][0][226]=-5.28268E-4; rul[11][0][227]=-5.25819E-4; rul[11][0][228]=6.44843E-4; rul[11][0][229]=6.55096E-4; 
rul[11][0][230]=-2.49595E-5; rul[11][0][231]=-2.4888E-5; rul[11][0][232]=4.0905E-6; rul[11][0][233]=4.1995E-6; rul[11][0][234]=2.32185E-5; rul[11][0][235]=2.34455E-5; 
rul[11][0][236]=7.65345E-5; rul[11][0][237]=7.7407E-5; rul[11][0][238]=-1.1416E-5; rul[11][0][239]=-1.1182E-5; rul[11][0][240]=-1.4782E-5; rul[11][0][241]=-1.4567E-5; 
rul[11][0][242]=-1.27201E-4; rul[11][0][243]=-1.25844E-4; rul[11][0][244]=-1.97024E-4; rul[11][0][245]=-1.95354E-4; rul[11][0][246]=-1.38505E-4; rul[11][0][247]=-1.38122E-4; 
rul[11][0][248]=-7.254E-6; rul[11][0][249]=-7.2445E-6; rul[11][0][250]=-7.09734E-4; rul[11][0][251]=-6.8309E-4; rul[11][0][252]=-1.25595E-5; rul[11][0][253]=-1.23225E-5; 
rul[11][0][254]=7.35E-8; rul[11][0][255]=8.6E-8; rul[11][0][256]=3.715E-7; rul[11][0][257]=4.17E-7; rul[11][0][258]=-2.66196E-4; rul[11][0][259]=-2.56848E-4; 
rul[11][0][260]=1.90132E-4; rul[11][0][261]=1.97578E-4; rul[11][0][262]=9.23075E-5; rul[11][0][263]=9.5677E-5; rul[11][0][264]=1.32315E-4; rul[11][0][265]=1.34747E-4; 
rul[11][0][266]=3.90475E-5; rul[11][0][267]=3.91495E-5; rul[11][0][268]=6.2416E-5; rul[11][0][269]=6.2943E-5; rul[11][0][270]=1.7185E-6; rul[11][0][271]=1.873E-6; 
rul[11][0][272]=-2.7755E-6; rul[11][0][273]=-2.7145E-6; rul[11][0][274]=5.71187E-4; rul[11][0][275]=5.7926E-4; rul[11][0][276]=-7.855E-7; rul[11][0][277]=-7.68E-7; 
rul[11][0][278]=-3.48437E-4; rul[11][0][279]=-3.42733E-4; rul[11][0][280]=-1.63727E-4; rul[11][0][281]=-1.62699E-4; rul[11][0][282]=2.1496E-5; rul[11][0][283]=2.1647E-5; 
rul[11][0][284]=-4.66415E-5; rul[11][0][285]=-4.47865E-5; rul[11][0][286]=-5.592E-6; rul[11][0][287]=-5.4535E-6; rul[11][0][288]=1.6187E-5; rul[11][0][289]=1.6479E-5; 
rul[11][0][290]=9.627E-5; rul[11][0][291]=9.6657E-5; rul[11][0][292]=-8.344E-6; rul[11][0][293]=-8.317E-6; rul[11][0][294]=3.74895E-5; rul[11][0][295]=3.7729E-5; 
rul[11][0][296]=-6.5385E-6; rul[11][0][297]=-6.516E-6; rul[11][0][298]=-6.4172E-5; rul[11][0][299]=-6.40335E-5; rul[11][0][300]=-2.1389E-5; rul[11][0][301]=-2.1172E-5; 
rul[11][0][302]=4.50558E-4; rul[11][0][303]=4.66939E-4; rul[11][0][304]=-1.06565E-5; rul[11][0][305]=-1.06135E-5; rul[11][0][306]=-0.00616151; rul[11][0][307]=-0.00592722; 
rul[11][0][308]=2.4685E-5; rul[11][0][309]=2.4763E-5; rul[11][0][310]=-5.6556E-5; rul[11][0][311]=-5.58875E-5; rul[11][0][312]=5.5585E-6; rul[11][0][313]=5.624E-6; 
rul[11][0][314]=-8.287E-6; rul[11][0][315]=-8.2645E-6; rul[11][0][316]=-3.43925E-5; rul[11][0][317]=-3.4038E-5; rul[11][0][318]=3.79705E-5; rul[11][0][319]=3.8222E-5; 
rul[11][0][320]=-2.0257E-5; rul[11][0][321]=-1.98565E-5; rul[11][0][322]=9.72745E-5; rul[11][0][323]=9.76075E-5; rul[11][0][324]=3.66853E-4; rul[11][0][325]=3.67705E-4; 
rul[11][0][326]=1.1065E-6; rul[11][0][327]=1.1475E-6; rul[11][0][328]=-3.71699E-4; rul[11][0][329]=-3.6657E-4; rul[11][0][330]=-2.645E-6; rul[11][0][331]=-2.612E-6; 
rul[11][0][332]=8.2028E-4; rul[11][0][333]=8.39144E-4; rul[11][0][334]=-1.06279E-4; rul[11][0][335]=-1.04809E-4; rul[11][0][336]=-6.27295E-5; rul[11][0][337]=-6.22945E-5; 
rul[11][0][338]=5.135E-6; rul[11][0][339]=5.1905E-6; rul[11][0][340]=2.90345E-5; rul[11][0][341]=2.97145E-5; rul[11][0][342]=0.00592256; rul[11][0][343]=0.00612712; 
rul[11][0][344]=-3.09895E-5; rul[11][0][345]=-3.08705E-5; rul[11][0][346]=-4.124E-6; rul[11][0][347]=-3.9815E-6; rul[11][0][348]=-0.0122092; rul[11][0][349]=-0.0118416; 
rul[11][0][350]=-1.379E-6; rul[11][0][351]=-1.3395E-6; rul[11][0][352]=3.13E-7; rul[11][0][353]=3.485E-7; rul[11][0][354]=1.42507E-4; rul[11][0][355]=1.46341E-4; 
rul[11][0][356]=-1.80326E-4; rul[11][0][357]=-1.77581E-4; rul[11][0][358]=0.0024911; rul[11][0][359]=0.00250012; rul[11][0][360]=-7.226E-6; rul[11][0][361]=-7.157E-6; 
rul[11][0][362]=-3.29904E-4; rul[11][0][363]=-3.18939E-4; rul[11][0][364]=3.216E-6; rul[11][0][365]=3.2855E-6; rul[11][0][366]=-0.00184867; rul[11][0][367]=-0.00183792; 
rul[11][0][368]=-3.60475E-5; rul[11][0][369]=-3.5829E-5; rul[11][0][370]=-9.2149E-5; rul[11][0][371]=-9.05065E-5; rul[11][0][372]=-8.20025E-5; rul[11][0][373]=-8.0923E-5; 
dl_reg[11]=1;
dec[11]=3; 
// 12. Koniec reguly
// 13. Regula
// 1. sekcja AND 13 reguly.
rul[12][0][0]=57; rul[12][0][1]=68; 
rul[12][0][2]=0.103867; rul[12][0][3]=max; rul[12][0][4]=-0.0597263; rul[12][0][5]=-0.0361831; rul[12][0][6]=-0.00288091; rul[12][0][7]=-0.00272378; 
rul[12][0][8]=-1.70065E-5; rul[12][0][9]=-1.6925E-5; rul[12][0][10]=5.41344E-4; rul[12][0][11]=5.44842E-4; rul[12][0][12]=3.05049E-4; rul[12][0][13]=3.07253E-4; 
rul[12][0][14]=0.0588463; rul[12][0][15]=0.082763; rul[12][0][16]=-0.00263424; rul[12][0][17]=-0.0025019; rul[12][0][18]=1.58495E-5; rul[12][0][19]=1.60195E-5; 
rul[12][0][20]=9.16877E-4; rul[12][0][21]=9.58852E-4; rul[12][0][22]=3.29327E-4; rul[12][0][23]=3.39559E-4; rul[12][0][24]=0.0135368; rul[12][0][25]=0.0152771; 
rul[12][0][26]=0.0315873; rul[12][0][27]=0.0463761; rul[12][0][28]=4.78209E-4; rul[12][0][29]=4.83652E-4; rul[12][0][30]=-2.4915E-6; rul[12][0][31]=-2.4365E-6; 
rul[12][0][32]=1.873E-6; rul[12][0][33]=1.949E-6; rul[12][0][34]=-0.248672992; rul[12][0][35]=-0.22128; rul[12][0][36]=-4.9855E-6; rul[12][0][37]=-4.9175E-6; 
rul[12][0][38]=4.805E-7; rul[12][0][39]=4.945E-7; rul[12][0][40]=5.624E-6; rul[12][0][41]=5.6855E-6; rul[12][0][42]=0.00313743; rul[12][0][43]=0.00320871; 
rul[12][0][44]=0.00142415; rul[12][0][45]=0.00145395; rul[12][0][46]=6.3959E-5; rul[12][0][47]=6.4022E-5; rul[12][0][48]=9.9162E-5; rul[12][0][49]=9.9528E-5; 
rul[12][0][50]=-1.05175E-5; rul[12][0][51]=-1.0499E-5; rul[12][0][52]=-5.1482E-4; rul[12][0][53]=-5.0215E-4; rul[12][0][54]=-0.00103941; rul[12][0][55]=-0.00102212; 
rul[12][0][56]=-2.39825E-5; rul[12][0][57]=-2.38775E-5; rul[12][0][58]=0.00904502; rul[12][0][59]=0.0115484; rul[12][0][60]=3.85345E-5; rul[12][0][61]=3.8666E-5; 
rul[12][0][62]=-0.00150286; rul[12][0][63]=-0.00141957; rul[12][0][64]=1.60989E-4; rul[12][0][65]=1.61067E-4; rul[12][0][66]=-9.927E-6; rul[12][0][67]=-9.671E-6; 
rul[12][0][68]=3.28895E-5; rul[12][0][69]=3.318E-5; 
dl_reg[12]=1;
dec[12]=5; 
// 13. Koniec reguly
// 14. Regula
// 1. sekcja AND 14 reguly.
rul[13][0][0]=66; rul[13][0][1]=408; 
rul[13][0][2]=7.8824E-5; rul[13][0][3]=8.15465E-5; rul[13][0][4]=min; rul[13][0][5]=7.76315E-5; rul[13][0][6]=9.28505E-5; rul[13][0][7]=9.5184E-5; 
rul[13][0][8]=2.00314E-4; rul[13][0][9]=2.01365E-4; rul[13][0][10]=8.1939E-5; rul[13][0][11]=8.3511E-5; rul[13][0][12]=5.72801E-4; rul[13][0][13]=5.77838E-4; 
rul[13][0][14]=1.22601E-4; rul[13][0][15]=1.23144E-4; rul[13][0][16]=1.4712E-4; rul[13][0][17]=1.47523E-4; rul[13][0][18]=5.04946E-4; rul[13][0][19]=5.08298E-4; 
rul[13][0][20]=1.65814E-4; rul[13][0][21]=1.66376E-4; rul[13][0][22]=4.76065E-4; rul[13][0][23]=4.79466E-4; rul[13][0][24]=2.03091E-4; rul[13][0][25]=2.04017E-4; 
rul[13][0][26]=1.00133E-4; rul[13][0][27]=1.00756E-4; rul[13][0][28]=1.24182E-4; rul[13][0][29]=1.24337E-4; rul[13][0][30]=7.9721E-4; rul[13][0][31]=8.21705E-4; 
rul[13][0][32]=3.19693E-4; rul[13][0][33]=3.21329E-4; rul[13][0][34]=2.49568E-4; rul[13][0][35]=2.50962E-4; rul[13][0][36]=2.65965E-4; rul[13][0][37]=2.6665E-4; 
rul[13][0][38]=2.17161E-4; rul[13][0][39]=2.18476E-4; rul[13][0][40]=4.47667E-4; rul[13][0][41]=4.48627E-4; rul[13][0][42]=3.22644E-4; rul[13][0][43]=3.23151E-4; 
rul[13][0][44]=1.34375E-4; rul[13][0][45]=1.3455E-4; rul[13][0][46]=1.96818E-4; rul[13][0][47]=1.97522E-4; rul[13][0][48]=2.71749E-4; rul[13][0][49]=2.72801E-4; 
rul[13][0][50]=2.88169E-4; rul[13][0][51]=2.8858E-4; rul[13][0][52]=1.72517E-4; rul[13][0][53]=1.74028E-4; rul[13][0][54]=4.23113E-4; rul[13][0][55]=4.2393E-4; 
rul[13][0][56]=2.41277E-4; rul[13][0][57]=2.41497E-4; rul[13][0][58]=2.36707E-4; rul[13][0][59]=2.37149E-4; rul[13][0][60]=1.87006E-4; rul[13][0][61]=1.88147E-4; 
rul[13][0][62]=1.54958E-4; rul[13][0][63]=1.55297E-4; rul[13][0][64]=8.4671E-5; rul[13][0][65]=8.5645E-5; rul[13][0][66]=3.13981E-4; rul[13][0][67]=3.14807E-4; 
rul[13][0][68]=1.39752E-4; rul[13][0][69]=1.401E-4; rul[13][0][70]=3.45037E-4; rul[13][0][71]=3.45424E-4; rul[13][0][72]=4.73524E-4; rul[13][0][73]=4.75404E-4; 
rul[13][0][74]=4.43043E-4; rul[13][0][75]=4.4464E-4; rul[13][0][76]=5.48054E-4; rul[13][0][77]=5.51231E-4; rul[13][0][78]=2.64677E-4; rul[13][0][79]=2.65823E-4; 
rul[13][0][80]=1.51532E-4; rul[13][0][81]=1.52431E-4; rul[13][0][82]=9.0414E-5; rul[13][0][83]=9.2259E-5; rul[13][0][84]=4.1274E-4; rul[13][0][85]=4.13986E-4; 
rul[13][0][86]=4.50565E-4; rul[13][0][87]=4.53257E-4; rul[13][0][88]=2.73796E-4; rul[13][0][89]=2.75735E-4; rul[13][0][90]=5.33833E-4; rul[13][0][91]=5.35587E-4; 
rul[13][0][92]=1.88439E-4; rul[13][0][93]=1.88961E-4; rul[13][0][94]=3.5424E-4; rul[13][0][95]=3.54662E-4; rul[13][0][96]=4.18663E-4; rul[13][0][97]=4.19505E-4; 
rul[13][0][98]=4.12216E-4; rul[13][0][99]=4.12404E-4; rul[13][0][100]=3.37046E-4; rul[13][0][101]=3.37357E-4; rul[13][0][102]=9.63455E-5; rul[13][0][103]=9.6876E-5; 
rul[13][0][104]=4.57035E-4; rul[13][0][105]=4.59418E-4; rul[13][0][106]=3.76976E-4; rul[13][0][107]=3.77459E-4; rul[13][0][108]=6.08142E-4; rul[13][0][109]=6.10717E-4; 
rul[13][0][110]=1.8104E-4; rul[13][0][111]=1.81342E-4; rul[13][0][112]=3.5315E-4; rul[13][0][113]=3.53407E-4; rul[13][0][114]=3.55223E-4; rul[13][0][115]=3.55834E-4; 
rul[13][0][116]=3.29626E-4; rul[13][0][117]=3.30354E-4; rul[13][0][118]=2.08247E-4; rul[13][0][119]=2.09309E-4; rul[13][0][120]=1.40954E-4; rul[13][0][121]=1.41724E-4; 
rul[13][0][122]=1.63503E-4; rul[13][0][123]=1.64146E-4; rul[13][0][124]=1.79386E-4; rul[13][0][125]=1.79701E-4; rul[13][0][126]=1.36242E-4; rul[13][0][127]=1.36308E-4; 
rul[13][0][128]=1.21998E-4; rul[13][0][129]=1.22451E-4; rul[13][0][130]=1.29872E-4; rul[13][0][131]=1.2998E-4; rul[13][0][132]=6.15707E-4; rul[13][0][133]=6.20073E-4; 
rul[13][0][134]=3.2161E-4; rul[13][0][135]=3.22537E-4; rul[13][0][136]=1.49835E-4; rul[13][0][137]=1.50018E-4; rul[13][0][138]=1.67151E-4; rul[13][0][139]=1.6751E-4; 
rul[13][0][140]=2.97784E-4; rul[13][0][141]=2.98386E-4; rul[13][0][142]=3.78148E-4; rul[13][0][143]=3.79264E-4; rul[13][0][144]=1.31219E-4; rul[13][0][145]=1.31475E-4; 
rul[13][0][146]=3.01617E-4; rul[13][0][147]=3.01686E-4; rul[13][0][148]=8.82589E-4; rul[13][0][149]=8.85043E-4; rul[13][0][150]=1.12581E-4; rul[13][0][151]=1.13265E-4; 
rul[13][0][152]=1.97843E-4; rul[13][0][153]=1.98186E-4; rul[13][0][154]=3.91566E-4; rul[13][0][155]=3.92156E-4; rul[13][0][156]=3.53761E-4; rul[13][0][157]=3.53925E-4; 
rul[13][0][158]=2.27987E-4; rul[13][0][159]=2.28189E-4; rul[13][0][160]=3.08201E-4; rul[13][0][161]=3.09266E-4; rul[13][0][162]=1.211E-4; rul[13][0][163]=1.21317E-4; 
rul[13][0][164]=1.62972E-4; rul[13][0][165]=1.63089E-4; rul[13][0][166]=2.06703E-4; rul[13][0][167]=2.07022E-4; rul[13][0][168]=4.54858E-4; rul[13][0][169]=4.55582E-4; 
rul[13][0][170]=8.91785E-5; rul[13][0][171]=8.9515E-5; rul[13][0][172]=2.32218E-4; rul[13][0][173]=2.32376E-4; rul[13][0][174]=1.37365E-4; rul[13][0][175]=1.3737E-4; 
rul[13][0][176]=9.916E-5; rul[13][0][177]=9.9623E-5; rul[13][0][178]=4.33885E-4; rul[13][0][179]=4.35588E-4; rul[13][0][180]=4.53698E-4; rul[13][0][181]=4.54065E-4; 
rul[13][0][182]=3.8202E-4; rul[13][0][183]=3.82329E-4; rul[13][0][184]=4.03534E-4; rul[13][0][185]=4.03677E-4; rul[13][0][186]=1.64292E-4; rul[13][0][187]=1.6454E-4; 
rul[13][0][188]=1.30391E-4; rul[13][0][189]=1.30479E-4; rul[13][0][190]=1.89428E-4; rul[13][0][191]=1.89653E-4; rul[13][0][192]=3.02276E-4; rul[13][0][193]=3.03216E-4; 
rul[13][0][194]=1.53757E-4; rul[13][0][195]=1.53822E-4; rul[13][0][196]=4.14477E-4; rul[13][0][197]=4.15039E-4; rul[13][0][198]=2.1268E-4; rul[13][0][199]=2.12965E-4; 
rul[13][0][200]=1.74147E-4; rul[13][0][201]=1.74484E-4; rul[13][0][202]=4.33155E-4; rul[13][0][203]=4.3375E-4; rul[13][0][204]=1.77928E-4; rul[13][0][205]=1.78078E-4; 
rul[13][0][206]=1.17141E-4; rul[13][0][207]=1.17292E-4; rul[13][0][208]=1.01047E-4; rul[13][0][209]=1.01657E-4; rul[13][0][210]=1.30868E-4; rul[13][0][211]=1.3091E-4; 
rul[13][0][212]=2.48132E-4; rul[13][0][213]=2.48208E-4; rul[13][0][214]=1.95632E-4; rul[13][0][215]=1.95706E-4; rul[13][0][216]=3.85308E-4; rul[13][0][217]=3.85775E-4; 
rul[13][0][218]=1.90047E-4; rul[13][0][219]=1.90818E-4; rul[13][0][220]=4.66223E-4; rul[13][0][221]=4.68238E-4; rul[13][0][222]=1.38018E-4; rul[13][0][223]=1.38025E-4; 
rul[13][0][224]=3.09594E-4; rul[13][0][225]=3.09864E-4; rul[13][0][226]=2.3266E-4; rul[13][0][227]=2.32769E-4; rul[13][0][228]=2.70251E-4; rul[13][0][229]=2.70915E-4; 
rul[13][0][230]=4.81855E-4; rul[13][0][231]=4.83687E-4; rul[13][0][232]=5.10423E-4; rul[13][0][233]=5.11355E-4; rul[13][0][234]=5.0229E-4; rul[13][0][235]=5.02587E-4; 
rul[13][0][236]=2.0183E-4; rul[13][0][237]=2.02164E-4; rul[13][0][238]=2.87528E-4; rul[13][0][239]=2.88017E-4; rul[13][0][240]=4.30496E-4; rul[13][0][241]=4.31353E-4; 
rul[13][0][242]=2.76165E-4; rul[13][0][243]=2.76265E-4; rul[13][0][244]=5.55719E-4; rul[13][0][245]=5.58754E-4; rul[13][0][246]=7.15133E-4; rul[13][0][247]=7.18648E-4; 
rul[13][0][248]=1.99814E-4; rul[13][0][249]=1.99981E-4; rul[13][0][250]=5.14795E-4; rul[13][0][251]=5.17067E-4; rul[13][0][252]=4.25802E-4; rul[13][0][253]=4.26004E-4; 
rul[13][0][254]=1.55329E-4; rul[13][0][255]=1.55401E-4; rul[13][0][256]=1.95992E-4; rul[13][0][257]=1.96098E-4; rul[13][0][258]=1.82646E-4; rul[13][0][259]=1.82956E-4; 
rul[13][0][260]=2.98738E-4; rul[13][0][261]=2.99152E-4; rul[13][0][262]=1.46413E-4; rul[13][0][263]=1.46474E-4; rul[13][0][264]=1.5759E-4; rul[13][0][265]=1.57777E-4; 
rul[13][0][266]=2.93079E-4; rul[13][0][267]=2.93488E-4; rul[13][0][268]=1.91555E-4; rul[13][0][269]=1.92016E-4; rul[13][0][270]=1.95745E-4; rul[13][0][271]=1.95806E-4; 
rul[13][0][272]=1.69135E-4; rul[13][0][273]=1.69296E-4; rul[13][0][274]=3.30656E-4; rul[13][0][275]=3.30825E-4; rul[13][0][276]=2.99786E-4; rul[13][0][277]=3.00088E-4; 
rul[13][0][278]=1.02203E-4; rul[13][0][279]=1.02258E-4; rul[13][0][280]=3.70793E-4; rul[13][0][281]=3.71648E-4; rul[13][0][282]=2.37477E-4; rul[13][0][283]=2.37713E-4; 
rul[13][0][284]=8.43986E-4; rul[13][0][285]=8.53833E-4; rul[13][0][286]=1.46581E-4; rul[13][0][287]=1.46597E-4; rul[13][0][288]=3.35857E-4; rul[13][0][289]=3.36288E-4; 
rul[13][0][290]=3.11635E-4; rul[13][0][291]=3.11972E-4; rul[13][0][292]=3.18727E-4; rul[13][0][293]=3.1937E-4; rul[13][0][294]=1.33101E-4; rul[13][0][295]=1.3345E-4; 
rul[13][0][296]=2.04515E-4; rul[13][0][297]=2.04669E-4; rul[13][0][298]=1.05876E-4; rul[13][0][299]=1.06244E-4; rul[13][0][300]=1.60248E-4; rul[13][0][301]=1.60281E-4; 
rul[13][0][302]=2.58893E-4; rul[13][0][303]=2.58949E-4; rul[13][0][304]=2.19441E-4; rul[13][0][305]=2.19625E-4; rul[13][0][306]=1.04711E-4; rul[13][0][307]=1.05468E-4; 
rul[13][0][308]=2.55444E-4; rul[13][0][309]=2.55771E-4; rul[13][0][310]=3.8433E-4; rul[13][0][311]=3.84642E-4; rul[13][0][312]=9.9123E-5; rul[13][0][313]=9.91335E-5; 
rul[13][0][314]=3.97693E-4; rul[13][0][315]=4.00546E-4; rul[13][0][316]=1.69662E-4; rul[13][0][317]=1.69867E-4; rul[13][0][318]=2.35875E-4; rul[13][0][319]=2.3636E-4; 
rul[13][0][320]=1.50192E-4; rul[13][0][321]=1.50416E-4; rul[13][0][322]=7.739E-4; rul[13][0][323]=7.75066E-4; rul[13][0][324]=3.62724E-4; rul[13][0][325]=3.62924E-4; 
rul[13][0][326]=1.23546E-4; rul[13][0][327]=1.23934E-4; rul[13][0][328]=4.24354E-4; rul[13][0][329]=4.2505E-4; rul[13][0][330]=1.53098E-4; rul[13][0][331]=1.53701E-4; 
rul[13][0][332]=1.46732E-4; rul[13][0][333]=1.46931E-4; rul[13][0][334]=4.62722E-4; rul[13][0][335]=4.63077E-4; rul[13][0][336]=1.59648E-4; rul[13][0][337]=1.59755E-4; 
rul[13][0][338]=2.60986E-4; rul[13][0][339]=2.61654E-4; rul[13][0][340]=3.56245E-4; rul[13][0][341]=3.56603E-4; rul[13][0][342]=1.59099E-4; rul[13][0][343]=1.59279E-4; 
rul[13][0][344]=1.76701E-4; rul[13][0][345]=1.77261E-4; rul[13][0][346]=2.52807E-4; rul[13][0][347]=2.53392E-4; rul[13][0][348]=1.51201E-4; rul[13][0][349]=1.51291E-4; 
rul[13][0][350]=1.29598E-4; rul[13][0][351]=1.2962E-4; rul[13][0][352]=2.22047E-4; rul[13][0][353]=2.22097E-4; rul[13][0][354]=1.43735E-4; rul[13][0][355]=1.43907E-4; 
rul[13][0][356]=2.62857E-4; rul[13][0][357]=2.63465E-4; rul[13][0][358]=2.6437E-4; rul[13][0][359]=2.64511E-4; rul[13][0][360]=3.01126E-4; rul[13][0][361]=3.01426E-4; 
rul[13][0][362]=3.15873E-4; rul[13][0][363]=3.16413E-4; rul[13][0][364]=1.47861E-4; rul[13][0][365]=1.48305E-4; rul[13][0][366]=2.75904E-4; rul[13][0][367]=2.76047E-4; 
rul[13][0][368]=6.39415E-4; rul[13][0][369]=6.41357E-4; rul[13][0][370]=1.11803E-4; rul[13][0][371]=1.12313E-4; rul[13][0][372]=1.34901E-4; rul[13][0][373]=1.34954E-4; 
rul[13][0][374]=2.25165E-4; rul[13][0][375]=2.25923E-4; rul[13][0][376]=5.39666E-4; rul[13][0][377]=5.44858E-4; rul[13][0][378]=1.17913E-4; rul[13][0][379]=1.18161E-4; 
rul[13][0][380]=3.67441E-4; rul[13][0][381]=3.6799E-4; rul[13][0][382]=7.80485E-5; rul[13][0][383]=7.85775E-5; rul[13][0][384]=2.15892E-4; rul[13][0][385]=2.15975E-4; 
rul[13][0][386]=1.27337E-4; rul[13][0][387]=1.27487E-4; rul[13][0][388]=1.71657E-4; rul[13][0][389]=1.71785E-4; rul[13][0][390]=6.97604E-4; rul[13][0][391]=6.98825E-4; 
rul[13][0][392]=1.19989E-4; rul[13][0][393]=1.20173E-4; rul[13][0][394]=4.45726E-4; rul[13][0][395]=4.46661E-4; rul[13][0][396]=2.82367E-4; rul[13][0][397]=2.82834E-4; 
rul[13][0][398]=6.82045E-4; rul[13][0][399]=6.8906E-4; rul[13][0][400]=4.11576E-4; rul[13][0][401]=4.12124E-4; rul[13][0][402]=0.00133605; rul[13][0][403]=0.00136597; 
rul[13][0][404]=3.1722E-4; rul[13][0][405]=3.17364E-4; rul[13][0][406]=1.31987E-4; rul[13][0][407]=1.32293E-4; rul[13][0][408]=3.8355E-4; rul[13][0][409]=3.83991E-4; 
dl_reg[13]=1;
dec[13]=2; 
// 14. Koniec reguly
// 15. Regula
// 1. sekcja AND 15 reguly.
rul[14][0][0]=66; rul[14][0][1]=366; 
rul[14][0][2]=1.83052E-4; rul[14][0][3]=1.84835E-4; rul[14][0][4]=0.00148706; rul[14][0][5]=0.00153365; rul[14][0][6]=1.16475E-4; rul[14][0][7]=1.17141E-4; 
rul[14][0][8]=1.69867E-4; rul[14][0][9]=1.71657E-4; rul[14][0][10]=3.25579E-4; rul[14][0][11]=3.2686E-4; rul[14][0][12]=1.26524E-4; rul[14][0][13]=1.27337E-4; 
rul[14][0][14]=1.59427E-4; rul[14][0][15]=1.59648E-4; rul[14][0][16]=2.2846E-4; rul[14][0][17]=2.29141E-4; rul[14][0][18]=1.35129E-4; rul[14][0][19]=1.35614E-4; 
rul[14][0][20]=1.98186E-4; rul[14][0][21]=1.9864E-4; rul[14][0][22]=2.2941E-4; rul[14][0][23]=2.30043E-4; rul[14][0][24]=2.53392E-4; rul[14][0][25]=2.5415E-4; 
rul[14][0][26]=1.24752E-4; rul[14][0][27]=1.25389E-4; rul[14][0][28]=1.3787E-4; rul[14][0][29]=1.38005E-4; rul[14][0][30]=1.95806E-4; rul[14][0][31]=1.95992E-4; 
rul[14][0][32]=1.09244E-4; rul[14][0][33]=1.10031E-4; rul[14][0][34]=8.5645E-5; rul[14][0][35]=8.6104E-5; rul[14][0][36]=1.14303E-4; rul[14][0][37]=1.15063E-4; 
rul[14][0][38]=5.25818E-4; rul[14][0][39]=5.28162E-4; rul[14][0][40]=4.07986E-4; rul[14][0][41]=4.09555E-4; rul[14][0][42]=2.63465E-4; rul[14][0][43]=2.6437E-4; 
rul[14][0][44]=1.62086E-4; rul[14][0][45]=1.62972E-4; rul[14][0][46]=2.54312E-4; rul[14][0][47]=2.54869E-4; rul[14][0][48]=1.60681E-4; rul[14][0][49]=1.61233E-4; 
rul[14][0][50]=1.51395E-4; rul[14][0][51]=1.51532E-4; rul[14][0][52]=2.42943E-4; rul[14][0][53]=2.43336E-4; rul[14][0][54]=1.27487E-4; rul[14][0][55]=1.28306E-4; 
rul[14][0][56]=2.43584E-4; rul[14][0][57]=2.44718E-4; rul[14][0][58]=1.30479E-4; rul[14][0][59]=1.30781E-4; rul[14][0][60]=1.17413E-4; rul[14][0][61]=1.17913E-4; 
rul[14][0][62]=4.2393E-4; rul[14][0][63]=4.24216E-4; rul[14][0][64]=1.50842E-4; rul[14][0][65]=1.51201E-4; rul[14][0][66]=1.88147E-4; rul[14][0][67]=1.88426E-4; 
rul[14][0][68]=2.69431E-4; rul[14][0][69]=2.70251E-4; rul[14][0][70]=0.00340296; rul[14][0][71]=0.00412511; rul[14][0][72]=1.03518E-4; rul[14][0][73]=1.03973E-4; 
rul[14][0][74]=1.28528E-4; rul[14][0][75]=1.2865E-4; rul[14][0][76]=1.64708E-4; rul[14][0][77]=1.64786E-4; rul[14][0][78]=1.43297E-4; rul[14][0][79]=1.43735E-4; 
rul[14][0][80]=2.32853E-4; rul[14][0][81]=2.33539E-4; rul[14][0][82]=1.21633E-4; rul[14][0][83]=1.21826E-4; rul[14][0][84]=2.57962E-4; rul[14][0][85]=2.58297E-4; 
rul[14][0][86]=2.55891E-4; rul[14][0][87]=2.56134E-4; rul[14][0][88]=5.981E-4; rul[14][0][89]=5.996E-4; rul[14][0][90]=1.17292E-4; rul[14][0][91]=1.17321E-4; 
rul[14][0][92]=7.57044E-4; rul[14][0][93]=7.739E-4; rul[14][0][94]=9.05407E-4; rul[14][0][95]=9.1536E-4; rul[14][0][96]=1.21317E-4; rul[14][0][97]=1.21443E-4; 
rul[14][0][98]=2.10414E-4; rul[14][0][99]=2.10638E-4; rul[14][0][100]=5.28257E-4; rul[14][0][101]=5.29226E-4; rul[14][0][102]=1.28937E-4; rul[14][0][103]=1.29264E-4; 
rul[14][0][104]=1.42907E-4; rul[14][0][105]=1.43167E-4; rul[14][0][106]=6.29217E-4; rul[14][0][107]=6.30249E-4; rul[14][0][108]=4.42537E-4; rul[14][0][109]=4.42802E-4; 
rul[14][0][110]=2.58855E-4; rul[14][0][111]=2.58893E-4; rul[14][0][112]=2.76047E-4; rul[14][0][113]=2.76165E-4; rul[14][0][114]=1.28712E-4; rul[14][0][115]=1.28767E-4; 
rul[14][0][116]=0.00326859; rul[14][0][117]=0.00333362; rul[14][0][118]=1.6751E-4; rul[14][0][119]=1.67676E-4; rul[14][0][120]=1.3959E-4; rul[14][0][121]=1.39752E-4; 
rul[14][0][122]=1.07131E-4; rul[14][0][123]=1.07664E-4; rul[14][0][124]=1.25834E-4; rul[14][0][125]=1.25939E-4; rul[14][0][126]=1.6182E-4; rul[14][0][127]=1.61921E-4; 
rul[14][0][128]=1.55401E-4; rul[14][0][129]=1.55762E-4; rul[14][0][130]=2.58773E-4; rul[14][0][131]=2.58795E-4; rul[14][0][132]=3.87501E-4; rul[14][0][133]=3.88233E-4; 
rul[14][0][134]=1.99148E-4; rul[14][0][135]=1.99658E-4; rul[14][0][136]=2.33901E-4; rul[14][0][137]=2.34637E-4; rul[14][0][138]=2.67511E-4; rul[14][0][139]=2.68757E-4; 
rul[14][0][140]=1.46547E-4; rul[14][0][141]=1.46565E-4; rul[14][0][142]=2.57755E-4; rul[14][0][143]=2.5784E-4; rul[14][0][144]=6.12145E-4; rul[14][0][145]=6.12703E-4; 
rul[14][0][146]=1.26116E-4; rul[14][0][147]=1.26412E-4; rul[14][0][148]=1.54545E-4; rul[14][0][149]=1.54671E-4; rul[14][0][150]=1.04517E-4; rul[14][0][151]=1.04571E-4; 
rul[14][0][152]=4.19505E-4; rul[14][0][153]=4.2113E-4; rul[14][0][154]=3.32663E-4; rul[14][0][155]=3.3388E-4; rul[14][0][156]=2.78578E-4; rul[14][0][157]=2.7971E-4; 
rul[14][0][158]=1.57328E-4; rul[14][0][159]=1.57409E-4; rul[14][0][160]=5.08298E-4; rul[14][0][161]=5.09229E-4; rul[14][0][162]=1.45836E-4; rul[14][0][163]=1.46173E-4; 
rul[14][0][164]=4.83687E-4; rul[14][0][165]=4.87965E-4; rul[14][0][166]=2.93488E-4; rul[14][0][167]=2.93996E-4; rul[14][0][168]=1.12313E-4; rul[14][0][169]=1.12539E-4; 
rul[14][0][170]=5.11355E-4; rul[14][0][171]=5.12126E-4; rul[14][0][172]=1.46931E-4; rul[14][0][173]=1.4712E-4; rul[14][0][174]=1.56544E-4; rul[14][0][175]=1.56657E-4; 
rul[14][0][176]=5.84852E-4; rul[14][0][177]=5.88109E-4; rul[14][0][178]=2.56448E-4; rul[14][0][179]=2.56853E-4; rul[14][0][180]=3.91214E-4; rul[14][0][181]=3.91566E-4; 
rul[14][0][182]=8.9515E-5; rul[14][0][183]=9.0414E-5; rul[14][0][184]=1.99728E-4; rul[14][0][185]=1.99814E-4; rul[14][0][186]=4.63077E-4; rul[14][0][187]=4.63733E-4; 
rul[14][0][188]=3.9576E-4; rul[14][0][189]=3.97015E-4; rul[14][0][190]=2.46838E-4; rul[14][0][191]=2.4699E-4; rul[14][0][192]=4.16704E-4; rul[14][0][193]=4.16929E-4; 
rul[14][0][194]=2.9506E-4; rul[14][0][195]=2.95535E-4; rul[14][0][196]=5.51231E-4; rul[14][0][197]=5.52221E-4; rul[14][0][198]=2.20932E-4; rul[14][0][199]=2.21481E-4; 
rul[14][0][200]=1.3091E-4; rul[14][0][201]=1.31219E-4; rul[14][0][202]=2.23228E-4; rul[14][0][203]=2.24333E-4; rul[14][0][204]=1.48475E-4; rul[14][0][205]=1.48573E-4; 
rul[14][0][206]=3.23151E-4; rul[14][0][207]=3.23438E-4; rul[14][0][208]=1.37479E-4; rul[14][0][209]=1.37616E-4; rul[14][0][210]=1.04176E-4; rul[14][0][211]=1.04373E-4; 
rul[14][0][212]=1.7239E-4; rul[14][0][213]=1.72517E-4; rul[14][0][214]=3.29369E-4; rul[14][0][215]=3.29626E-4; rul[14][0][216]=2.86395E-4; rul[14][0][217]=2.8659E-4; 
rul[14][0][218]=3.35372E-4; rul[14][0][219]=3.35512E-4; rul[14][0][220]=3.82329E-4; rul[14][0][221]=3.82861E-4; rul[14][0][222]=1.69296E-4; rul[14][0][223]=1.69475E-4; 
rul[14][0][224]=1.38755E-4; rul[14][0][225]=1.39062E-4; rul[14][0][226]=2.15824E-4; rul[14][0][227]=2.15892E-4; rul[14][0][228]=3.53407E-4; rul[14][0][229]=3.53761E-4; 
rul[14][0][230]=2.05268E-4; rul[14][0][231]=2.05668E-4; rul[14][0][232]=1.57896E-4; rul[14][0][233]=1.58033E-4; rul[14][0][234]=2.1446E-4; rul[14][0][235]=2.15467E-4; 
rul[14][0][236]=5.67693E-4; rul[14][0][237]=5.69761E-4; rul[14][0][238]=6.23778E-4; rul[14][0][239]=6.26466E-4; rul[14][0][240]=2.72801E-4; rul[14][0][241]=2.73175E-4; 
rul[14][0][242]=3.58845E-4; rul[14][0][243]=3.60732E-4; rul[14][0][244]=2.84444E-4; rul[14][0][245]=2.84767E-4; rul[14][0][246]=2.32494E-4; rul[14][0][247]=2.3266E-4; 
rul[14][0][248]=8.27891E-4; rul[14][0][249]=8.43986E-4; rul[14][0][250]=1.93079E-4; rul[14][0][251]=1.93188E-4; rul[14][0][252]=2.6665E-4; rul[14][0][253]=2.67339E-4; 
rul[14][0][254]=2.04017E-4; rul[14][0][255]=2.04515E-4; rul[14][0][256]=6.4452E-4; rul[14][0][257]=6.47382E-4; rul[14][0][258]=1.34123E-4; rul[14][0][259]=1.3419E-4; 
rul[14][0][260]=4.48627E-4; rul[14][0][261]=4.48708E-4; rul[14][0][262]=0.00123786; rul[14][0][263]=0.00125035; rul[14][0][264]=3.50878E-4; rul[14][0][265]=3.51199E-4; 
rul[14][0][266]=3.85775E-4; rul[14][0][267]=3.86482E-4; rul[14][0][268]=0.00120203; rul[14][0][269]=0.00121551; rul[14][0][270]=5.60582E-4; rul[14][0][271]=5.60684E-4; 
rul[14][0][272]=0.00117431; rul[14][0][273]=0.00118468; rul[14][0][274]=4.13986E-4; rul[14][0][275]=4.14477E-4; rul[14][0][276]=2.89752E-4; rul[14][0][277]=2.91715E-4; 
rul[14][0][278]=3.84642E-4; rul[14][0][279]=3.85308E-4; rul[14][0][280]=1.3473E-4; rul[14][0][281]=1.34839E-4; rul[14][0][282]=1.46474E-4; rul[14][0][283]=1.46527E-4; 
rul[14][0][284]=3.81262E-4; rul[14][0][285]=3.81499E-4; rul[14][0][286]=2.0627E-4; rul[14][0][287]=2.06411E-4; rul[14][0][288]=1.44613E-4; rul[14][0][289]=1.44861E-4; 
rul[14][0][290]=2.51808E-4; rul[14][0][291]=2.52807E-4; rul[14][0][292]=1.48912E-4; rul[14][0][293]=1.49384E-4; rul[14][0][294]=1.32293E-4; rul[14][0][295]=1.33101E-4; 
rul[14][0][296]=2.59119E-4; rul[14][0][297]=2.60613E-4; rul[14][0][298]=1.92282E-4; rul[14][0][299]=1.92833E-4; rul[14][0][300]=4.17722E-4; rul[14][0][301]=4.18663E-4; 
rul[14][0][302]=2.65823E-4; rul[14][0][303]=2.65965E-4; rul[14][0][304]=1.89781E-4; rul[14][0][305]=1.90047E-4; rul[14][0][306]=9.83755E-5; rul[14][0][307]=9.8851E-5; 
rul[14][0][308]=7.46066E-4; rul[14][0][309]=7.46655E-4; rul[14][0][310]=1.38025E-4; rul[14][0][311]=1.38064E-4; rul[14][0][312]=1.0288E-4; rul[14][0][313]=1.03117E-4; 
rul[14][0][314]=5.01205E-4; rul[14][0][315]=5.0229E-4; rul[14][0][316]=2.71292E-4; rul[14][0][317]=2.71513E-4; rul[14][0][318]=0.00106414; rul[14][0][319]=0.00107751; 
rul[14][0][320]=2.02339E-4; rul[14][0][321]=2.02691E-4; rul[14][0][322]=0.00289472; rul[14][0][323]=0.00319668; rul[14][0][324]=5.02587E-4; rul[14][0][325]=5.02944E-4; 
rul[14][0][326]=3.97449E-4; rul[14][0][327]=3.9763E-4; rul[14][0][328]=1.46358E-4; rul[14][0][329]=1.46413E-4; rul[14][0][330]=1.18161E-4; rul[14][0][331]=1.18329E-4; 
rul[14][0][332]=3.01795E-4; rul[14][0][333]=3.02276E-4; rul[14][0][334]=1.34286E-4; rul[14][0][335]=1.34326E-4; rul[14][0][336]=5.61176E-4; rul[14][0][337]=5.61813E-4; 
rul[14][0][338]=1.29709E-4; rul[14][0][339]=1.2981E-4; rul[14][0][340]=2.38574E-4; rul[14][0][341]=2.39677E-4; rul[14][0][342]=2.86735E-4; rul[14][0][343]=2.86784E-4; 
rul[14][0][344]=9.5184E-5; rul[14][0][345]=9.63455E-5; rul[14][0][346]=0.00127038; rul[14][0][347]=0.00133605; rul[14][0][348]=1.966E-4; rul[14][0][349]=1.96705E-4; 
rul[14][0][350]=2.50962E-4; rul[14][0][351]=2.51308E-4; rul[14][0][352]=1.36728E-4; rul[14][0][353]=1.36827E-4; rul[14][0][354]=1.07842E-4; rul[14][0][355]=1.08354E-4; 
rul[14][0][356]=3.22537E-4; rul[14][0][357]=3.22644E-4; rul[14][0][358]=2.82834E-4; rul[14][0][359]=2.83219E-4; rul[14][0][360]=9.75051E-4; rul[14][0][361]=9.77239E-4; 
rul[14][0][362]=1.66699E-4; rul[14][0][363]=1.67151E-4; rul[14][0][364]=0.00101373; rul[14][0][365]=0.00103365; rul[14][0][366]=3.92156E-4; rul[14][0][367]=3.93169E-4; 
dl_reg[14]=1;
dec[14]=4; 
// 15. Koniec reguly
// 16. Regula
// 1. sekcja AND 16 reguly.
rul[15][0][0]=66; rul[15][0][1]=338; 
rul[15][0][2]=4.15415E-4; rul[15][0][3]=4.16704E-4; rul[15][0][4]=0.00240921; rul[15][0][5]=0.00259651; rul[15][0][6]=3.60732E-4; rul[15][0][7]=3.62017E-4; 
rul[15][0][8]=3.45538E-4; rul[15][0][9]=3.48423E-4; rul[15][0][10]=1.94317E-4; rul[15][0][11]=1.95376E-4; rul[15][0][12]=1.25389E-4; rul[15][0][13]=1.25834E-4; 
rul[15][0][14]=1.72238E-4; rul[15][0][15]=1.7239E-4; rul[15][0][16]=4.68238E-4; rul[15][0][17]=4.70336E-4; rul[15][0][18]=2.07022E-4; rul[15][0][19]=2.08247E-4; 
rul[15][0][20]=3.41712E-4; rul[15][0][21]=3.42438E-4; rul[15][0][22]=1.58483E-4; rul[15][0][23]=1.59099E-4; rul[15][0][24]=3.05332E-4; rul[15][0][25]=3.06339E-4; 
rul[15][0][26]=3.04364E-4; rul[15][0][27]=3.05183E-4; rul[15][0][28]=4.41161E-4; rul[15][0][29]=4.42081E-4; rul[15][0][30]=4.0337E-4; rul[15][0][31]=4.03534E-4; 
rul[15][0][32]=8.63133E-4; rul[15][0][33]=8.82589E-4; rul[15][0][34]=4.59929E-4; rul[15][0][35]=4.60744E-4; rul[15][0][36]=1.06244E-4; rul[15][0][37]=1.07131E-4; 
rul[15][0][38]=2.19625E-4; rul[15][0][39]=2.20932E-4; rul[15][0][40]=0.00112445; rul[15][0][41]=0.00113069; rul[15][0][42]=1.38515E-4; rul[15][0][43]=1.38755E-4; 
rul[15][0][44]=1.54464E-4; rul[15][0][45]=1.54545E-4; rul[15][0][46]=1.43907E-4; rul[15][0][47]=1.44613E-4; rul[15][0][48]=6.06154E-4; rul[15][0][49]=6.08142E-4; 
rul[15][0][50]=2.58673E-4; rul[15][0][51]=2.58773E-4; rul[15][0][52]=8.3511E-5; rul[15][0][53]=8.42065E-5; rul[15][0][54]=5.63542E-4; rul[15][0][55]=5.66179E-4; 
rul[15][0][56]=7.18648E-4; rul[15][0][57]=7.20082E-4; rul[15][0][58]=3.17364E-4; rul[15][0][59]=3.18022E-4; rul[15][0][60]=6.30249E-4; rul[15][0][61]=6.35921E-4; 
rul[15][0][62]=1.57281E-4; rul[15][0][63]=1.57328E-4; rul[15][0][64]=3.62924E-4; rul[15][0][65]=3.6374E-4; rul[15][0][66]=5.29226E-4; rul[15][0][67]=5.30183E-4; 
rul[15][0][68]=2.64511E-4; rul[15][0][69]=2.64677E-4; rul[15][0][70]=1.54671E-4; rul[15][0][71]=1.548E-4; rul[15][0][72]=5.91823E-4; rul[15][0][73]=5.981E-4; 
rul[15][0][74]=2.28189E-4; rul[15][0][75]=2.2846E-4; rul[15][0][76]=1.33674E-4; rul[15][0][77]=1.33959E-4; rul[15][0][78]=6.222E-4; rul[15][0][79]=6.23079E-4; 
rul[15][0][80]=3.28825E-4; rul[15][0][81]=3.29369E-4; rul[15][0][82]=2.48493E-4; rul[15][0][83]=2.48796E-4; rul[15][0][84]=2.18476E-4; rul[15][0][85]=2.19107E-4; 
rul[15][0][86]=2.49118E-4; rul[15][0][87]=2.49568E-4; rul[15][0][88]=3.03216E-4; rul[15][0][89]=3.03749E-4; rul[15][0][90]=1.78989E-4; rul[15][0][91]=1.79207E-4; 
rul[15][0][92]=9.8851E-5; rul[15][0][93]=9.9123E-5; rul[15][0][94]=3.57012E-4; rul[15][0][95]=3.57293E-4; rul[15][0][96]=2.38385E-4; rul[15][0][97]=2.38574E-4; 
rul[15][0][98]=0.00114414; rul[15][0][99]=0.00116132; rul[15][0][100]=5.46107E-4; rul[15][0][101]=5.48054E-4; rul[15][0][102]=2.58949E-4; rul[15][0][103]=2.59119E-4; 
rul[15][0][104]=4.64526E-4; rul[15][0][105]=4.64913E-4; rul[15][0][106]=1.08354E-4; rul[15][0][107]=1.09244E-4; rul[15][0][108]=3.31676E-4; rul[15][0][109]=3.32663E-4; 
rul[15][0][110]=2.12302E-4; rul[15][0][111]=2.1251E-4; rul[15][0][112]=1.44933E-4; rul[15][0][113]=1.45836E-4; rul[15][0][114]=2.06411E-4; rul[15][0][115]=2.06703E-4; 
rul[15][0][116]=3.64704E-4; rul[15][0][117]=3.6494E-4; rul[15][0][118]=2.05668E-4; rul[15][0][119]=2.05918E-4; rul[15][0][120]=2.42374E-4; rul[15][0][121]=2.42552E-4; 
rul[15][0][122]=4.3375E-4; rul[15][0][123]=4.33885E-4; rul[15][0][124]=9.9623E-5; rul[15][0][125]=1.00133E-4; rul[15][0][126]=2.68757E-4; rul[15][0][127]=2.69078E-4; 
rul[15][0][128]=2.7716E-4; rul[15][0][129]=2.77759E-4; rul[15][0][130]=3.00503E-4; rul[15][0][131]=3.01126E-4; rul[15][0][132]=0.00153365; rul[15][0][133]=0.00155059; 
rul[15][0][134]=1.2981E-4; rul[15][0][135]=1.29872E-4; rul[15][0][136]=1.21826E-4; rul[15][0][137]=1.21964E-4; rul[15][0][138]=1.47523E-4; rul[15][0][139]=1.47861E-4; 
rul[15][0][140]=2.32769E-4; rul[15][0][141]=2.32853E-4; rul[15][0][142]=2.15467E-4; rul[15][0][143]=2.15824E-4; rul[15][0][144]=3.36288E-4; rul[15][0][145]=3.37046E-4; 
rul[15][0][146]=5.52221E-4; rul[15][0][147]=5.55719E-4; rul[15][0][148]=1.35614E-4; rul[15][0][149]=1.35804E-4; rul[15][0][150]=1.03401E-4; rul[15][0][151]=1.03518E-4; 
rul[15][0][152]=3.88233E-4; rul[15][0][153]=3.89854E-4; rul[15][0][154]=3.79264E-4; rul[15][0][155]=3.80457E-4; rul[15][0][156]=7.13813E-4; rul[15][0][157]=7.15133E-4; 
rul[15][0][158]=1.2998E-4; rul[15][0][159]=1.30085E-4; rul[15][0][160]=1.96098E-4; rul[15][0][161]=1.966E-4; rul[15][0][162]=2.37713E-4; rul[15][0][163]=2.38188E-4; 
rul[15][0][164]=9.7439E-5; rul[15][0][165]=9.7906E-5; rul[15][0][166]=3.728E-4; rul[15][0][167]=3.7388E-4; rul[15][0][168]=4.12124E-4; rul[15][0][169]=4.12216E-4; 
rul[15][0][170]=9.6876E-5; rul[15][0][171]=9.71995E-5; rul[15][0][172]=3.77459E-4; rul[15][0][173]=3.78148E-4; rul[15][0][174]=2.71014E-4; rul[15][0][175]=2.71057E-4; 
rul[15][0][176]=0.00319668; rul[15][0][177]=0.00324634; rul[15][0][178]=3.30825E-4; rul[15][0][179]=3.31054E-4; rul[15][0][180]=3.25236E-4; rul[15][0][181]=3.25579E-4; 
rul[15][0][182]=1.12539E-4; rul[15][0][183]=1.12581E-4; rul[15][0][184]=1.99981E-4; rul[15][0][185]=2.00314E-4; rul[15][0][186]=1.57777E-4; rul[15][0][187]=1.57824E-4; 
rul[15][0][188]=1.3407E-4; rul[15][0][189]=1.34123E-4; rul[15][0][190]=1.18757E-4; rul[15][0][191]=1.18855E-4; rul[15][0][192]=1.36533E-4; rul[15][0][193]=1.36728E-4; 
rul[15][0][194]=2.10859E-4; rul[15][0][195]=2.1191E-4; rul[15][0][196]=1.92833E-4; rul[15][0][197]=1.93079E-4; rul[15][0][198]=2.19316E-4; rul[15][0][199]=2.19441E-4; 
rul[15][0][200]=4.05777E-4; rul[15][0][201]=4.07986E-4; rul[15][0][202]=1.9674E-4; rul[15][0][203]=1.96818E-4; rul[15][0][204]=3.09864E-4; rul[15][0][205]=3.10252E-4; 
rul[15][0][206]=3.71648E-4; rul[15][0][207]=3.7214E-4; rul[15][0][208]=1.82956E-4; rul[15][0][209]=1.83052E-4; rul[15][0][210]=2.34637E-4; rul[15][0][211]=2.35032E-4; 
rul[15][0][212]=2.13477E-4; rul[15][0][213]=2.1446E-4; rul[15][0][214]=1.89179E-4; rul[15][0][215]=1.89428E-4; rul[15][0][216]=2.22097E-4; rul[15][0][217]=2.22432E-4; 
rul[15][0][218]=1.05468E-4; rul[15][0][219]=1.05876E-4; rul[15][0][220]=1.72005E-4; rul[15][0][221]=1.72137E-4; rul[15][0][222]=1.04373E-4; rul[15][0][223]=1.04517E-4; 
rul[15][0][224]=1.13265E-4; rul[15][0][225]=1.13522E-4; rul[15][0][226]=1.3737E-4; rul[15][0][227]=1.37479E-4; rul[15][0][228]=1.401E-4; rul[15][0][229]=1.40345E-4; 
rul[15][0][230]=1.60333E-4; rul[15][0][231]=1.60409E-4; rul[15][0][232]=1.65596E-4; rul[15][0][233]=1.65672E-4; rul[15][0][234]=1.23934E-4; rul[15][0][235]=1.24182E-4; 
rul[15][0][236]=3.9048E-4; rul[15][0][237]=3.91214E-4; rul[15][0][238]=3.86962E-4; rul[15][0][239]=3.87501E-4; rul[15][0][240]=1.01657E-4; rul[15][0][241]=1.02203E-4; 
rul[15][0][242]=2.76309E-4; rul[15][0][243]=2.76339E-4; rul[15][0][244]=1.61233E-4; rul[15][0][245]=1.6182E-4; rul[15][0][246]=3.52016E-4; rul[15][0][247]=3.52279E-4; 
rul[15][0][248]=1.13923E-4; rul[15][0][249]=1.14181E-4; rul[15][0][250]=3.97015E-4; rul[15][0][251]=3.97399E-4; rul[15][0][252]=1.53822E-4; rul[15][0][253]=1.54093E-4; 
rul[15][0][254]=3.13042E-4; rul[15][0][255]=3.13582E-4; rul[15][0][256]=2.67339E-4; rul[15][0][257]=2.67511E-4; rul[15][0][258]=3.1491E-4; rul[15][0][259]=3.15507E-4; 
rul[15][0][260]=1.38005E-4; rul[15][0][261]=1.38018E-4; rul[15][0][262]=1.48746E-4; rul[15][0][263]=1.48912E-4; rul[15][0][264]=2.46209E-4; rul[15][0][265]=2.46315E-4; 
rul[15][0][266]=3.35512E-4; rul[15][0][267]=3.35673E-4; rul[15][0][268]=3.65224E-4; rul[15][0][269]=3.65444E-4; rul[15][0][270]=1.43167E-4; rul[15][0][271]=1.43297E-4; 
rul[15][0][272]=1.2962E-4; rul[15][0][273]=1.29709E-4; rul[15][0][274]=1.10031E-4; rul[15][0][275]=1.10794E-4; rul[15][0][276]=1.78309E-4; rul[15][0][277]=1.78582E-4; 
rul[15][0][278]=2.96266E-4; rul[15][0][279]=2.96637E-4; rul[15][0][280]=2.5415E-4; rul[15][0][281]=2.54312E-4; rul[15][0][282]=1.31475E-4; rul[15][0][283]=1.31987E-4; 
rul[15][0][284]=1.77261E-4; rul[15][0][285]=1.77807E-4; rul[15][0][286]=1.18329E-4; rul[15][0][287]=1.18566E-4; rul[15][0][288]=1.04571E-4; rul[15][0][289]=1.04711E-4; 
rul[15][0][290]=2.88017E-4; rul[15][0][291]=2.88169E-4; rul[15][0][292]=2.19161E-4; rul[15][0][293]=2.19217E-4; rul[15][0][294]=1.90818E-4; rul[15][0][295]=1.91555E-4; 
rul[15][0][296]=3.23438E-4; rul[15][0][297]=3.23845E-4; rul[15][0][298]=1.26412E-4; rul[15][0][299]=1.26524E-4; rul[15][0][300]=1.46173E-4; rul[15][0][301]=1.46358E-4; 
rul[15][0][302]=2.45693E-4; rul[15][0][303]=2.46064E-4; rul[15][0][304]=9.2259E-5; rul[15][0][305]=9.28505E-5; rul[15][0][306]=2.16213E-4; rul[15][0][307]=2.17161E-4; 
rul[15][0][308]=1.80483E-4; rul[15][0][309]=1.80764E-4; rul[15][0][310]=4.48708E-4; rul[15][0][311]=4.50565E-4; rul[15][0][312]=4.26073E-4; rul[15][0][313]=4.26915E-4; 
rul[15][0][314]=4.56695E-4; rul[15][0][315]=4.57035E-4; rul[15][0][316]=7.76315E-5; rul[15][0][317]=7.80485E-5; rul[15][0][318]=1.60281E-4; rul[15][0][319]=1.60307E-4; 
rul[15][0][320]=2.4699E-4; rul[15][0][321]=2.47256E-4; rul[15][0][322]=6.61398E-4; rul[15][0][323]=6.67849E-4; rul[15][0][324]=2.8858E-4; rul[15][0][325]=2.88929E-4; 
rul[15][0][326]=2.51308E-4; rul[15][0][327]=2.51808E-4; rul[15][0][328]=2.21582E-4; rul[15][0][329]=2.2169E-4; rul[15][0][330]=3.10586E-4; rul[15][0][331]=3.1092E-4; 
rul[15][0][332]=5.13896E-4; rul[15][0][333]=5.14795E-4; rul[15][0][334]=4.35588E-4; rul[15][0][335]=4.36017E-4; rul[15][0][336]=5.88109E-4; rul[15][0][337]=5.9057E-4; 
rul[15][0][338]=2.49048E-4; rul[15][0][339]=2.49096E-4; 
dl_reg[15]=1;
dec[15]=3; 
// 16. Koniec reguly
// 17. Regula
// 1. sekcja AND 17 reguly.
rul[16][0][0]=66; rul[16][0][1]=70; 
rul[16][0][2]=0.0046224; rul[16][0][3]=0.00625699; rul[16][0][4]=7.05299E-4; rul[16][0][5]=7.12009E-4; rul[16][0][6]=0.00103365; rul[16][0][7]=0.00105561; 
rul[16][0][8]=0.00166182; rul[16][0][9]=0.00170465; rul[16][0][10]=3.9763E-4; rul[16][0][11]=3.97693E-4; rul[16][0][12]=3.97399E-4; rul[16][0][13]=3.97449E-4; 
rul[16][0][14]=3.35673E-4; rul[16][0][15]=3.35857E-4; rul[16][0][16]=4.64177E-4; rul[16][0][17]=4.64526E-4; rul[16][0][18]=7.44503E-4; rul[16][0][19]=7.46066E-4; 
rul[16][0][20]=3.2821E-4; rul[16][0][21]=3.28425E-4; rul[16][0][22]=0.00195653; rul[16][0][23]=0.00204333; rul[16][0][24]=0.00413532; rul[16][0][25]=0.00419232; 
rul[16][0][26]=0.00118468; rul[16][0][27]=0.00119352; rul[16][0][28]=6.02379E-4; rul[16][0][29]=6.04286E-4; rul[16][0][30]=3.51651E-4; rul[16][0][31]=3.52016E-4; 
rul[16][0][32]=2.40672E-4; rul[16][0][33]=2.41277E-4; rul[16][0][34]=9.70568E-4; rul[16][0][35]=9.75051E-4; rul[16][0][36]=2.81982E-4; rul[16][0][37]=2.82367E-4; 
rul[16][0][38]=3.1092E-4; rul[16][0][39]=3.11187E-4; rul[16][0][40]=4.75404E-4; rul[16][0][41]=4.76065E-4; rul[16][0][42]=2.43336E-4; rul[16][0][43]=2.43584E-4; 
rul[16][0][44]=2.69078E-4; rul[16][0][45]=2.69276E-4; rul[16][0][46]=0.00427856; rul[16][0][47]=0.00435642; rul[16][0][48]=0.00333362; rul[16][0][49]=0.00340296; 
rul[16][0][50]=4.79466E-4; rul[16][0][51]=4.81855E-4; rul[16][0][52]=0.00155059; rul[16][0][53]=0.00156429; rul[16][0][54]=2.04669E-4; rul[16][0][55]=2.04776E-4; 
rul[16][0][56]=3.43002E-4; rul[16][0][57]=3.43994E-4; rul[16][0][58]=2.71513E-4; rul[16][0][59]=2.71589E-4; rul[16][0][60]=9.1536E-4; rul[16][0][61]=9.19049E-4; 
rul[16][0][62]=3.37508E-4; rul[16][0][63]=3.37774E-4; rul[16][0][64]=0.00259651; rul[16][0][65]=0.00289472; rul[16][0][66]=0.00223845; rul[16][0][67]=0.00240921; 
rul[16][0][68]=2.7971E-4; rul[16][0][69]=2.80108E-4; rul[16][0][70]=2.54869E-4; rul[16][0][71]=2.55141E-4; 
dl_reg[16]=1;
dec[16]=5; 
// 17. Koniec reguly
// 18. Regula
// 1. sekcja AND 18 reguly.
rul[17][0][0]=66; rul[17][0][1]=60; 
rul[17][0][2]=3.7388E-4; rul[17][0][3]=3.74792E-4; rul[17][0][4]=4.42081E-4; rul[17][0][5]=4.42537E-4; rul[17][0][6]=2.76265E-4; rul[17][0][7]=2.76309E-4; 
rul[17][0][8]=9.35921E-4; rul[17][0][9]=9.56442E-4; rul[17][0][10]=3.82861E-4; rul[17][0][11]=3.8355E-4; rul[17][0][12]=2.02164E-4; rul[17][0][13]=2.02339E-4; 
rul[17][0][14]=0.00105561; rul[17][0][15]=0.00106414; rul[17][0][16]=6.05362E-4; rul[17][0][17]=6.05406E-4; rul[17][0][18]=4.42802E-4; rul[17][0][19]=4.43043E-4; 
rul[17][0][20]=6.69868E-4; rul[17][0][21]=6.82045E-4; rul[17][0][22]=6.23079E-4; rul[17][0][23]=6.23778E-4; rul[17][0][24]=2.86956E-4; rul[17][0][25]=2.87528E-4; 
rul[17][0][26]=2.62132E-4; rul[17][0][27]=2.62857E-4; rul[17][0][28]=2.31134E-4; rul[17][0][29]=2.31238E-4; rul[17][0][30]=4.09555E-4; rul[17][0][31]=4.10481E-4; 
rul[17][0][32]=1.76144E-4; rul[17][0][33]=1.76701E-4; rul[17][0][34]=0.00125035; rul[17][0][35]=0.00125384; rul[17][0][36]=3.35107E-4; rul[17][0][37]=3.35372E-4; 
rul[17][0][38]=1.54845E-4; rul[17][0][39]=1.54885E-4; rul[17][0][40]=0.00116132; rul[17][0][41]=0.00117431; rul[17][0][42]=1.79207E-4; rul[17][0][43]=1.79298E-4; 
rul[17][0][44]=0.00189572; rul[17][0][45]=0.00195653; rul[17][0][46]=3.37774E-4; rul[17][0][47]=3.38381E-4; rul[17][0][48]=2.47733E-4; rul[17][0][49]=2.48132E-4; 
rul[17][0][50]=1.88961E-4; rul[17][0][51]=1.89179E-4; rul[17][0][52]=3.66458E-4; rul[17][0][53]=3.67066E-4; rul[17][0][54]=5.80872E-4; rul[17][0][55]=5.84852E-4; 
rul[17][0][56]=2.76537E-4; rul[17][0][57]=2.76774E-4; rul[17][0][58]=9.77239E-4; rul[17][0][59]=9.83197E-4; rul[17][0][60]=5.25213E-4; rul[17][0][61]=5.25724E-4; 
dl_reg[17]=1;
dec[17]=1; 
// 18. Koniec reguly
// 19. Regula
// 1. sekcja AND 19 reguly.
rul[18][0][0]=54; rul[18][0][1]=414; 
rul[18][0][2]=3.80055E-4; rul[18][0][3]=3.88674E-4; rul[18][0][4]=3.92906E-4; rul[18][0][5]=4.03881E-4; rul[18][0][6]=3.00527E-4; rul[18][0][7]=3.11628E-4; 
rul[18][0][8]=2.38317E-4; rul[18][0][9]=2.41985E-4; rul[18][0][10]=2.42627E-4; rul[18][0][11]=2.43917E-4; rul[18][0][12]=9.64335E-5; rul[18][0][13]=9.6946E-5; 
rul[18][0][14]=2.34816E-4; rul[18][0][15]=2.38038E-4; rul[18][0][16]=1.99305E-4; rul[18][0][17]=2.01565E-4; rul[18][0][18]=4.5443E-4; rul[18][0][19]=4.61196E-4; 
rul[18][0][20]=3.74952E-4; rul[18][0][21]=3.7817E-4; rul[18][0][22]=1.50682E-4; rul[18][0][23]=1.51799E-4; rul[18][0][24]=1.8765E-4; rul[18][0][25]=1.88757E-4; 
rul[18][0][26]=6.84202E-4; rul[18][0][27]=6.99851E-4; rul[18][0][28]=5.38487E-4; rul[18][0][29]=5.53588E-4; rul[18][0][30]=4.17075E-5; rul[18][0][31]=4.197E-5; 
rul[18][0][32]=1.46578E-4; rul[18][0][33]=1.4833E-4; rul[18][0][34]=8.0116E-5; rul[18][0][35]=8.01865E-5; rul[18][0][36]=5.27335E-5; rul[18][0][37]=5.297E-5; 
rul[18][0][38]=7.78075E-5; rul[18][0][39]=7.7842E-5; rul[18][0][40]=1.19198E-4; rul[18][0][41]=1.19704E-4; rul[18][0][42]=5.2429E-5; rul[18][0][43]=5.26295E-5; 
rul[18][0][44]=2.86039E-4; rul[18][0][45]=2.89107E-4; rul[18][0][46]=8.4431E-5; rul[18][0][47]=8.47715E-5; rul[18][0][48]=3.46275E-4; rul[18][0][49]=3.4793E-4; 
rul[18][0][50]=1.8964E-4; rul[18][0][51]=1.90442E-4; rul[18][0][52]=9.14725E-5; rul[18][0][53]=9.1944E-5; rul[18][0][54]=1.68246E-4; rul[18][0][55]=1.68609E-4; 
rul[18][0][56]=1.63812E-4; rul[18][0][57]=1.65801E-4; rul[18][0][58]=1.09917E-4; rul[18][0][59]=1.10523E-4; rul[18][0][60]=7.84205E-5; rul[18][0][61]=7.8955E-5; 
rul[18][0][62]=2.02842E-4; rul[18][0][63]=2.0704E-4; rul[18][0][64]=2.9356E-4; rul[18][0][65]=2.9611E-4; rul[18][0][66]=2.64469E-4; rul[18][0][67]=2.70336E-4; 
rul[18][0][68]=5.1193E-5; rul[18][0][69]=5.1288E-5; rul[18][0][70]=2.60039E-4; rul[18][0][71]=2.6057E-4; rul[18][0][72]=4.1331E-4; rul[18][0][73]=4.17729E-4; 
rul[18][0][74]=1.94199E-4; rul[18][0][75]=1.94809E-4; rul[18][0][76]=4.64407E-4; rul[18][0][77]=4.84584E-4; rul[18][0][78]=1.04052E-4; rul[18][0][79]=1.04208E-4; 
rul[18][0][80]=2.79494E-4; rul[18][0][81]=2.82204E-4; rul[18][0][82]=5.574E-5; rul[18][0][83]=5.5882E-5; rul[18][0][84]=3.58158E-4; rul[18][0][85]=3.63058E-4; 
rul[18][0][86]=1.51892E-4; rul[18][0][87]=1.52162E-4; rul[18][0][88]=8.2794E-5; rul[18][0][89]=8.32775E-5; rul[18][0][90]=5.6617E-5; rul[18][0][91]=5.6777E-5; 
rul[18][0][92]=3.6905E-4; rul[18][0][93]=3.72187E-4; rul[18][0][94]=1.52816E-4; rul[18][0][95]=1.54854E-4; rul[18][0][96]=1.61213E-4; rul[18][0][97]=1.627E-4; 
rul[18][0][98]=7.5065E-5; rul[18][0][99]=7.5537E-5; rul[18][0][100]=5.96225E-5; rul[18][0][101]=5.979E-5; rul[18][0][102]=3.22835E-5; rul[18][0][103]=3.2379E-5; 
rul[18][0][104]=5.9445E-5; rul[18][0][105]=5.95275E-5; rul[18][0][106]=5.70485E-5; rul[18][0][107]=5.7172E-5; rul[18][0][108]=6.1655E-5; rul[18][0][109]=6.1756E-5; 
rul[18][0][110]=2.77625E-5; rul[18][0][111]=2.77845E-5; rul[18][0][112]=9.3971E-5; rul[18][0][113]=9.41035E-5; rul[18][0][114]=2.75415E-4; rul[18][0][115]=2.76279E-4; 
rul[18][0][116]=1.27104E-4; rul[18][0][117]=1.27145E-4; rul[18][0][118]=4.07454E-4; rul[18][0][119]=4.08295E-4; rul[18][0][120]=1.93435E-5; rul[18][0][121]=1.94465E-5; 
rul[18][0][122]=3.42674E-4; rul[18][0][123]=3.44329E-4; rul[18][0][124]=7.64525E-5; rul[18][0][125]=7.66015E-5; rul[18][0][126]=3.6238E-5; rul[18][0][127]=3.6355E-5; 
rul[18][0][128]=7.3958E-5; rul[18][0][129]=7.42805E-5; rul[18][0][130]=2.6947E-5; rul[18][0][131]=2.7133E-5; rul[18][0][132]=1.69292E-4; rul[18][0][133]=1.69502E-4; 
rul[18][0][134]=6.5276E-5; rul[18][0][135]=6.5296E-5; rul[18][0][136]=1.92068E-4; rul[18][0][137]=1.935E-4; rul[18][0][138]=6.51175E-5; rul[18][0][139]=6.5207E-5; 
rul[18][0][140]=1.07617E-4; rul[18][0][141]=1.07749E-4; rul[18][0][142]=3.0909E-5; rul[18][0][143]=3.0926E-5; rul[18][0][144]=4.81465E-5; rul[18][0][145]=4.8152E-5; 
rul[18][0][146]=1.67756E-4; rul[18][0][147]=1.68072E-4; rul[18][0][148]=3.33106E-4; rul[18][0][149]=3.3729E-4; rul[18][0][150]=1.48649E-4; rul[18][0][151]=1.48843E-4; 
rul[18][0][152]=2.59296E-4; rul[18][0][153]=2.59669E-4; rul[18][0][154]=6.9196E-5; rul[18][0][155]=6.926E-5; rul[18][0][156]=1.01781E-4; rul[18][0][157]=1.01974E-4; 
rul[18][0][158]=1.03255E-4; rul[18][0][159]=1.03444E-4; rul[18][0][160]=4.8508E-5; rul[18][0][161]=4.8589E-5; rul[18][0][162]=1.36114E-4; rul[18][0][163]=1.364E-4; 
rul[18][0][164]=2.4542E-5; rul[18][0][165]=2.46155E-5; rul[18][0][166]=2.51655E-4; rul[18][0][167]=2.53032E-4; rul[18][0][168]=2.90229E-4; rul[18][0][169]=2.91488E-4; 
rul[18][0][170]=4.23396E-4; rul[18][0][171]=4.30245E-4; rul[18][0][172]=1.44245E-4; rul[18][0][173]=1.44332E-4; rul[18][0][174]=4.60945E-5; rul[18][0][175]=4.6174E-5; 
rul[18][0][176]=5.9143E-5; rul[18][0][177]=5.92545E-5; rul[18][0][178]=1.06622E-4; rul[18][0][179]=1.07457E-4; rul[18][0][180]=1.24767E-4; rul[18][0][181]=1.25109E-4; 
rul[18][0][182]=4.86569E-4; rul[18][0][183]=4.88385E-4; rul[18][0][184]=3.52055E-5; rul[18][0][185]=3.52865E-5; rul[18][0][186]=2.32116E-4; rul[18][0][187]=2.3324E-4; 
rul[18][0][188]=5.88185E-5; rul[18][0][189]=5.9042E-5; rul[18][0][190]=9.24245E-5; rul[18][0][191]=9.30305E-5; rul[18][0][192]=2.0176E-5; rul[18][0][193]=2.01865E-5; 
rul[18][0][194]=4.2294E-5; rul[18][0][195]=4.23675E-5; rul[18][0][196]=6.403E-5; rul[18][0][197]=6.4071E-5; rul[18][0][198]=6.7874E-5; rul[18][0][199]=6.81985E-5; 
rul[18][0][200]=2.7577E-5; rul[18][0][201]=2.7735E-5; rul[18][0][202]=9.0335E-5; rul[18][0][203]=9.03855E-5; rul[18][0][204]=7.46915E-5; rul[18][0][205]=7.49125E-5; 
rul[18][0][206]=1.81862E-4; rul[18][0][207]=1.82576E-4; rul[18][0][208]=2.01995E-5; rul[18][0][209]=2.043E-5; rul[18][0][210]=1.17579E-4; rul[18][0][211]=1.17682E-4; 
rul[18][0][212]=9.2222E-5; rul[18][0][213]=9.23495E-5; rul[18][0][214]=1.37554E-4; rul[18][0][215]=1.37925E-4; rul[18][0][216]=9.91065E-5; rul[18][0][217]=9.94015E-5; 
rul[18][0][218]=3.8379E-5; rul[18][0][219]=3.8397E-5; rul[18][0][220]=4.4434E-5; rul[18][0][221]=4.44815E-5; rul[18][0][222]=4.8621E-5; rul[18][0][223]=4.8668E-5; 
rul[18][0][224]=3.55905E-5; rul[18][0][225]=3.5786E-5; rul[18][0][226]=3.26815E-5; rul[18][0][227]=3.28355E-5; rul[18][0][228]=3.22455E-4; rul[18][0][229]=3.24667E-4; 
rul[18][0][230]=1.30059E-4; rul[18][0][231]=1.30474E-4; rul[18][0][232]=1.00229E-4; rul[18][0][233]=1.00552E-4; rul[18][0][234]=2.15213E-4; rul[18][0][235]=2.15583E-4; 
rul[18][0][236]=9.58275E-5; rul[18][0][237]=9.6187E-5; rul[18][0][238]=3.822E-5; rul[18][0][239]=3.8301E-5; rul[18][0][240]=8.0568E-5; rul[18][0][241]=8.0852E-5; 
rul[18][0][242]=1.08338E-4; rul[18][0][243]=1.08438E-4; rul[18][0][244]=3.3565E-5; rul[18][0][245]=3.3679E-5; rul[18][0][246]=1.43336E-4; rul[18][0][247]=1.43847E-4; 
rul[18][0][248]=6.29924E-4; rul[18][0][249]=6.33763E-4; rul[18][0][250]=3.9894E-5; rul[18][0][251]=3.99945E-5; rul[18][0][252]=1.32633E-4; rul[18][0][253]=1.32975E-4; 
rul[18][0][254]=5.46215E-5; rul[18][0][255]=5.46715E-5; rul[18][0][256]=1.66702E-4; rul[18][0][257]=1.67263E-4; rul[18][0][258]=2.01961E-4; rul[18][0][259]=2.02093E-4; 
rul[18][0][260]=7.82295E-5; rul[18][0][261]=7.8327E-5; rul[18][0][262]=3.15356E-4; rul[18][0][263]=3.16598E-4; rul[18][0][264]=9.0548E-5; rul[18][0][265]=9.0714E-5; 
rul[18][0][266]=4.95465E-5; rul[18][0][267]=4.95585E-5; rul[18][0][268]=3.90765E-5; rul[18][0][269]=3.92195E-5; rul[18][0][270]=1.1682E-4; rul[18][0][271]=1.1704E-4; 
rul[18][0][272]=9.8146E-5; rul[18][0][273]=9.8239E-5; rul[18][0][274]=1.38556E-4; rul[18][0][275]=1.38996E-4; rul[18][0][276]=4.96045E-5; rul[18][0][277]=4.97815E-5; 
rul[18][0][278]=9.3275E-5; rul[18][0][279]=9.35635E-5; rul[18][0][280]=8.4234E-5; rul[18][0][281]=8.4391E-5; rul[18][0][282]=3.0282E-5; rul[18][0][283]=3.04465E-5; 
rul[18][0][284]=1.08902E-4; rul[18][0][285]=1.09207E-4; rul[18][0][286]=4.3712E-4; rul[18][0][287]=4.38091E-4; rul[18][0][288]=1.79186E-4; rul[18][0][289]=1.79794E-4; 
rul[18][0][290]=3.89706E-4; rul[18][0][291]=3.90753E-4; rul[18][0][292]=9.9562E-5; rul[18][0][293]=9.9717E-5; rul[18][0][294]=2.447E-5; rul[18][0][295]=2.4493E-5; 
rul[18][0][296]=5.62655E-5; rul[18][0][297]=5.63345E-5; rul[18][0][298]=1.18992E-4; rul[18][0][299]=1.19096E-4; rul[18][0][300]=2.89386E-4; rul[18][0][301]=2.89491E-4; 
rul[18][0][302]=4.03725E-5; rul[18][0][303]=4.0509E-5; rul[18][0][304]=7.35825E-5; rul[18][0][305]=7.36965E-5; rul[18][0][306]=2.76713E-4; rul[18][0][307]=2.78427E-4; 
rul[18][0][308]=7.79225E-5; rul[18][0][309]=7.802E-5; rul[18][0][310]=3.09565E-5; rul[18][0][311]=3.10395E-5; rul[18][0][312]=1.96982E-4; rul[18][0][313]=1.98143E-4; 
rul[18][0][314]=5.01512E-4; rul[18][0][315]=5.04607E-4; rul[18][0][316]=1.20071E-4; rul[18][0][317]=1.2047E-4; rul[18][0][318]=5.30975E-5; rul[18][0][319]=5.31215E-5; 
rul[18][0][320]=5.32485E-5; rul[18][0][321]=5.3388E-5; rul[18][0][322]=7.26945E-5; rul[18][0][323]=7.3021E-5; rul[18][0][324]=1.42283E-4; rul[18][0][325]=1.42319E-4; 
rul[18][0][326]=8.0247E-5; rul[18][0][327]=8.0286E-5; rul[18][0][328]=8.61E-5; rul[18][0][329]=8.6225E-5; rul[18][0][330]=4.0158E-5; rul[18][0][331]=4.0259E-5; 
rul[18][0][332]=8.52305E-5; rul[18][0][333]=8.5616E-5; rul[18][0][334]=5.734E-5; rul[18][0][335]=5.73485E-5; rul[18][0][336]=2.7361E-5; rul[18][0][337]=2.7402E-5; 
rul[18][0][338]=9.4216E-5; rul[18][0][339]=9.44745E-5; rul[18][0][340]=7.0936E-5; rul[18][0][341]=7.1279E-5; rul[18][0][342]=6.55125E-5; rul[18][0][343]=6.5733E-5; 
rul[18][0][344]=7.9346E-5; rul[18][0][345]=7.96815E-5; rul[18][0][346]=9.3097E-5; rul[18][0][347]=9.32125E-5; rul[18][0][348]=1.02124E-4; rul[18][0][349]=1.02395E-4; 
rul[18][0][350]=2.07311E-4; rul[18][0][351]=2.0807E-4; rul[18][0][352]=1.74829E-4; rul[18][0][353]=1.7531E-4; rul[18][0][354]=4.3833E-5; rul[18][0][355]=4.39015E-5; 
rul[18][0][356]=1.02626E-4; rul[18][0][357]=1.02679E-4; rul[18][0][358]=1.40483E-4; rul[18][0][359]=1.40706E-4; rul[18][0][360]=5.17181E-4; rul[18][0][361]=5.17727E-4; 
rul[18][0][362]=3.7857E-5; rul[18][0][363]=3.7925E-5; rul[18][0][364]=6.28625E-5; rul[18][0][365]=6.29575E-5; rul[18][0][366]=6.935E-5; rul[18][0][367]=6.93925E-5; 
rul[18][0][368]=1.83243E-4; rul[18][0][369]=1.84884E-4; rul[18][0][370]=3.7969E-5; rul[18][0][371]=3.8169E-5; rul[18][0][372]=7.2043E-5; rul[18][0][373]=7.2196E-5; 
rul[18][0][374]=4.8294E-5; rul[18][0][375]=4.83835E-5; rul[18][0][376]=1.12828E-4; rul[18][0][377]=1.13353E-4; rul[18][0][378]=1.26264E-4; rul[18][0][379]=1.2693E-4; 
rul[18][0][380]=3.5139E-5; rul[18][0][381]=3.5175E-5; rul[18][0][382]=5.1013E-5; rul[18][0][383]=5.114E-5; rul[18][0][384]=2.73156E-4; rul[18][0][385]=2.74947E-4; 
rul[18][0][386]=8.1844E-5; rul[18][0][387]=8.18915E-5; rul[18][0][388]=4.39173E-4; rul[18][0][389]=4.50714E-4; rul[18][0][390]=6.27425E-5; rul[18][0][391]=6.281E-5; 
rul[18][0][392]=2.5416E-4; rul[18][0][393]=2.56143E-4; rul[18][0][394]=7.73965E-5; rul[18][0][395]=7.75685E-5; rul[18][0][396]=1.39308E-4; rul[18][0][397]=1.39919E-4; 
rul[18][0][398]=1.66011E-4; rul[18][0][399]=1.66339E-4; rul[18][0][400]=6.07046E-4; rul[18][0][401]=6.11386E-4; rul[18][0][402]=5.98718E-4; rul[18][0][403]=6.02601E-4; 
rul[18][0][404]=3.26037E-4; rul[18][0][405]=3.30267E-4; rul[18][0][406]=1.73869E-4; rul[18][0][407]=1.74263E-4; rul[18][0][408]=1.05627E-4; rul[18][0][409]=1.0579E-4; 
rul[18][0][410]=1.0368E-4; rul[18][0][411]=1.03925E-4; rul[18][0][412]=3.06125E-5; rul[18][0][413]=3.06855E-5; rul[18][0][414]=3.43635E-5; rul[18][0][415]=3.44545E-5; 
dl_reg[18]=1;
dec[18]=2; 
// 19. Koniec reguly
// 20. Regula
// 1. sekcja AND 20 reguly.
rul[19][0][0]=54; rul[19][0][1]=340; 
rul[19][0][2]=1.0329E-5; rul[19][0][3]=1.25145E-5; rul[19][0][4]=5.1845E-6; rul[19][0][5]=7.4295E-6; rul[19][0][6]=2.54405E-5; rul[19][0][7]=2.60505E-5; 
rul[19][0][8]=6.038E-5; rul[19][0][9]=6.08245E-5; rul[19][0][10]=3.3746E-5; rul[19][0][11]=3.4128E-5; rul[19][0][12]=1.77275E-5; rul[19][0][13]=1.83395E-5; 
rul[19][0][14]=3.14095E-5; rul[19][0][15]=3.176E-5; rul[19][0][16]=6.23525E-5; rul[19][0][17]=6.26835E-5; rul[19][0][18]=2.25345E-5; rul[19][0][19]=2.29475E-5; 
rul[19][0][20]=4.97815E-5; rul[19][0][21]=5.03145E-5; rul[19][0][22]=2.7247E-5; rul[19][0][23]=2.7361E-5; rul[19][0][24]=9.5945E-6; rul[19][0][25]=1.01235E-5; 
rul[19][0][26]=1.01544E-4; rul[19][0][27]=1.01781E-4; rul[19][0][28]=6.53185E-5; rul[19][0][29]=6.5472E-5; rul[19][0][30]=3.3032E-5; rul[19][0][31]=3.3325E-5; 
rul[19][0][32]=2.08305E-5; rul[19][0][33]=2.1718E-5; rul[19][0][34]=6.0973E-5; rul[19][0][35]=6.12405E-5; rul[19][0][36]=1.3418E-5; rul[19][0][37]=1.38945E-5; 
rul[19][0][38]=5.38255E-5; rul[19][0][39]=5.4299E-5; rul[19][0][40]=3.66005E-5; rul[19][0][41]=3.6765E-5; rul[19][0][42]=6.4071E-5; rul[19][0][43]=6.5047E-5; 
rul[19][0][44]=1.20977E-4; rul[19][0][45]=1.21106E-4; rul[19][0][46]=3.2992E-5; rul[19][0][47]=3.3025E-5; rul[19][0][48]=6.33035E-5; rul[19][0][49]=6.3628E-5; 
rul[19][0][50]=5.4839E-5; rul[19][0][51]=5.5141E-5; rul[19][0][52]=3.7217E-5; rul[19][0][53]=3.75905E-5; rul[19][0][54]=3.10395E-5; rul[19][0][55]=3.1343E-5; 
rul[19][0][56]=3.2061E-5; rul[19][0][57]=3.2224E-5; rul[19][0][58]=1.95155E-5; rul[19][0][59]=1.9882E-5; rul[19][0][60]=7.172E-5; rul[19][0][61]=7.2043E-5; 
rul[19][0][62]=2.77845E-5; rul[19][0][63]=2.8246E-5; rul[19][0][64]=3.11628E-4; rul[19][0][65]=3.15356E-4; rul[19][0][66]=1.0579E-4; rul[19][0][67]=1.05981E-4; 
rul[19][0][68]=1.10658E-4; rul[19][0][69]=1.10826E-4; rul[19][0][70]=2.46155E-5; rul[19][0][71]=2.51845E-5; rul[19][0][72]=5.22345E-5; rul[19][0][73]=5.2339E-5; 
rul[19][0][74]=1.49935E-5; rul[19][0][75]=1.58235E-5; rul[19][0][76]=3.69555E-5; rul[19][0][77]=3.71545E-5; rul[19][0][78]=5.8478E-5; rul[19][0][79]=5.85585E-5; 
rul[19][0][80]=1.4247E-5; rul[19][0][81]=1.48945E-5; rul[19][0][82]=1.31145E-5; rul[19][0][83]=1.32875E-5; rul[19][0][84]=1.25109E-4; rul[19][0][85]=1.26264E-4; 
rul[19][0][86]=2.66065E-5; rul[19][0][87]=2.6947E-5; rul[19][0][88]=3.28355E-5; rul[19][0][89]=3.28855E-5; rul[19][0][90]=8.1941E-5; rul[19][0][91]=8.20925E-5; 
rul[19][0][92]=1.29311E-4; rul[19][0][93]=1.30059E-4; rul[19][0][94]=1.39919E-4; rul[19][0][95]=1.40483E-4; rul[19][0][96]=8.38025E-5; rul[19][0][97]=8.3982E-5; 
rul[19][0][98]=5.2383E-5; rul[19][0][99]=5.2429E-5; rul[19][0][100]=1.98143E-4; rul[19][0][101]=1.99305E-4; rul[19][0][102]=1.49165E-4; rul[19][0][103]=1.49449E-4; 
rul[19][0][104]=5.26295E-5; rul[19][0][105]=5.27335E-5; rul[19][0][106]=1.03444E-4; rul[19][0][107]=1.0368E-4; rul[19][0][108]=1.24171E-4; rul[19][0][109]=1.24767E-4; 
rul[19][0][110]=3.2379E-5; rul[19][0][111]=3.24785E-5; rul[19][0][112]=2.83855E-5; rul[19][0][113]=2.85015E-5; rul[19][0][114]=9.03855E-5; rul[19][0][115]=9.0548E-5; 
rul[19][0][116]=6.70634E-4; rul[19][0][117]=6.84202E-4; rul[19][0][118]=1.08058E-4; rul[19][0][119]=1.08121E-4; rul[19][0][120]=4.88185E-5; rul[19][0][121]=4.89995E-5; 
rul[19][0][122]=9.0714E-5; rul[19][0][123]=9.07725E-5; rul[19][0][124]=6.0355E-5; rul[19][0][125]=6.0367E-5; rul[19][0][126]=5.81875E-5; rul[19][0][127]=5.8262E-5; 
rul[19][0][128]=1.8597E-5; rul[19][0][129]=1.86285E-5; rul[19][0][130]=6.9172E-5; rul[19][0][131]=6.9196E-5; rul[19][0][132]=8.50415E-5; rul[19][0][133]=8.52305E-5; 
rul[19][0][134]=1.13652E-4; rul[19][0][135]=1.13926E-4; rul[19][0][136]=8.2425E-6; rul[19][0][137]=8.4195E-6; rul[19][0][138]=8.87505E-5; rul[19][0][139]=8.8786E-5; 
rul[19][0][140]=3.06855E-5; rul[19][0][141]=3.0909E-5; rul[19][0][142]=4.03E-6; rul[19][0][143]=4.1805E-6; rul[19][0][144]=6.1756E-5; rul[19][0][145]=6.20115E-5; 
rul[19][0][146]=4.49005E-5; rul[19][0][147]=4.49945E-5; rul[19][0][148]=4.0104E-5; rul[19][0][149]=4.0158E-5; rul[19][0][150]=4.5128E-5; rul[19][0][151]=4.54735E-5; 
rul[19][0][152]=1.7275E-5; rul[19][0][153]=1.75225E-5; rul[19][0][154]=2.4174E-5; rul[19][0][155]=2.4309E-5; rul[19][0][156]=3.84695E-5; rul[19][0][157]=3.84985E-5; 
rul[19][0][158]=2.2028E-5; rul[19][0][159]=2.2339E-5; rul[19][0][160]=4.9593E-5; rul[19][0][161]=4.96045E-5; rul[19][0][162]=5.6003E-5; rul[19][0][163]=5.609E-5; 
rul[19][0][164]=5.63345E-5; rul[19][0][165]=5.64375E-5; rul[19][0][166]=9.3915E-6; rul[19][0][167]=9.5105E-6; rul[19][0][168]=6.8385E-5; rul[19][0][169]=6.8578E-5; 
rul[19][0][170]=6.155E-5; rul[19][0][171]=6.1655E-5; rul[19][0][172]=1.02679E-4; rul[19][0][173]=1.0283E-4; rul[19][0][174]=4.4335E-5; rul[19][0][175]=4.4434E-5; 
rul[19][0][176]=2.38038E-4; rul[19][0][177]=2.38317E-4; rul[19][0][178]=3.89005E-5; rul[19][0][179]=3.90765E-5; rul[19][0][180]=4.9421E-5; rul[19][0][181]=4.9484E-5; 
rul[19][0][182]=5.3388E-5; rul[19][0][183]=5.37775E-5; rul[19][0][184]=3.99945E-5; rul[19][0][185]=4.0059E-5; rul[19][0][186]=9.32125E-5; rul[19][0][187]=9.3275E-5; 
rul[19][0][188]=5.45045E-5; rul[19][0][189]=5.45735E-5; rul[19][0][190]=4.11415E-5; rul[19][0][191]=4.13585E-5; rul[19][0][192]=4.4119E-5; rul[19][0][193]=4.42025E-5; 
rul[19][0][194]=8.66415E-5; rul[19][0][195]=8.7256E-5; rul[19][0][196]=2.82204E-4; rul[19][0][197]=2.844E-4; rul[19][0][198]=1.1704E-4; rul[19][0][199]=1.17172E-4; 
rul[19][0][200]=9.41035E-5; rul[19][0][201]=9.4165E-5; rul[19][0][202]=1.73046E-4; rul[19][0][203]=1.73869E-4; rul[19][0][204]=8.3531E-5; rul[19][0][205]=8.3716E-5; 
rul[19][0][206]=5.6186E-5; rul[19][0][207]=5.62655E-5; rul[19][0][208]=4.32925E-5; rul[19][0][209]=4.35615E-5; rul[19][0][210]=3.9534E-5; rul[19][0][211]=3.96825E-5; 
rul[19][0][212]=3.33935E-5; rul[19][0][213]=3.3565E-5; rul[19][0][214]=2.4493E-5; rul[19][0][215]=2.4542E-5; rul[19][0][216]=1.87395E-5; rul[19][0][217]=1.8966E-5; 
rul[19][0][218]=4.88385E-4; rul[19][0][219]=4.94936E-4; rul[19][0][220]=4.8134E-5; rul[19][0][221]=4.81465E-5; rul[19][0][222]=1.09664E-4; rul[19][0][223]=1.09917E-4; 
rul[19][0][224]=3.6862E-5; rul[19][0][225]=3.6928E-5; rul[19][0][226]=1.03061E-4; rul[19][0][227]=1.03255E-4; rul[19][0][228]=8.7185E-6; rul[19][0][229]=9.337E-6; 
rul[19][0][230]=9.12775E-5; rul[19][0][231]=9.13685E-5; rul[19][0][232]=3.18265E-5; rul[19][0][233]=3.1931E-5; rul[19][0][234]=1.06142E-4; rul[19][0][235]=1.06289E-4; 
rul[19][0][236]=1.27036E-4; rul[19][0][237]=1.27104E-4; rul[19][0][238]=7.7425E-6; rul[19][0][239]=8.136E-6; rul[19][0][240]=5.17515E-5; rul[19][0][241]=5.1921E-5; 
rul[19][0][242]=8.5616E-5; rul[19][0][243]=8.61E-5; rul[19][0][244]=5.1628E-5; rul[19][0][245]=5.1694E-5; rul[19][0][246]=2.43905E-5; rul[19][0][247]=2.447E-5; 
rul[19][0][248]=6.5733E-5; rul[19][0][249]=6.5954E-5; rul[19][0][250]=4.23675E-5; rul[19][0][251]=4.2579E-5; rul[19][0][252]=4.44815E-5; rul[19][0][253]=4.4724E-5; 
rul[19][0][254]=3.52865E-5; rul[19][0][255]=3.539E-5; rul[19][0][256]=2.7133E-5; rul[19][0][257]=2.71635E-5; rul[19][0][258]=2.96725E-5; rul[19][0][259]=2.98635E-5; 
rul[19][0][260]=4.5847E-5; rul[19][0][261]=4.59695E-5; rul[19][0][262]=1.42458E-4; rul[19][0][263]=1.42672E-4; rul[19][0][264]=2.41985E-4; rul[19][0][265]=2.42483E-4; 
rul[19][0][266]=8.4391E-5; rul[19][0][267]=8.4431E-5; rul[19][0][268]=6.99851E-4; rul[19][0][269]=7.19261E-4; rul[19][0][270]=7.3257E-5; rul[19][0][271]=7.32735E-5; 
rul[19][0][272]=9.44745E-5; rul[19][0][273]=9.4586E-5; rul[19][0][274]=1.20674E-4; rul[19][0][275]=1.20816E-4; rul[19][0][276]=5.7959E-5; rul[19][0][277]=5.81725E-5; 
rul[19][0][278]=4.0509E-5; rul[19][0][279]=4.064E-5; rul[19][0][280]=7.7842E-5; rul[19][0][281]=7.79225E-5; rul[19][0][282]=6.87615E-5; rul[19][0][283]=6.8812E-5; 
rul[19][0][284]=6.281E-5; rul[19][0][285]=6.28625E-5; rul[19][0][286]=3.5175E-5; rul[19][0][287]=3.52055E-5; rul[19][0][288]=5.95615E-5; rul[19][0][289]=5.96225E-5; 
rul[19][0][290]=1.3117E-4; rul[19][0][291]=1.31998E-4; rul[19][0][292]=3.0926E-5; rul[19][0][293]=3.09565E-5; rul[19][0][294]=2.7402E-5; rul[19][0][295]=2.7463E-5; 
rul[19][0][296]=5.297E-5; rul[19][0][297]=5.30975E-5; rul[19][0][298]=3.4687E-5; rul[19][0][299]=3.47075E-5; rul[19][0][300]=8.23785E-5; rul[19][0][301]=8.2794E-5; 
rul[19][0][302]=1.627E-4; rul[19][0][303]=1.63224E-4; rul[19][0][304]=2.2365E-6; rul[19][0][305]=2.5695E-6; rul[19][0][306]=1.74263E-4; rul[19][0][307]=1.7434E-4; 
rul[19][0][308]=2.1767E-5; rul[19][0][309]=2.1799E-5; rul[19][0][310]=9.23495E-5; rul[19][0][311]=9.23795E-5; rul[19][0][312]=4.10531E-4; rul[19][0][313]=4.1331E-4; 
rul[19][0][314]=6.30445E-5; rul[19][0][315]=6.3129E-5; rul[19][0][316]=4.8668E-5; rul[19][0][317]=4.87235E-5; rul[19][0][318]=3.00135E-5; rul[19][0][319]=3.0282E-5; 
rul[19][0][320]=5.73605E-5; rul[19][0][321]=5.7412E-5; rul[19][0][322]=7.33785E-5; rul[19][0][323]=7.35825E-5; rul[19][0][324]=4.197E-5; rul[19][0][325]=4.22155E-5; 
rul[19][0][326]=6.9631E-5; rul[19][0][327]=7.0045E-5; rul[19][0][328]=9.02515E-5; rul[19][0][329]=9.0335E-5; rul[19][0][330]=8.1237E-5; rul[19][0][331]=8.1408E-5; 
rul[19][0][332]=3.796E-5; rul[19][0][333]=3.79665E-5; rul[19][0][334]=4.39015E-5; rul[19][0][335]=4.39325E-5; rul[19][0][336]=9.6187E-5; rul[19][0][337]=9.64335E-5; 
rul[19][0][338]=4.57395E-5; rul[19][0][339]=4.5783E-5; rul[19][0][340]=1.59725E-5; rul[19][0][341]=1.6155E-5; 
dl_reg[19]=1;
dec[19]=4; 
// 20. Koniec reguly
// 21. Regula
// 1. sekcja AND 21 reguly.
rul[20][0][0]=54; rul[20][0][1]=352; 
rul[20][0][2]=0.00115414; rul[20][0][3]=0.00364649; rul[20][0][4]=2.60505E-5; rul[20][0][5]=2.66065E-5; rul[20][0][6]=6.8812E-5; rul[20][0][7]=6.9172E-5; 
rul[20][0][8]=1.41061E-4; rul[20][0][9]=1.41706E-4; rul[20][0][10]=1.7531E-4; rul[20][0][11]=1.77207E-4; rul[20][0][12]=5.30253E-4; rul[20][0][13]=5.38487E-4; 
rul[20][0][14]=7.60865E-5; rul[20][0][15]=7.64525E-5; rul[20][0][16]=2.12755E-4; rul[20][0][17]=2.1385E-4; rul[20][0][18]=6.08245E-5; rul[20][0][19]=6.0973E-5; 
rul[20][0][20]=6.2239E-5; rul[20][0][21]=6.23525E-5; rul[20][0][22]=5.7412E-5; rul[20][0][23]=5.78915E-5; rul[20][0][24]=5.7233E-5; rul[20][0][25]=5.734E-5; 
rul[20][0][26]=1.69502E-4; rul[20][0][27]=1.72215E-4; rul[20][0][28]=1.07749E-4; rul[20][0][29]=1.08E-4; rul[20][0][30]=6.7479E-5; rul[20][0][31]=6.7874E-5; 
rul[20][0][32]=9.8239E-5; rul[20][0][33]=9.91065E-5; rul[20][0][34]=7.3021E-5; rul[20][0][35]=7.3162E-5; rul[20][0][36]=4.75145E-5; rul[20][0][37]=4.8098E-5; 
rul[20][0][38]=7.0045E-5; rul[20][0][39]=7.06985E-5; rul[20][0][40]=1.21106E-4; rul[20][0][41]=1.21316E-4; rul[20][0][42]=1.18268E-4; rul[20][0][43]=1.18992E-4; 
rul[20][0][44]=8.6225E-5; rul[20][0][45]=8.66415E-5; rul[20][0][46]=4.0939E-5; rul[20][0][47]=4.11415E-5; rul[20][0][48]=7.96815E-5; rul[20][0][49]=8.0116E-5; 
rul[20][0][50]=2.56143E-4; rul[20][0][51]=2.59296E-4; rul[20][0][52]=1.16347E-4; rul[20][0][53]=1.1682E-4; rul[20][0][54]=4.35615E-5; rul[20][0][55]=4.3833E-5; 
rul[20][0][56]=5.55345E-5; rul[20][0][57]=5.574E-5; rul[20][0][58]=7.36965E-5; rul[20][0][59]=7.3753E-5; rul[20][0][60]=9.07725E-5; rul[20][0][61]=9.1127E-5; 
rul[20][0][62]=1.44583E-4; rul[20][0][63]=1.45088E-4; rul[20][0][64]=2.7463E-5; rul[20][0][65]=2.7577E-5; rul[20][0][66]=5.85585E-5; rul[20][0][67]=5.86415E-5; 
rul[20][0][68]=7.4295E-6; rul[20][0][69]=7.6525E-6; rul[20][0][70]=2.2339E-5; rul[20][0][71]=2.25345E-5; rul[20][0][72]=4.69335E-5; rul[20][0][73]=4.7446E-5; 
rul[20][0][74]=8.7256E-5; rul[20][0][75]=8.77705E-5; rul[20][0][76]=1.63224E-4; rul[20][0][77]=1.63812E-4; rul[20][0][78]=2.42483E-4; rul[20][0][79]=2.42627E-4; 
rul[20][0][80]=1.86285E-5; rul[20][0][81]=1.86725E-5; rul[20][0][82]=4.61196E-4; rul[20][0][83]=4.62674E-4; rul[20][0][84]=1.37925E-4; rul[20][0][85]=1.3804E-4; 
rul[20][0][86]=5.45735E-5; rul[20][0][87]=5.46E-5; rul[20][0][88]=6.66345E-5; rul[20][0][89]=6.66915E-5; rul[20][0][90]=3.6928E-5; rul[20][0][91]=3.69555E-5; 
rul[20][0][92]=3.28855E-5; rul[20][0][93]=3.2992E-5; rul[20][0][94]=1.68609E-4; rul[20][0][95]=1.68814E-4; rul[20][0][96]=4.9533E-5; rul[20][0][97]=4.95465E-5; 
rul[20][0][98]=1.13353E-4; rul[20][0][99]=1.13652E-4; rul[20][0][100]=8.32775E-5; rul[20][0][101]=8.3531E-5; rul[20][0][102]=9.00335E-5; rul[20][0][103]=9.02515E-5; 
rul[20][0][104]=3.79665E-5; rul[20][0][105]=3.7969E-5; rul[20][0][106]=7.8955E-5; rul[20][0][107]=7.9346E-5; rul[20][0][108]=2.0771E-5; rul[20][0][109]=2.08305E-5; 
rul[20][0][110]=1.45446E-4; rul[20][0][111]=1.45925E-4; rul[20][0][112]=4.31385E-5; rul[20][0][113]=4.32925E-5; rul[20][0][114]=1.20858E-4; rul[20][0][115]=1.20977E-4; 
rul[20][0][116]=2.9111E-5; rul[20][0][117]=2.9339E-5; rul[20][0][118]=3.5522E-4; rul[20][0][119]=3.58158E-4; rul[20][0][120]=1.14579E-4; rul[20][0][121]=1.14834E-4; 
rul[20][0][122]=1.90442E-4; rul[20][0][123]=1.92068E-4; rul[20][0][124]=1.59119E-4; rul[20][0][125]=1.59846E-4; rul[20][0][126]=3.20375E-5; rul[20][0][127]=3.2061E-5; 
rul[20][0][128]=3.24667E-4; rul[20][0][129]=3.26037E-4; rul[20][0][130]=1.04208E-4; rul[20][0][131]=1.04254E-4; rul[20][0][132]=5.31475E-5; rul[20][0][133]=5.32485E-5; 
rul[20][0][134]=5.979E-5; rul[20][0][135]=6.0138E-5; rul[20][0][136]=1.01428E-4; rul[20][0][137]=1.01544E-4; rul[20][0][138]=7.463E-5; rul[20][0][139]=7.46915E-5; 
rul[20][0][140]=2.18675E-5; rul[20][0][141]=2.2028E-5; rul[20][0][142]=6.26835E-5; rul[20][0][143]=6.27425E-5; rul[20][0][144]=2.28985E-4; rul[20][0][145]=2.30508E-4; 
rul[20][0][146]=1.78376E-4; rul[20][0][147]=1.79186E-4; rul[20][0][148]=7.66015E-5; rul[20][0][149]=7.6688E-5; rul[20][0][150]=7.6739E-5; rul[20][0][151]=7.68045E-5; 
rul[20][0][152]=3.3025E-5; rul[20][0][153]=3.3032E-5; rul[20][0][154]=4.6038E-5; rul[20][0][155]=4.605E-5; rul[20][0][156]=6.29575E-5; rul[20][0][157]=6.30445E-5; 
rul[20][0][158]=3.30267E-4; rul[20][0][159]=3.33106E-4; rul[20][0][160]=1.68072E-4; rul[20][0][161]=1.68246E-4; rul[20][0][162]=3.88555E-5; rul[20][0][163]=3.89005E-5; 
rul[20][0][164]=1.86756E-4; rul[20][0][165]=1.8765E-4; rul[20][0][166]=4.6311E-5; rul[20][0][167]=4.63375E-5; rul[20][0][168]=3.79278E-4; rul[20][0][169]=3.80055E-4; 
rul[20][0][170]=4.49945E-5; rul[20][0][171]=4.5128E-5; rul[20][0][172]=1.19704E-4; rul[20][0][173]=1.20071E-4; rul[20][0][174]=5.95275E-5; rul[20][0][175]=5.95615E-5; 
rul[20][0][176]=1.85676E-4; rul[20][0][177]=1.86157E-4; rul[20][0][178]=3.44545E-5; rul[20][0][179]=3.45755E-5; rul[20][0][180]=1.10523E-4; rul[20][0][181]=1.10658E-4; 
rul[20][0][182]=1.35837E-4; rul[20][0][183]=1.36114E-4; rul[20][0][184]=2.79124E-4; rul[20][0][185]=2.79494E-4; rul[20][0][186]=1.10826E-4; rul[20][0][187]=1.1095E-4; 
rul[20][0][188]=1.88757E-4; rul[20][0][189]=1.8964E-4; rul[20][0][190]=5.64982E-4; rul[20][0][191]=5.72361E-4; rul[20][0][192]=4.09135E-5; rul[20][0][193]=4.09255E-5; 
rul[20][0][194]=1.09535E-4; rul[20][0][195]=1.09664E-4; rul[20][0][196]=9.35635E-5; rul[20][0][197]=9.3872E-5; rul[20][0][198]=6.8578E-5; rul[20][0][199]=6.87615E-5; 
rul[20][0][200]=3.20443E-4; rul[20][0][201]=3.22455E-4; rul[20][0][202]=1.2047E-4; rul[20][0][203]=1.20674E-4; rul[20][0][204]=4.22155E-5; rul[20][0][205]=4.2294E-5; 
rul[20][0][206]=1.36959E-4; rul[20][0][207]=1.37554E-4; rul[20][0][208]=1.584E-4; rul[20][0][209]=1.58803E-4; rul[20][0][210]=1.95634E-4; rul[20][0][211]=1.96982E-4; 
rul[20][0][212]=1.0283E-4; rul[20][0][213]=1.03061E-4; rul[20][0][214]=4.15425E-5; rul[20][0][215]=4.16215E-5; rul[20][0][216]=4.65805E-5; rul[20][0][217]=4.6797E-5; 
rul[20][0][218]=5.1921E-5; rul[20][0][219]=5.1954E-5; rul[20][0][220]=3.92195E-5; rul[20][0][221]=3.93115E-5; rul[20][0][222]=5.1288E-5; rul[20][0][223]=5.1559E-5; 
rul[20][0][224]=5.04607E-4; rul[20][0][225]=5.1307E-4; rul[20][0][226]=1.84884E-4; rul[20][0][227]=1.85357E-4; rul[20][0][228]=1.00713E-4; rul[20][0][229]=1.00769E-4; 
rul[20][0][230]=9.4165E-5; rul[20][0][231]=9.4216E-5; rul[20][0][232]=6.5047E-5; rul[20][0][233]=6.51175E-5; rul[20][0][234]=6.5296E-5; rul[20][0][235]=6.53185E-5; 
rul[20][0][236]=3.71545E-5; rul[20][0][237]=3.7217E-5; rul[20][0][238]=6.955E-5; rul[20][0][239]=6.9631E-5; rul[20][0][240]=6.61625E-5; rul[20][0][241]=6.6461E-5; 
rul[20][0][242]=5.1994E-5; rul[20][0][243]=5.22345E-5; rul[20][0][244]=5.37775E-5; rul[20][0][245]=5.38255E-5; rul[20][0][246]=8.3716E-5; rul[20][0][247]=8.38025E-5; 
rul[20][0][248]=0.00109672; rul[20][0][249]=0.00111489; rul[20][0][250]=1.27145E-4; rul[20][0][251]=1.2726E-4; rul[20][0][252]=2.40895E-5; rul[20][0][253]=2.41345E-5; 
rul[20][0][254]=4.5783E-5; rul[20][0][255]=4.5847E-5; rul[20][0][256]=3.65153E-4; rul[20][0][257]=3.6905E-4; rul[20][0][258]=2.14752E-4; rul[20][0][259]=2.15213E-4; 
rul[20][0][260]=1.807E-4; rul[20][0][261]=1.81862E-4; rul[20][0][262]=1.08121E-4; rul[20][0][263]=1.08338E-4; rul[20][0][264]=2.7735E-5; rul[20][0][265]=2.77625E-5; 
rul[20][0][266]=8.18915E-5; rul[20][0][267]=8.1941E-5; rul[20][0][268]=5.9042E-5; rul[20][0][269]=5.9143E-5; rul[20][0][270]=2.27224E-4; rul[20][0][271]=2.28444E-4; 
rul[20][0][272]=4.40045E-5; rul[20][0][273]=4.4119E-5; rul[20][0][274]=1.54854E-4; rul[20][0][275]=1.56471E-4; rul[20][0][276]=8.0852E-5; rul[20][0][277]=8.09715E-5; 
rul[20][0][278]=2.76279E-4; rul[20][0][279]=2.76713E-4; rul[20][0][280]=1.27928E-4; rul[20][0][281]=1.28428E-4; rul[20][0][282]=3.6069E-5; rul[20][0][283]=3.6238E-5; 
rul[20][0][284]=7.38515E-5; rul[20][0][285]=7.3958E-5; rul[20][0][286]=1.44332E-4; rul[20][0][287]=1.4446E-4; rul[20][0][288]=8.9223E-5; rul[20][0][289]=8.9757E-5; 
rul[20][0][290]=1.03925E-4; rul[20][0][291]=1.04052E-4; rul[20][0][292]=2.15583E-4; rul[20][0][293]=2.16003E-4; rul[20][0][294]=1.0127E-4; rul[20][0][295]=1.01362E-4; 
rul[20][0][296]=5.8262E-5; rul[20][0][297]=5.83955E-5; rul[20][0][298]=1.32975E-4; rul[20][0][299]=1.33638E-4; rul[20][0][300]=1.08438E-4; rul[20][0][301]=1.08584E-4; 
rul[20][0][302]=4.8152E-5; rul[20][0][303]=4.81775E-5; rul[20][0][304]=9.53476E-4; rul[20][0][305]=9.64656E-4; rul[20][0][306]=2.71775E-4; rul[20][0][307]=2.73156E-4; 
rul[20][0][308]=7.42805E-5; rul[20][0][309]=7.45645E-5; rul[20][0][310]=7.8327E-5; rul[20][0][311]=7.84205E-5; rul[20][0][312]=6.11386E-4; rul[20][0][313]=6.29924E-4; 
rul[20][0][314]=1.32875E-5; rul[20][0][315]=1.3418E-5; rul[20][0][316]=6.5472E-5; rul[20][0][317]=6.55125E-5; rul[20][0][318]=8.136E-6; rul[20][0][319]=8.2425E-6; 
rul[20][0][320]=9.94015E-5; rul[20][0][321]=9.9562E-5; rul[20][0][322]=8.3982E-5; rul[20][0][323]=8.4234E-5; rul[20][0][324]=2.0704E-4; rul[20][0][325]=2.07311E-4; 
rul[20][0][326]=8.98591E-4; rul[20][0][327]=9.42421E-4; rul[20][0][328]=4.03881E-4; rul[20][0][329]=4.05634E-4; rul[20][0][330]=2.9906E-4; rul[20][0][331]=3.00527E-4; 
rul[20][0][332]=4.81135E-5; rul[20][0][333]=4.8134E-5; rul[20][0][334]=9.20645E-5; rul[20][0][335]=9.2222E-5; rul[20][0][336]=9.46925E-5; rul[20][0][337]=9.48955E-5; 
rul[20][0][338]=3.46625E-5; rul[20][0][339]=3.4687E-5; rul[20][0][340]=1.06289E-4; rul[20][0][341]=1.06494E-4; rul[20][0][342]=5.17075E-4; rul[20][0][343]=5.17181E-4; 
rul[20][0][344]=8.1103E-5; rul[20][0][345]=8.1124E-5; rul[20][0][346]=8.45364E-4; rul[20][0][347]=8.59705E-4; rul[20][0][348]=9.5041E-5; rul[20][0][349]=9.51825E-5; 
rul[20][0][350]=1.07548E-4; rul[20][0][351]=1.07617E-4; rul[20][0][352]=3.4128E-5; rul[20][0][353]=3.43635E-5; 
dl_reg[20]=1;
dec[20]=3; 
// 21. Koniec reguly
// 22. Regula
// 1. sekcja AND 22 reguly.
rul[21][0][0]=54; rul[21][0][1]=68; 
rul[21][0][2]=9.64656E-4; rul[21][0][3]=0.00105582; rul[21][0][4]=1.08584E-4; rul[21][0][5]=1.08902E-4; rul[21][0][6]=6.52173E-4; rul[21][0][7]=6.70634E-4; 
rul[21][0][8]=6.02601E-4; rul[21][0][9]=6.07046E-4; rul[21][0][10]=4.62674E-4; rul[21][0][11]=4.63741E-4; rul[21][0][12]=4.19998E-4; rul[21][0][13]=4.23396E-4; 
rul[21][0][14]=2.44482E-4; rul[21][0][15]=2.45475E-4; rul[21][0][16]=2.9611E-4; rul[21][0][17]=2.9906E-4; rul[21][0][18]=5.90568E-4; rul[21][0][19]=5.92394E-4; 
rul[21][0][20]=2.64067E-4; rul[21][0][21]=2.64469E-4; rul[21][0][22]=5.9525E-4; rul[21][0][23]=5.98718E-4; rul[21][0][24]=3.24785E-5; rul[21][0][25]=3.26815E-5; 
rul[21][0][26]=7.19261E-4; rul[21][0][27]=7.38197E-4; rul[21][0][28]=2.53032E-4; rul[21][0][29]=2.5416E-4; rul[21][0][30]=3.91516E-4; rul[21][0][31]=3.92906E-4; 
rul[21][0][32]=4.17729E-4; rul[21][0][33]=4.18136E-4; rul[21][0][34]=3.16598E-4; rul[21][0][35]=3.1712E-4; rul[21][0][36]=4.08295E-4; rul[21][0][37]=4.10531E-4; 
rul[21][0][38]=0.00111489; rul[21][0][39]=0.00115414; rul[21][0][40]=3.38536E-4; rul[21][0][41]=3.39581E-4; rul[21][0][42]=4.39325E-5; rul[21][0][43]=4.40045E-5; 
rul[21][0][44]=4.38091E-4; rul[21][0][45]=4.39173E-4; rul[21][0][46]=5.72361E-4; rul[21][0][47]=5.81408E-4; rul[21][0][48]=4.4555E-6; rul[21][0][49]=4.867E-6; 
rul[21][0][50]=2.70545E-4; rul[21][0][51]=2.70978E-4; rul[21][0][52]=3.7817E-4; rul[21][0][53]=3.79278E-4; rul[21][0][54]=4.3628E-4; rul[21][0][55]=4.3712E-4; 
rul[21][0][56]=5.64375E-5; rul[21][0][57]=5.6617E-5; rul[21][0][58]=2.46093E-4; rul[21][0][59]=2.46677E-4; rul[21][0][60]=2.78427E-4; rul[21][0][61]=2.78731E-4; 
rul[21][0][62]=3.75905E-5; rul[21][0][63]=3.7857E-5; rul[21][0][64]=1.2751E-4; rul[21][0][65]=1.27616E-4; rul[21][0][66]=2.30508E-4; rul[21][0][67]=2.32116E-4; 
rul[21][0][68]=5.00266E-4; rul[21][0][69]=5.01512E-4; 
dl_reg[21]=1;
dec[21]=1; 
// 22. Koniec reguly      

}

/** \brief Metoda dla regu³ niemomentowych
	\author LM
*/
void RulInter::ZapiszRule1()
{
 double min = -DBL_MAX;
 double max = DBL_MAX;
 //cout << "DBL_MAX = " << max << " DBL_MIN = " << min << endl;
 //cout << "TEst -9999999 < min = " << (-9999999 < min) << endl;

 // 1. Regula
// 1. sekcja AND 1 reguly.
rul[0][0][0]=35; rul[0][0][1]=2; 
rul[0][0][2]=1; rul[0][0][3]=1; 
// 2. sekcja AND 1 reguly.
rul[0][1][0]=18; rul[0][1][1]=2; 
rul[0][1][2]=0.9085; rul[0][1][3]=max; 
// 3. sekcja AND 1 reguly.
rul[0][2][0]=15; rul[0][2][1]=4; 
rul[0][2][2]=min; rul[0][2][3]=18.43; rul[0][2][4]=18.43; rul[0][2][5]=max; 
// 4. sekcja AND 1 reguly.
rul[0][3][0]=16; rul[0][3][1]=2; 
rul[0][3][2]=0.8145; rul[0][3][3]=max; 
// 5. sekcja AND 1 reguly.
rul[0][4][0]=3; rul[0][4][1]=2; 
rul[0][4][2]=min; rul[0][4][3]=1.368; 
// 6. sekcja AND 1 reguly.
rul[0][5][0]=21; rul[0][5][1]=2; 
rul[0][5][2]=0.1245; rul[0][5][3]=max; 
// 7. sekcja AND 1 reguly.
rul[0][6][0]=6; rul[0][6][1]=2; 
rul[0][6][2]=8.215; rul[0][6][3]=max; 
// 8. sekcja AND 1 reguly.
rul[0][7][0]=27; rul[0][7][1]=2; 
rul[0][7][2]=0.6905; rul[0][7][3]=max; 
dl_reg[0]=8;
dec[0]=2; 
// 1. Koniec reguly
// 2. Regula
// 1. sekcja AND 2 reguly.
rul[1][0][0]=35; rul[1][0][1]=2; 
rul[1][0][2]=1; rul[1][0][3]=1; 
// 2. sekcja AND 2 reguly.
rul[1][1][0]=6; rul[1][1][1]=2; 
rul[1][1][2]=8.215; rul[1][1][3]=max; 
// 3. sekcja AND 2 reguly.
rul[1][2][0]=8; rul[1][2][1]=2; 
rul[1][2][2]=1.0185; rul[1][2][3]=max; 
// 4. sekcja AND 2 reguly.
rul[1][3][0]=3; rul[1][3][1]=4; 
rul[1][3][2]=1.368; rul[1][3][3]=max; rul[1][3][4]=min; rul[1][3][5]=1.368; 
// 5. sekcja AND 2 reguly.
rul[1][4][0]=21; rul[1][4][1]=2; 
rul[1][4][2]=0.1245; rul[1][4][3]=max; 
// 6. sekcja AND 2 reguly.
rul[1][5][0]=4; rul[1][5][1]=2; 
rul[1][5][2]=min; rul[1][5][3]=0.6655; 
// 7. sekcja AND 2 reguly.
rul[1][6][0]=16; rul[1][6][1]=2; 
rul[1][6][2]=min; rul[1][6][3]=0.8145; 
// 8. sekcja AND 2 reguly.
rul[1][7][0]=27; rul[1][7][1]=4; 
rul[1][7][2]=min; rul[1][7][3]=0.5825; rul[1][7][4]=0.5825; rul[1][7][5]=0.6905; 
// 9. sekcja AND 2 reguly.
rul[1][8][0]=18; rul[1][8][1]=4; 
rul[1][8][2]=min; rul[1][8][3]=0.9085; rul[1][8][4]=0.9085; rul[1][8][5]=max; 
// 10. sekcja AND 2 reguly.
rul[1][9][0]=15; rul[1][9][1]=4; 
rul[1][9][2]=18.43; rul[1][9][3]=max; rul[1][9][4]=min; rul[1][9][5]=18.43; 
// 11. sekcja AND 2 reguly.
rul[1][10][0]=26; rul[1][10][1]=4; 
rul[1][10][2]=0.3215; rul[1][10][3]=0.6065; rul[1][10][4]=0.6065; rul[1][10][5]=0.8585; 
// 12. sekcja AND 2 reguly.
rul[1][11][0]=33; rul[1][11][1]=2; 
rul[1][11][2]=min; rul[1][11][3]=73.918; 
dl_reg[1]=12;
dec[1]=2; 
// 2. Koniec reguly
// 3. Regula
// 1. sekcja AND 3 reguly.
rul[2][0][0]=35; rul[2][0][1]=2; 
rul[2][0][2]=1; rul[2][0][3]=1; 
// 2. sekcja AND 3 reguly.
rul[2][1][0]=15; rul[2][1][1]=2; 
rul[2][1][2]=min; rul[2][1][3]=18.43; 
// 3. sekcja AND 3 reguly.
rul[2][2][0]=7; rul[2][2][1]=2; 
rul[2][2][2]=min; rul[2][2][3]=6.171; 
// 4. sekcja AND 3 reguly.
rul[2][3][0]=18; rul[2][3][1]=4; 
rul[2][3][2]=0.9085; rul[2][3][3]=max; rul[2][3][4]=min; rul[2][3][5]=0.9085; 
// 5. sekcja AND 3 reguly.
rul[2][4][0]=33; rul[2][4][1]=2; 
rul[2][4][2]=73.918; rul[2][4][3]=137.781; 
// 6. sekcja AND 3 reguly.
rul[2][5][0]=34; rul[2][5][1]=2; 
rul[2][5][2]=240.981; rul[2][5][3]=max; 
// 7. sekcja AND 3 reguly.
rul[2][6][0]=21; rul[2][6][1]=4; 
rul[2][6][2]=0.1245; rul[2][6][3]=max; rul[2][6][4]=min; rul[2][6][5]=0.1245; 
// 8. sekcja AND 3 reguly.
rul[2][7][0]=20; rul[2][7][1]=4; 
rul[2][7][2]=220.22; rul[2][7][3]=356.734; rul[2][7][4]=min; rul[2][7][5]=220.22; 
dl_reg[2]=8;
dec[2]=4; 
// 3. Koniec reguly
// 4. Regula
// 1. sekcja AND 4 reguly.
rul[3][0][0]=35; rul[3][0][1]=2; 
rul[3][0][2]=1; rul[3][0][3]=1; 
// 2. sekcja AND 4 reguly.
rul[3][1][0]=18; rul[3][1][1]=2; 
rul[3][1][2]=0.9085; rul[3][1][3]=max; 
// 3. sekcja AND 4 reguly.
rul[3][2][0]=15; rul[3][2][1]=4; 
rul[3][2][2]=min; rul[3][2][3]=18.43; rul[3][2][4]=18.43; rul[3][2][5]=max; 
// 4. sekcja AND 4 reguly.
rul[3][3][0]=16; rul[3][3][1]=2; 
rul[3][3][2]=0.8145; rul[3][3][3]=max; 
// 5. sekcja AND 4 reguly.
rul[3][4][0]=3; rul[3][4][1]=2; 
rul[3][4][2]=min; rul[3][4][3]=1.368; 
// 6. sekcja AND 4 reguly.
rul[3][5][0]=26; rul[3][5][1]=4; 
rul[3][5][2]=0.8585; rul[3][5][3]=max; rul[3][5][4]=0.6065; rul[3][5][5]=0.8585; 
// 7. sekcja AND 4 reguly.
rul[3][6][0]=27; rul[3][6][1]=2; 
rul[3][6][2]=0.6905; rul[3][6][3]=max; 
// 8. sekcja AND 4 reguly.
rul[3][7][0]=4; rul[3][7][1]=4; 
rul[3][7][2]=min; rul[3][7][3]=0.6655; rul[3][7][4]=0.6655; rul[3][7][5]=max; 
// 9. sekcja AND 4 reguly.
rul[3][8][0]=21; rul[3][8][1]=2; 
rul[3][8][2]=0.1245; rul[3][8][3]=max; 
// 10. sekcja AND 4 reguly.
rul[3][9][0]=6; rul[3][9][1]=2; 
rul[3][9][2]=8.215; rul[3][9][3]=max; 
dl_reg[3]=10;
dec[3]=2; 
// 4. Koniec reguly
// 5. Regula
// 1. sekcja AND 5 reguly.
rul[4][0][0]=35; rul[4][0][1]=2; 
rul[4][0][2]=1; rul[4][0][3]=1; 
// 2. sekcja AND 5 reguly.
rul[4][1][0]=18; rul[4][1][1]=2; 
rul[4][1][2]=0.9085; rul[4][1][3]=max; 
// 3. sekcja AND 5 reguly.
rul[4][2][0]=6; rul[4][2][1]=4; 
rul[4][2][2]=8.215; rul[4][2][3]=max; rul[4][2][4]=min; rul[4][2][5]=8.215; 
// 4. sekcja AND 5 reguly.
rul[4][3][0]=8; rul[4][3][1]=2; 
rul[4][3][2]=1.0185; rul[4][3][3]=max; 
// 5. sekcja AND 5 reguly.
rul[4][4][0]=33; rul[4][4][1]=2; 
rul[4][4][2]=min; rul[4][4][3]=73.918; 
// 6. sekcja AND 5 reguly.
rul[4][5][0]=3; rul[4][5][1]=4; 
rul[4][5][2]=1.368; rul[4][5][3]=max; rul[4][5][4]=min; rul[4][5][5]=1.368; 
// 7. sekcja AND 5 reguly.
rul[4][6][0]=16; rul[4][6][1]=2; 
rul[4][6][2]=min; rul[4][6][3]=0.8145; 
// 8. sekcja AND 5 reguly.
rul[4][7][0]=4; rul[4][7][1]=2; 
rul[4][7][2]=min; rul[4][7][3]=0.6655; 
// 9. sekcja AND 5 reguly.
rul[4][8][0]=34; rul[4][8][1]=4; 
rul[4][8][2]=189.705; rul[4][8][3]=240.981; rul[4][8][4]=min; rul[4][8][5]=189.705; 
dl_reg[4]=9;
dec[4]=2; 
// 5. Koniec reguly
// 6. Regula
// 1. sekcja AND 6 reguly.
rul[5][0][0]=35; rul[5][0][1]=2; 
rul[5][0][2]=1; rul[5][0][3]=1; 
// 2. sekcja AND 6 reguly.
rul[5][1][0]=15; rul[5][1][1]=2; 
rul[5][1][2]=min; rul[5][1][3]=18.43; 
// 3. sekcja AND 6 reguly.
rul[5][2][0]=18; rul[5][2][1]=4; 
rul[5][2][2]=0.9085; rul[5][2][3]=max; rul[5][2][4]=min; rul[5][2][5]=0.9085; 
// 4. sekcja AND 6 reguly.
rul[5][3][0]=4; rul[5][3][1]=2; 
rul[5][3][2]=0.6655; rul[5][3][3]=max; 
// 5. sekcja AND 6 reguly.
rul[5][4][0]=3; rul[5][4][1]=2; 
rul[5][4][2]=1.368; rul[5][4][3]=max; 
// 6. sekcja AND 6 reguly.
rul[5][5][0]=6; rul[5][5][1]=4; 
rul[5][5][2]=8.215; rul[5][5][3]=max; rul[5][5][4]=min; rul[5][5][5]=8.215; 
// 7. sekcja AND 6 reguly.
rul[5][6][0]=8; rul[5][6][1]=4; 
rul[5][6][2]=1.0185; rul[5][6][3]=max; rul[5][6][4]=min; rul[5][6][5]=1.0185; 
// 8. sekcja AND 6 reguly.
rul[5][7][0]=34; rul[5][7][1]=2; 
rul[5][7][2]=min; rul[5][7][3]=189.705; 
// 9. sekcja AND 6 reguly.
rul[5][8][0]=10; rul[5][8][1]=2; 
rul[5][8][2]=1.5705; rul[5][8][3]=max; 
// 10. sekcja AND 6 reguly.
rul[5][9][0]=33; rul[5][9][1]=2; 
rul[5][9][2]=min; rul[5][9][3]=73.918; 
// 11. sekcja AND 6 reguly.
rul[5][10][0]=32; rul[5][10][1]=2; 
rul[5][10][2]=min; rul[5][10][3]=198.694; 
dl_reg[5]=11;
dec[5]=4; 
// 6. Koniec reguly
// 7. Regula
// 1. sekcja AND 7 reguly.
rul[6][0][0]=35; rul[6][0][1]=2; 
rul[6][0][2]=1; rul[6][0][3]=1; 
// 2. sekcja AND 7 reguly.
rul[6][1][0]=3; rul[6][1][1]=2; 
rul[6][1][2]=1.368; rul[6][1][3]=max; 
// 3. sekcja AND 7 reguly.
rul[6][2][0]=6; rul[6][2][1]=2; 
rul[6][2][2]=8.215; rul[6][2][3]=max; 
// 4. sekcja AND 7 reguly.
rul[6][3][0]=8; rul[6][3][1]=2; 
rul[6][3][2]=1.0185; rul[6][3][3]=max; 
// 5. sekcja AND 7 reguly.
rul[6][4][0]=16; rul[6][4][1]=2; 
rul[6][4][2]=min; rul[6][4][3]=0.8145; 
// 6. sekcja AND 7 reguly.
rul[6][5][0]=21; rul[6][5][1]=2; 
rul[6][5][2]=0.1245; rul[6][5][3]=max; 
// 7. sekcja AND 7 reguly.
rul[6][6][0]=15; rul[6][6][1]=2; 
rul[6][6][2]=18.43; rul[6][6][3]=max; 
// 8. sekcja AND 7 reguly.
rul[6][7][0]=18; rul[6][7][1]=4; 
rul[6][7][2]=min; rul[6][7][3]=0.9085; rul[6][7][4]=0.9085; rul[6][7][5]=max; 
// 9. sekcja AND 7 reguly.
rul[6][8][0]=26; rul[6][8][1]=2; 
rul[6][8][2]=min; rul[6][8][3]=0.3215; 
// 10. sekcja AND 7 reguly.
rul[6][9][0]=4; rul[6][9][1]=2; 
rul[6][9][2]=min; rul[6][9][3]=0.6655; 
// 11. sekcja AND 7 reguly.
rul[6][10][0]=7; rul[6][10][1]=2; 
rul[6][10][2]=8.48; rul[6][10][3]=14.437; 
dl_reg[6]=11;
dec[6]=3; 
// 7. Koniec reguly
// 8. Regula
// 1. sekcja AND 8 reguly.
rul[7][0][0]=35; rul[7][0][1]=2; 
rul[7][0][2]=1; rul[7][0][3]=1; 
// 2. sekcja AND 8 reguly.
rul[7][1][0]=6; rul[7][1][1]=2; 
rul[7][1][2]=8.215; rul[7][1][3]=max; 
// 3. sekcja AND 8 reguly.
rul[7][2][0]=8; rul[7][2][1]=2; 
rul[7][2][2]=1.0185; rul[7][2][3]=max; 
// 4. sekcja AND 8 reguly.
rul[7][3][0]=4; rul[7][3][1]=2; 
rul[7][3][2]=min; rul[7][3][3]=0.6655; 
// 5. sekcja AND 8 reguly.
rul[7][4][0]=3; rul[7][4][1]=2; 
rul[7][4][2]=1.368; rul[7][4][3]=max; 
// 6. sekcja AND 8 reguly.
rul[7][5][0]=21; rul[7][5][1]=2; 
rul[7][5][2]=0.1245; rul[7][5][3]=max; 
// 7. sekcja AND 8 reguly.
rul[7][6][0]=27; rul[7][6][1]=2; 
rul[7][6][2]=min; rul[7][6][3]=0.5825; 
// 8. sekcja AND 8 reguly.
rul[7][7][0]=16; rul[7][7][1]=2; 
rul[7][7][2]=min; rul[7][7][3]=0.8145; 
// 9. sekcja AND 8 reguly.
rul[7][8][0]=15; rul[7][8][1]=2; 
rul[7][8][2]=18.43; rul[7][8][3]=max; 
// 10. sekcja AND 8 reguly.
rul[7][9][0]=33; rul[7][9][1]=4; 
rul[7][9][2]=min; rul[7][9][3]=73.918; rul[7][9][4]=73.918; rul[7][9][5]=137.781; 
// 11. sekcja AND 8 reguly.
rul[7][10][0]=32; rul[7][10][1]=4; 
rul[7][10][2]=min; rul[7][10][3]=198.694; rul[7][10][4]=198.694; rul[7][10][5]=234.086; 
// 12. sekcja AND 8 reguly.
rul[7][11][0]=18; rul[7][11][1]=4; 
rul[7][11][2]=min; rul[7][11][3]=0.9085; rul[7][11][4]=0.9085; rul[7][11][5]=max; 
// 13. sekcja AND 8 reguly.
rul[7][12][0]=7; rul[7][12][1]=4; 
rul[7][12][2]=min; rul[7][12][3]=6.171; rul[7][12][4]=14.437; rul[7][12][5]=max; 
// 14. sekcja AND 8 reguly.
rul[7][13][0]=26; rul[7][13][1]=4; 
rul[7][13][2]=0.3215; rul[7][13][3]=0.6065; rul[7][13][4]=0.6065; rul[7][13][5]=0.8585; 
dl_reg[7]=14;
dec[7]=2; 
// 8. Koniec reguly
// 9. Regula
// 1. sekcja AND 9 reguly.
rul[8][0][0]=35; rul[8][0][1]=2; 
rul[8][0][2]=1; rul[8][0][3]=1; 
// 2. sekcja AND 9 reguly.
rul[8][1][0]=6; rul[8][1][1]=2; 
rul[8][1][2]=8.215; rul[8][1][3]=max; 
// 3. sekcja AND 9 reguly.
rul[8][2][0]=8; rul[8][2][1]=2; 
rul[8][2][2]=1.0185; rul[8][2][3]=max; 
// 4. sekcja AND 9 reguly.
rul[8][3][0]=4; rul[8][3][1]=2; 
rul[8][3][2]=min; rul[8][3][3]=0.6655; 
// 5. sekcja AND 9 reguly.
rul[8][4][0]=3; rul[8][4][1]=2; 
rul[8][4][2]=1.368; rul[8][4][3]=max; 
// 6. sekcja AND 9 reguly.
rul[8][5][0]=21; rul[8][5][1]=2; 
rul[8][5][2]=0.1245; rul[8][5][3]=max; 
// 7. sekcja AND 9 reguly.
rul[8][6][0]=27; rul[8][6][1]=2; 
rul[8][6][2]=min; rul[8][6][3]=0.5825; 
// 8. sekcja AND 9 reguly.
rul[8][7][0]=16; rul[8][7][1]=4; 
rul[8][7][2]=min; rul[8][7][3]=0.8145; rul[8][7][4]=0.8145; rul[8][7][5]=max; 
// 9. sekcja AND 9 reguly.
rul[8][8][0]=15; rul[8][8][1]=4; 
rul[8][8][2]=18.43; rul[8][8][3]=max; rul[8][8][4]=min; rul[8][8][5]=18.43; 
// 10. sekcja AND 9 reguly.
rul[8][9][0]=33; rul[8][9][1]=2; 
rul[8][9][2]=min; rul[8][9][3]=73.918; 
// 11. sekcja AND 9 reguly.
rul[8][10][0]=26; rul[8][10][1]=4; 
rul[8][10][2]=0.3215; rul[8][10][3]=0.6065; rul[8][10][4]=0.6065; rul[8][10][5]=0.8585; 
// 12. sekcja AND 9 reguly.
rul[8][11][0]=7; rul[8][11][1]=6; 
rul[8][11][2]=6.171; rul[8][11][3]=8.48; rul[8][11][4]=min; rul[8][11][5]=6.171; rul[8][11][6]=14.437; rul[8][11][7]=max; 
// 13. sekcja AND 9 reguly.
rul[8][12][0]=10; rul[8][12][1]=4; 
rul[8][12][2]=min; rul[8][12][3]=1.5705; rul[8][12][4]=1.5705; rul[8][12][5]=max; 
dl_reg[8]=13;
dec[8]=2; 
// 9. Koniec reguly
// 10. Regula
// 1. sekcja AND 10 reguly.
rul[9][0][0]=35; rul[9][0][1]=2; 
rul[9][0][2]=1; rul[9][0][3]=1; 
// 2. sekcja AND 10 reguly.
rul[9][1][0]=18; rul[9][1][1]=2; 
rul[9][1][2]=0.9085; rul[9][1][3]=max; 
// 3. sekcja AND 10 reguly.
rul[9][2][0]=15; rul[9][2][1]=2; 
rul[9][2][2]=min; rul[9][2][3]=18.43; 
// 4. sekcja AND 10 reguly.
rul[9][3][0]=16; rul[9][3][1]=2; 
rul[9][3][2]=0.8145; rul[9][3][3]=max; 
// 5. sekcja AND 10 reguly.
rul[9][4][0]=3; rul[9][4][1]=2; 
rul[9][4][2]=min; rul[9][4][3]=1.368; 
// 6. sekcja AND 10 reguly.
rul[9][5][0]=26; rul[9][5][1]=2; 
rul[9][5][2]=0.8585; rul[9][5][3]=max; 
// 7. sekcja AND 10 reguly.
rul[9][6][0]=8; rul[9][6][1]=4; 
rul[9][6][2]=1.0185; rul[9][6][3]=max; rul[9][6][4]=min; rul[9][6][5]=1.0185; 
// 8. sekcja AND 10 reguly.
rul[9][7][0]=6; rul[9][7][1]=2; 
rul[9][7][2]=8.215; rul[9][7][3]=max; 
// 9. sekcja AND 10 reguly.
rul[9][8][0]=10; rul[9][8][1]=2; 
rul[9][8][2]=min; rul[9][8][3]=1.5705; 
// 10. sekcja AND 10 reguly.
rul[9][9][0]=32; rul[9][9][1]=4; 
rul[9][9][2]=234.086; rul[9][9][3]=max; rul[9][9][4]=198.694; rul[9][9][5]=234.086; 
dl_reg[9]=10;
dec[9]=2; 
// 10. Koniec reguly

// 11. Regula
// 1. sekcja AND 11 reguly.
rul[10][0][0]=35; rul[10][0][1]=2; 
rul[10][0][2]=1; rul[10][0][3]=1; 
// 2. sekcja AND 11 reguly.
rul[10][1][0]=18; rul[10][1][1]=2; 
rul[10][1][2]=0.9085; rul[10][1][3]=max; 
// 3. sekcja AND 11 reguly.
rul[10][2][0]=16; rul[10][2][1]=2; 
rul[10][2][2]=0.8145; rul[10][2][3]=max; 
// 4. sekcja AND 11 reguly.
rul[10][3][0]=6; rul[10][3][1]=2; 
rul[10][3][2]=8.215; rul[10][3][3]=max; 
// 5. sekcja AND 11 reguly.
rul[10][4][0]=21; rul[10][4][1]=2; 
rul[10][4][2]=0.1245; rul[10][4][3]=max; 
// 6. sekcja AND 11 reguly.
rul[10][5][0]=4; rul[10][5][1]=2; 
rul[10][5][2]=0.6655; rul[10][5][3]=max; 
// 7. sekcja AND 11 reguly.
rul[10][6][0]=3; rul[10][6][1]=2; 
rul[10][6][2]=min; rul[10][6][3]=1.368; 
// 8. sekcja AND 11 reguly.
rul[10][7][0]=33; rul[10][7][1]=2; 
rul[10][7][2]=min; rul[10][7][3]=73.918; 
dl_reg[10]=8;
dec[10]=2; 
// 11. Koniec reguly
// 12. Regula
// 1. sekcja AND 12 reguly.
rul[11][0][0]=21; rul[11][0][1]=2; 
rul[11][0][2]=0.1245; rul[11][0][3]=max; 
// 2. sekcja AND 12 reguly.
rul[11][1][0]=6; rul[11][1][1]=2; 
rul[11][1][2]=8.215; rul[11][1][3]=max; 
// 3. sekcja AND 12 reguly.
rul[11][2][0]=8; rul[11][2][1]=2; 
rul[11][2][2]=1.0185; rul[11][2][3]=max; 
// 4. sekcja AND 12 reguly.
rul[11][3][0]=3; rul[11][3][1]=2; 
rul[11][3][2]=1.368; rul[11][3][3]=max; 
// 5. sekcja AND 12 reguly.
rul[11][4][0]=4; rul[11][4][1]=2; 
rul[11][4][2]=0.6655; rul[11][4][3]=max; 
// 6. sekcja AND 12 reguly.
rul[11][5][0]=32; rul[11][5][1]=2; 
rul[11][5][2]=234.086; rul[11][5][3]=max; 
// 7. sekcja AND 12 reguly.
rul[11][6][0]=16; rul[11][6][1]=2; 
rul[11][6][2]=min; rul[11][6][3]=0.8145; 
// 8. sekcja AND 12 reguly.
rul[11][7][0]=15; rul[11][7][1]=2; 
rul[11][7][2]=18.43; rul[11][7][3]=max; 
// 9. sekcja AND 12 reguly.
rul[11][8][0]=7; rul[11][8][1]=2; 
rul[11][8][2]=14.437; rul[11][8][3]=max; 
// 10. sekcja AND 12 reguly.
rul[11][9][0]=35; rul[11][9][1]=4; 
rul[11][9][2]=1; rul[11][9][3]=1; rul[11][9][4]=2; rul[11][9][5]=2; 
// 11. sekcja AND 12 reguly.
rul[11][10][0]=27; rul[11][10][1]=4; 
rul[11][10][2]=min; rul[11][10][3]=0.5825; rul[11][10][4]=0.5825; rul[11][10][5]=0.6905; 
dl_reg[11]=11;
dec[11]=5; 
// 12. Koniec reguly
// 13. Regula
// 1. sekcja AND 13 reguly.
rul[12][0][0]=35; rul[12][0][1]=2; 
rul[12][0][2]=1; rul[12][0][3]=1; 
// 2. sekcja AND 13 reguly.
rul[12][1][0]=15; rul[12][1][1]=2; 
rul[12][1][2]=min; rul[12][1][3]=18.43; 
// 3. sekcja AND 13 reguly.
rul[12][2][0]=7; rul[12][2][1]=4; 
rul[12][2][2]=min; rul[12][2][3]=6.171; rul[12][2][4]=6.171; rul[12][2][5]=8.48; 
// 4. sekcja AND 13 reguly.
rul[12][3][0]=18; rul[12][3][1]=4; 
rul[12][3][2]=0.9085; rul[12][3][3]=max; rul[12][3][4]=min; rul[12][3][5]=0.9085; 
// 5. sekcja AND 13 reguly.
rul[12][4][0]=27; rul[12][4][1]=2; 
rul[12][4][2]=0.6905; rul[12][4][3]=max; 
// 6. sekcja AND 13 reguly.
rul[12][5][0]=6; rul[12][5][1]=2; 
rul[12][5][2]=min; rul[12][5][3]=8.215; 
// 7. sekcja AND 13 reguly.
rul[12][6][0]=8; rul[12][6][1]=2; 
rul[12][6][2]=min; rul[12][6][3]=1.0185; 
// 8. sekcja AND 13 reguly.
rul[12][7][0]=16; rul[12][7][1]=2; 
rul[12][7][2]=0.8145; rul[12][7][3]=max; 
// 9. sekcja AND 13 reguly.
rul[12][8][0]=4; rul[12][8][1]=4; 
rul[12][8][2]=min; rul[12][8][3]=0.6655; rul[12][8][4]=0.6655; rul[12][8][5]=max; 
// 10. sekcja AND 13 reguly.
rul[12][9][0]=34; rul[12][9][1]=4; 
rul[12][9][2]=240.981; rul[12][9][3]=max; rul[12][9][4]=189.705; rul[12][9][5]=240.981; 
// 11. sekcja AND 13 reguly.
rul[12][10][0]=32; rul[12][10][1]=2; 
rul[12][10][2]=198.694; rul[12][10][3]=234.086; 
dl_reg[12]=11;
dec[12]=4; 
// 13. Koniec reguly
// 14. Regula
// 1. sekcja AND 14 reguly.
rul[13][0][0]=35; rul[13][0][1]=2; 
rul[13][0][2]=1; rul[13][0][3]=1; 
// 2. sekcja AND 14 reguly.
rul[13][1][0]=15; rul[13][1][1]=2; 
rul[13][1][2]=min; rul[13][1][3]=18.43; 
// 3. sekcja AND 14 reguly.
rul[13][2][0]=7; rul[13][2][1]=2; 
rul[13][2][2]=min; rul[13][2][3]=6.171; 
// 4. sekcja AND 14 reguly.
rul[13][3][0]=16; rul[13][3][1]=2; 
rul[13][3][2]=0.8145; rul[13][3][3]=max; 
// 5. sekcja AND 14 reguly.
rul[13][4][0]=6; rul[13][4][1]=2; 
rul[13][4][2]=min; rul[13][4][3]=8.215; 
// 6. sekcja AND 14 reguly.
rul[13][5][0]=27; rul[13][5][1]=2; 
rul[13][5][2]=0.6905; rul[13][5][3]=max; 
// 7. sekcja AND 14 reguly.
rul[13][6][0]=8; rul[13][6][1]=2; 
rul[13][6][2]=min; rul[13][6][3]=1.0185; 
// 8. sekcja AND 14 reguly.
rul[13][7][0]=10; rul[13][7][1]=2; 
rul[13][7][2]=min; rul[13][7][3]=1.5705; 
// 9. sekcja AND 14 reguly.
rul[13][8][0]=21; rul[13][8][1]=4; 
rul[13][8][2]=min; rul[13][8][3]=0.1245; rul[13][8][4]=0.1245; rul[13][8][5]=max; 
// 10. sekcja AND 14 reguly.
rul[13][9][0]=26; rul[13][9][1]=4; 
rul[13][9][2]=0.6065; rul[13][9][3]=0.8585; rul[13][9][4]=0.3215; rul[13][9][5]=0.6065; 
// 11. sekcja AND 14 reguly.
rul[13][10][0]=4; rul[13][10][1]=2; 
rul[13][10][2]=0.6655; rul[13][10][3]=max; 
// 12. sekcja AND 14 reguly.
rul[13][11][0]=3; rul[13][11][1]=2; 
rul[13][11][2]=1.368; rul[13][11][3]=max; 
dl_reg[13]=12;
dec[13]=4; 
// 14. Koniec reguly
// 15. Regula
// 1. sekcja AND 15 reguly.
rul[14][0][0]=35; rul[14][0][1]=2; 
rul[14][0][2]=1; rul[14][0][3]=1; 
// 2. sekcja AND 15 reguly.
rul[14][1][0]=6; rul[14][1][1]=2; 
rul[14][1][2]=8.215; rul[14][1][3]=max; 
// 3. sekcja AND 15 reguly.
rul[14][2][0]=8; rul[14][2][1]=2; 
rul[14][2][2]=1.0185; rul[14][2][3]=max; 
// 4. sekcja AND 15 reguly.
rul[14][3][0]=3; rul[14][3][1]=4; 
rul[14][3][2]=1.368; rul[14][3][3]=max; rul[14][3][4]=min; rul[14][3][5]=1.368; 
// 5. sekcja AND 15 reguly.
rul[14][4][0]=4; rul[14][4][1]=2; 
rul[14][4][2]=min; rul[14][4][3]=0.6655; 
// 6. sekcja AND 15 reguly.
rul[14][5][0]=21; rul[14][5][1]=2; 
rul[14][5][2]=0.1245; rul[14][5][3]=max; 
// 7. sekcja AND 15 reguly.
rul[14][6][0]=16; rul[14][6][1]=2; 
rul[14][6][2]=min; rul[14][6][3]=0.8145; 
// 8. sekcja AND 15 reguly.
rul[14][7][0]=27; rul[14][7][1]=2; 
rul[14][7][2]=min; rul[14][7][3]=0.5825; 
// 9. sekcja AND 15 reguly.
rul[14][8][0]=18; rul[14][8][1]=4; 
rul[14][8][2]=min; rul[14][8][3]=0.9085; rul[14][8][4]=0.9085; rul[14][8][5]=max; 
// 10. sekcja AND 15 reguly.
rul[14][9][0]=15; rul[14][9][1]=2; 
rul[14][9][2]=18.43; rul[14][9][3]=max; 
// 11. sekcja AND 15 reguly.
rul[14][10][0]=33; rul[14][10][1]=2; 
rul[14][10][2]=min; rul[14][10][3]=73.918; 
// 12. sekcja AND 15 reguly.
rul[14][11][0]=7; rul[14][11][1]=6; 
rul[14][11][2]=min; rul[14][11][3]=6.171; rul[14][11][4]=6.171; rul[14][11][5]=8.48; rul[14][11][6]=14.437; rul[14][11][7]=max; 
// 13. sekcja AND 15 reguly.
rul[14][12][0]=10; rul[14][12][1]=4; 
rul[14][12][2]=1.5705; rul[14][12][3]=max; rul[14][12][4]=min; rul[14][12][5]=1.5705; 
// 14. sekcja AND 15 reguly.
rul[14][13][0]=32; rul[14][13][1]=4; 
rul[14][13][2]=min; rul[14][13][3]=198.694; rul[14][13][4]=198.694; rul[14][13][5]=234.086; 
dl_reg[14]=14;
dec[14]=2; 
// 15. Koniec reguly
// 16. Regula
// 1. sekcja AND 16 reguly.
rul[15][0][0]=35; rul[15][0][1]=2; 
rul[15][0][2]=1; rul[15][0][3]=1; 
// 2. sekcja AND 16 reguly.
rul[15][1][0]=15; rul[15][1][1]=2; 
rul[15][1][2]=min; rul[15][1][3]=18.43; 
// 3. sekcja AND 16 reguly.
rul[15][2][0]=4; rul[15][2][1]=2; 
rul[15][2][2]=0.6655; rul[15][2][3]=max; 
// 4. sekcja AND 16 reguly.
rul[15][3][0]=7; rul[15][3][1]=2; 
rul[15][3][2]=min; rul[15][3][3]=6.171; 
// 5. sekcja AND 16 reguly.
rul[15][4][0]=21; rul[15][4][1]=4; 
rul[15][4][2]=min; rul[15][4][3]=0.1245; rul[15][4][4]=0.1245; rul[15][4][5]=max; 
// 6. sekcja AND 16 reguly.
rul[15][5][0]=27; rul[15][5][1]=2; 
rul[15][5][2]=0.6905; rul[15][5][3]=max; 
// 7. sekcja AND 16 reguly.
rul[15][6][0]=8; rul[15][6][1]=2; 
rul[15][6][2]=min; rul[15][6][3]=1.0185; 
// 8. sekcja AND 16 reguly.
rul[15][7][0]=6; rul[15][7][1]=2; 
rul[15][7][2]=min; rul[15][7][3]=8.215; 
// 9. sekcja AND 16 reguly.
rul[15][8][0]=33; rul[15][8][1]=2; 
rul[15][8][2]=min; rul[15][8][3]=73.918; 
// 10. sekcja AND 16 reguly.
rul[15][9][0]=10; rul[15][9][1]=2; 
rul[15][9][2]=1.5705; rul[15][9][3]=max; 
// 11. sekcja AND 16 reguly.
rul[15][10][0]=3; rul[15][10][1]=2; 
rul[15][10][2]=min; rul[15][10][3]=1.368; 
// 12. sekcja AND 16 reguly.
rul[15][11][0]=26; rul[15][11][1]=2; 
rul[15][11][2]=0.8585; rul[15][11][3]=max; 
// 13. sekcja AND 16 reguly.
rul[15][12][0]=18; rul[15][12][1]=2; 
rul[15][12][2]=0.9085; rul[15][12][3]=max; 
// 14. sekcja AND 16 reguly.
rul[15][13][0]=16; rul[15][13][1]=2; 
rul[15][13][2]=min; rul[15][13][3]=0.8145; 
// 15. sekcja AND 16 reguly.
rul[15][14][0]=32; rul[15][14][1]=4; 
rul[15][14][2]=min; rul[15][14][3]=198.694; rul[15][14][4]=198.694; rul[15][14][5]=234.086; 
dl_reg[15]=15;
dec[15]=4; 
// 16. Koniec reguly
// 17. Regula
// 1. sekcja AND 17 reguly.
rul[16][0][0]=35; rul[16][0][1]=2; 
rul[16][0][2]=1; rul[16][0][3]=1; 
// 2. sekcja AND 17 reguly.
rul[16][1][0]=15; rul[16][1][1]=2; 
rul[16][1][2]=min; rul[16][1][3]=18.43; 
// 3. sekcja AND 17 reguly.
rul[16][2][0]=7; rul[16][2][1]=2; 
rul[16][2][2]=min; rul[16][2][3]=6.171; 
// 4. sekcja AND 17 reguly.
rul[16][3][0]=27; rul[16][3][1]=2; 
rul[16][3][2]=0.6905; rul[16][3][3]=max; 
// 5. sekcja AND 17 reguly.
rul[16][4][0]=6; rul[16][4][1]=2; 
rul[16][4][2]=min; rul[16][4][3]=8.215; 
// 6. sekcja AND 17 reguly.
rul[16][5][0]=8; rul[16][5][1]=2; 
rul[16][5][2]=min; rul[16][5][3]=1.0185; 
// 7. sekcja AND 17 reguly.
rul[16][6][0]=16; rul[16][6][1]=2; 
rul[16][6][2]=0.8145; rul[16][6][3]=max; 
// 8. sekcja AND 17 reguly.
rul[16][7][0]=21; rul[16][7][1]=4; 
rul[16][7][2]=min; rul[16][7][3]=0.1245; rul[16][7][4]=0.1245; rul[16][7][5]=max; 
// 9. sekcja AND 17 reguly.
rul[16][8][0]=33; rul[16][8][1]=2; 
rul[16][8][2]=min; rul[16][8][3]=73.918; 
// 10. sekcja AND 17 reguly.
rul[16][9][0]=3; rul[16][9][1]=4; 
rul[16][9][2]=min; rul[16][9][3]=1.368; rul[16][9][4]=1.368; rul[16][9][5]=max; 
// 11. sekcja AND 17 reguly.
rul[16][10][0]=18; rul[16][10][1]=2; 
rul[16][10][2]=min; rul[16][10][3]=0.9085; 
// 12. sekcja AND 17 reguly.
rul[16][11][0]=4; rul[16][11][1]=2; 
rul[16][11][2]=0.6655; rul[16][11][3]=max; 
// 13. sekcja AND 17 reguly.
rul[16][12][0]=10; rul[16][12][1]=4; 
rul[16][12][2]=1.5705; rul[16][12][3]=max; rul[16][12][4]=min; rul[16][12][5]=1.5705; 
// 14. sekcja AND 17 reguly.
rul[16][13][0]=32; rul[16][13][1]=4; 
rul[16][13][2]=198.694; rul[16][13][3]=234.086; rul[16][13][4]=min; rul[16][13][5]=198.694; 
dl_reg[16]=14;
dec[16]=4; 
// 17. Koniec reguly
// 18. Regula
// 1. sekcja AND 18 reguly.
rul[17][0][0]=35; rul[17][0][1]=2; 
rul[17][0][2]=1; rul[17][0][3]=1; 
// 2. sekcja AND 18 reguly.
rul[17][1][0]=18; rul[17][1][1]=4; 
rul[17][1][2]=0.9085; rul[17][1][3]=max; rul[17][1][4]=min; rul[17][1][5]=0.9085; 
// 3. sekcja AND 18 reguly.
rul[17][2][0]=6; rul[17][2][1]=2; 
rul[17][2][2]=8.215; rul[17][2][3]=max; 
// 4. sekcja AND 18 reguly.
rul[17][3][0]=8; rul[17][3][1]=4; 
rul[17][3][2]=1.0185; rul[17][3][3]=max; rul[17][3][4]=min; rul[17][3][5]=1.0185; 
// 5. sekcja AND 18 reguly.
rul[17][4][0]=33; rul[17][4][1]=2; 
rul[17][4][2]=min; rul[17][4][3]=73.918; 
// 6. sekcja AND 18 reguly.
rul[17][5][0]=3; rul[17][5][1]=4; 
rul[17][5][2]=1.368; rul[17][5][3]=max; rul[17][5][4]=min; rul[17][5][5]=1.368; 
// 7. sekcja AND 18 reguly.
rul[17][6][0]=4; rul[17][6][1]=2; 
rul[17][6][2]=min; rul[17][6][3]=0.6655; 
// 8. sekcja AND 18 reguly.
rul[17][7][0]=27; rul[17][7][1]=4; 
rul[17][7][2]=min; rul[17][7][3]=0.5825; rul[17][7][4]=0.6905; rul[17][7][5]=max; 
// 9. sekcja AND 18 reguly.
rul[17][8][0]=16; rul[17][8][1]=2; 
rul[17][8][2]=min; rul[17][8][3]=0.8145; 
// 10. sekcja AND 18 reguly.
rul[17][9][0]=21; rul[17][9][1]=4; 
rul[17][9][2]=0.1245; rul[17][9][3]=max; rul[17][9][4]=min; rul[17][9][5]=0.1245; 
// 11. sekcja AND 18 reguly.
rul[17][10][0]=7; rul[17][10][1]=4; 
rul[17][10][2]=min; rul[17][10][3]=6.171; rul[17][10][4]=14.437; rul[17][10][5]=max; 
// 12. sekcja AND 18 reguly.
rul[17][11][0]=34; rul[17][11][1]=2; 
rul[17][11][2]=min; rul[17][11][3]=189.705; 
dl_reg[17]=12;
dec[17]=2; 
// 18. Koniec reguly
// 19. Regula
// 1. sekcja AND 19 reguly.
rul[18][0][0]=35; rul[18][0][1]=2; 
rul[18][0][2]=1; rul[18][0][3]=1; 
// 2. sekcja AND 19 reguly.
rul[18][1][0]=18; rul[18][1][1]=2; 
rul[18][1][2]=0.9085; rul[18][1][3]=max; 
// 3. sekcja AND 19 reguly.
rul[18][2][0]=6; rul[18][2][1]=2; 
rul[18][2][2]=8.215; rul[18][2][3]=max; 
// 4. sekcja AND 19 reguly.
rul[18][3][0]=8; rul[18][3][1]=4; 
rul[18][3][2]=1.0185; rul[18][3][3]=max; rul[18][3][4]=min; rul[18][3][5]=1.0185; 
// 5. sekcja AND 19 reguly.
rul[18][4][0]=3; rul[18][4][1]=2; 
rul[18][4][2]=1.368; rul[18][4][3]=max; 
// 6. sekcja AND 19 reguly.
rul[18][5][0]=33; rul[18][5][1]=2; 
rul[18][5][2]=min; rul[18][5][3]=73.918; 
// 7. sekcja AND 19 reguly.
rul[18][6][0]=4; rul[18][6][1]=2; 
rul[18][6][2]=min; rul[18][6][3]=0.6655; 
// 8. sekcja AND 19 reguly.
rul[18][7][0]=27; rul[18][7][1]=2; 
rul[18][7][2]=min; rul[18][7][3]=0.5825; 
// 9. sekcja AND 19 reguly.
rul[18][8][0]=26; rul[18][8][1]=2; 
rul[18][8][2]=0.6065; rul[18][8][3]=0.8585; 
// 10. sekcja AND 19 reguly.
rul[18][9][0]=16; rul[18][9][1]=2; 
rul[18][9][2]=min; rul[18][9][3]=0.8145; 
// 11. sekcja AND 19 reguly.
rul[18][10][0]=10; rul[18][10][1]=2; 
rul[18][10][2]=1.5705; rul[18][10][3]=max; 
dl_reg[18]=11;
dec[18]=2; 
// 19. Koniec reguly
// 20. Regula
// 1. sekcja AND 20 reguly.
rul[19][0][0]=35; rul[19][0][1]=2; 
rul[19][0][2]=1; rul[19][0][3]=1; 
// 2. sekcja AND 20 reguly.
rul[19][1][0]=18; rul[19][1][1]=4; 
rul[19][1][2]=0.9085; rul[19][1][3]=max; rul[19][1][4]=min; rul[19][1][5]=0.9085; 
// 3. sekcja AND 20 reguly.
rul[19][2][0]=6; rul[19][2][1]=2; 
rul[19][2][2]=8.215; rul[19][2][3]=max; 
// 4. sekcja AND 20 reguly.
rul[19][3][0]=8; rul[19][3][1]=2; 
rul[19][3][2]=1.0185; rul[19][3][3]=max; 
// 5. sekcja AND 20 reguly.
rul[19][4][0]=3; rul[19][4][1]=4; 
rul[19][4][2]=1.368; rul[19][4][3]=max; rul[19][4][4]=min; rul[19][4][5]=1.368; 
// 6. sekcja AND 20 reguly.
rul[19][5][0]=33; rul[19][5][1]=2; 
rul[19][5][2]=min; rul[19][5][3]=73.918; 
// 7. sekcja AND 20 reguly.
rul[19][6][0]=4; rul[19][6][1]=2; 
rul[19][6][2]=min; rul[19][6][3]=0.6655; 
// 8. sekcja AND 20 reguly.
rul[19][7][0]=10; rul[19][7][1]=2; 
rul[19][7][2]=min; rul[19][7][3]=1.5705; 
// 9. sekcja AND 20 reguly.
rul[19][8][0]=27; rul[19][8][1]=2; 
rul[19][8][2]=min; rul[19][8][3]=0.5825; 
// 10. sekcja AND 20 reguly.
rul[19][9][0]=34; rul[19][9][1]=4; 
rul[19][9][2]=min; rul[19][9][3]=189.705; rul[19][9][4]=189.705; rul[19][9][5]=240.981; 
// 11. sekcja AND 20 reguly.
rul[19][10][0]=21; rul[19][10][1]=4; 
rul[19][10][2]=0.1245; rul[19][10][3]=max; rul[19][10][4]=min; rul[19][10][5]=0.1245; 
// 12. sekcja AND 20 reguly.
rul[19][11][0]=15; rul[19][11][1]=2; 
rul[19][11][2]=18.43; rul[19][11][3]=max; 
dl_reg[19]=12;
dec[19]=2; 
// 20. Koniec reguly
// 21. Regula
// 1. sekcja AND 21 reguly.
rul[20][0][0]=35; rul[20][0][1]=2; 
rul[20][0][2]=1; rul[20][0][3]=1; 
// 2. sekcja AND 21 reguly.
rul[20][1][0]=4; rul[20][1][1]=2; 
rul[20][1][2]=0.6655; rul[20][1][3]=max; 
// 3. sekcja AND 21 reguly.
rul[20][2][0]=3; rul[20][2][1]=2; 
rul[20][2][2]=1.368; rul[20][2][3]=max; 
// 4. sekcja AND 21 reguly.
rul[20][3][0]=6; rul[20][3][1]=2; 
rul[20][3][2]=8.215; rul[20][3][3]=max; 
// 5. sekcja AND 21 reguly.
rul[20][4][0]=8; rul[20][4][1]=2; 
rul[20][4][2]=1.0185; rul[20][4][3]=max; 
// 6. sekcja AND 21 reguly.
rul[20][5][0]=16; rul[20][5][1]=2; 
rul[20][5][2]=min; rul[20][5][3]=0.8145; 
// 7. sekcja AND 21 reguly.
rul[20][6][0]=21; rul[20][6][1]=2; 
rul[20][6][2]=0.1245; rul[20][6][3]=max; 
// 8. sekcja AND 21 reguly.
rul[20][7][0]=27; rul[20][7][1]=2; 
rul[20][7][2]=min; rul[20][7][3]=0.5825; 
// 9. sekcja AND 21 reguly.
rul[20][8][0]=18; rul[20][8][1]=4; 
rul[20][8][2]=min; rul[20][8][3]=0.9085; rul[20][8][4]=0.9085; rul[20][8][5]=max; 
// 10. sekcja AND 21 reguly.
rul[20][9][0]=26; rul[20][9][1]=4; 
rul[20][9][2]=min; rul[20][9][3]=0.3215; rul[20][9][4]=0.3215; rul[20][9][5]=0.6065; 
// 11. sekcja AND 21 reguly.
rul[20][10][0]=15; rul[20][10][1]=2; 
rul[20][10][2]=18.43; rul[20][10][3]=max; 
// 12. sekcja AND 21 reguly.
rul[20][11][0]=32; rul[20][11][1]=4; 
rul[20][11][2]=min; rul[20][11][3]=198.694; rul[20][11][4]=198.694; rul[20][11][5]=234.086; 
// 13. sekcja AND 21 reguly.
rul[20][12][0]=34; rul[20][12][1]=2; 
rul[20][12][2]=240.981; rul[20][12][3]=max; 
// 14. sekcja AND 21 reguly.
rul[20][13][0]=10; rul[20][13][1]=2; 
rul[20][13][2]=1.5705; rul[20][13][3]=max; 
dl_reg[20]=14;
dec[20]=4; 
// 21. Koniec reguly
// 22. Regula
// 1. sekcja AND 22 reguly.
rul[21][0][0]=35; rul[21][0][1]=2; 
rul[21][0][2]=1; rul[21][0][3]=1; 
// 2. sekcja AND 22 reguly.
rul[21][1][0]=18; rul[21][1][1]=2; 
rul[21][1][2]=0.9085; rul[21][1][3]=max; 
// 3. sekcja AND 22 reguly.
rul[21][2][0]=3; rul[21][2][1]=2; 
rul[21][2][2]=1.368; rul[21][2][3]=max; 
// 4. sekcja AND 22 reguly.
rul[21][3][0]=6; rul[21][3][1]=2; 
rul[21][3][2]=8.215; rul[21][3][3]=max; 
// 5. sekcja AND 22 reguly.
rul[21][4][0]=8; rul[21][4][1]=2; 
rul[21][4][2]=1.0185; rul[21][4][3]=max; 
// 6. sekcja AND 22 reguly.
rul[21][5][0]=10; rul[21][5][1]=2; 
rul[21][5][2]=1.5705; rul[21][5][3]=max; 
// 7. sekcja AND 22 reguly.
rul[21][6][0]=32; rul[21][6][1]=4; 
rul[21][6][2]=234.086; rul[21][6][3]=max; rul[21][6][4]=198.694; rul[21][6][5]=234.086; 
// 8. sekcja AND 22 reguly.
rul[21][7][0]=34; rul[21][7][1]=2; 
rul[21][7][2]=min; rul[21][7][3]=189.705; 
// 9. sekcja AND 22 reguly.
rul[21][8][0]=15; rul[21][8][1]=2; 
rul[21][8][2]=18.43; rul[21][8][3]=max; 
// 10. sekcja AND 22 reguly.
rul[21][9][0]=4; rul[21][9][1]=2; 
rul[21][9][2]=min; rul[21][9][3]=0.6655; 
// 11. sekcja AND 22 reguly.
rul[21][10][0]=16; rul[21][10][1]=2; 
rul[21][10][2]=min; rul[21][10][3]=0.8145; 
dl_reg[21]=11;
dec[21]=3; 
// 22. Koniec reguly
// 23. Regula
// 1. sekcja AND 23 reguly.
rul[22][0][0]=35; rul[22][0][1]=2; 
rul[22][0][2]=1; rul[22][0][3]=1; 
// 2. sekcja AND 23 reguly.
rul[22][1][0]=15; rul[22][1][1]=2; 
rul[22][1][2]=min; rul[22][1][3]=18.43; 
// 3. sekcja AND 23 reguly.
rul[22][2][0]=7; rul[22][2][1]=4; 
rul[22][2][2]=min; rul[22][2][3]=6.171; rul[22][2][4]=6.171; rul[22][2][5]=8.48; 
// 4. sekcja AND 23 reguly.
rul[22][3][0]=18; rul[22][3][1]=2; 
rul[22][3][2]=0.9085; rul[22][3][3]=max; 
// 5. sekcja AND 23 reguly.
rul[22][4][0]=3; rul[22][4][1]=2; 
rul[22][4][2]=1.368; rul[22][4][3]=max; 
// 6. sekcja AND 23 reguly.
rul[22][5][0]=4; rul[22][5][1]=2; 
rul[22][5][2]=0.6655; rul[22][5][3]=max; 
// 7. sekcja AND 23 reguly.
rul[22][6][0]=21; rul[22][6][1]=2; 
rul[22][6][2]=min; rul[22][6][3]=0.1245; 
// 8. sekcja AND 23 reguly.
rul[22][7][0]=8; rul[22][7][1]=2; 
rul[22][7][2]=min; rul[22][7][3]=1.0185; 
// 9. sekcja AND 23 reguly.
rul[22][8][0]=10; rul[22][8][1]=4; 
rul[22][8][2]=1.5705; rul[22][8][3]=max; rul[22][8][4]=min; rul[22][8][5]=1.5705; 
// 10. sekcja AND 23 reguly.
rul[22][9][0]=26; rul[22][9][1]=2; 
rul[22][9][2]=0.3215; rul[22][9][3]=0.6065; 
dl_reg[22]=10;
dec[22]=4; 
// 23. Koniec reguly
// 24. Regula
// 1. sekcja AND 24 reguly.
rul[23][0][0]=35; rul[23][0][1]=2; 
rul[23][0][2]=1; rul[23][0][3]=1; 
// 2. sekcja AND 24 reguly.
rul[23][1][0]=15; rul[23][1][1]=2; 
rul[23][1][2]=min; rul[23][1][3]=18.43; 
// 3. sekcja AND 24 reguly.
rul[23][2][0]=7; rul[23][2][1]=2; 
rul[23][2][2]=min; rul[23][2][3]=6.171; 
// 4. sekcja AND 24 reguly.
rul[23][3][0]=18; rul[23][3][1]=2; 
rul[23][3][2]=0.9085; rul[23][3][3]=max; 
// 5. sekcja AND 24 reguly.
rul[23][4][0]=3; rul[23][4][1]=2; 
rul[23][4][2]=1.368; rul[23][4][3]=max; 
// 6. sekcja AND 24 reguly.
rul[23][5][0]=33; rul[23][5][1]=4; 
rul[23][5][2]=min; rul[23][5][3]=73.918; rul[23][5][4]=73.918; rul[23][5][5]=137.781; 
// 7. sekcja AND 24 reguly.
rul[23][6][0]=4; rul[23][6][1]=2; 
rul[23][6][2]=0.6655; rul[23][6][3]=max; 
// 8. sekcja AND 24 reguly.
rul[23][7][0]=6; rul[23][7][1]=2; 
rul[23][7][2]=min; rul[23][7][3]=8.215; 
// 9. sekcja AND 24 reguly.
rul[23][8][0]=27; rul[23][8][1]=2; 
rul[23][8][2]=0.6905; rul[23][8][3]=max; 
// 10. sekcja AND 24 reguly.
rul[23][9][0]=8; rul[23][9][1]=2; 
rul[23][9][2]=min; rul[23][9][3]=1.0185; 
// 11. sekcja AND 24 reguly.
rul[23][10][0]=10; rul[23][10][1]=2; 
rul[23][10][2]=min; rul[23][10][3]=1.5705; 
dl_reg[23]=11;
dec[23]=4; 
// 24. Koniec reguly
// 25. Regula
// 1. sekcja AND 25 reguly.
rul[24][0][0]=35; rul[24][0][1]=2; 
rul[24][0][2]=1; rul[24][0][3]=1; 
// 2. sekcja AND 25 reguly.
rul[24][1][0]=18; rul[24][1][1]=2; 
rul[24][1][2]=0.9085; rul[24][1][3]=max; 
// 3. sekcja AND 25 reguly.
rul[24][2][0]=15; rul[24][2][1]=2; 
rul[24][2][2]=min; rul[24][2][3]=18.43; 
// 4. sekcja AND 25 reguly.
rul[24][3][0]=16; rul[24][3][1]=2; 
rul[24][3][2]=0.8145; rul[24][3][3]=max; 
// 5. sekcja AND 25 reguly.
rul[24][4][0]=27; rul[24][4][1]=4; 
rul[24][4][2]=0.6905; rul[24][4][3]=max; rul[24][4][4]=0.5825; rul[24][4][5]=0.6905; 
// 6. sekcja AND 25 reguly.
rul[24][5][0]=7; rul[24][5][1]=4; 
rul[24][5][2]=min; rul[24][5][3]=6.171; rul[24][5][4]=8.48; rul[24][5][5]=14.437; 
// 7. sekcja AND 25 reguly.
rul[24][6][0]=8; rul[24][6][1]=2; 
rul[24][6][2]=min; rul[24][6][3]=1.0185; 
// 8. sekcja AND 25 reguly.
rul[24][7][0]=6; rul[24][7][1]=4; 
rul[24][7][2]=min; rul[24][7][3]=8.215; rul[24][7][4]=8.215; rul[24][7][5]=max; 
// 9. sekcja AND 25 reguly.
rul[24][8][0]=34; rul[24][8][1]=2; 
rul[24][8][2]=min; rul[24][8][3]=189.705; 
// 10. sekcja AND 25 reguly.
rul[24][9][0]=32; rul[24][9][1]=2; 
rul[24][9][2]=234.086; rul[24][9][3]=max; 
// 11. sekcja AND 25 reguly.
rul[24][10][0]=33; rul[24][10][1]=2; 
rul[24][10][2]=137.781; rul[24][10][3]=max; 
// 12. sekcja AND 25 reguly.
rul[24][11][0]=4; rul[24][11][1]=2; 
rul[24][11][2]=min; rul[24][11][3]=0.6655; 
// 13. sekcja AND 25 reguly.
rul[24][12][0]=10; rul[24][12][1]=2; 
rul[24][12][2]=1.5705; rul[24][12][3]=max; 
dl_reg[24]=13;
dec[24]=3; 
// 25. Koniec reguly
// 26. Regula
// 1. sekcja AND 26 reguly.
rul[25][0][0]=35; rul[25][0][1]=2; 
rul[25][0][2]=1; rul[25][0][3]=1; 
// 2. sekcja AND 26 reguly.
rul[25][1][0]=18; rul[25][1][1]=2; 
rul[25][1][2]=0.9085; rul[25][1][3]=max; 
// 3. sekcja AND 26 reguly.
rul[25][2][0]=15; rul[25][2][1]=2; 
rul[25][2][2]=min; rul[25][2][3]=18.43; 
// 4. sekcja AND 26 reguly.
rul[25][3][0]=3; rul[25][3][1]=4; 
rul[25][3][2]=1.368; rul[25][3][3]=max; rul[25][3][4]=min; rul[25][3][5]=1.368; 
// 5. sekcja AND 26 reguly.
rul[25][4][0]=6; rul[25][4][1]=2; 
rul[25][4][2]=8.215; rul[25][4][3]=max; 
// 6. sekcja AND 26 reguly.
rul[25][5][0]=8; rul[25][5][1]=2; 
rul[25][5][2]=1.0185; rul[25][5][3]=max; 
// 7. sekcja AND 26 reguly.
rul[25][6][0]=16; rul[25][6][1]=2; 
rul[25][6][2]=0.8145; rul[25][6][3]=max; 
// 8. sekcja AND 26 reguly.
rul[25][7][0]=4; rul[25][7][1]=2; 
rul[25][7][2]=min; rul[25][7][3]=0.6655; 
// 9. sekcja AND 26 reguly.
rul[25][8][0]=34; rul[25][8][1]=2; 
rul[25][8][2]=min; rul[25][8][3]=189.705; 
// 10. sekcja AND 26 reguly.
rul[25][9][0]=21; rul[25][9][1]=2; 
rul[25][9][2]=min; rul[25][9][3]=0.1245; 
// 11. sekcja AND 26 reguly.
rul[25][10][0]=20; rul[25][10][1]=2; 
rul[25][10][2]=650.372; rul[25][10][3]=max; 
// 12. sekcja AND 26 reguly.
rul[25][11][0]=32; rul[25][11][1]=4; 
rul[25][11][2]=234.086; rul[25][11][3]=max; rul[25][11][4]=198.694; rul[25][11][5]=234.086; 
// 13. sekcja AND 26 reguly.
rul[25][12][0]=26; rul[25][12][1]=2; 
rul[25][12][2]=0.6065; rul[25][12][3]=0.8585; 
dl_reg[25]=13;
dec[25]=3; 
// 26. Koniec reguly
// 27. Regula
// 1. sekcja AND 27 reguly.
rul[26][0][0]=35; rul[26][0][1]=2; 
rul[26][0][2]=1; rul[26][0][3]=1; 
// 2. sekcja AND 27 reguly.
rul[26][1][0]=15; rul[26][1][1]=2; 
rul[26][1][2]=min; rul[26][1][3]=18.43; 
// 3. sekcja AND 27 reguly.
rul[26][2][0]=16; rul[26][2][1]=2; 
rul[26][2][2]=0.8145; rul[26][2][3]=max; 
// 4. sekcja AND 27 reguly.
rul[26][3][0]=18; rul[26][3][1]=2; 
rul[26][3][2]=0.9085; rul[26][3][3]=max; 
// 5. sekcja AND 27 reguly.
rul[26][4][0]=8; rul[26][4][1]=2; 
rul[26][4][2]=1.0185; rul[26][4][3]=max; 
// 6. sekcja AND 27 reguly.
rul[26][5][0]=26; rul[26][5][1]=2; 
rul[26][5][2]=0.6065; rul[26][5][3]=0.8585; 
// 7. sekcja AND 27 reguly.
rul[26][6][0]=6; rul[26][6][1]=2; 
rul[26][6][2]=8.215; rul[26][6][3]=max; 
// 8. sekcja AND 27 reguly.
rul[26][7][0]=33; rul[26][7][1]=4; 
rul[26][7][2]=min; rul[26][7][3]=73.918; rul[26][7][4]=73.918; rul[26][7][5]=137.781; 
// 9. sekcja AND 27 reguly.
rul[26][8][0]=7; rul[26][8][1]=2; 
rul[26][8][2]=8.48; rul[26][8][3]=14.437; 
// 10. sekcja AND 27 reguly.
rul[26][9][0]=10; rul[26][9][1]=2; 
rul[26][9][2]=min; rul[26][9][3]=1.5705; 
dl_reg[26]=10;
dec[26]=3; 
// 27. Koniec reguly
// 28. Regula
// 1. sekcja AND 28 reguly.
rul[27][0][0]=35; rul[27][0][1]=2; 
rul[27][0][2]=1; rul[27][0][3]=1; 
// 2. sekcja AND 28 reguly.
rul[27][1][0]=6; rul[27][1][1]=2; 
rul[27][1][2]=8.215; rul[27][1][3]=max; 
// 3. sekcja AND 28 reguly.
rul[27][2][0]=8; rul[27][2][1]=4; 
rul[27][2][2]=1.0185; rul[27][2][3]=max; rul[27][2][4]=min; rul[27][2][5]=1.0185; 
// 4. sekcja AND 28 reguly.
rul[27][3][0]=3; rul[27][3][1]=2; 
rul[27][3][2]=1.368; rul[27][3][3]=max; 
// 5. sekcja AND 28 reguly.
rul[27][4][0]=4; rul[27][4][1]=2; 
rul[27][4][2]=min; rul[27][4][3]=0.6655; 
// 6. sekcja AND 28 reguly.
rul[27][5][0]=21; rul[27][5][1]=4; 
rul[27][5][2]=0.1245; rul[27][5][3]=max; rul[27][5][4]=min; rul[27][5][5]=0.1245; 
// 7. sekcja AND 28 reguly.
rul[27][6][0]=27; rul[27][6][1]=4; 
rul[27][6][2]=min; rul[27][6][3]=0.5825; rul[27][6][4]=0.5825; rul[27][6][5]=0.6905; 
// 8. sekcja AND 28 reguly.
rul[27][7][0]=16; rul[27][7][1]=2; 
rul[27][7][2]=min; rul[27][7][3]=0.8145; 
// 9. sekcja AND 28 reguly.
rul[27][8][0]=15; rul[27][8][1]=4; 
rul[27][8][2]=18.43; rul[27][8][3]=max; rul[27][8][4]=min; rul[27][8][5]=18.43; 
// 10. sekcja AND 28 reguly.
rul[27][9][0]=18; rul[27][9][1]=4; 
rul[27][9][2]=min; rul[27][9][3]=0.9085; rul[27][9][4]=0.9085; rul[27][9][5]=max; 
// 11. sekcja AND 28 reguly.
rul[27][10][0]=10; rul[27][10][1]=2; 
rul[27][10][2]=1.5705; rul[27][10][3]=max; 
// 12. sekcja AND 28 reguly.
rul[27][11][0]=32; rul[27][11][1]=2; 
rul[27][11][2]=min; rul[27][11][3]=198.694; 
// 13. sekcja AND 28 reguly.
rul[27][12][0]=7; rul[27][12][1]=6; 
rul[27][12][2]=min; rul[27][12][3]=6.171; rul[27][12][4]=6.171; rul[27][12][5]=8.48; rul[27][12][6]=14.437; rul[27][12][7]=max; 
// 14. sekcja AND 28 reguly.
rul[27][13][0]=34; rul[27][13][1]=6; 
rul[27][13][2]=240.981; rul[27][13][3]=max; rul[27][13][4]=189.705; rul[27][13][5]=240.981; rul[27][13][6]=min; rul[27][13][7]=189.705; 
// 15. sekcja AND 28 reguly.
rul[27][14][0]=26; rul[27][14][1]=4; 
rul[27][14][2]=0.3215; rul[27][14][3]=0.6065; rul[27][14][4]=0.6065; rul[27][14][5]=0.8585; 
// 16. sekcja AND 28 reguly.
rul[27][15][0]=33; rul[27][15][1]=4; 
rul[27][15][2]=73.918; rul[27][15][3]=137.781; rul[27][15][4]=min; rul[27][15][5]=73.918; 
dl_reg[27]=16;
dec[27]=2; 
// 28. Koniec reguly
// 29. Regula
// 1. sekcja AND 29 reguly.
rul[28][0][0]=35; rul[28][0][1]=2; 
rul[28][0][2]=1; rul[28][0][3]=1; 
// 2. sekcja AND 29 reguly.
rul[28][1][0]=18; rul[28][1][1]=2; 
rul[28][1][2]=0.9085; rul[28][1][3]=max; 
// 3. sekcja AND 29 reguly.
rul[28][2][0]=15; rul[28][2][1]=2; 
rul[28][2][2]=min; rul[28][2][3]=18.43; 
// 4. sekcja AND 29 reguly.
rul[28][3][0]=10; rul[28][3][1]=2; 
rul[28][3][2]=1.5705; rul[28][3][3]=max; 
// 5. sekcja AND 29 reguly.
rul[28][4][0]=16; rul[28][4][1]=2; 
rul[28][4][2]=0.8145; rul[28][4][3]=max; 
// 6. sekcja AND 29 reguly.
rul[28][5][0]=3; rul[28][5][1]=2; 
rul[28][5][2]=min; rul[28][5][3]=1.368; 
// 7. sekcja AND 29 reguly.
rul[28][6][0]=4; rul[28][6][1]=2; 
rul[28][6][2]=0.6655; rul[28][6][3]=max; 
// 8. sekcja AND 29 reguly.
rul[28][7][0]=7; rul[28][7][1]=6; 
rul[28][7][2]=6.171; rul[28][7][3]=8.48; rul[28][7][4]=8.48; rul[28][7][5]=14.437; rul[28][7][6]=14.437; rul[28][7][7]=max; 
dl_reg[28]=8;
dec[28]=2; 
// 29. Koniec reguly
// 30. Regula
// 1. sekcja AND 30 reguly.
rul[29][0][0]=21; rul[29][0][1]=4; 
rul[29][0][2]=0.1245; rul[29][0][3]=max; rul[29][0][4]=min; rul[29][0][5]=0.1245; 
// 2. sekcja AND 30 reguly.
rul[29][1][0]=6; rul[29][1][1]=2; 
rul[29][1][2]=8.215; rul[29][1][3]=max; 
// 3. sekcja AND 30 reguly.
rul[29][2][0]=8; rul[29][2][1]=2; 
rul[29][2][2]=1.0185; rul[29][2][3]=max; 
// 4. sekcja AND 30 reguly.
rul[29][3][0]=3; rul[29][3][1]=2; 
rul[29][3][2]=1.368; rul[29][3][3]=max; 
// 5. sekcja AND 30 reguly.
rul[29][4][0]=4; rul[29][4][1]=2; 
rul[29][4][2]=0.6655; rul[29][4][3]=max; 
// 6. sekcja AND 30 reguly.
rul[29][5][0]=32; rul[29][5][1]=2; 
rul[29][5][2]=234.086; rul[29][5][3]=max; 
// 7. sekcja AND 30 reguly.
rul[29][6][0]=16; rul[29][6][1]=2; 
rul[29][6][2]=min; rul[29][6][3]=0.8145; 
// 8. sekcja AND 30 reguly.
rul[29][7][0]=15; rul[29][7][1]=2; 
rul[29][7][2]=18.43; rul[29][7][3]=max; 
// 9. sekcja AND 30 reguly.
rul[29][8][0]=7; rul[29][8][1]=2; 
rul[29][8][2]=14.437; rul[29][8][3]=max; 
// 10. sekcja AND 30 reguly.
rul[29][9][0]=26; rul[29][9][1]=4; 
rul[29][9][2]=min; rul[29][9][3]=0.3215; rul[29][9][4]=0.3215; rul[29][9][5]=0.6065; 
// 11. sekcja AND 30 reguly.
rul[29][10][0]=18; rul[29][10][1]=2; 
rul[29][10][2]=min; rul[29][10][3]=0.9085; 
// 12. sekcja AND 30 reguly.
rul[29][11][0]=10; rul[29][11][1]=4; 
rul[29][11][2]=1.5705; rul[29][11][3]=max; rul[29][11][4]=min; rul[29][11][5]=1.5705; 
// 13. sekcja AND 30 reguly.
rul[29][12][0]=27; rul[29][12][1]=2; 
rul[29][12][2]=min; rul[29][12][3]=0.5825; 
dl_reg[29]=13;
dec[29]=5; 
// 30. Koniec reguly
// 31. Regula
// 1. sekcja AND 31 reguly.
rul[30][0][0]=35; rul[30][0][1]=2; 
rul[30][0][2]=1; rul[30][0][3]=1; 
// 2. sekcja AND 31 reguly.
rul[30][1][0]=15; rul[30][1][1]=2; 
rul[30][1][2]=min; rul[30][1][3]=18.43; 
// 3. sekcja AND 31 reguly.
rul[30][2][0]=4; rul[30][2][1]=2; 
rul[30][2][2]=0.6655; rul[30][2][3]=max; 
// 4. sekcja AND 31 reguly.
rul[30][3][0]=3; rul[30][3][1]=2; 
rul[30][3][2]=1.368; rul[30][3][3]=max; 
// 5. sekcja AND 31 reguly.
rul[30][4][0]=6; rul[30][4][1]=2; 
rul[30][4][2]=8.215; rul[30][4][3]=max; 
// 6. sekcja AND 31 reguly.
rul[30][5][0]=8; rul[30][5][1]=4; 
rul[30][5][2]=1.0185; rul[30][5][3]=max; rul[30][5][4]=min; rul[30][5][5]=1.0185; 
// 7. sekcja AND 31 reguly.
rul[30][6][0]=16; rul[30][6][1]=4; 
rul[30][6][2]=min; rul[30][6][3]=0.8145; rul[30][6][4]=0.8145; rul[30][6][5]=max; 
// 8. sekcja AND 31 reguly.
rul[30][7][0]=33; rul[30][7][1]=4; 
rul[30][7][2]=min; rul[30][7][3]=73.918; rul[30][7][4]=73.918; rul[30][7][5]=137.781; 
// 9. sekcja AND 31 reguly.
rul[30][8][0]=21; rul[30][8][1]=2; 
rul[30][8][2]=min; rul[30][8][3]=0.1245; 
// 10. sekcja AND 31 reguly.
rul[30][9][0]=34; rul[30][9][1]=4; 
rul[30][9][2]=min; rul[30][9][3]=189.705; rul[30][9][4]=189.705; rul[30][9][5]=240.981; 
// 11. sekcja AND 31 reguly.
rul[30][10][0]=18; rul[30][10][1]=2; 
rul[30][10][2]=0.9085; rul[30][10][3]=max; 
// 12. sekcja AND 31 reguly.
rul[30][11][0]=26; rul[30][11][1]=2; 
rul[30][11][2]=0.3215; rul[30][11][3]=0.6065; 
// 13. sekcja AND 31 reguly.
rul[30][12][0]=10; rul[30][12][1]=2; 
rul[30][12][2]=min; rul[30][12][3]=1.5705; 
dl_reg[30]=13;
dec[30]=4; 
// 31. Koniec reguly
// 32. Regula
// 1. sekcja AND 32 reguly.
rul[31][0][0]=35; rul[31][0][1]=2; 
rul[31][0][2]=1; rul[31][0][3]=1; 
// 2. sekcja AND 32 reguly.
rul[31][1][0]=15; rul[31][1][1]=2; 
rul[31][1][2]=min; rul[31][1][3]=18.43; 
// 3. sekcja AND 32 reguly.
rul[31][2][0]=4; rul[31][2][1]=2; 
rul[31][2][2]=0.6655; rul[31][2][3]=max; 
// 4. sekcja AND 32 reguly.
rul[31][3][0]=3; rul[31][3][1]=2; 
rul[31][3][2]=1.368; rul[31][3][3]=max; 
// 5. sekcja AND 32 reguly.
rul[31][4][0]=6; rul[31][4][1]=2; 
rul[31][4][2]=8.215; rul[31][4][3]=max; 
// 6. sekcja AND 32 reguly.
rul[31][5][0]=8; rul[31][5][1]=2; 
rul[31][5][2]=1.0185; rul[31][5][3]=max; 
// 7. sekcja AND 32 reguly.
rul[31][6][0]=16; rul[31][6][1]=2; 
rul[31][6][2]=min; rul[31][6][3]=0.8145; 
// 8. sekcja AND 32 reguly.
rul[31][7][0]=33; rul[31][7][1]=4; 
rul[31][7][2]=min; rul[31][7][3]=73.918; rul[31][7][4]=73.918; rul[31][7][5]=137.781; 
// 9. sekcja AND 32 reguly.
rul[31][8][0]=7; rul[31][8][1]=4; 
rul[31][8][2]=min; rul[31][8][3]=6.171; rul[31][8][4]=6.171; rul[31][8][5]=8.48; 
// 10. sekcja AND 32 reguly.
rul[31][9][0]=18; rul[31][9][1]=2; 
rul[31][9][2]=min; rul[31][9][3]=0.9085; 
// 11. sekcja AND 32 reguly.
rul[31][10][0]=26; rul[31][10][1]=4; 
rul[31][10][2]=min; rul[31][10][3]=0.3215; rul[31][10][4]=0.3215; rul[31][10][5]=0.6065; 
// 12. sekcja AND 32 reguly.
rul[31][11][0]=10; rul[31][11][1]=4; 
rul[31][11][2]=min; rul[31][11][3]=1.5705; rul[31][11][4]=1.5705; rul[31][11][5]=max; 
// 13. sekcja AND 32 reguly.
rul[31][12][0]=21; rul[31][12][1]=2; 
rul[31][12][2]=min; rul[31][12][3]=0.1245; 
dl_reg[31]=13;
dec[31]=4; 
// 32. Koniec reguly
// 33. Regula
// 1. sekcja AND 33 reguly.
rul[32][0][0]=35; rul[32][0][1]=2; 
rul[32][0][2]=1; rul[32][0][3]=1; 
// 2. sekcja AND 33 reguly.
rul[32][1][0]=15; rul[32][1][1]=2; 
rul[32][1][2]=min; rul[32][1][3]=18.43; 
// 3. sekcja AND 33 reguly.
rul[32][2][0]=4; rul[32][2][1]=2; 
rul[32][2][2]=0.6655; rul[32][2][3]=max; 
// 4. sekcja AND 33 reguly.
rul[32][3][0]=3; rul[32][3][1]=2; 
rul[32][3][2]=1.368; rul[32][3][3]=max; 
// 5. sekcja AND 33 reguly.
rul[32][4][0]=6; rul[32][4][1]=2; 
rul[32][4][2]=8.215; rul[32][4][3]=max; 
// 6. sekcja AND 33 reguly.
rul[32][5][0]=8; rul[32][5][1]=2; 
rul[32][5][2]=1.0185; rul[32][5][3]=max; 
// 7. sekcja AND 33 reguly.
rul[32][6][0]=16; rul[32][6][1]=2; 
rul[32][6][2]=min; rul[32][6][3]=0.8145; 
// 8. sekcja AND 33 reguly.
rul[32][7][0]=21; rul[32][7][1]=4; 
rul[32][7][2]=0.1245; rul[32][7][3]=max; rul[32][7][4]=min; rul[32][7][5]=0.1245; 
// 9. sekcja AND 33 reguly.
rul[32][8][0]=10; rul[32][8][1]=2; 
rul[32][8][2]=1.5705; rul[32][8][3]=max; 
// 10. sekcja AND 33 reguly.
rul[32][9][0]=7; rul[32][9][1]=6; 
rul[32][9][2]=min; rul[32][9][3]=6.171; rul[32][9][4]=14.437; rul[32][9][5]=max; rul[32][9][6]=6.171; rul[32][9][7]=8.48; 
// 11. sekcja AND 33 reguly.
rul[32][10][0]=18; rul[32][10][1]=2; 
rul[32][10][2]=min; rul[32][10][3]=0.9085; 
// 12. sekcja AND 33 reguly.
rul[32][11][0]=26; rul[32][11][1]=2; 
rul[32][11][2]=min; rul[32][11][3]=0.3215; 
// 13. sekcja AND 33 reguly.
rul[32][12][0]=33; rul[32][12][1]=4; 
rul[32][12][2]=73.918; rul[32][12][3]=137.781; rul[32][12][4]=min; rul[32][12][5]=73.918; 
dl_reg[32]=13;
dec[32]=4; 
// 33. Koniec reguly
// 34. Regula
// 1. sekcja AND 34 reguly.
rul[33][0][0]=35; rul[33][0][1]=2; 
rul[33][0][2]=1; rul[33][0][3]=1; 
// 2. sekcja AND 34 reguly.
rul[33][1][0]=15; rul[33][1][1]=4; 
rul[33][1][2]=min; rul[33][1][3]=18.43; rul[33][1][4]=18.43; rul[33][1][5]=max; 
// 3. sekcja AND 34 reguly.
rul[33][2][0]=4; rul[33][2][1]=2; 
rul[33][2][2]=0.6655; rul[33][2][3]=max; 
// 4. sekcja AND 34 reguly.
rul[33][3][0]=3; rul[33][3][1]=2; 
rul[33][3][2]=1.368; rul[33][3][3]=max; 
// 5. sekcja AND 34 reguly.
rul[33][4][0]=6; rul[33][4][1]=2; 
rul[33][4][2]=8.215; rul[33][4][3]=max; 
// 6. sekcja AND 34 reguly.
rul[33][5][0]=8; rul[33][5][1]=2; 
rul[33][5][2]=1.0185; rul[33][5][3]=max; 
// 7. sekcja AND 34 reguly.
rul[33][6][0]=16; rul[33][6][1]=2; 
rul[33][6][2]=min; rul[33][6][3]=0.8145; 
// 8. sekcja AND 34 reguly.
rul[33][7][0]=33; rul[33][7][1]=2; 
rul[33][7][2]=min; rul[33][7][3]=73.918; 
// 9. sekcja AND 34 reguly.
rul[33][8][0]=10; rul[33][8][1]=2; 
rul[33][8][2]=1.5705; rul[33][8][3]=max; 
// 10. sekcja AND 34 reguly.
rul[33][9][0]=34; rul[33][9][1]=2; 
rul[33][9][2]=min; rul[33][9][3]=189.705; 
// 11. sekcja AND 34 reguly.
rul[33][10][0]=21; rul[33][10][1]=2; 
rul[33][10][2]=min; rul[33][10][3]=0.1245; 
// 12. sekcja AND 34 reguly.
rul[33][11][0]=18; rul[33][11][1]=4; 
rul[33][11][2]=0.9085; rul[33][11][3]=max; rul[33][11][4]=min; rul[33][11][5]=0.9085; 
// 13. sekcja AND 34 reguly.
rul[33][12][0]=7; rul[33][12][1]=6; 
rul[33][12][2]=8.48; rul[33][12][3]=14.437; rul[33][12][4]=6.171; rul[33][12][5]=8.48; rul[33][12][6]=14.437; rul[33][12][7]=max; 
dl_reg[33]=13;
dec[33]=4; 
// 34. Koniec reguly
// 35. Regula
// 1. sekcja AND 35 reguly.
rul[34][0][0]=35; rul[34][0][1]=2; 
rul[34][0][2]=1; rul[34][0][3]=1; 
// 2. sekcja AND 35 reguly.
rul[34][1][0]=15; rul[34][1][1]=2; 
rul[34][1][2]=min; rul[34][1][3]=18.43; 
// 3. sekcja AND 35 reguly.
rul[34][2][0]=7; rul[34][2][1]=2; 
rul[34][2][2]=min; rul[34][2][3]=6.171; 
// 4. sekcja AND 35 reguly.
rul[34][3][0]=4; rul[34][3][1]=2; 
rul[34][3][2]=0.6655; rul[34][3][3]=max; 
// 5. sekcja AND 35 reguly.
rul[34][4][0]=27; rul[34][4][1]=2; 
rul[34][4][2]=0.6905; rul[34][4][3]=max; 
// 6. sekcja AND 35 reguly.
rul[34][5][0]=8; rul[34][5][1]=2; 
rul[34][5][2]=min; rul[34][5][3]=1.0185; 
// 7. sekcja AND 35 reguly.
rul[34][6][0]=6; rul[34][6][1]=2; 
rul[34][6][2]=min; rul[34][6][3]=8.215; 
// 8. sekcja AND 35 reguly.
rul[34][7][0]=21; rul[34][7][1]=4; 
rul[34][7][2]=min; rul[34][7][3]=0.1245; rul[34][7][4]=0.1245; rul[34][7][5]=max; 
// 9. sekcja AND 35 reguly.
rul[34][8][0]=16; rul[34][8][1]=2; 
rul[34][8][2]=0.8145; rul[34][8][3]=max; 
// 10. sekcja AND 35 reguly.
rul[34][9][0]=18; rul[34][9][1]=2; 
rul[34][9][2]=min; rul[34][9][3]=0.9085; 
// 11. sekcja AND 35 reguly.
rul[34][10][0]=33; rul[34][10][1]=2; 
rul[34][10][2]=min; rul[34][10][3]=73.918; 
// 12. sekcja AND 35 reguly.
rul[34][11][0]=3; rul[34][11][1]=4; 
rul[34][11][2]=min; rul[34][11][3]=1.368; rul[34][11][4]=1.368; rul[34][11][5]=max; 
// 13. sekcja AND 35 reguly.
rul[34][12][0]=32; rul[34][12][1]=4; 
rul[34][12][2]=min; rul[34][12][3]=198.694; rul[34][12][4]=198.694; rul[34][12][5]=234.086; 
dl_reg[34]=13;
dec[34]=4; 
// 35. Koniec reguly
// 36. Regula
// 1. sekcja AND 36 reguly.
rul[35][0][0]=35; rul[35][0][1]=2; 
rul[35][0][2]=1; rul[35][0][3]=1; 
// 2. sekcja AND 36 reguly.
rul[35][1][0]=15; rul[35][1][1]=2; 
rul[35][1][2]=min; rul[35][1][3]=18.43; 
// 3. sekcja AND 36 reguly.
rul[35][2][0]=7; rul[35][2][1]=4; 
rul[35][2][2]=min; rul[35][2][3]=6.171; rul[35][2][4]=6.171; rul[35][2][5]=8.48; 
// 4. sekcja AND 36 reguly.
rul[35][3][0]=18; rul[35][3][1]=4; 
rul[35][3][2]=0.9085; rul[35][3][3]=max; rul[35][3][4]=min; rul[35][3][5]=0.9085; 
// 5. sekcja AND 36 reguly.
rul[35][4][0]=4; rul[35][4][1]=2; 
rul[35][4][2]=0.6655; rul[35][4][3]=max; 
// 6. sekcja AND 36 reguly.
rul[35][5][0]=27; rul[35][5][1]=2; 
rul[35][5][2]=0.6905; rul[35][5][3]=max; 
// 7. sekcja AND 36 reguly.
rul[35][6][0]=10; rul[35][6][1]=4; 
rul[35][6][2]=1.5705; rul[35][6][3]=max; rul[35][6][4]=min; rul[35][6][5]=1.5705; 
// 8. sekcja AND 36 reguly.
rul[35][7][0]=21; rul[35][7][1]=4; 
rul[35][7][2]=min; rul[35][7][3]=0.1245; rul[35][7][4]=0.1245; rul[35][7][5]=max; 
// 9. sekcja AND 36 reguly.
rul[35][8][0]=8; rul[35][8][1]=2; 
rul[35][8][2]=min; rul[35][8][3]=1.0185; 
// 10. sekcja AND 36 reguly.
rul[35][9][0]=6; rul[35][9][1]=2; 
rul[35][9][2]=min; rul[35][9][3]=8.215; 
// 11. sekcja AND 36 reguly.
rul[35][10][0]=16; rul[35][10][1]=4; 
rul[35][10][2]=min; rul[35][10][3]=0.8145; rul[35][10][4]=0.8145; rul[35][10][5]=max; 
// 12. sekcja AND 36 reguly.
rul[35][11][0]=3; rul[35][11][1]=4; 
rul[35][11][2]=min; rul[35][11][3]=1.368; rul[35][11][4]=1.368; rul[35][11][5]=max; 
// 13. sekcja AND 36 reguly.
rul[35][12][0]=26; rul[35][12][1]=4; 
rul[35][12][2]=0.8585; rul[35][12][3]=max; rul[35][12][4]=0.6065; rul[35][12][5]=0.8585; 
// 14. sekcja AND 36 reguly.
rul[35][13][0]=32; rul[35][13][1]=2; 
rul[35][13][2]=198.694; rul[35][13][3]=234.086; 
dl_reg[35]=14;
dec[35]=4; 
// 36. Koniec reguly
// 37. Regula
// 1. sekcja AND 37 reguly.
rul[36][0][0]=35; rul[36][0][1]=2; 
rul[36][0][2]=1; rul[36][0][3]=1; 
// 2. sekcja AND 37 reguly.
rul[36][1][0]=15; rul[36][1][1]=2; 
rul[36][1][2]=min; rul[36][1][3]=18.43; 
// 3. sekcja AND 37 reguly.
rul[36][2][0]=7; rul[36][2][1]=2; 
rul[36][2][2]=min; rul[36][2][3]=6.171; 
// 4. sekcja AND 37 reguly.
rul[36][3][0]=18; rul[36][3][1]=2; 
rul[36][3][2]=0.9085; rul[36][3][3]=max; 
// 5. sekcja AND 37 reguly.
rul[36][4][0]=3; rul[36][4][1]=2; 
rul[36][4][2]=1.368; rul[36][4][3]=max; 
// 6. sekcja AND 37 reguly.
rul[36][5][0]=4; rul[36][5][1]=2; 
rul[36][5][2]=0.6655; rul[36][5][3]=max; 
// 7. sekcja AND 37 reguly.
rul[36][6][0]=26; rul[36][6][1]=2; 
rul[36][6][2]=0.3215; rul[36][6][3]=0.6065; 
// 8. sekcja AND 37 reguly.
rul[36][7][0]=6; rul[36][7][1]=4; 
rul[36][7][2]=8.215; rul[36][7][3]=max; rul[36][7][4]=min; rul[36][7][5]=8.215; 
// 9. sekcja AND 37 reguly.
rul[36][8][0]=16; rul[36][8][1]=4; 
rul[36][8][2]=min; rul[36][8][3]=0.8145; rul[36][8][4]=0.8145; rul[36][8][5]=max; 
// 10. sekcja AND 37 reguly.
rul[36][9][0]=8; rul[36][9][1]=4; 
rul[36][9][2]=1.0185; rul[36][9][3]=max; rul[36][9][4]=min; rul[36][9][5]=1.0185; 
// 11. sekcja AND 37 reguly.
rul[36][10][0]=21; rul[36][10][1]=2; 
rul[36][10][2]=0.1245; rul[36][10][3]=max; 
// 12. sekcja AND 37 reguly.
rul[36][11][0]=32; rul[36][11][1]=4; 
rul[36][11][2]=198.694; rul[36][11][3]=234.086; rul[36][11][4]=min; rul[36][11][5]=198.694; 
dl_reg[36]=12;
dec[36]=4; 
// 37. Koniec reguly
// 38. Regula
// 1. sekcja AND 38 reguly.
rul[37][0][0]=35; rul[37][0][1]=2; 
rul[37][0][2]=1; rul[37][0][3]=1; 
// 2. sekcja AND 38 reguly.
rul[37][1][0]=18; rul[37][1][1]=2; 
rul[37][1][2]=0.9085; rul[37][1][3]=max; 
// 3. sekcja AND 38 reguly.
rul[37][2][0]=15; rul[37][2][1]=4; 
rul[37][2][2]=min; rul[37][2][3]=18.43; rul[37][2][4]=18.43; rul[37][2][5]=max; 
// 4. sekcja AND 38 reguly.
rul[37][3][0]=16; rul[37][3][1]=2; 
rul[37][3][2]=0.8145; rul[37][3][3]=max; 
// 5. sekcja AND 38 reguly.
rul[37][4][0]=3; rul[37][4][1]=4; 
rul[37][4][2]=1.368; rul[37][4][3]=max; rul[37][4][4]=min; rul[37][4][5]=1.368; 
// 6. sekcja AND 38 reguly.
rul[37][5][0]=6; rul[37][5][1]=2; 
rul[37][5][2]=8.215; rul[37][5][3]=max; 
// 7. sekcja AND 38 reguly.
rul[37][6][0]=8; rul[37][6][1]=2; 
rul[37][6][2]=1.0185; rul[37][6][3]=max; 
// 8. sekcja AND 38 reguly.
rul[37][7][0]=10; rul[37][7][1]=2; 
rul[37][7][2]=1.5705; rul[37][7][3]=max; 
// 9. sekcja AND 38 reguly.
rul[37][8][0]=4; rul[37][8][1]=2; 
rul[37][8][2]=min; rul[37][8][3]=0.6655; 
// 10. sekcja AND 38 reguly.
rul[37][9][0]=7; rul[37][9][1]=2; 
rul[37][9][2]=6.171; rul[37][9][3]=8.48; 
// 11. sekcja AND 38 reguly.
rul[37][10][0]=34; rul[37][10][1]=4; 
rul[37][10][2]=min; rul[37][10][3]=189.705; rul[37][10][4]=240.981; rul[37][10][5]=max; 
dl_reg[37]=11;
dec[37]=3; 
// 38. Koniec reguly
// 39. Regula
// 1. sekcja AND 39 reguly.
rul[38][0][0]=18; rul[38][0][1]=2; 
rul[38][0][2]=0.9085; rul[38][0][3]=max; 
// 2. sekcja AND 39 reguly.
rul[38][1][0]=6; rul[38][1][1]=2; 
rul[38][1][2]=8.215; rul[38][1][3]=max; 
// 3. sekcja AND 39 reguly.
rul[38][2][0]=8; rul[38][2][1]=2; 
rul[38][2][2]=1.0185; rul[38][2][3]=max; 
// 4. sekcja AND 39 reguly.
rul[38][3][0]=3; rul[38][3][1]=2; 
rul[38][3][2]=1.368; rul[38][3][3]=max; 
// 5. sekcja AND 39 reguly.
rul[38][4][0]=32; rul[38][4][1]=2; 
rul[38][4][2]=234.086; rul[38][4][3]=max; 
// 6. sekcja AND 39 reguly.
rul[38][5][0]=10; rul[38][5][1]=2; 
rul[38][5][2]=1.5705; rul[38][5][3]=max; 
// 7. sekcja AND 39 reguly.
rul[38][6][0]=15; rul[38][6][1]=4; 
rul[38][6][2]=18.43; rul[38][6][3]=max; rul[38][6][4]=min; rul[38][6][5]=18.43; 
// 8. sekcja AND 39 reguly.
rul[38][7][0]=33; rul[38][7][1]=4; 
rul[38][7][2]=137.781; rul[38][7][3]=max; rul[38][7][4]=73.918; rul[38][7][5]=137.781; 
// 9. sekcja AND 39 reguly.
rul[38][8][0]=4; rul[38][8][1]=2; 
rul[38][8][2]=min; rul[38][8][3]=0.6655; 
// 10. sekcja AND 39 reguly.
rul[38][9][0]=7; rul[38][9][1]=2; 
rul[38][9][2]=6.171; rul[38][9][3]=8.48; 
dl_reg[38]=10;
dec[38]=3; 
// 39. Koniec reguly
// 40. Regula
// 1. sekcja AND 40 reguly.
rul[39][0][0]=3; rul[39][0][1]=2; 
rul[39][0][2]=1.368; rul[39][0][3]=max; 
// 2. sekcja AND 40 reguly.
rul[39][1][0]=6; rul[39][1][1]=2; 
rul[39][1][2]=8.215; rul[39][1][3]=max; 
// 3. sekcja AND 40 reguly.
rul[39][2][0]=8; rul[39][2][1]=2; 
rul[39][2][2]=1.0185; rul[39][2][3]=max; 
// 4. sekcja AND 40 reguly.
rul[39][3][0]=16; rul[39][3][1]=2; 
rul[39][3][2]=min; rul[39][3][3]=0.8145; 
// 5. sekcja AND 40 reguly.
rul[39][4][0]=21; rul[39][4][1]=2; 
rul[39][4][2]=0.1245; rul[39][4][3]=max; 
// 6. sekcja AND 40 reguly.
rul[39][5][0]=27; rul[39][5][1]=2; 
rul[39][5][2]=min; rul[39][5][3]=0.5825; 
// 7. sekcja AND 40 reguly.
rul[39][6][0]=4; rul[39][6][1]=4; 
rul[39][6][2]=0.6655; rul[39][6][3]=max; rul[39][6][4]=min; rul[39][6][5]=0.6655; 
// 8. sekcja AND 40 reguly.
rul[39][7][0]=7; rul[39][7][1]=2; 
rul[39][7][2]=8.48; rul[39][7][3]=14.437; 
// 9. sekcja AND 40 reguly.
rul[39][8][0]=10; rul[39][8][1]=2; 
rul[39][8][2]=1.5705; rul[39][8][3]=max; 
// 10. sekcja AND 40 reguly.
rul[39][9][0]=32; rul[39][9][1]=2; 
rul[39][9][2]=234.086; rul[39][9][3]=max; 
// 11. sekcja AND 40 reguly.
rul[39][10][0]=15; rul[39][10][1]=2; 
rul[39][10][2]=18.43; rul[39][10][3]=max; 
dl_reg[39]=11;
dec[39]=3; 
// 40. Koniec reguly
// 41. Regula
// 1. sekcja AND 41 reguly.
rul[40][0][0]=35; rul[40][0][1]=2; 
rul[40][0][2]=1; rul[40][0][3]=1; 
// 2. sekcja AND 41 reguly.
rul[40][1][0]=6; rul[40][1][1]=2; 
rul[40][1][2]=8.215; rul[40][1][3]=max; 
// 3. sekcja AND 41 reguly.
rul[40][2][0]=8; rul[40][2][1]=2; 
rul[40][2][2]=1.0185; rul[40][2][3]=max; 
// 4. sekcja AND 41 reguly.
rul[40][3][0]=4; rul[40][3][1]=4; 
rul[40][3][2]=min; rul[40][3][3]=0.6655; rul[40][3][4]=0.6655; rul[40][3][5]=max; 
// 5. sekcja AND 41 reguly.
rul[40][4][0]=3; rul[40][4][1]=2; 
rul[40][4][2]=1.368; rul[40][4][3]=max; 
// 6. sekcja AND 41 reguly.
rul[40][5][0]=21; rul[40][5][1]=2; 
rul[40][5][2]=0.1245; rul[40][5][3]=max; 
// 7. sekcja AND 41 reguly.
rul[40][6][0]=27; rul[40][6][1]=2; 
rul[40][6][2]=min; rul[40][6][3]=0.5825; 
// 8. sekcja AND 41 reguly.
rul[40][7][0]=16; rul[40][7][1]=2; 
rul[40][7][2]=min; rul[40][7][3]=0.8145; 
// 9. sekcja AND 41 reguly.
rul[40][8][0]=15; rul[40][8][1]=2; 
rul[40][8][2]=18.43; rul[40][8][3]=max; 
// 10. sekcja AND 41 reguly.
rul[40][9][0]=33; rul[40][9][1]=2; 
rul[40][9][2]=min; rul[40][9][3]=73.918; 
// 11. sekcja AND 41 reguly.
rul[40][10][0]=32; rul[40][10][1]=4; 
rul[40][10][2]=min; rul[40][10][3]=198.694; rul[40][10][4]=198.694; rul[40][10][5]=234.086; 
// 12. sekcja AND 41 reguly.
rul[40][11][0]=10; rul[40][11][1]=4; 
rul[40][11][2]=1.5705; rul[40][11][3]=max; rul[40][11][4]=min; rul[40][11][5]=1.5705; 
// 13. sekcja AND 41 reguly.
rul[40][12][0]=18; rul[40][12][1]=2; 
rul[40][12][2]=min; rul[40][12][3]=0.9085; 
// 14. sekcja AND 41 reguly.
rul[40][13][0]=7; rul[40][13][1]=4; 
rul[40][13][2]=6.171; rul[40][13][3]=8.48; rul[40][13][4]=min; rul[40][13][5]=6.171; 
dl_reg[40]=14;
dec[40]=2; 
// 41. Koniec reguly
// 42. Regula
// 1. sekcja AND 42 reguly.
rul[41][0][0]=35; rul[41][0][1]=2; 
rul[41][0][2]=1; rul[41][0][3]=1; 
// 2. sekcja AND 42 reguly.
rul[41][1][0]=18; rul[41][1][1]=4; 
rul[41][1][2]=0.9085; rul[41][1][3]=max; rul[41][1][4]=min; rul[41][1][5]=0.9085; 
// 3. sekcja AND 42 reguly.
rul[41][2][0]=6; rul[41][2][1]=2; 
rul[41][2][2]=8.215; rul[41][2][3]=max; 
// 4. sekcja AND 42 reguly.
rul[41][3][0]=8; rul[41][3][1]=4; 
rul[41][3][2]=1.0185; rul[41][3][3]=max; rul[41][3][4]=min; rul[41][3][5]=1.0185; 
// 5. sekcja AND 42 reguly.
rul[41][4][0]=4; rul[41][4][1]=2; 
rul[41][4][2]=min; rul[41][4][3]=0.6655; 
// 6. sekcja AND 42 reguly.
rul[41][5][0]=3; rul[41][5][1]=2; 
rul[41][5][2]=1.368; rul[41][5][3]=max; 
// 7. sekcja AND 42 reguly.
rul[41][6][0]=21; rul[41][6][1]=4; 
rul[41][6][2]=0.1245; rul[41][6][3]=max; rul[41][6][4]=min; rul[41][6][5]=0.1245; 
// 8. sekcja AND 42 reguly.
rul[41][7][0]=27; rul[41][7][1]=4; 
rul[41][7][2]=min; rul[41][7][3]=0.5825; rul[41][7][4]=0.5825; rul[41][7][5]=0.6905; 
// 9. sekcja AND 42 reguly.
rul[41][8][0]=16; rul[41][8][1]=2; 
rul[41][8][2]=min; rul[41][8][3]=0.8145; 
// 10. sekcja AND 42 reguly.
rul[41][9][0]=32; rul[41][9][1]=2; 
rul[41][9][2]=min; rul[41][9][3]=198.694; 
// 11. sekcja AND 42 reguly.
rul[41][10][0]=10; rul[41][10][1]=2; 
rul[41][10][2]=1.5705; rul[41][10][3]=max; 
// 12. sekcja AND 42 reguly.
rul[41][11][0]=15; rul[41][11][1]=4; 
rul[41][11][2]=18.43; rul[41][11][3]=max; rul[41][11][4]=min; rul[41][11][5]=18.43; 
// 13. sekcja AND 42 reguly.
rul[41][12][0]=26; rul[41][12][1]=4; 
rul[41][12][2]=0.3215; rul[41][12][3]=0.6065; rul[41][12][4]=0.6065; rul[41][12][5]=0.8585; 
// 14. sekcja AND 42 reguly.
rul[41][13][0]=34; rul[41][13][1]=6; 
rul[41][13][2]=240.981; rul[41][13][3]=max; rul[41][13][4]=189.705; rul[41][13][5]=240.981; rul[41][13][6]=min; rul[41][13][7]=189.705; 
// 15. sekcja AND 42 reguly.
rul[41][14][0]=33; rul[41][14][1]=4; 
rul[41][14][2]=73.918; rul[41][14][3]=137.781; rul[41][14][4]=min; rul[41][14][5]=73.918; 
dl_reg[41]=15;
dec[41]=2; 
// 42. Koniec reguly
// 43. Regula
// 1. sekcja AND 43 reguly.
rul[42][0][0]=35; rul[42][0][1]=2; 
rul[42][0][2]=1; rul[42][0][3]=1; 
// 2. sekcja AND 43 reguly.
rul[42][1][0]=18; rul[42][1][1]=4; 
rul[42][1][2]=0.9085; rul[42][1][3]=max; rul[42][1][4]=min; rul[42][1][5]=0.9085; 
// 3. sekcja AND 43 reguly.
rul[42][2][0]=6; rul[42][2][1]=2; 
rul[42][2][2]=8.215; rul[42][2][3]=max; 
// 4. sekcja AND 43 reguly.
rul[42][3][0]=8; rul[42][3][1]=2; 
rul[42][3][2]=1.0185; rul[42][3][3]=max; 
// 5. sekcja AND 43 reguly.
rul[42][4][0]=33; rul[42][4][1]=2; 
rul[42][4][2]=min; rul[42][4][3]=73.918; 
// 6. sekcja AND 43 reguly.
rul[42][5][0]=3; rul[42][5][1]=4; 
rul[42][5][2]=1.368; rul[42][5][3]=max; rul[42][5][4]=min; rul[42][5][5]=1.368; 
// 7. sekcja AND 43 reguly.
rul[42][6][0]=4; rul[42][6][1]=2; 
rul[42][6][2]=min; rul[42][6][3]=0.6655; 
// 8. sekcja AND 43 reguly.
rul[42][7][0]=27; rul[42][7][1]=4; 
rul[42][7][2]=min; rul[42][7][3]=0.5825; rul[42][7][4]=0.5825; rul[42][7][5]=0.6905; 
// 9. sekcja AND 43 reguly.
rul[42][8][0]=16; rul[42][8][1]=2; 
rul[42][8][2]=min; rul[42][8][3]=0.8145; 
// 10. sekcja AND 43 reguly.
rul[42][9][0]=21; rul[42][9][1]=2; 
rul[42][9][2]=0.1245; rul[42][9][3]=max; 
// 11. sekcja AND 43 reguly.
rul[42][10][0]=15; rul[42][10][1]=4; 
rul[42][10][2]=18.43; rul[42][10][3]=max; rul[42][10][4]=min; rul[42][10][5]=18.43; 
// 12. sekcja AND 43 reguly.
rul[42][11][0]=32; rul[42][11][1]=6; 
rul[42][11][2]=min; rul[42][11][3]=198.694; rul[42][11][4]=198.694; rul[42][11][5]=234.086; rul[42][11][6]=234.086; rul[42][11][7]=max; 
// 13. sekcja AND 43 reguly.
rul[42][12][0]=10; rul[42][12][1]=4; 
rul[42][12][2]=1.5705; rul[42][12][3]=max; rul[42][12][4]=min; rul[42][12][5]=1.5705; 
// 14. sekcja AND 43 reguly.
rul[42][13][0]=26; rul[42][13][1]=4; 
rul[42][13][2]=0.3215; rul[42][13][3]=0.6065; rul[42][13][4]=0.6065; rul[42][13][5]=0.8585; 
dl_reg[42]=14;
dec[42]=2; 
// 43. Koniec reguly
// 44. Regula
// 1. sekcja AND 44 reguly.
rul[43][0][0]=35; rul[43][0][1]=2; 
rul[43][0][2]=1; rul[43][0][3]=1; 
// 2. sekcja AND 44 reguly.
rul[43][1][0]=18; rul[43][1][1]=2; 
rul[43][1][2]=0.9085; rul[43][1][3]=max; 
// 3. sekcja AND 44 reguly.
rul[43][2][0]=15; rul[43][2][1]=2; 
rul[43][2][2]=min; rul[43][2][3]=18.43; 
// 4. sekcja AND 44 reguly.
rul[43][3][0]=16; rul[43][3][1]=2; 
rul[43][3][2]=0.8145; rul[43][3][3]=max; 
// 5. sekcja AND 44 reguly.
rul[43][4][0]=33; rul[43][4][1]=4; 
rul[43][4][2]=min; rul[43][4][3]=73.918; rul[43][4][4]=73.918; rul[43][4][5]=137.781; 
// 6. sekcja AND 44 reguly.
rul[43][5][0]=20; rul[43][5][1]=2; 
rul[43][5][2]=650.372; rul[43][5][3]=max; 
// 7. sekcja AND 44 reguly.
rul[43][6][0]=21; rul[43][6][1]=2; 
rul[43][6][2]=min; rul[43][6][3]=0.1245; 
// 8. sekcja AND 44 reguly.
rul[43][7][0]=7; rul[43][7][1]=2; 
rul[43][7][2]=min; rul[43][7][3]=6.171; 
// 9. sekcja AND 44 reguly.
rul[43][8][0]=6; rul[43][8][1]=2; 
rul[43][8][2]=min; rul[43][8][3]=8.215; 
// 10. sekcja AND 44 reguly.
rul[43][9][0]=4; rul[43][9][1]=2; 
rul[43][9][2]=min; rul[43][9][3]=0.6655; 
// 11. sekcja AND 44 reguly.
rul[43][10][0]=26; rul[43][10][1]=4; 
rul[43][10][2]=0.8585; rul[43][10][3]=max; rul[43][10][4]=0.6065; rul[43][10][5]=0.8585; 
// 12. sekcja AND 44 reguly.
rul[43][11][0]=10; rul[43][11][1]=2; 
rul[43][11][2]=1.5705; rul[43][11][3]=max; 
// 13. sekcja AND 44 reguly.
rul[43][12][0]=3; rul[43][12][1]=2; 
rul[43][12][2]=min; rul[43][12][3]=1.368; 
dl_reg[43]=13;
dec[43]=2; 
// 44. Koniec reguly
// 45. Regula
// 1. sekcja AND 45 reguly.
rul[44][0][0]=35; rul[44][0][1]=2; 
rul[44][0][2]=1; rul[44][0][3]=1; 
// 2. sekcja AND 45 reguly.
rul[44][1][0]=18; rul[44][1][1]=4; 
rul[44][1][2]=0.9085; rul[44][1][3]=max; rul[44][1][4]=min; rul[44][1][5]=0.9085; 
// 3. sekcja AND 45 reguly.
rul[44][2][0]=6; rul[44][2][1]=2; 
rul[44][2][2]=8.215; rul[44][2][3]=max; 
// 4. sekcja AND 45 reguly.
rul[44][3][0]=33; rul[44][3][1]=2; 
rul[44][3][2]=min; rul[44][3][3]=73.918; 
// 5. sekcja AND 45 reguly.
rul[44][4][0]=8; rul[44][4][1]=2; 
rul[44][4][2]=1.0185; rul[44][4][3]=max; 
// 6. sekcja AND 45 reguly.
rul[44][5][0]=3; rul[44][5][1]=2; 
rul[44][5][2]=1.368; rul[44][5][3]=max; 
// 7. sekcja AND 45 reguly.
rul[44][6][0]=4; rul[44][6][1]=2; 
rul[44][6][2]=min; rul[44][6][3]=0.6655; 
// 8. sekcja AND 45 reguly.
rul[44][7][0]=10; rul[44][7][1]=4; 
rul[44][7][2]=min; rul[44][7][3]=1.5705; rul[44][7][4]=1.5705; rul[44][7][5]=max; 
// 9. sekcja AND 45 reguly.
rul[44][8][0]=15; rul[44][8][1]=2; 
rul[44][8][2]=18.43; rul[44][8][3]=max; 
// 10. sekcja AND 45 reguly.
rul[44][9][0]=32; rul[44][9][1]=4; 
rul[44][9][2]=234.086; rul[44][9][3]=max; rul[44][9][4]=min; rul[44][9][5]=198.694; 
// 11. sekcja AND 45 reguly.
rul[44][10][0]=7; rul[44][10][1]=2; 
rul[44][10][2]=6.171; rul[44][10][3]=8.48; 
dl_reg[44]=11;
dec[44]=2; 
// 45. Koniec reguly
// 46. Regula
// 1. sekcja AND 46 reguly.
rul[45][0][0]=35; rul[45][0][1]=2; 
rul[45][0][2]=1; rul[45][0][3]=1; 
// 2. sekcja AND 46 reguly.
rul[45][1][0]=15; rul[45][1][1]=2; 
rul[45][1][2]=min; rul[45][1][3]=18.43; 
// 3. sekcja AND 46 reguly.
rul[45][2][0]=18; rul[45][2][1]=2; 
rul[45][2][2]=0.9085; rul[45][2][3]=max; 
// 4. sekcja AND 46 reguly.
rul[45][3][0]=16; rul[45][3][1]=2; 
rul[45][3][2]=0.8145; rul[45][3][3]=max; 
// 5. sekcja AND 46 reguly.
rul[45][4][0]=8; rul[45][4][1]=2; 
rul[45][4][2]=1.0185; rul[45][4][3]=max; 
// 6. sekcja AND 46 reguly.
rul[45][5][0]=4; rul[45][5][1]=2; 
rul[45][5][2]=min; rul[45][5][3]=0.6655; 
// 7. sekcja AND 46 reguly.
rul[45][6][0]=33; rul[45][6][1]=2; 
rul[45][6][2]=min; rul[45][6][3]=73.918; 
// 8. sekcja AND 46 reguly.
rul[45][7][0]=20; rul[45][7][1]=2; 
rul[45][7][2]=650.372; rul[45][7][3]=max; 
// 9. sekcja AND 46 reguly.
rul[45][8][0]=21; rul[45][8][1]=2; 
rul[45][8][2]=min; rul[45][8][3]=0.1245; 
// 10. sekcja AND 46 reguly.
rul[45][9][0]=26; rul[45][9][1]=2; 
rul[45][9][2]=0.8585; rul[45][9][3]=max; 
// 11. sekcja AND 46 reguly.
rul[45][10][0]=3; rul[45][10][1]=2; 
rul[45][10][2]=min; rul[45][10][3]=1.368; 
// 12. sekcja AND 46 reguly.
rul[45][11][0]=6; rul[45][11][1]=2; 
rul[45][11][2]=min; rul[45][11][3]=8.215; 
dl_reg[45]=12;
dec[45]=2; 
// 46. Koniec reguly
// 47. Regula
// 1. sekcja AND 47 reguly.
rul[46][0][0]=6; rul[46][0][1]=2; 
rul[46][0][2]=8.215; rul[46][0][3]=max; 
// 2. sekcja AND 47 reguly.
rul[46][1][0]=8; rul[46][1][1]=2; 
rul[46][1][2]=1.0185; rul[46][1][3]=max; 
// 3. sekcja AND 47 reguly.
rul[46][2][0]=3; rul[46][2][1]=2; 
rul[46][2][2]=1.368; rul[46][2][3]=max; 
// 4. sekcja AND 47 reguly.
rul[46][3][0]=4; rul[46][3][1]=2; 
rul[46][3][2]=0.6655; rul[46][3][3]=max; 
// 5. sekcja AND 47 reguly.
rul[46][4][0]=16; rul[46][4][1]=4; 
rul[46][4][2]=min; rul[46][4][3]=0.8145; rul[46][4][4]=0.8145; rul[46][4][5]=max; 
// 6. sekcja AND 47 reguly.
rul[46][5][0]=32; rul[46][5][1]=2; 
rul[46][5][2]=234.086; rul[46][5][3]=max; 
// 7. sekcja AND 47 reguly.
rul[46][6][0]=21; rul[46][6][1]=2; 
rul[46][6][2]=0.1245; rul[46][6][3]=max; 
// 8. sekcja AND 47 reguly.
rul[46][7][0]=20; rul[46][7][1]=6; 
rul[46][7][2]=356.734; rul[46][7][3]=488.907; rul[46][7][4]=220.22; rul[46][7][5]=356.734; rul[46][7][6]=min; rul[46][7][7]=220.22; 
// 9. sekcja AND 47 reguly.
rul[46][8][0]=33; rul[46][8][1]=4; 
rul[46][8][2]=137.781; rul[46][8][3]=max; rul[46][8][4]=min; rul[46][8][5]=73.918; 
// 10. sekcja AND 47 reguly.
rul[46][9][0]=7; rul[46][9][1]=2; 
rul[46][9][2]=14.437; rul[46][9][3]=max; 
dl_reg[46]=10;
dec[46]=5; 
// 47. Koniec reguly
// 48. Regula
// 1. sekcja AND 48 reguly.
rul[47][0][0]=35; rul[47][0][1]=2; 
rul[47][0][2]=1; rul[47][0][3]=1; 
// 2. sekcja AND 48 reguly.
rul[47][1][0]=15; rul[47][1][1]=2; 
rul[47][1][2]=min; rul[47][1][3]=18.43; 
// 3. sekcja AND 48 reguly.
rul[47][2][0]=4; rul[47][2][1]=2; 
rul[47][2][2]=0.6655; rul[47][2][3]=max; 
// 4. sekcja AND 48 reguly.
rul[47][3][0]=3; rul[47][3][1]=2; 
rul[47][3][2]=1.368; rul[47][3][3]=max; 
// 5. sekcja AND 48 reguly.
rul[47][4][0]=6; rul[47][4][1]=4; 
rul[47][4][2]=8.215; rul[47][4][3]=max; rul[47][4][4]=min; rul[47][4][5]=8.215; 
// 6. sekcja AND 48 reguly.
rul[47][5][0]=8; rul[47][5][1]=4; 
rul[47][5][2]=1.0185; rul[47][5][3]=max; rul[47][5][4]=min; rul[47][5][5]=1.0185; 
// 7. sekcja AND 48 reguly.
rul[47][6][0]=16; rul[47][6][1]=2; 
rul[47][6][2]=min; rul[47][6][3]=0.8145; 
// 8. sekcja AND 48 reguly.
rul[47][7][0]=18; rul[47][7][1]=2; 
rul[47][7][2]=0.9085; rul[47][7][3]=max; 
// 9. sekcja AND 48 reguly.
rul[47][8][0]=26; rul[47][8][1]=2; 
rul[47][8][2]=0.3215; rul[47][8][3]=0.6065; 
// 10. sekcja AND 48 reguly.
rul[47][9][0]=21; rul[47][9][1]=4; 
rul[47][9][2]=0.1245; rul[47][9][3]=max; rul[47][9][4]=min; rul[47][9][5]=0.1245; 
// 11. sekcja AND 48 reguly.
rul[47][10][0]=10; rul[47][10][1]=4; 
rul[47][10][2]=1.5705; rul[47][10][3]=max; rul[47][10][4]=min; rul[47][10][5]=1.5705; 
// 12. sekcja AND 48 reguly.
rul[47][11][0]=27; rul[47][11][1]=2; 
rul[47][11][2]=0.5825; rul[47][11][3]=0.6905; 
// 13. sekcja AND 48 reguly.
rul[47][12][0]=7; rul[47][12][1]=2; 
rul[47][12][2]=min; rul[47][12][3]=6.171; 
dl_reg[47]=13;
dec[47]=4; 
// 48. Koniec reguly
// 49. Regula
// 1. sekcja AND 49 reguly.
rul[48][0][0]=35; rul[48][0][1]=2; 
rul[48][0][2]=1; rul[48][0][3]=1; 
// 2. sekcja AND 49 reguly.
rul[48][1][0]=15; rul[48][1][1]=2; 
rul[48][1][2]=min; rul[48][1][3]=18.43; 
// 3. sekcja AND 49 reguly.
rul[48][2][0]=7; rul[48][2][1]=2; 
rul[48][2][2]=min; rul[48][2][3]=6.171; 
// 4. sekcja AND 49 reguly.
rul[48][3][0]=18; rul[48][3][1]=4; 
rul[48][3][2]=0.9085; rul[48][3][3]=max; rul[48][3][4]=min; rul[48][3][5]=0.9085; 
// 5. sekcja AND 49 reguly.
rul[48][4][0]=27; rul[48][4][1]=2; 
rul[48][4][2]=0.6905; rul[48][4][3]=max; 
// 6. sekcja AND 49 reguly.
rul[48][5][0]=6; rul[48][5][1]=2; 
rul[48][5][2]=min; rul[48][5][3]=8.215; 
// 7. sekcja AND 49 reguly.
rul[48][6][0]=8; rul[48][6][1]=2; 
rul[48][6][2]=min; rul[48][6][3]=1.0185; 
// 8. sekcja AND 49 reguly.
rul[48][7][0]=16; rul[48][7][1]=2; 
rul[48][7][2]=0.8145; rul[48][7][3]=max; 
// 9. sekcja AND 49 reguly.
rul[48][8][0]=21; rul[48][8][1]=4; 
rul[48][8][2]=min; rul[48][8][3]=0.1245; rul[48][8][4]=0.1245; rul[48][8][5]=max; 
// 10. sekcja AND 49 reguly.
rul[48][9][0]=33; rul[48][9][1]=4; 
rul[48][9][2]=min; rul[48][9][3]=73.918; rul[48][9][4]=73.918; rul[48][9][5]=137.781; 
// 11. sekcja AND 49 reguly.
rul[48][10][0]=4; rul[48][10][1]=2; 
rul[48][10][2]=0.6655; rul[48][10][3]=max; 
// 12. sekcja AND 49 reguly.
rul[48][11][0]=26; rul[48][11][1]=4; 
rul[48][11][2]=0.6065; rul[48][11][3]=0.8585; rul[48][11][4]=0.3215; rul[48][11][5]=0.6065; 
// 13. sekcja AND 49 reguly.
rul[48][12][0]=3; rul[48][12][1]=2; 
rul[48][12][2]=1.368; rul[48][12][3]=max; 
// 14. sekcja AND 49 reguly.
rul[48][13][0]=10; rul[48][13][1]=2; 
rul[48][13][2]=min; rul[48][13][3]=1.5705; 
dl_reg[48]=14;
dec[48]=4; 
// 49. Koniec reguly
// 50. Regula
// 1. sekcja AND 50 reguly.
rul[49][0][0]=35; rul[49][0][1]=2; 
rul[49][0][2]=1; rul[49][0][3]=1; 
// 2. sekcja AND 50 reguly.
rul[49][1][0]=15; rul[49][1][1]=2; 
rul[49][1][2]=min; rul[49][1][3]=18.43; 
// 3. sekcja AND 50 reguly.
rul[49][2][0]=7; rul[49][2][1]=2; 
rul[49][2][2]=min; rul[49][2][3]=6.171; 
// 4. sekcja AND 50 reguly.
rul[49][3][0]=18; rul[49][3][1]=4; 
rul[49][3][2]=0.9085; rul[49][3][3]=max; rul[49][3][4]=min; rul[49][3][5]=0.9085; 
// 5. sekcja AND 50 reguly.
rul[49][4][0]=27; rul[49][4][1]=2; 
rul[49][4][2]=0.6905; rul[49][4][3]=max; 
// 6. sekcja AND 50 reguly.
rul[49][5][0]=6; rul[49][5][1]=2; 
rul[49][5][2]=min; rul[49][5][3]=8.215; 
// 7. sekcja AND 50 reguly.
rul[49][6][0]=8; rul[49][6][1]=2; 
rul[49][6][2]=min; rul[49][6][3]=1.0185; 
// 8. sekcja AND 50 reguly.
rul[49][7][0]=16; rul[49][7][1]=4; 
rul[49][7][2]=0.8145; rul[49][7][3]=max; rul[49][7][4]=min; rul[49][7][5]=0.8145; 
// 9. sekcja AND 50 reguly.
rul[49][8][0]=21; rul[49][8][1]=4; 
rul[49][8][2]=min; rul[49][8][3]=0.1245; rul[49][8][4]=0.1245; rul[49][8][5]=max; 
// 10. sekcja AND 50 reguly.
rul[49][9][0]=33; rul[49][9][1]=2; 
rul[49][9][2]=min; rul[49][9][3]=73.918; 
// 11. sekcja AND 50 reguly.
rul[49][10][0]=10; rul[49][10][1]=2; 
rul[49][10][2]=1.5705; rul[49][10][3]=max; 
// 12. sekcja AND 50 reguly.
rul[49][11][0]=4; rul[49][11][1]=2; 
rul[49][11][2]=0.6655; rul[49][11][3]=max; 
// 13. sekcja AND 50 reguly.
rul[49][12][0]=34; rul[49][12][1]=2; 
rul[49][12][2]=189.705; rul[49][12][3]=240.981; 
// 14. sekcja AND 50 reguly.
rul[49][13][0]=20; rul[49][13][1]=6; 
rul[49][13][2]=356.734; rul[49][13][3]=488.907; rul[49][13][4]=220.22; rul[49][13][5]=356.734; rul[49][13][6]=min; rul[49][13][7]=220.22; 
dl_reg[49]=14;
dec[49]=4; 
// 50. Koniec reguly
// 51. Regula
// 1. sekcja AND 51 reguly.
rul[50][0][0]=35; rul[50][0][1]=2; 
rul[50][0][2]=1; rul[50][0][3]=1; 
// 2. sekcja AND 51 reguly.
rul[50][1][0]=15; rul[50][1][1]=2; 
rul[50][1][2]=min; rul[50][1][3]=18.43; 
// 3. sekcja AND 51 reguly.
rul[50][2][0]=4; rul[50][2][1]=2; 
rul[50][2][2]=0.6655; rul[50][2][3]=max; 
// 4. sekcja AND 51 reguly.
rul[50][3][0]=3; rul[50][3][1]=2; 
rul[50][3][2]=1.368; rul[50][3][3]=max; 
// 5. sekcja AND 51 reguly.
rul[50][4][0]=6; rul[50][4][1]=2; 
rul[50][4][2]=8.215; rul[50][4][3]=max; 
// 6. sekcja AND 51 reguly.
rul[50][5][0]=8; rul[50][5][1]=2; 
rul[50][5][2]=1.0185; rul[50][5][3]=max; 
// 7. sekcja AND 51 reguly.
rul[50][6][0]=16; rul[50][6][1]=2; 
rul[50][6][2]=min; rul[50][6][3]=0.8145; 
// 8. sekcja AND 51 reguly.
rul[50][7][0]=18; rul[50][7][1]=4; 
rul[50][7][2]=0.9085; rul[50][7][3]=max; rul[50][7][4]=min; rul[50][7][5]=0.9085; 
// 9. sekcja AND 51 reguly.
rul[50][8][0]=26; rul[50][8][1]=4; 
rul[50][8][2]=0.3215; rul[50][8][3]=0.6065; rul[50][8][4]=min; rul[50][8][5]=0.3215; 
// 10. sekcja AND 51 reguly.
rul[50][9][0]=10; rul[50][9][1]=2; 
rul[50][9][2]=min; rul[50][9][3]=1.5705; 
// 11. sekcja AND 51 reguly.
rul[50][10][0]=34; rul[50][10][1]=2; 
rul[50][10][2]=240.981; rul[50][10][3]=max; 
// 12. sekcja AND 51 reguly.
rul[50][11][0]=7; rul[50][11][1]=2; 
rul[50][11][2]=6.171; rul[50][11][3]=8.48; 
dl_reg[50]=12;
dec[50]=4; 
// 51. Koniec reguly
// 52. Regula
// 1. sekcja AND 52 reguly.
rul[51][0][0]=35; rul[51][0][1]=2; 
rul[51][0][2]=1; rul[51][0][3]=1; 
// 2. sekcja AND 52 reguly.
rul[51][1][0]=15; rul[51][1][1]=2; 
rul[51][1][2]=min; rul[51][1][3]=18.43; 
// 3. sekcja AND 52 reguly.
rul[51][2][0]=7; rul[51][2][1]=2; 
rul[51][2][2]=min; rul[51][2][3]=6.171; 
// 4. sekcja AND 52 reguly.
rul[51][3][0]=18; rul[51][3][1]=4; 
rul[51][3][2]=0.9085; rul[51][3][3]=max; rul[51][3][4]=min; rul[51][3][5]=0.9085; 
// 5. sekcja AND 52 reguly.
rul[51][4][0]=16; rul[51][4][1]=2; 
rul[51][4][2]=0.8145; rul[51][4][3]=max; 
// 6. sekcja AND 52 reguly.
rul[51][5][0]=32; rul[51][5][1]=4; 
rul[51][5][2]=min; rul[51][5][3]=198.694; rul[51][5][4]=198.694; rul[51][5][5]=234.086; 
// 7. sekcja AND 52 reguly.
rul[51][6][0]=21; rul[51][6][1]=4; 
rul[51][6][2]=min; rul[51][6][3]=0.1245; rul[51][6][4]=0.1245; rul[51][6][5]=max; 
// 8. sekcja AND 52 reguly.
rul[51][7][0]=6; rul[51][7][1]=4; 
rul[51][7][2]=min; rul[51][7][3]=8.215; rul[51][7][4]=8.215; rul[51][7][5]=max; 
// 9. sekcja AND 52 reguly.
rul[51][8][0]=27; rul[51][8][1]=4; 
rul[51][8][2]=0.6905; rul[51][8][3]=max; rul[51][8][4]=0.5825; rul[51][8][5]=0.6905; 
// 10. sekcja AND 52 reguly.
rul[51][9][0]=4; rul[51][9][1]=2; 
rul[51][9][2]=0.6655; rul[51][9][3]=max; 
// 11. sekcja AND 52 reguly.
rul[51][10][0]=33; rul[51][10][1]=2; 
rul[51][10][2]=73.918; rul[51][10][3]=137.781; 
// 12. sekcja AND 52 reguly.
rul[51][11][0]=34; rul[51][11][1]=4; 
rul[51][11][2]=240.981; rul[51][11][3]=max; rul[51][11][4]=189.705; rul[51][11][5]=240.981; 
dl_reg[51]=12;
dec[51]=4; 
// 52. Koniec reguly
// 53. Regula
// 1. sekcja AND 53 reguly.
rul[52][0][0]=35; rul[52][0][1]=2; 
rul[52][0][2]=1; rul[52][0][3]=1; 
// 2. sekcja AND 53 reguly.
rul[52][1][0]=4; rul[52][1][1]=2; 
rul[52][1][2]=0.6655; rul[52][1][3]=max; 
// 3. sekcja AND 53 reguly.
rul[52][2][0]=3; rul[52][2][1]=2; 
rul[52][2][2]=1.368; rul[52][2][3]=max; 
// 4. sekcja AND 53 reguly.
rul[52][3][0]=6; rul[52][3][1]=2; 
rul[52][3][2]=8.215; rul[52][3][3]=max; 
// 5. sekcja AND 53 reguly.
rul[52][4][0]=8; rul[52][4][1]=2; 
rul[52][4][2]=1.0185; rul[52][4][3]=max; 
// 6. sekcja AND 53 reguly.
rul[52][5][0]=16; rul[52][5][1]=2; 
rul[52][5][2]=min; rul[52][5][3]=0.8145; 
// 7. sekcja AND 53 reguly.
rul[52][6][0]=21; rul[52][6][1]=2; 
rul[52][6][2]=0.1245; rul[52][6][3]=max; 
// 8. sekcja AND 53 reguly.
rul[52][7][0]=18; rul[52][7][1]=2; 
rul[52][7][2]=min; rul[52][7][3]=0.9085; 
// 9. sekcja AND 53 reguly.
rul[52][8][0]=26; rul[52][8][1]=2; 
rul[52][8][2]=min; rul[52][8][3]=0.3215; 
// 10. sekcja AND 53 reguly.
rul[52][9][0]=27; rul[52][9][1]=2; 
rul[52][9][2]=min; rul[52][9][3]=0.5825; 
// 11. sekcja AND 53 reguly.
rul[52][10][0]=10; rul[52][10][1]=2; 
rul[52][10][2]=min; rul[52][10][3]=1.5705; 
// 12. sekcja AND 53 reguly.
rul[52][11][0]=33; rul[52][11][1]=2; 
rul[52][11][2]=73.918; rul[52][11][3]=137.781; 
// 13. sekcja AND 53 reguly.
rul[52][12][0]=7; rul[52][12][1]=4; 
rul[52][12][2]=8.48; rul[52][12][3]=14.437; rul[52][12][4]=min; rul[52][12][5]=6.171; 
dl_reg[52]=13;
dec[52]=4; 
// 53. Koniec reguly
// 54. Regula
// 1. sekcja AND 54 reguly.
rul[53][0][0]=35; rul[53][0][1]=2; 
rul[53][0][2]=1; rul[53][0][3]=1; 
// 2. sekcja AND 54 reguly.
rul[53][1][0]=4; rul[53][1][1]=2; 
rul[53][1][2]=0.6655; rul[53][1][3]=max; 
// 3. sekcja AND 54 reguly.
rul[53][2][0]=6; rul[53][2][1]=4; 
rul[53][2][2]=8.215; rul[53][2][3]=max; rul[53][2][4]=min; rul[53][2][5]=8.215; 
// 4. sekcja AND 54 reguly.
rul[53][3][0]=3; rul[53][3][1]=4; 
rul[53][3][2]=1.368; rul[53][3][3]=max; rul[53][3][4]=min; rul[53][3][5]=1.368; 
// 5. sekcja AND 54 reguly.
rul[53][4][0]=8; rul[53][4][1]=4; 
rul[53][4][2]=1.0185; rul[53][4][3]=max; rul[53][4][4]=min; rul[53][4][5]=1.0185; 
// 6. sekcja AND 54 reguly.
rul[53][5][0]=16; rul[53][5][1]=2; 
rul[53][5][2]=min; rul[53][5][3]=0.8145; 
// 7. sekcja AND 54 reguly.
rul[53][6][0]=10; rul[53][6][1]=2; 
rul[53][6][2]=1.5705; rul[53][6][3]=max; 
// 8. sekcja AND 54 reguly.
rul[53][7][0]=33; rul[53][7][1]=2; 
rul[53][7][2]=min; rul[53][7][3]=73.918; 
// 9. sekcja AND 54 reguly.
rul[53][8][0]=15; rul[53][8][1]=4; 
rul[53][8][2]=18.43; rul[53][8][3]=max; rul[53][8][4]=min; rul[53][8][5]=18.43; 
// 10. sekcja AND 54 reguly.
rul[53][9][0]=7; rul[53][9][1]=6; 
rul[53][9][2]=14.437; rul[53][9][3]=max; rul[53][9][4]=8.48; rul[53][9][5]=14.437; rul[53][9][6]=min; rul[53][9][7]=6.171; 
// 11. sekcja AND 54 reguly.
rul[53][10][0]=18; rul[53][10][1]=4; 
rul[53][10][2]=min; rul[53][10][3]=0.9085; rul[53][10][4]=0.9085; rul[53][10][5]=max; 
// 12. sekcja AND 54 reguly.
rul[53][11][0]=20; rul[53][11][1]=6; 
rul[53][11][2]=548.425; rul[53][11][3]=650.372; rul[53][11][4]=488.907; rul[53][11][5]=548.425; rul[53][11][6]=356.734; rul[53][11][7]=488.907; 
dl_reg[53]=12;
dec[53]=4; 
// 54. Koniec reguly
// 55. Regula
// 1. sekcja AND 55 reguly.
rul[54][0][0]=35; rul[54][0][1]=2; 
rul[54][0][2]=1; rul[54][0][3]=1; 
// 2. sekcja AND 55 reguly.
rul[54][1][0]=15; rul[54][1][1]=2; 
rul[54][1][2]=min; rul[54][1][3]=18.43; 
// 3. sekcja AND 55 reguly.
rul[54][2][0]=3; rul[54][2][1]=2; 
rul[54][2][2]=1.368; rul[54][2][3]=max; 
// 4. sekcja AND 55 reguly.
rul[54][3][0]=4; rul[54][3][1]=2; 
rul[54][3][2]=0.6655; rul[54][3][3]=max; 
// 5. sekcja AND 55 reguly.
rul[54][4][0]=6; rul[54][4][1]=4; 
rul[54][4][2]=8.215; rul[54][4][3]=max; rul[54][4][4]=min; rul[54][4][5]=8.215; 
// 6. sekcja AND 55 reguly.
rul[54][5][0]=16; rul[54][5][1]=2; 
rul[54][5][2]=min; rul[54][5][3]=0.8145; 
// 7. sekcja AND 55 reguly.
rul[54][6][0]=8; rul[54][6][1]=2; 
rul[54][6][2]=1.0185; rul[54][6][3]=max; 
// 8. sekcja AND 55 reguly.
rul[54][7][0]=10; rul[54][7][1]=4; 
rul[54][7][2]=min; rul[54][7][3]=1.5705; rul[54][7][4]=1.5705; rul[54][7][5]=max; 
// 9. sekcja AND 55 reguly.
rul[54][8][0]=7; rul[54][8][1]=2; 
rul[54][8][2]=min; rul[54][8][3]=6.171; 
// 10. sekcja AND 55 reguly.
rul[54][9][0]=26; rul[54][9][1]=2; 
rul[54][9][2]=0.3215; rul[54][9][3]=0.6065; 
// 11. sekcja AND 55 reguly.
rul[54][10][0]=27; rul[54][10][1]=2; 
rul[54][10][2]=0.5825; rul[54][10][3]=0.6905; 
dl_reg[54]=11;
dec[54]=4; 
// 55. Koniec reguly
// 56. Regula
// 1. sekcja AND 56 reguly.
rul[55][0][0]=35; rul[55][0][1]=2; 
rul[55][0][2]=1; rul[55][0][3]=1; 
// 2. sekcja AND 56 reguly.
rul[55][1][0]=18; rul[55][1][1]=2; 
rul[55][1][2]=0.9085; rul[55][1][3]=max; 
// 3. sekcja AND 56 reguly.
rul[55][2][0]=15; rul[55][2][1]=2; 
rul[55][2][2]=min; rul[55][2][3]=18.43; 
// 4. sekcja AND 56 reguly.
rul[55][3][0]=3; rul[55][3][1]=2; 
rul[55][3][2]=1.368; rul[55][3][3]=max; 
// 5. sekcja AND 56 reguly.
rul[55][4][0]=6; rul[55][4][1]=2; 
rul[55][4][2]=8.215; rul[55][4][3]=max; 
// 6. sekcja AND 56 reguly.
rul[55][5][0]=8; rul[55][5][1]=2; 
rul[55][5][2]=1.0185; rul[55][5][3]=max; 
// 7. sekcja AND 56 reguly.
rul[55][6][0]=21; rul[55][6][1]=2; 
rul[55][6][2]=0.1245; rul[55][6][3]=max; 
// 8. sekcja AND 56 reguly.
rul[55][7][0]=4; rul[55][7][1]=2; 
rul[55][7][2]=0.6655; rul[55][7][3]=max; 
// 9. sekcja AND 56 reguly.
rul[55][8][0]=16; rul[55][8][1]=2; 
rul[55][8][2]=min; rul[55][8][3]=0.8145; 
// 10. sekcja AND 56 reguly.
rul[55][9][0]=26; rul[55][9][1]=2; 
rul[55][9][2]=0.3215; rul[55][9][3]=0.6065; 
// 11. sekcja AND 56 reguly.
rul[55][10][0]=10; rul[55][10][1]=4; 
rul[55][10][2]=1.5705; rul[55][10][3]=max; rul[55][10][4]=min; rul[55][10][5]=1.5705; 
// 12. sekcja AND 56 reguly.
rul[55][11][0]=7; rul[55][11][1]=2; 
rul[55][11][2]=6.171; rul[55][11][3]=8.48; 
// 13. sekcja AND 56 reguly.
rul[55][12][0]=20; rul[55][12][1]=2; 
rul[55][12][2]=220.22; rul[55][12][3]=356.734; 
dl_reg[55]=13;
dec[55]=3; 
// 56. Koniec reguly
// 57. Regula
// 1. sekcja AND 57 reguly.
rul[56][0][0]=35; rul[56][0][1]=4; 
rul[56][0][2]=1; rul[56][0][3]=1; rul[56][0][4]=2; rul[56][0][5]=2; 
// 2. sekcja AND 57 reguly.
rul[56][1][0]=3; rul[56][1][1]=2; 
rul[56][1][2]=1.368; rul[56][1][3]=max; 
// 3. sekcja AND 57 reguly.
rul[56][2][0]=6; rul[56][2][1]=2; 
rul[56][2][2]=8.215; rul[56][2][3]=max; 
// 4. sekcja AND 57 reguly.
rul[56][3][0]=8; rul[56][3][1]=2; 
rul[56][3][2]=1.0185; rul[56][3][3]=max; 
// 5. sekcja AND 57 reguly.
rul[56][4][0]=18; rul[56][4][1]=2; 
rul[56][4][2]=0.9085; rul[56][4][3]=max; 
// 6. sekcja AND 57 reguly.
rul[56][5][0]=21; rul[56][5][1]=4; 
rul[56][5][2]=0.1245; rul[56][5][3]=max; rul[56][5][4]=min; rul[56][5][5]=0.1245; 
// 7. sekcja AND 57 reguly.
rul[56][6][0]=15; rul[56][6][1]=2; 
rul[56][6][2]=min; rul[56][6][3]=18.43; 
// 8. sekcja AND 57 reguly.
rul[56][7][0]=4; rul[56][7][1]=4; 
rul[56][7][2]=0.6655; rul[56][7][3]=max; rul[56][7][4]=min; rul[56][7][5]=0.6655; 
// 9. sekcja AND 57 reguly.
rul[56][8][0]=26; rul[56][8][1]=2; 
rul[56][8][2]=0.6065; rul[56][8][3]=0.8585; 
// 10. sekcja AND 57 reguly.
rul[56][9][0]=16; rul[56][9][1]=2; 
rul[56][9][2]=0.8145; rul[56][9][3]=max; 
// 11. sekcja AND 57 reguly.
rul[56][10][0]=7; rul[56][10][1]=4; 
rul[56][10][2]=8.48; rul[56][10][3]=14.437; rul[56][10][4]=6.171; rul[56][10][5]=8.48; 
// 12. sekcja AND 57 reguly.
rul[56][11][0]=27; rul[56][11][1]=2; 
rul[56][11][2]=0.6905; rul[56][11][3]=max; 
dl_reg[56]=12;
dec[56]=3; 
// 57. Koniec reguly
// 58. Regula
// 1. sekcja AND 58 reguly.
rul[57][0][0]=35; rul[57][0][1]=2; 
rul[57][0][2]=1; rul[57][0][3]=1; 
// 2. sekcja AND 58 reguly.
rul[57][1][0]=18; rul[57][1][1]=2; 
rul[57][1][2]=0.9085; rul[57][1][3]=max; 
// 3. sekcja AND 58 reguly.
rul[57][2][0]=15; rul[57][2][1]=2; 
rul[57][2][2]=min; rul[57][2][3]=18.43; 
// 4. sekcja AND 58 reguly.
rul[57][3][0]=16; rul[57][3][1]=2; 
rul[57][3][2]=0.8145; rul[57][3][3]=max; 
// 5. sekcja AND 58 reguly.
rul[57][4][0]=3; rul[57][4][1]=2; 
rul[57][4][2]=1.368; rul[57][4][3]=max; 
// 6. sekcja AND 58 reguly.
rul[57][5][0]=6; rul[57][5][1]=2; 
rul[57][5][2]=8.215; rul[57][5][3]=max; 
// 7. sekcja AND 58 reguly.
rul[57][6][0]=8; rul[57][6][1]=4; 
rul[57][6][2]=1.0185; rul[57][6][3]=max; rul[57][6][4]=min; rul[57][6][5]=1.0185; 
// 8. sekcja AND 58 reguly.
rul[57][7][0]=10; rul[57][7][1]=2; 
rul[57][7][2]=1.5705; rul[57][7][3]=max; 
// 9. sekcja AND 58 reguly.
rul[57][8][0]=4; rul[57][8][1]=2; 
rul[57][8][2]=min; rul[57][8][3]=0.6655; 
// 10. sekcja AND 58 reguly.
rul[57][9][0]=21; rul[57][9][1]=2; 
rul[57][9][2]=min; rul[57][9][3]=0.1245; 
// 11. sekcja AND 58 reguly.
rul[57][10][0]=7; rul[57][10][1]=2; 
rul[57][10][2]=min; rul[57][10][3]=6.171; 
dl_reg[57]=11;
dec[57]=3; 
// 58. Koniec reguly
// 59. Regula
// 1. sekcja AND 59 reguly.
rul[58][0][0]=35; rul[58][0][1]=2; 
rul[58][0][2]=1; rul[58][0][3]=1; 
// 2. sekcja AND 59 reguly.
rul[58][1][0]=18; rul[58][1][1]=4; 
rul[58][1][2]=0.9085; rul[58][1][3]=max; rul[58][1][4]=min; rul[58][1][5]=0.9085; 
// 3. sekcja AND 59 reguly.
rul[58][2][0]=15; rul[58][2][1]=4; 
rul[58][2][2]=min; rul[58][2][3]=18.43; rul[58][2][4]=18.43; rul[58][2][5]=max; 
// 4. sekcja AND 59 reguly.
rul[58][3][0]=16; rul[58][3][1]=4; 
rul[58][3][2]=0.8145; rul[58][3][3]=max; rul[58][3][4]=min; rul[58][3][5]=0.8145; 
// 5. sekcja AND 59 reguly.
rul[58][4][0]=3; rul[58][4][1]=2; 
rul[58][4][2]=1.368; rul[58][4][3]=max; 
// 6. sekcja AND 59 reguly.
rul[58][5][0]=6; rul[58][5][1]=4; 
rul[58][5][2]=8.215; rul[58][5][3]=max; rul[58][5][4]=min; rul[58][5][5]=8.215; 
// 7. sekcja AND 59 reguly.
rul[58][6][0]=27; rul[58][6][1]=2; 
rul[58][6][2]=0.6905; rul[58][6][3]=max; 
// 8. sekcja AND 59 reguly.
rul[58][7][0]=8; rul[58][7][1]=4; 
rul[58][7][2]=min; rul[58][7][3]=1.0185; rul[58][7][4]=1.0185; rul[58][7][5]=max; 
// 9. sekcja AND 59 reguly.
rul[58][8][0]=7; rul[58][8][1]=6; 
rul[58][8][2]=min; rul[58][8][3]=6.171; rul[58][8][4]=6.171; rul[58][8][5]=8.48; rul[58][8][6]=8.48; rul[58][8][7]=14.437; 
// 10. sekcja AND 59 reguly.
rul[58][9][0]=33; rul[58][9][1]=2; 
rul[58][9][2]=137.781; rul[58][9][3]=max; 
// 11. sekcja AND 59 reguly.
rul[58][10][0]=4; rul[58][10][1]=2; 
rul[58][10][2]=min; rul[58][10][3]=0.6655; 
dl_reg[58]=11;
dec[58]=3; 
// 59. Koniec reguly
// 60. Regula
// 1. sekcja AND 60 reguly.
rul[59][0][0]=35; rul[59][0][1]=4; 
rul[59][0][2]=1; rul[59][0][3]=1; rul[59][0][4]=2; rul[59][0][5]=2; 
// 2. sekcja AND 60 reguly.
rul[59][1][0]=3; rul[59][1][1]=2; 
rul[59][1][2]=1.368; rul[59][1][3]=max; 
// 3. sekcja AND 60 reguly.
rul[59][2][0]=6; rul[59][2][1]=2; 
rul[59][2][2]=8.215; rul[59][2][3]=max; 
// 4. sekcja AND 60 reguly.
rul[59][3][0]=8; rul[59][3][1]=2; 
rul[59][3][2]=1.0185; rul[59][3][3]=max; 
// 5. sekcja AND 60 reguly.
rul[59][4][0]=16; rul[59][4][1]=2; 
rul[59][4][2]=min; rul[59][4][3]=0.8145; 
// 6. sekcja AND 60 reguly.
rul[59][5][0]=21; rul[59][5][1]=2; 
rul[59][5][2]=0.1245; rul[59][5][3]=max; 
// 7. sekcja AND 60 reguly.
rul[59][6][0]=15; rul[59][6][1]=2; 
rul[59][6][2]=18.43; rul[59][6][3]=max; 
// 8. sekcja AND 60 reguly.
rul[59][7][0]=4; rul[59][7][1]=4; 
rul[59][7][2]=0.6655; rul[59][7][3]=max; rul[59][7][4]=min; rul[59][7][5]=0.6655; 
// 9. sekcja AND 60 reguly.
rul[59][8][0]=27; rul[59][8][1]=2; 
rul[59][8][2]=min; rul[59][8][3]=0.5825; 
// 10. sekcja AND 60 reguly.
rul[59][9][0]=10; rul[59][9][1]=2; 
rul[59][9][2]=1.5705; rul[59][9][3]=max; 
// 11. sekcja AND 60 reguly.
rul[59][10][0]=7; rul[59][10][1]=2; 
rul[59][10][2]=8.48; rul[59][10][3]=14.437; 
// 12. sekcja AND 60 reguly.
rul[59][11][0]=32; rul[59][11][1]=2; 
rul[59][11][2]=234.086; rul[59][11][3]=max; 
dl_reg[59]=12;
dec[59]=3; 
// 60. Koniec reguly
// 61. Regula
// 1. sekcja AND 61 reguly.
rul[60][0][0]=35; rul[60][0][1]=2; 
rul[60][0][2]=1; rul[60][0][3]=1; 
// 2. sekcja AND 61 reguly.
rul[60][1][0]=15; rul[60][1][1]=2; 
rul[60][1][2]=min; rul[60][1][3]=18.43; 
// 3. sekcja AND 61 reguly.
rul[60][2][0]=7; rul[60][2][1]=2; 
rul[60][2][2]=min; rul[60][2][3]=6.171; 
// 4. sekcja AND 61 reguly.
rul[60][3][0]=6; rul[60][3][1]=2; 
rul[60][3][2]=min; rul[60][3][3]=8.215; 
// 5. sekcja AND 61 reguly.
rul[60][4][0]=27; rul[60][4][1]=2; 
rul[60][4][2]=0.6905; rul[60][4][3]=max; 
// 6. sekcja AND 61 reguly.
rul[60][5][0]=8; rul[60][5][1]=2; 
rul[60][5][2]=min; rul[60][5][3]=1.0185; 
// 7. sekcja AND 61 reguly.
rul[60][6][0]=21; rul[60][6][1]=2; 
rul[60][6][2]=min; rul[60][6][3]=0.1245; 
// 8. sekcja AND 61 reguly.
rul[60][7][0]=16; rul[60][7][1]=2; 
rul[60][7][2]=0.8145; rul[60][7][3]=max; 
// 9. sekcja AND 61 reguly.
rul[60][8][0]=4; rul[60][8][1]=4; 
rul[60][8][2]=min; rul[60][8][3]=0.6655; rul[60][8][4]=0.6655; rul[60][8][5]=max; 
// 10. sekcja AND 61 reguly.
rul[60][9][0]=10; rul[60][9][1]=2; 
rul[60][9][2]=min; rul[60][9][3]=1.5705; 
// 11. sekcja AND 61 reguly.
rul[60][10][0]=18; rul[60][10][1]=2; 
rul[60][10][2]=min; rul[60][10][3]=0.9085; 
// 12. sekcja AND 61 reguly.
rul[60][11][0]=33; rul[60][11][1]=2; 
rul[60][11][2]=137.781; rul[60][11][3]=max; 
dl_reg[60]=12;
dec[60]=3; 
// 61. Koniec reguly
// 62. Regula
// 1. sekcja AND 62 reguly.
rul[61][0][0]=15; rul[61][0][1]=2; 
rul[61][0][2]=min; rul[61][0][3]=18.43; 
// 2. sekcja AND 62 reguly.
rul[61][1][0]=18; rul[61][1][1]=4; 
rul[61][1][2]=0.9085; rul[61][1][3]=max; rul[61][1][4]=min; rul[61][1][5]=0.9085; 
// 3. sekcja AND 62 reguly.
rul[61][2][0]=16; rul[61][2][1]=2; 
rul[61][2][2]=0.8145; rul[61][2][3]=max; 
// 4. sekcja AND 62 reguly.
rul[61][3][0]=27; rul[61][3][1]=2; 
rul[61][3][2]=0.6905; rul[61][3][3]=max; 
// 5. sekcja AND 62 reguly.
rul[61][4][0]=35; rul[61][4][1]=2; 
rul[61][4][2]=2; rul[61][4][3]=2; 
// 6. sekcja AND 62 reguly.
rul[61][5][0]=6; rul[61][5][1]=4; 
rul[61][5][2]=8.215; rul[61][5][3]=max; rul[61][5][4]=min; rul[61][5][5]=8.215; 
// 7. sekcja AND 62 reguly.
rul[61][6][0]=10; rul[61][6][1]=2; 
rul[61][6][2]=min; rul[61][6][3]=1.5705; 
dl_reg[61]=7;
dec[61]=3; 
// 62. Koniec reguly
// 63. Regula
// 1. sekcja AND 63 reguly.
rul[62][0][0]=35; rul[62][0][1]=2; 
rul[62][0][2]=1; rul[62][0][3]=1; 
// 2. sekcja AND 63 reguly.
rul[62][1][0]=18; rul[62][1][1]=2; 
rul[62][1][2]=0.9085; rul[62][1][3]=max; 
// 3. sekcja AND 63 reguly.
rul[62][2][0]=6; rul[62][2][1]=2; 
rul[62][2][2]=8.215; rul[62][2][3]=max; 
// 4. sekcja AND 63 reguly.
rul[62][3][0]=8; rul[62][3][1]=2; 
rul[62][3][2]=1.0185; rul[62][3][3]=max; 
// 5. sekcja AND 63 reguly.
rul[62][4][0]=3; rul[62][4][1]=2; 
rul[62][4][2]=1.368; rul[62][4][3]=max; 
// 6. sekcja AND 63 reguly.
rul[62][5][0]=4; rul[62][5][1]=2; 
rul[62][5][2]=min; rul[62][5][3]=0.6655; 
// 7. sekcja AND 63 reguly.
rul[62][6][0]=21; rul[62][6][1]=4; 
rul[62][6][2]=0.1245; rul[62][6][3]=max; rul[62][6][4]=min; rul[62][6][5]=0.1245; 
// 8. sekcja AND 63 reguly.
rul[62][7][0]=16; rul[62][7][1]=2; 
rul[62][7][2]=min; rul[62][7][3]=0.8145; 
// 9. sekcja AND 63 reguly.
rul[62][8][0]=27; rul[62][8][1]=4; 
rul[62][8][2]=min; rul[62][8][3]=0.5825; rul[62][8][4]=0.5825; rul[62][8][5]=0.6905; 
// 10. sekcja AND 63 reguly.
rul[62][9][0]=15; rul[62][9][1]=4; 
rul[62][9][2]=min; rul[62][9][3]=18.43; rul[62][9][4]=18.43; rul[62][9][5]=max; 
// 11. sekcja AND 63 reguly.
rul[62][10][0]=7; rul[62][10][1]=4; 
rul[62][10][2]=min; rul[62][10][3]=6.171; rul[62][10][4]=6.171; rul[62][10][5]=8.48; 
// 12. sekcja AND 63 reguly.
rul[62][11][0]=32; rul[62][11][1]=2; 
rul[62][11][2]=min; rul[62][11][3]=198.694; 
// 13. sekcja AND 63 reguly.
rul[62][12][0]=10; rul[62][12][1]=2; 
rul[62][12][2]=1.5705; rul[62][12][3]=max; 
// 14. sekcja AND 63 reguly.
rul[62][13][0]=33; rul[62][13][1]=2; 
rul[62][13][2]=73.918; rul[62][13][3]=137.781; 
dl_reg[62]=14;
dec[62]=2; 
// 63. Koniec reguly
// 64. Regula
// 1. sekcja AND 64 reguly.
rul[63][0][0]=35; rul[63][0][1]=2; 
rul[63][0][2]=1; rul[63][0][3]=1; 
// 2. sekcja AND 64 reguly.
rul[63][1][0]=18; rul[63][1][1]=2; 
rul[63][1][2]=0.9085; rul[63][1][3]=max; 
// 3. sekcja AND 64 reguly.
rul[63][2][0]=15; rul[63][2][1]=4; 
rul[63][2][2]=min; rul[63][2][3]=18.43; rul[63][2][4]=18.43; rul[63][2][5]=max; 
// 4. sekcja AND 64 reguly.
rul[63][3][0]=16; rul[63][3][1]=2; 
rul[63][3][2]=0.8145; rul[63][3][3]=max; 
// 5. sekcja AND 64 reguly.
rul[63][4][0]=3; rul[63][4][1]=4; 
rul[63][4][2]=min; rul[63][4][3]=1.368; rul[63][4][4]=1.368; rul[63][4][5]=max; 
// 6. sekcja AND 64 reguly.
rul[63][5][0]=6; rul[63][5][1]=4; 
rul[63][5][2]=min; rul[63][5][3]=8.215; rul[63][5][4]=8.215; rul[63][5][5]=max; 
// 7. sekcja AND 64 reguly.
rul[63][6][0]=8; rul[63][6][1]=4; 
rul[63][6][2]=min; rul[63][6][3]=1.0185; rul[63][6][4]=1.0185; rul[63][6][5]=max; 
// 8. sekcja AND 64 reguly.
rul[63][7][0]=32; rul[63][7][1]=2; 
rul[63][7][2]=min; rul[63][7][3]=198.694; 
// 9. sekcja AND 64 reguly.
rul[63][8][0]=34; rul[63][8][1]=2; 
rul[63][8][2]=240.981; rul[63][8][3]=max; 
// 10. sekcja AND 64 reguly.
rul[63][9][0]=4; rul[63][9][1]=4; 
rul[63][9][2]=min; rul[63][9][3]=0.6655; rul[63][9][4]=0.6655; rul[63][9][5]=max; 
// 11. sekcja AND 64 reguly.
rul[63][10][0]=33; rul[63][10][1]=4; 
rul[63][10][2]=73.918; rul[63][10][3]=137.781; rul[63][10][4]=min; rul[63][10][5]=73.918; 
// 12. sekcja AND 64 reguly.
rul[63][11][0]=7; rul[63][11][1]=4; 
rul[63][11][2]=min; rul[63][11][3]=6.171; rul[63][11][4]=14.437; rul[63][11][5]=max; 
// 13. sekcja AND 64 reguly.
rul[63][12][0]=20; rul[63][12][1]=4; 
rul[63][12][2]=650.372; rul[63][12][3]=max; rul[63][12][4]=548.425; rul[63][12][5]=650.372; 
dl_reg[63]=13;
dec[63]=2; 
// 64. Koniec reguly
// 65. Regula
// 1. sekcja AND 65 reguly.
rul[64][0][0]=35; rul[64][0][1]=2; 
rul[64][0][2]=1; rul[64][0][3]=1; 
// 2. sekcja AND 65 reguly.
rul[64][1][0]=6; rul[64][1][1]=2; 
rul[64][1][2]=8.215; rul[64][1][3]=max; 
// 3. sekcja AND 65 reguly.
rul[64][2][0]=8; rul[64][2][1]=2; 
rul[64][2][2]=1.0185; rul[64][2][3]=max; 
// 4. sekcja AND 65 reguly.
rul[64][3][0]=3; rul[64][3][1]=4; 
rul[64][3][2]=1.368; rul[64][3][3]=max; rul[64][3][4]=min; rul[64][3][5]=1.368; 
// 5. sekcja AND 65 reguly.
rul[64][4][0]=4; rul[64][4][1]=2; 
rul[64][4][2]=min; rul[64][4][3]=0.6655; 
// 6. sekcja AND 65 reguly.
rul[64][5][0]=16; rul[64][5][1]=2; 
rul[64][5][2]=min; rul[64][5][3]=0.8145; 
// 7. sekcja AND 65 reguly.
rul[64][6][0]=21; rul[64][6][1]=2; 
rul[64][6][2]=0.1245; rul[64][6][3]=max; 
// 8. sekcja AND 65 reguly.
rul[64][7][0]=27; rul[64][7][1]=4; 
rul[64][7][2]=min; rul[64][7][3]=0.5825; rul[64][7][4]=0.5825; rul[64][7][5]=0.6905; 
// 9. sekcja AND 65 reguly.
rul[64][8][0]=18; rul[64][8][1]=4; 
rul[64][8][2]=min; rul[64][8][3]=0.9085; rul[64][8][4]=0.9085; rul[64][8][5]=max; 
// 10. sekcja AND 65 reguly.
rul[64][9][0]=15; rul[64][9][1]=4; 
rul[64][9][2]=18.43; rul[64][9][3]=max; rul[64][9][4]=min; rul[64][9][5]=18.43; 
// 11. sekcja AND 65 reguly.
rul[64][10][0]=33; rul[64][10][1]=2; 
rul[64][10][2]=min; rul[64][10][3]=73.918; 
// 12. sekcja AND 65 reguly.
rul[64][11][0]=10; rul[64][11][1]=4; 
rul[64][11][2]=min; rul[64][11][3]=1.5705; rul[64][11][4]=1.5705; rul[64][11][5]=max; 
// 13. sekcja AND 65 reguly.
rul[64][12][0]=26; rul[64][12][1]=4; 
rul[64][12][2]=0.6065; rul[64][12][3]=0.8585; rul[64][12][4]=0.3215; rul[64][12][5]=0.6065; 
dl_reg[64]=13;
dec[64]=2; 
// 65. Koniec reguly
// 66. Regula
// 1. sekcja AND 66 reguly.
rul[65][0][0]=35; rul[65][0][1]=2; 
rul[65][0][2]=1; rul[65][0][3]=1; 
// 2. sekcja AND 66 reguly.
rul[65][1][0]=18; rul[65][1][1]=2; 
rul[65][1][2]=0.9085; rul[65][1][3]=max; 
// 3. sekcja AND 66 reguly.
rul[65][2][0]=6; rul[65][2][1]=2; 
rul[65][2][2]=8.215; rul[65][2][3]=max; 
// 4. sekcja AND 66 reguly.
rul[65][3][0]=8; rul[65][3][1]=2; 
rul[65][3][2]=1.0185; rul[65][3][3]=max; 
// 5. sekcja AND 66 reguly.
rul[65][4][0]=3; rul[65][4][1]=2; 
rul[65][4][2]=1.368; rul[65][4][3]=max; 
// 6. sekcja AND 66 reguly.
rul[65][5][0]=4; rul[65][5][1]=2; 
rul[65][5][2]=min; rul[65][5][3]=0.6655; 
// 7. sekcja AND 66 reguly.
rul[65][6][0]=33; rul[65][6][1]=2; 
rul[65][6][2]=73.918; rul[65][6][3]=137.781; 
// 8. sekcja AND 66 reguly.
rul[65][7][0]=15; rul[65][7][1]=2; 
rul[65][7][2]=18.43; rul[65][7][3]=max; 
// 9. sekcja AND 66 reguly.
rul[65][8][0]=21; rul[65][8][1]=2; 
rul[65][8][2]=0.1245; rul[65][8][3]=max; 
// 10. sekcja AND 66 reguly.
rul[65][9][0]=7; rul[65][9][1]=2; 
rul[65][9][2]=6.171; rul[65][9][3]=8.48; 
dl_reg[65]=10;
dec[65]=2; 
// 66. Koniec reguly
// 67. Regula
// 1. sekcja AND 67 reguly.
rul[66][0][0]=21; rul[66][0][1]=2; 
rul[66][0][2]=0.1245; rul[66][0][3]=max; 
// 2. sekcja AND 67 reguly.
rul[66][1][0]=35; rul[66][1][1]=2; 
rul[66][1][2]=1; rul[66][1][3]=1; 
// 3. sekcja AND 67 reguly.
rul[66][2][0]=6; rul[66][2][1]=2; 
rul[66][2][2]=8.215; rul[66][2][3]=max; 
// 4. sekcja AND 67 reguly.
rul[66][3][0]=8; rul[66][3][1]=2; 
rul[66][3][2]=1.0185; rul[66][3][3]=max; 
// 5. sekcja AND 67 reguly.
rul[66][4][0]=3; rul[66][4][1]=2; 
rul[66][4][2]=1.368; rul[66][4][3]=max; 
// 6. sekcja AND 67 reguly.
rul[66][5][0]=4; rul[66][5][1]=2; 
rul[66][5][2]=0.6655; rul[66][5][3]=max; 
// 7. sekcja AND 67 reguly.
rul[66][6][0]=27; rul[66][6][1]=2; 
rul[66][6][2]=0.5825; rul[66][6][3]=0.6905; 
// 8. sekcja AND 67 reguly.
rul[66][7][0]=7; rul[66][7][1]=2; 
rul[66][7][2]=14.437; rul[66][7][3]=max; 
// 9. sekcja AND 67 reguly.
rul[66][8][0]=15; rul[66][8][1]=2; 
rul[66][8][2]=18.43; rul[66][8][3]=max; 
// 10. sekcja AND 67 reguly.
rul[66][9][0]=16; rul[66][9][1]=2; 
rul[66][9][2]=min; rul[66][9][3]=0.8145; 
// 11. sekcja AND 67 reguly.
rul[66][10][0]=26; rul[66][10][1]=2; 
rul[66][10][2]=min; rul[66][10][3]=0.3215; 
// 12. sekcja AND 67 reguly.
rul[66][11][0]=34; rul[66][11][1]=2; 
rul[66][11][2]=240.981; rul[66][11][3]=max; 
// 13. sekcja AND 67 reguly.
rul[66][12][0]=18; rul[66][12][1]=2; 
rul[66][12][2]=min; rul[66][12][3]=0.9085; 
dl_reg[66]=13;
dec[66]=5; 
// 67. Koniec reguly
// 68. Regula
// 1. sekcja AND 68 reguly.
rul[67][0][0]=21; rul[67][0][1]=2; 
rul[67][0][2]=0.1245; rul[67][0][3]=max; 
// 2. sekcja AND 68 reguly.
rul[67][1][0]=3; rul[67][1][1]=2; 
rul[67][1][2]=1.368; rul[67][1][3]=max; 
// 3. sekcja AND 68 reguly.
rul[67][2][0]=35; rul[67][2][1]=2; 
rul[67][2][2]=1; rul[67][2][3]=1; 
// 4. sekcja AND 68 reguly.
rul[67][3][0]=15; rul[67][3][1]=2; 
rul[67][3][2]=min; rul[67][3][3]=18.43; 
// 5. sekcja AND 68 reguly.
rul[67][4][0]=20; rul[67][4][1]=2; 
rul[67][4][2]=220.22; rul[67][4][3]=356.734; 
// 6. sekcja AND 68 reguly.
rul[67][5][0]=16; rul[67][5][1]=2; 
rul[67][5][2]=0.8145; rul[67][5][3]=max; 
// 7. sekcja AND 68 reguly.
rul[67][6][0]=33; rul[67][6][1]=2; 
rul[67][6][2]=min; rul[67][6][3]=73.918; 
// 8. sekcja AND 68 reguly.
rul[67][7][0]=4; rul[67][7][1]=2; 
rul[67][7][2]=min; rul[67][7][3]=0.6655; 
// 9. sekcja AND 68 reguly.
rul[67][8][0]=7; rul[67][8][1]=2; 
rul[67][8][2]=min; rul[67][8][3]=6.171; 
// 10. sekcja AND 68 reguly.
rul[67][9][0]=8; rul[67][9][1]=2; 
rul[67][9][2]=min; rul[67][9][3]=1.0185; 
dl_reg[67]=10;
dec[67]=5; 
// 68. Koniec reguly
// 69. Regula
// 1. sekcja AND 69 reguly.
rul[68][0][0]=3; rul[68][0][1]=2; 
rul[68][0][2]=1.368; rul[68][0][3]=max; 
// 2. sekcja AND 69 reguly.
rul[68][1][0]=6; rul[68][1][1]=2; 
rul[68][1][2]=8.215; rul[68][1][3]=max; 
// 3. sekcja AND 69 reguly.
rul[68][2][0]=8; rul[68][2][1]=2; 
rul[68][2][2]=1.0185; rul[68][2][3]=max; 
// 4. sekcja AND 69 reguly.
rul[68][3][0]=16; rul[68][3][1]=2; 
rul[68][3][2]=min; rul[68][3][3]=0.8145; 
// 5. sekcja AND 69 reguly.
rul[68][4][0]=27; rul[68][4][1]=2; 
rul[68][4][2]=min; rul[68][4][3]=0.5825; 
// 6. sekcja AND 69 reguly.
rul[68][5][0]=7; rul[68][5][1]=2; 
rul[68][5][2]=min; rul[68][5][3]=6.171; 
// 7. sekcja AND 69 reguly.
rul[68][6][0]=4; rul[68][6][1]=2; 
rul[68][6][2]=min; rul[68][6][3]=0.6655; 
// 8. sekcja AND 69 reguly.
rul[68][7][0]=20; rul[68][7][1]=2; 
rul[68][7][2]=650.372; rul[68][7][3]=max; 
// 9. sekcja AND 69 reguly.
rul[68][8][0]=18; rul[68][8][1]=2; 
rul[68][8][2]=min; rul[68][8][3]=0.9085; 
// 10. sekcja AND 69 reguly.
rul[68][9][0]=35; rul[68][9][1]=2; 
rul[68][9][2]=1; rul[68][9][3]=1; 
// 11. sekcja AND 69 reguly.
rul[68][10][0]=26; rul[68][10][1]=2; 
rul[68][10][2]=min; rul[68][10][3]=0.3215; 
// 12. sekcja AND 69 reguly.
rul[68][11][0]=15; rul[68][11][1]=2; 
rul[68][11][2]=18.43; rul[68][11][3]=max; 
// 13. sekcja AND 69 reguly.
rul[68][12][0]=21; rul[68][12][1]=2; 
rul[68][12][2]=0.1245; rul[68][12][3]=max; 
// 14. sekcja AND 69 reguly.
rul[68][13][0]=10; rul[68][13][1]=2; 
rul[68][13][2]=min; rul[68][13][3]=1.5705; 
dl_reg[68]=14;
dec[68]=1; 
// 69. Koniec reguly
// 70. Regula
// 1. sekcja AND 70 reguly.
rul[69][0][0]=3; rul[69][0][1]=2; 
rul[69][0][2]=1.368; rul[69][0][3]=max; 
// 2. sekcja AND 70 reguly.
rul[69][1][0]=6; rul[69][1][1]=2; 
rul[69][1][2]=8.215; rul[69][1][3]=max; 
// 3. sekcja AND 70 reguly.
rul[69][2][0]=8; rul[69][2][1]=2; 
rul[69][2][2]=1.0185; rul[69][2][3]=max; 
// 4. sekcja AND 70 reguly.
rul[69][3][0]=16; rul[69][3][1]=2; 
rul[69][3][2]=min; rul[69][3][3]=0.8145; 
// 5. sekcja AND 70 reguly.
rul[69][4][0]=21; rul[69][4][1]=4; 
rul[69][4][2]=0.1245; rul[69][4][3]=max; rul[69][4][4]=min; rul[69][4][5]=0.1245; 
// 6. sekcja AND 70 reguly.
rul[69][5][0]=27; rul[69][5][1]=2; 
rul[69][5][2]=min; rul[69][5][3]=0.5825; 
// 7. sekcja AND 70 reguly.
rul[69][6][0]=35; rul[69][6][1]=4; 
rul[69][6][2]=1; rul[69][6][3]=1; rul[69][6][4]=2; rul[69][6][5]=2; 
// 8. sekcja AND 70 reguly.
rul[69][7][0]=4; rul[69][7][1]=2; 
rul[69][7][2]=min; rul[69][7][3]=0.6655; 
// 9. sekcja AND 70 reguly.
rul[69][8][0]=20; rul[69][8][1]=2; 
rul[69][8][2]=650.372; rul[69][8][3]=max; 
// 10. sekcja AND 70 reguly.
rul[69][9][0]=32; rul[69][9][1]=6; 
rul[69][9][2]=min; rul[69][9][3]=198.694; rul[69][9][4]=198.694; rul[69][9][5]=234.086; rul[69][9][6]=234.086; rul[69][9][7]=max; 
// 11. sekcja AND 70 reguly.
rul[69][10][0]=34; rul[69][10][1]=2; 
rul[69][10][2]=240.981; rul[69][10][3]=max; 
// 12. sekcja AND 70 reguly.
rul[69][11][0]=10; rul[69][11][1]=4; 
rul[69][11][2]=1.5705; rul[69][11][3]=max; rul[69][11][4]=min; rul[69][11][5]=1.5705; 
// 13. sekcja AND 70 reguly.
rul[69][12][0]=7; rul[69][12][1]=4; 
rul[69][12][2]=min; rul[69][12][3]=6.171; rul[69][12][4]=8.48; rul[69][12][5]=14.437; 
// 14. sekcja AND 70 reguly.
rul[69][13][0]=18; rul[69][13][1]=2; 
rul[69][13][2]=min; rul[69][13][3]=0.9085; 
dl_reg[69]=14;
dec[69]=1; 
// 70. Koniec reguly
// 71. Regula
// 1. sekcja AND 71 reguly.
rul[70][0][0]=3; rul[70][0][1]=2; 
rul[70][0][2]=1.368; rul[70][0][3]=max; 
// 2. sekcja AND 71 reguly.
rul[70][1][0]=6; rul[70][1][1]=2; 
rul[70][1][2]=8.215; rul[70][1][3]=max; 
// 3. sekcja AND 71 reguly.
rul[70][2][0]=8; rul[70][2][1]=2; 
rul[70][2][2]=1.0185; rul[70][2][3]=max; 
// 4. sekcja AND 71 reguly.
rul[70][3][0]=16; rul[70][3][1]=2; 
rul[70][3][2]=min; rul[70][3][3]=0.8145; 
// 5. sekcja AND 71 reguly.
rul[70][4][0]=21; rul[70][4][1]=2; 
rul[70][4][2]=0.1245; rul[70][4][3]=max; 
// 6. sekcja AND 71 reguly.
rul[70][5][0]=27; rul[70][5][1]=2; 
rul[70][5][2]=min; rul[70][5][3]=0.5825; 
// 7. sekcja AND 71 reguly.
rul[70][6][0]=7; rul[70][6][1]=2; 
rul[70][6][2]=min; rul[70][6][3]=6.171; 
// 8. sekcja AND 71 reguly.
rul[70][7][0]=15; rul[70][7][1]=4; 
rul[70][7][2]=min; rul[70][7][3]=18.43; rul[70][7][4]=18.43; rul[70][7][5]=max; 
// 9. sekcja AND 71 reguly.
rul[70][8][0]=32; rul[70][8][1]=4; 
rul[70][8][2]=234.086; rul[70][8][3]=max; rul[70][8][4]=min; rul[70][8][5]=198.694; 
// 10. sekcja AND 71 reguly.
rul[70][9][0]=18; rul[70][9][1]=2; 
rul[70][9][2]=min; rul[70][9][3]=0.9085; 
// 11. sekcja AND 71 reguly.
rul[70][10][0]=33; rul[70][10][1]=2; 
rul[70][10][2]=137.781; rul[70][10][3]=max; 
dl_reg[70]=11;
dec[70]=1; 
// 71. Koniec reguly
// 72. Regula
// 1. sekcja AND 72 reguly.
rul[71][0][0]=3; rul[71][0][1]=2; 
rul[71][0][2]=1.368; rul[71][0][3]=max; 
// 2. sekcja AND 72 reguly.
rul[71][1][0]=6; rul[71][1][1]=2; 
rul[71][1][2]=8.215; rul[71][1][3]=max; 
// 3. sekcja AND 72 reguly.
rul[71][2][0]=8; rul[71][2][1]=2; 
rul[71][2][2]=1.0185; rul[71][2][3]=max; 
// 4. sekcja AND 72 reguly.
rul[71][3][0]=16; rul[71][3][1]=2; 
rul[71][3][2]=min; rul[71][3][3]=0.8145; 
// 5. sekcja AND 72 reguly.
rul[71][4][0]=4; rul[71][4][1]=2; 
rul[71][4][2]=min; rul[71][4][3]=0.6655; 
// 6. sekcja AND 72 reguly.
rul[71][5][0]=34; rul[71][5][1]=2; 
rul[71][5][2]=240.981; rul[71][5][3]=max; 
// 7. sekcja AND 72 reguly.
rul[71][6][0]=20; rul[71][6][1]=4; 
rul[71][6][2]=650.372; rul[71][6][3]=max; rul[71][6][4]=220.22; rul[71][6][5]=356.734; 
// 8. sekcja AND 72 reguly.
rul[71][7][0]=26; rul[71][7][1]=4; 
rul[71][7][2]=0.3215; rul[71][7][3]=0.6065; rul[71][7][4]=min; rul[71][7][5]=0.3215; 
// 9. sekcja AND 72 reguly.
rul[71][8][0]=21; rul[71][8][1]=4; 
rul[71][8][2]=0.1245; rul[71][8][3]=max; rul[71][8][4]=min; rul[71][8][5]=0.1245; 
// 10. sekcja AND 72 reguly.
rul[71][9][0]=10; rul[71][9][1]=4; 
rul[71][9][2]=1.5705; rul[71][9][3]=max; rul[71][9][4]=min; rul[71][9][5]=1.5705; 
// 11. sekcja AND 72 reguly.
rul[71][10][0]=7; rul[71][10][1]=2; 
rul[71][10][2]=min; rul[71][10][3]=6.171; 
dl_reg[71]=11;
dec[71]=1; 
// 72. Koniec reguly
// 73. Regula
// 1. sekcja AND 73 reguly.
rul[72][0][0]=35; rul[72][0][1]=2; 
rul[72][0][2]=1; rul[72][0][3]=1; 
// 2. sekcja AND 73 reguly.
rul[72][1][0]=15; rul[72][1][1]=4; 
rul[72][1][2]=min; rul[72][1][3]=18.43; rul[72][1][4]=18.43; rul[72][1][5]=max; 
// 3. sekcja AND 73 reguly.
rul[72][2][0]=4; rul[72][2][1]=2; 
rul[72][2][2]=0.6655; rul[72][2][3]=max; 
// 4. sekcja AND 73 reguly.
rul[72][3][0]=3; rul[72][3][1]=2; 
rul[72][3][2]=1.368; rul[72][3][3]=max; 
// 5. sekcja AND 73 reguly.
rul[72][4][0]=6; rul[72][4][1]=2; 
rul[72][4][2]=8.215; rul[72][4][3]=max; 
// 6. sekcja AND 73 reguly.
rul[72][5][0]=8; rul[72][5][1]=2; 
rul[72][5][2]=1.0185; rul[72][5][3]=max; 
// 7. sekcja AND 73 reguly.
rul[72][6][0]=16; rul[72][6][1]=2; 
rul[72][6][2]=min; rul[72][6][3]=0.8145; 
// 8. sekcja AND 73 reguly.
rul[72][7][0]=33; rul[72][7][1]=2; 
rul[72][7][2]=min; rul[72][7][3]=73.918; 
// 9. sekcja AND 73 reguly.
rul[72][8][0]=21; rul[72][8][1]=2; 
rul[72][8][2]=min; rul[72][8][3]=0.1245; 
// 10. sekcja AND 73 reguly.
rul[72][9][0]=34; rul[72][9][1]=2; 
rul[72][9][2]=min; rul[72][9][3]=189.705; 
// 11. sekcja AND 73 reguly.
rul[72][10][0]=18; rul[72][10][1]=4; 
rul[72][10][2]=0.9085; rul[72][10][3]=max; rul[72][10][4]=min; rul[72][10][5]=0.9085; 
// 12. sekcja AND 73 reguly.
rul[72][11][0]=26; rul[72][11][1]=4; 
rul[72][11][2]=0.3215; rul[72][11][3]=0.6065; rul[72][11][4]=min; rul[72][11][5]=0.3215; 
// 13. sekcja AND 73 reguly.
rul[72][12][0]=10; rul[72][12][1]=2; 
rul[72][12][2]=1.5705; rul[72][12][3]=max; 
// 14. sekcja AND 73 reguly.
rul[72][13][0]=20; rul[72][13][1]=6; 
rul[72][13][2]=650.372; rul[72][13][3]=max; rul[72][13][4]=548.425; rul[72][13][5]=650.372; rul[72][13][6]=488.907; rul[72][13][7]=548.425; 
// 15. sekcja AND 73 reguly.
rul[72][14][0]=7; rul[72][14][1]=6; 
rul[72][14][2]=6.171; rul[72][14][3]=8.48; rul[72][14][4]=8.48; rul[72][14][5]=14.437; rul[72][14][6]=14.437; rul[72][14][7]=max; 
dl_reg[72]=15;
dec[72]=4; 
// 73. Koniec reguly
// 74. Regula
// 1. sekcja AND 74 reguly.
rul[73][0][0]=35; rul[73][0][1]=2; 
rul[73][0][2]=1; rul[73][0][3]=1; 
// 2. sekcja AND 74 reguly.
rul[73][1][0]=15; rul[73][1][1]=2; 
rul[73][1][2]=min; rul[73][1][3]=18.43; 
// 3. sekcja AND 74 reguly.
rul[73][2][0]=7; rul[73][2][1]=2; 
rul[73][2][2]=min; rul[73][2][3]=6.171; 
// 4. sekcja AND 74 reguly.
rul[73][3][0]=18; rul[73][3][1]=2; 
rul[73][3][2]=0.9085; rul[73][3][3]=max; 
// 5. sekcja AND 74 reguly.
rul[73][4][0]=27; rul[73][4][1]=2; 
rul[73][4][2]=0.6905; rul[73][4][3]=max; 
// 6. sekcja AND 74 reguly.
rul[73][5][0]=6; rul[73][5][1]=2; 
rul[73][5][2]=min; rul[73][5][3]=8.215; 
// 7. sekcja AND 74 reguly.
rul[73][6][0]=8; rul[73][6][1]=2; 
rul[73][6][2]=min; rul[73][6][3]=1.0185; 
// 8. sekcja AND 74 reguly.
rul[73][7][0]=16; rul[73][7][1]=2; 
rul[73][7][2]=0.8145; rul[73][7][3]=max; 
// 9. sekcja AND 74 reguly.
rul[73][8][0]=21; rul[73][8][1]=2; 
rul[73][8][2]=min; rul[73][8][3]=0.1245; 
// 10. sekcja AND 74 reguly.
rul[73][9][0]=26; rul[73][9][1]=2; 
rul[73][9][2]=0.6065; rul[73][9][3]=0.8585; 
// 11. sekcja AND 74 reguly.
rul[73][10][0]=4; rul[73][10][1]=2; 
rul[73][10][2]=0.6655; rul[73][10][3]=max; 
// 12. sekcja AND 74 reguly.
rul[73][11][0]=10; rul[73][11][1]=2; 
rul[73][11][2]=1.5705; rul[73][11][3]=max; 
// 13. sekcja AND 74 reguly.
rul[73][12][0]=34; rul[73][12][1]=2; 
rul[73][12][2]=min; rul[73][12][3]=189.705; 
// 14. sekcja AND 74 reguly.
rul[73][13][0]=3; rul[73][13][1]=2; 
rul[73][13][2]=min; rul[73][13][3]=1.368; 
// 15. sekcja AND 74 reguly.
rul[73][14][0]=32; rul[73][14][1]=2; 
rul[73][14][2]=234.086; rul[73][14][3]=max; 
dl_reg[73]=15;
dec[73]=4; 
// 74. Koniec reguly
// 75. Regula
// 1. sekcja AND 75 reguly.
rul[74][0][0]=35; rul[74][0][1]=2; 
rul[74][0][2]=1; rul[74][0][3]=1; 
// 2. sekcja AND 75 reguly.
rul[74][1][0]=15; rul[74][1][1]=2; 
rul[74][1][2]=min; rul[74][1][3]=18.43; 
// 3. sekcja AND 75 reguly.
rul[74][2][0]=4; rul[74][2][1]=2; 
rul[74][2][2]=0.6655; rul[74][2][3]=max; 
// 4. sekcja AND 75 reguly.
rul[74][3][0]=3; rul[74][3][1]=2; 
rul[74][3][2]=1.368; rul[74][3][3]=max; 
// 5. sekcja AND 75 reguly.
rul[74][4][0]=6; rul[74][4][1]=2; 
rul[74][4][2]=8.215; rul[74][4][3]=max; 
// 6. sekcja AND 75 reguly.
rul[74][5][0]=8; rul[74][5][1]=2; 
rul[74][5][2]=1.0185; rul[74][5][3]=max; 
// 7. sekcja AND 75 reguly.
rul[74][6][0]=16; rul[74][6][1]=2; 
rul[74][6][2]=min; rul[74][6][3]=0.8145; 
// 8. sekcja AND 75 reguly.
rul[74][7][0]=21; rul[74][7][1]=2; 
rul[74][7][2]=0.1245; rul[74][7][3]=max; 
// 9. sekcja AND 75 reguly.
rul[74][8][0]=10; rul[74][8][1]=2; 
rul[74][8][2]=1.5705; rul[74][8][3]=max; 
// 10. sekcja AND 75 reguly.
rul[74][9][0]=18; rul[74][9][1]=2; 
rul[74][9][2]=0.9085; rul[74][9][3]=max; 
// 11. sekcja AND 75 reguly.
rul[74][10][0]=26; rul[74][10][1]=2; 
rul[74][10][2]=0.3215; rul[74][10][3]=0.6065; 
// 12. sekcja AND 75 reguly.
rul[74][11][0]=32; rul[74][11][1]=2; 
rul[74][11][2]=min; rul[74][11][3]=198.694; 
// 13. sekcja AND 75 reguly.
rul[74][12][0]=33; rul[74][12][1]=2; 
rul[74][12][2]=73.918; rul[74][12][3]=137.781; 
// 14. sekcja AND 75 reguly.
rul[74][13][0]=34; rul[74][13][1]=2; 
rul[74][13][2]=240.981; rul[74][13][3]=max; 
// 15. sekcja AND 75 reguly.
rul[74][14][0]=20; rul[74][14][1]=2; 
rul[74][14][2]=356.734; rul[74][14][3]=488.907; 
dl_reg[74]=15;
dec[74]=4; 
// 75. Koniec reguly
// 76. Regula
// 1. sekcja AND 76 reguly.
rul[75][0][0]=35; rul[75][0][1]=2; 
rul[75][0][2]=1; rul[75][0][3]=1; 
// 2. sekcja AND 76 reguly.
rul[75][1][0]=15; rul[75][1][1]=2; 
rul[75][1][2]=min; rul[75][1][3]=18.43; 
// 3. sekcja AND 76 reguly.
rul[75][2][0]=4; rul[75][2][1]=2; 
rul[75][2][2]=0.6655; rul[75][2][3]=max; 
// 4. sekcja AND 76 reguly.
rul[75][3][0]=3; rul[75][3][1]=2; 
rul[75][3][2]=1.368; rul[75][3][3]=max; 
// 5. sekcja AND 76 reguly.
rul[75][4][0]=6; rul[75][4][1]=2; 
rul[75][4][2]=8.215; rul[75][4][3]=max; 
// 6. sekcja AND 76 reguly.
rul[75][5][0]=8; rul[75][5][1]=2; 
rul[75][5][2]=1.0185; rul[75][5][3]=max; 
// 7. sekcja AND 76 reguly.
rul[75][6][0]=16; rul[75][6][1]=2; 
rul[75][6][2]=min; rul[75][6][3]=0.8145; 
// 8. sekcja AND 76 reguly.
rul[75][7][0]=33; rul[75][7][1]=2; 
rul[75][7][2]=min; rul[75][7][3]=73.918; 
// 9. sekcja AND 76 reguly.
rul[75][8][0]=20; rul[75][8][1]=2; 
rul[75][8][2]=650.372; rul[75][8][3]=max; 
// 10. sekcja AND 76 reguly.
rul[75][9][0]=27; rul[75][9][1]=2; 
rul[75][9][2]=min; rul[75][9][3]=0.5825; 
// 11. sekcja AND 76 reguly.
rul[75][10][0]=18; rul[75][10][1]=2; 
rul[75][10][2]=min; rul[75][10][3]=0.9085; 
// 12. sekcja AND 76 reguly.
rul[75][11][0]=10; rul[75][11][1]=2; 
rul[75][11][2]=1.5705; rul[75][11][3]=max; 
// 13. sekcja AND 76 reguly.
rul[75][12][0]=7; rul[75][12][1]=4; 
rul[75][12][2]=min; rul[75][12][3]=6.171; rul[75][12][4]=14.437; rul[75][12][5]=max; 
// 14. sekcja AND 76 reguly.
rul[75][13][0]=32; rul[75][13][1]=2; 
rul[75][13][2]=198.694; rul[75][13][3]=234.086; 
dl_reg[75]=14;
dec[75]=4; 
// 76. Koniec reguly
// 77. Regula
// 1. sekcja AND 77 reguly.
rul[76][0][0]=35; rul[76][0][1]=2; 
rul[76][0][2]=1; rul[76][0][3]=1; 
// 2. sekcja AND 77 reguly.
rul[76][1][0]=15; rul[76][1][1]=2; 
rul[76][1][2]=min; rul[76][1][3]=18.43; 
// 3. sekcja AND 77 reguly.
rul[76][2][0]=4; rul[76][2][1]=2; 
rul[76][2][2]=0.6655; rul[76][2][3]=max; 
// 4. sekcja AND 77 reguly.
rul[76][3][0]=3; rul[76][3][1]=2; 
rul[76][3][2]=1.368; rul[76][3][3]=max; 
// 5. sekcja AND 77 reguly.
rul[76][4][0]=6; rul[76][4][1]=2; 
rul[76][4][2]=8.215; rul[76][4][3]=max; 
// 6. sekcja AND 77 reguly.
rul[76][5][0]=8; rul[76][5][1]=2; 
rul[76][5][2]=1.0185; rul[76][5][3]=max; 
// 7. sekcja AND 77 reguly.
rul[76][6][0]=16; rul[76][6][1]=2; 
rul[76][6][2]=min; rul[76][6][3]=0.8145; 
// 8. sekcja AND 77 reguly.
rul[76][7][0]=33; rul[76][7][1]=2; 
rul[76][7][2]=min; rul[76][7][3]=73.918; 
// 9. sekcja AND 77 reguly.
rul[76][8][0]=10; rul[76][8][1]=2; 
rul[76][8][2]=min; rul[76][8][3]=1.5705; 
// 10. sekcja AND 77 reguly.
rul[76][9][0]=18; rul[76][9][1]=2; 
rul[76][9][2]=0.9085; rul[76][9][3]=max; 
// 11. sekcja AND 77 reguly.
rul[76][10][0]=21; rul[76][10][1]=2; 
rul[76][10][2]=min; rul[76][10][3]=0.1245; 
// 12. sekcja AND 77 reguly.
rul[76][11][0]=20; rul[76][11][1]=2; 
rul[76][11][2]=650.372; rul[76][11][3]=max; 
// 13. sekcja AND 77 reguly.
rul[76][12][0]=32; rul[76][12][1]=2; 
rul[76][12][2]=234.086; rul[76][12][3]=max; 
// 14. sekcja AND 77 reguly.
rul[76][13][0]=34; rul[76][13][1]=2; 
rul[76][13][2]=189.705; rul[76][13][3]=240.981; 
dl_reg[76]=14;
dec[76]=4; 
// 77. Koniec reguly
// 78. Regula
// 1. sekcja AND 78 reguly.
rul[77][0][0]=35; rul[77][0][1]=2; 
rul[77][0][2]=1; rul[77][0][3]=1; 
// 2. sekcja AND 78 reguly.
rul[77][1][0]=15; rul[77][1][1]=2; 
rul[77][1][2]=min; rul[77][1][3]=18.43; 
// 3. sekcja AND 78 reguly.
rul[77][2][0]=7; rul[77][2][1]=2; 
rul[77][2][2]=min; rul[77][2][3]=6.171; 
// 4. sekcja AND 78 reguly.
rul[77][3][0]=18; rul[77][3][1]=2; 
rul[77][3][2]=0.9085; rul[77][3][3]=max; 
// 5. sekcja AND 78 reguly.
rul[77][4][0]=3; rul[77][4][1]=4; 
rul[77][4][2]=1.368; rul[77][4][3]=max; rul[77][4][4]=min; rul[77][4][5]=1.368; 
// 6. sekcja AND 78 reguly.
rul[77][5][0]=4; rul[77][5][1]=2; 
rul[77][5][2]=0.6655; rul[77][5][3]=max; 
// 7. sekcja AND 78 reguly.
rul[77][6][0]=21; rul[77][6][1]=4; 
rul[77][6][2]=min; rul[77][6][3]=0.1245; rul[77][6][4]=0.1245; rul[77][6][5]=max; 
// 8. sekcja AND 78 reguly.
rul[77][7][0]=10; rul[77][7][1]=2; 
rul[77][7][2]=1.5705; rul[77][7][3]=max; 
// 9. sekcja AND 78 reguly.
rul[77][8][0]=27; rul[77][8][1]=2; 
rul[77][8][2]=0.6905; rul[77][8][3]=max; 
// 10. sekcja AND 78 reguly.
rul[77][9][0]=6; rul[77][9][1]=2; 
rul[77][9][2]=8.215; rul[77][9][3]=max; 
// 11. sekcja AND 78 reguly.
rul[77][10][0]=8; rul[77][10][1]=2; 
rul[77][10][2]=1.0185; rul[77][10][3]=max; 
// 12. sekcja AND 78 reguly.
rul[77][11][0]=16; rul[77][11][1]=2; 
rul[77][11][2]=0.8145; rul[77][11][3]=max; 
dl_reg[77]=12;
dec[77]=4; 
// 78. Koniec reguly
// 79. Regula
// 1. sekcja AND 79 reguly.
rul[78][0][0]=35; rul[78][0][1]=2; 
rul[78][0][2]=1; rul[78][0][3]=1; 
// 2. sekcja AND 79 reguly.
rul[78][1][0]=15; rul[78][1][1]=2; 
rul[78][1][2]=min; rul[78][1][3]=18.43; 
// 3. sekcja AND 79 reguly.
rul[78][2][0]=7; rul[78][2][1]=2; 
rul[78][2][2]=min; rul[78][2][3]=6.171; 
// 4. sekcja AND 79 reguly.
rul[78][3][0]=16; rul[78][3][1]=2; 
rul[78][3][2]=0.8145; rul[78][3][3]=max; 
// 5. sekcja AND 79 reguly.
rul[78][4][0]=6; rul[78][4][1]=2; 
rul[78][4][2]=min; rul[78][4][3]=8.215; 
// 6. sekcja AND 79 reguly.
rul[78][5][0]=27; rul[78][5][1]=2; 
rul[78][5][2]=0.6905; rul[78][5][3]=max; 
// 7. sekcja AND 79 reguly.
rul[78][6][0]=8; rul[78][6][1]=2; 
rul[78][6][2]=min; rul[78][6][3]=1.0185; 
// 8. sekcja AND 79 reguly.
rul[78][7][0]=10; rul[78][7][1]=4; 
rul[78][7][2]=min; rul[78][7][3]=1.5705; rul[78][7][4]=1.5705; rul[78][7][5]=max; 
// 9. sekcja AND 79 reguly.
rul[78][8][0]=21; rul[78][8][1]=4; 
rul[78][8][2]=min; rul[78][8][3]=0.1245; rul[78][8][4]=0.1245; rul[78][8][5]=max; 
// 10. sekcja AND 79 reguly.
rul[78][9][0]=26; rul[78][9][1]=2; 
rul[78][9][2]=0.6065; rul[78][9][3]=0.8585; 
// 11. sekcja AND 79 reguly.
rul[78][10][0]=18; rul[78][10][1]=2; 
rul[78][10][2]=min; rul[78][10][3]=0.9085; 
// 12. sekcja AND 79 reguly.
rul[78][11][0]=33; rul[78][11][1]=2; 
rul[78][11][2]=min; rul[78][11][3]=73.918; 
// 13. sekcja AND 79 reguly.
rul[78][12][0]=4; rul[78][12][1]=4; 
rul[78][12][2]=min; rul[78][12][3]=0.6655; rul[78][12][4]=0.6655; rul[78][12][5]=max; 
// 14. sekcja AND 79 reguly.
rul[78][13][0]=3; rul[78][13][1]=4; 
rul[78][13][2]=min; rul[78][13][3]=1.368; rul[78][13][4]=1.368; rul[78][13][5]=max; 
// 15. sekcja AND 79 reguly.
rul[78][14][0]=34; rul[78][14][1]=4; 
rul[78][14][2]=240.981; rul[78][14][3]=max; rul[78][14][4]=189.705; rul[78][14][5]=240.981; 
dl_reg[78]=15;
dec[78]=4; 
// 79. Koniec reguly
// 80. Regula
// 1. sekcja AND 80 reguly.
rul[79][0][0]=35; rul[79][0][1]=2; 
rul[79][0][2]=1; rul[79][0][3]=1; 
// 2. sekcja AND 80 reguly.
rul[79][1][0]=15; rul[79][1][1]=2; 
rul[79][1][2]=min; rul[79][1][3]=18.43; 
// 3. sekcja AND 80 reguly.
rul[79][2][0]=4; rul[79][2][1]=2; 
rul[79][2][2]=0.6655; rul[79][2][3]=max; 
// 4. sekcja AND 80 reguly.
rul[79][3][0]=3; rul[79][3][1]=4; 
rul[79][3][2]=1.368; rul[79][3][3]=max; rul[79][3][4]=min; rul[79][3][5]=1.368; 
// 5. sekcja AND 80 reguly.
rul[79][4][0]=6; rul[79][4][1]=2; 
rul[79][4][2]=8.215; rul[79][4][3]=max; 
// 6. sekcja AND 80 reguly.
rul[79][5][0]=8; rul[79][5][1]=2; 
rul[79][5][2]=1.0185; rul[79][5][3]=max; 
// 7. sekcja AND 80 reguly.
rul[79][6][0]=16; rul[79][6][1]=2; 
rul[79][6][2]=min; rul[79][6][3]=0.8145; 
// 8. sekcja AND 80 reguly.
rul[79][7][0]=34; rul[79][7][1]=6; 
rul[79][7][2]=min; rul[79][7][3]=189.705; rul[79][7][4]=189.705; rul[79][7][5]=240.981; rul[79][7][6]=240.981; rul[79][7][7]=max; 
// 9. sekcja AND 80 reguly.
rul[79][8][0]=32; rul[79][8][1]=6; 
rul[79][8][2]=234.086; rul[79][8][3]=max; rul[79][8][4]=min; rul[79][8][5]=198.694; rul[79][8][6]=198.694; rul[79][8][7]=234.086; 
// 10. sekcja AND 80 reguly.
rul[79][9][0]=20; rul[79][9][1]=4; 
rul[79][9][2]=650.372; rul[79][9][3]=max; rul[79][9][4]=548.425; rul[79][9][5]=650.372; 
// 11. sekcja AND 80 reguly.
rul[79][10][0]=21; rul[79][10][1]=4; 
rul[79][10][2]=min; rul[79][10][3]=0.1245; rul[79][10][4]=0.1245; rul[79][10][5]=max; 
// 12. sekcja AND 80 reguly.
rul[79][11][0]=7; rul[79][11][1]=4; 
rul[79][11][2]=6.171; rul[79][11][3]=8.48; rul[79][11][4]=14.437; rul[79][11][5]=max; 
dl_reg[79]=12;
dec[79]=4; 
// 80. Koniec reguly
// 81. Regula
// 1. sekcja AND 81 reguly.
rul[80][0][0]=35; rul[80][0][1]=2; 
rul[80][0][2]=1; rul[80][0][3]=1; 
// 2. sekcja AND 81 reguly.
rul[80][1][0]=15; rul[80][1][1]=2; 
rul[80][1][2]=min; rul[80][1][3]=18.43; 
// 3. sekcja AND 81 reguly.
rul[80][2][0]=7; rul[80][2][1]=4; 
rul[80][2][2]=min; rul[80][2][3]=6.171; rul[80][2][4]=6.171; rul[80][2][5]=8.48; 
// 4. sekcja AND 81 reguly.
rul[80][3][0]=16; rul[80][3][1]=2; 
rul[80][3][2]=0.8145; rul[80][3][3]=max; 
// 5. sekcja AND 81 reguly.
rul[80][4][0]=27; rul[80][4][1]=2; 
rul[80][4][2]=0.6905; rul[80][4][3]=max; 
// 6. sekcja AND 81 reguly.
rul[80][5][0]=6; rul[80][5][1]=2; 
rul[80][5][2]=min; rul[80][5][3]=8.215; 
// 7. sekcja AND 81 reguly.
rul[80][6][0]=3; rul[80][6][1]=4; 
rul[80][6][2]=min; rul[80][6][3]=1.368; rul[80][6][4]=1.368; rul[80][6][5]=max; 
// 8. sekcja AND 81 reguly.
rul[80][7][0]=8; rul[80][7][1]=2; 
rul[80][7][2]=min; rul[80][7][3]=1.0185; 
// 9. sekcja AND 81 reguly.
rul[80][8][0]=10; rul[80][8][1]=2; 
rul[80][8][2]=min; rul[80][8][3]=1.5705; 
// 10. sekcja AND 81 reguly.
rul[80][9][0]=4; rul[80][9][1]=4; 
rul[80][9][2]=min; rul[80][9][3]=0.6655; rul[80][9][4]=0.6655; rul[80][9][5]=max; 
// 11. sekcja AND 81 reguly.
rul[80][10][0]=18; rul[80][10][1]=4; 
rul[80][10][2]=min; rul[80][10][3]=0.9085; rul[80][10][4]=0.9085; rul[80][10][5]=max; 
// 12. sekcja AND 81 reguly.
rul[80][11][0]=33; rul[80][11][1]=4; 
rul[80][11][2]=min; rul[80][11][3]=73.918; rul[80][11][4]=73.918; rul[80][11][5]=137.781; 
// 13. sekcja AND 81 reguly.
rul[80][12][0]=21; rul[80][12][1]=2; 
rul[80][12][2]=min; rul[80][12][3]=0.1245; 
// 14. sekcja AND 81 reguly.
rul[80][13][0]=20; rul[80][13][1]=2; 
rul[80][13][2]=488.907; rul[80][13][3]=548.425; 
dl_reg[80]=14;
dec[80]=4; 
// 81. Koniec reguly
// 82. Regula
// 1. sekcja AND 82 reguly.
rul[81][0][0]=35; rul[81][0][1]=2; 
rul[81][0][2]=1; rul[81][0][3]=1; 
// 2. sekcja AND 82 reguly.
rul[81][1][0]=15; rul[81][1][1]=2; 
rul[81][1][2]=min; rul[81][1][3]=18.43; 
// 3. sekcja AND 82 reguly.
rul[81][2][0]=7; rul[81][2][1]=4; 
rul[81][2][2]=min; rul[81][2][3]=6.171; rul[81][2][4]=6.171; rul[81][2][5]=8.48; 
// 4. sekcja AND 82 reguly.
rul[81][3][0]=4; rul[81][3][1]=2; 
rul[81][3][2]=0.6655; rul[81][3][3]=max; 
// 5. sekcja AND 82 reguly.
rul[81][4][0]=3; rul[81][4][1]=2; 
rul[81][4][2]=1.368; rul[81][4][3]=max; 
// 6. sekcja AND 82 reguly.
rul[81][5][0]=6; rul[81][5][1]=2; 
rul[81][5][2]=8.215; rul[81][5][3]=max; 
// 7. sekcja AND 82 reguly.
rul[81][6][0]=8; rul[81][6][1]=2; 
rul[81][6][2]=1.0185; rul[81][6][3]=max; 
// 8. sekcja AND 82 reguly.
rul[81][7][0]=16; rul[81][7][1]=2; 
rul[81][7][2]=min; rul[81][7][3]=0.8145; 
// 9. sekcja AND 82 reguly.
rul[81][8][0]=21; rul[81][8][1]=2; 
rul[81][8][2]=min; rul[81][8][3]=0.1245; 
// 10. sekcja AND 82 reguly.
rul[81][9][0]=10; rul[81][9][1]=4; 
rul[81][9][2]=1.5705; rul[81][9][3]=max; rul[81][9][4]=min; rul[81][9][5]=1.5705; 
// 11. sekcja AND 82 reguly.
rul[81][10][0]=33; rul[81][10][1]=4; 
rul[81][10][2]=min; rul[81][10][3]=73.918; rul[81][10][4]=73.918; rul[81][10][5]=137.781; 
// 12. sekcja AND 82 reguly.
rul[81][11][0]=18; rul[81][11][1]=2; 
rul[81][11][2]=min; rul[81][11][3]=0.9085; 
dl_reg[81]=12;
dec[81]=4; 
// 82. Koniec reguly
// 83. Regula
// 1. sekcja AND 83 reguly.
rul[82][0][0]=35; rul[82][0][1]=2; 
rul[82][0][2]=1; rul[82][0][3]=1; 
// 2. sekcja AND 83 reguly.
rul[82][1][0]=18; rul[82][1][1]=4; 
rul[82][1][2]=0.9085; rul[82][1][3]=max; rul[82][1][4]=min; rul[82][1][5]=0.9085; 
// 3. sekcja AND 83 reguly.
rul[82][2][0]=6; rul[82][2][1]=2; 
rul[82][2][2]=8.215; rul[82][2][3]=max; 
// 4. sekcja AND 83 reguly.
rul[82][3][0]=8; rul[82][3][1]=2; 
rul[82][3][2]=1.0185; rul[82][3][3]=max; 
// 5. sekcja AND 83 reguly.
rul[82][4][0]=4; rul[82][4][1]=2; 
rul[82][4][2]=0.6655; rul[82][4][3]=max; 
// 6. sekcja AND 83 reguly.
rul[82][5][0]=3; rul[82][5][1]=2; 
rul[82][5][2]=1.368; rul[82][5][3]=max; 
// 7. sekcja AND 83 reguly.
rul[82][6][0]=21; rul[82][6][1]=2; 
rul[82][6][2]=0.1245; rul[82][6][3]=max; 
// 8. sekcja AND 83 reguly.
rul[82][7][0]=16; rul[82][7][1]=2; 
rul[82][7][2]=min; rul[82][7][3]=0.8145; 
// 9. sekcja AND 83 reguly.
rul[82][8][0]=26; rul[82][8][1]=4; 
rul[82][8][2]=0.3215; rul[82][8][3]=0.6065; rul[82][8][4]=min; rul[82][8][5]=0.3215; 
// 10. sekcja AND 83 reguly.
rul[82][9][0]=10; rul[82][9][1]=2; 
rul[82][9][2]=1.5705; rul[82][9][3]=max; 
// 11. sekcja AND 83 reguly.
rul[82][10][0]=15; rul[82][10][1]=2; 
rul[82][10][2]=18.43; rul[82][10][3]=max; 
// 12. sekcja AND 83 reguly.
rul[82][11][0]=27; rul[82][11][1]=2; 
rul[82][11][2]=min; rul[82][11][3]=0.5825; 
// 13. sekcja AND 83 reguly.
rul[82][12][0]=34; rul[82][12][1]=2; 
rul[82][12][2]=240.981; rul[82][12][3]=max; 
dl_reg[82]=13;
dec[82]=4; 
// 83. Koniec reguly
// 84. Regula
// 1. sekcja AND 84 reguly.
rul[83][0][0]=35; rul[83][0][1]=2; 
rul[83][0][2]=1; rul[83][0][3]=1; 
// 2. sekcja AND 84 reguly.
rul[83][1][0]=15; rul[83][1][1]=2; 
rul[83][1][2]=min; rul[83][1][3]=18.43; 
// 3. sekcja AND 84 reguly.
rul[83][2][0]=7; rul[83][2][1]=2; 
rul[83][2][2]=min; rul[83][2][3]=6.171; 
// 4. sekcja AND 84 reguly.
rul[83][3][0]=6; rul[83][3][1]=2; 
rul[83][3][2]=min; rul[83][3][3]=8.215; 
// 5. sekcja AND 84 reguly.
rul[83][4][0]=8; rul[83][4][1]=2; 
rul[83][4][2]=min; rul[83][4][3]=1.0185; 
// 6. sekcja AND 84 reguly.
rul[83][5][0]=10; rul[83][5][1]=4; 
rul[83][5][2]=1.5705; rul[83][5][3]=max; rul[83][5][4]=min; rul[83][5][5]=1.5705; 
// 7. sekcja AND 84 reguly.
rul[83][6][0]=20; rul[83][6][1]=2; 
rul[83][6][2]=356.734; rul[83][6][3]=488.907; 
// 8. sekcja AND 84 reguly.
rul[83][7][0]=3; rul[83][7][1]=2; 
rul[83][7][2]=1.368; rul[83][7][3]=max; 
// 9. sekcja AND 84 reguly.
rul[83][8][0]=32; rul[83][8][1]=2; 
rul[83][8][2]=198.694; rul[83][8][3]=234.086; 
// 10. sekcja AND 84 reguly.
rul[83][9][0]=4; rul[83][9][1]=2; 
rul[83][9][2]=min; rul[83][9][3]=0.6655; 
// 11. sekcja AND 84 reguly.
rul[83][10][0]=18; rul[83][10][1]=2; 
rul[83][10][2]=0.9085; rul[83][10][3]=max; 
// 12. sekcja AND 84 reguly.
rul[83][11][0]=21; rul[83][11][1]=2; 
rul[83][11][2]=0.1245; rul[83][11][3]=max; 
dl_reg[83]=12;
dec[83]=4; 
// 84. Koniec reguly
// 85. Regula
// 1. sekcja AND 85 reguly.
rul[84][0][0]=35; rul[84][0][1]=2; 
rul[84][0][2]=1; rul[84][0][3]=1; 
// 2. sekcja AND 85 reguly.
rul[84][1][0]=15; rul[84][1][1]=2; 
rul[84][1][2]=min; rul[84][1][3]=18.43; 
// 3. sekcja AND 85 reguly.
rul[84][2][0]=33; rul[84][2][1]=2; 
rul[84][2][2]=min; rul[84][2][3]=73.918; 
// 4. sekcja AND 85 reguly.
rul[84][3][0]=10; rul[84][3][1]=4; 
rul[84][3][2]=min; rul[84][3][3]=1.5705; rul[84][3][4]=1.5705; rul[84][3][5]=max; 
// 5. sekcja AND 85 reguly.
rul[84][4][0]=7; rul[84][4][1]=4; 
rul[84][4][2]=min; rul[84][4][3]=6.171; rul[84][4][4]=6.171; rul[84][4][5]=8.48; 
// 6. sekcja AND 85 reguly.
rul[84][5][0]=6; rul[84][5][1]=2; 
rul[84][5][2]=min; rul[84][5][3]=8.215; 
// 7. sekcja AND 85 reguly.
rul[84][6][0]=3; rul[84][6][1]=4; 
rul[84][6][2]=min; rul[84][6][3]=1.368; rul[84][6][4]=1.368; rul[84][6][5]=max; 
// 8. sekcja AND 85 reguly.
rul[84][7][0]=16; rul[84][7][1]=4; 
rul[84][7][2]=0.8145; rul[84][7][3]=max; rul[84][7][4]=min; rul[84][7][5]=0.8145; 
// 9. sekcja AND 85 reguly.
rul[84][8][0]=21; rul[84][8][1]=4; 
rul[84][8][2]=min; rul[84][8][3]=0.1245; rul[84][8][4]=0.1245; rul[84][8][5]=max; 
// 10. sekcja AND 85 reguly.
rul[84][9][0]=27; rul[84][9][1]=4; 
rul[84][9][2]=0.6905; rul[84][9][3]=max; rul[84][9][4]=0.5825; rul[84][9][5]=0.6905; 
// 11. sekcja AND 85 reguly.
rul[84][10][0]=4; rul[84][10][1]=4; 
rul[84][10][2]=min; rul[84][10][3]=0.6655; rul[84][10][4]=0.6655; rul[84][10][5]=max; 
// 12. sekcja AND 85 reguly.
rul[84][11][0]=20; rul[84][11][1]=6; 
rul[84][11][2]=548.425; rul[84][11][3]=650.372; rul[84][11][4]=356.734; rul[84][11][5]=488.907; rul[84][11][6]=min; rul[84][11][7]=220.22; 
// 13. sekcja AND 85 reguly.
rul[84][12][0]=34; rul[84][12][1]=2; 
rul[84][12][2]=189.705; rul[84][12][3]=240.981; 
dl_reg[84]=13;
dec[84]=4; 
// 85. Koniec reguly
// 86. Regula
// 1. sekcja AND 86 reguly.
rul[85][0][0]=35; rul[85][0][1]=2; 
rul[85][0][2]=1; rul[85][0][3]=1; 
// 2. sekcja AND 86 reguly.
rul[85][1][0]=18; rul[85][1][1]=4; 
rul[85][1][2]=0.9085; rul[85][1][3]=max; rul[85][1][4]=min; rul[85][1][5]=0.9085; 
// 3. sekcja AND 86 reguly.
rul[85][2][0]=15; rul[85][2][1]=2; 
rul[85][2][2]=min; rul[85][2][3]=18.43; 
// 4. sekcja AND 86 reguly.
rul[85][3][0]=16; rul[85][3][1]=2; 
rul[85][3][2]=0.8145; rul[85][3][3]=max; 
// 5. sekcja AND 86 reguly.
rul[85][4][0]=27; rul[85][4][1]=2; 
rul[85][4][2]=0.6905; rul[85][4][3]=max; 
// 6. sekcja AND 86 reguly.
rul[85][5][0]=7; rul[85][5][1]=2; 
rul[85][5][2]=min; rul[85][5][3]=6.171; 
// 7. sekcja AND 86 reguly.
rul[85][6][0]=8; rul[85][6][1]=4; 
rul[85][6][2]=min; rul[85][6][3]=1.0185; rul[85][6][4]=1.0185; rul[85][6][5]=max; 
// 8. sekcja AND 86 reguly.
rul[85][7][0]=6; rul[85][7][1]=2; 
rul[85][7][2]=min; rul[85][7][3]=8.215; 
// 9. sekcja AND 86 reguly.
rul[85][8][0]=3; rul[85][8][1]=2; 
rul[85][8][2]=min; rul[85][8][3]=1.368; 
// 10. sekcja AND 86 reguly.
rul[85][9][0]=26; rul[85][9][1]=2; 
rul[85][9][2]=0.8585; rul[85][9][3]=max; 
// 11. sekcja AND 86 reguly.
rul[85][10][0]=4; rul[85][10][1]=2; 
rul[85][10][2]=min; rul[85][10][3]=0.6655; 
// 12. sekcja AND 86 reguly.
rul[85][11][0]=10; rul[85][11][1]=2; 
rul[85][11][2]=min; rul[85][11][3]=1.5705; 
// 13. sekcja AND 86 reguly.
rul[85][12][0]=20; rul[85][12][1]=2; 
rul[85][12][2]=356.734; rul[85][12][3]=488.907; 
dl_reg[85]=13;
dec[85]=3; 
// 86. Koniec reguly
// 87. Regula
// 1. sekcja AND 87 reguly.
rul[86][0][0]=35; rul[86][0][1]=2; 
rul[86][0][2]=1; rul[86][0][3]=1; 
// 2. sekcja AND 87 reguly.
rul[86][1][0]=3; rul[86][1][1]=2; 
rul[86][1][2]=1.368; rul[86][1][3]=max; 
// 3. sekcja AND 87 reguly.
rul[86][2][0]=6; rul[86][2][1]=2; 
rul[86][2][2]=8.215; rul[86][2][3]=max; 
// 4. sekcja AND 87 reguly.
rul[86][3][0]=8; rul[86][3][1]=2; 
rul[86][3][2]=1.0185; rul[86][3][3]=max; 
// 5. sekcja AND 87 reguly.
rul[86][4][0]=18; rul[86][4][1]=2; 
rul[86][4][2]=0.9085; rul[86][4][3]=max; 
// 6. sekcja AND 87 reguly.
rul[86][5][0]=21; rul[86][5][1]=2; 
rul[86][5][2]=0.1245; rul[86][5][3]=max; 
// 7. sekcja AND 87 reguly.
rul[86][6][0]=15; rul[86][6][1]=4; 
rul[86][6][2]=min; rul[86][6][3]=18.43; rul[86][6][4]=18.43; rul[86][6][5]=max; 
// 8. sekcja AND 87 reguly.
rul[86][7][0]=4; rul[86][7][1]=4; 
rul[86][7][2]=0.6655; rul[86][7][3]=max; rul[86][7][4]=min; rul[86][7][5]=0.6655; 
// 9. sekcja AND 87 reguly.
rul[86][8][0]=32; rul[86][8][1]=2; 
rul[86][8][2]=234.086; rul[86][8][3]=max; 
// 10. sekcja AND 87 reguly.
rul[86][9][0]=16; rul[86][9][1]=2; 
rul[86][9][2]=min; rul[86][9][3]=0.8145; 
// 11. sekcja AND 87 reguly.
rul[86][10][0]=27; rul[86][10][1]=4; 
rul[86][10][2]=min; rul[86][10][3]=0.5825; rul[86][10][4]=0.5825; rul[86][10][5]=0.6905; 
// 12. sekcja AND 87 reguly.
rul[86][11][0]=34; rul[86][11][1]=4; 
rul[86][11][2]=min; rul[86][11][3]=189.705; rul[86][11][4]=189.705; rul[86][11][5]=240.981; 
// 13. sekcja AND 87 reguly.
rul[86][12][0]=33; rul[86][12][1]=4; 
rul[86][12][2]=137.781; rul[86][12][3]=max; rul[86][12][4]=min; rul[86][12][5]=73.918; 
// 14. sekcja AND 87 reguly.
rul[86][13][0]=20; rul[86][13][1]=2; 
rul[86][13][2]=220.22; rul[86][13][3]=356.734; 
dl_reg[86]=14;
dec[86]=3; 
// 87. Koniec reguly
// 88. Regula
// 1. sekcja AND 88 reguly.
rul[87][0][0]=35; rul[87][0][1]=2; 
rul[87][0][2]=1; rul[87][0][3]=1; 
// 2. sekcja AND 88 reguly.
rul[87][1][0]=18; rul[87][1][1]=2; 
rul[87][1][2]=0.9085; rul[87][1][3]=max; 
// 3. sekcja AND 88 reguly.
rul[87][2][0]=15; rul[87][2][1]=2; 
rul[87][2][2]=min; rul[87][2][3]=18.43; 
// 4. sekcja AND 88 reguly.
rul[87][3][0]=16; rul[87][3][1]=2; 
rul[87][3][2]=0.8145; rul[87][3][3]=max; 
// 5. sekcja AND 88 reguly.
rul[87][4][0]=34; rul[87][4][1]=4; 
rul[87][4][2]=min; rul[87][4][3]=189.705; rul[87][4][4]=189.705; rul[87][4][5]=240.981; 
// 6. sekcja AND 88 reguly.
rul[87][5][0]=32; rul[87][5][1]=4; 
rul[87][5][2]=234.086; rul[87][5][3]=max; rul[87][5][4]=min; rul[87][5][5]=198.694; 
// 7. sekcja AND 88 reguly.
rul[87][6][0]=33; rul[87][6][1]=4; 
rul[87][6][2]=137.781; rul[87][6][3]=max; rul[87][6][4]=73.918; rul[87][6][5]=137.781; 
// 8. sekcja AND 88 reguly.
rul[87][7][0]=21; rul[87][7][1]=2; 
rul[87][7][2]=0.1245; rul[87][7][3]=max; 
// 9. sekcja AND 88 reguly.
rul[87][8][0]=4; rul[87][8][1]=2; 
rul[87][8][2]=min; rul[87][8][3]=0.6655; 
// 10. sekcja AND 88 reguly.
rul[87][9][0]=26; rul[87][9][1]=2; 
rul[87][9][2]=0.8585; rul[87][9][3]=max; 
// 11. sekcja AND 88 reguly.
rul[87][10][0]=3; rul[87][10][1]=4; 
rul[87][10][2]=min; rul[87][10][3]=1.368; rul[87][10][4]=1.368; rul[87][10][5]=max; 
// 12. sekcja AND 88 reguly.
rul[87][11][0]=6; rul[87][11][1]=2; 
rul[87][11][2]=min; rul[87][11][3]=8.215; 
dl_reg[87]=12;
dec[87]=3; 
// 88. Koniec reguly
// 89. Regula
// 1. sekcja AND 89 reguly.
rul[88][0][0]=35; rul[88][0][1]=2; 
rul[88][0][2]=1; rul[88][0][3]=1; 
// 2. sekcja AND 89 reguly.
rul[88][1][0]=18; rul[88][1][1]=2; 
rul[88][1][2]=0.9085; rul[88][1][3]=max; 
// 3. sekcja AND 89 reguly.
rul[88][2][0]=15; rul[88][2][1]=2; 
rul[88][2][2]=min; rul[88][2][3]=18.43; 
// 4. sekcja AND 89 reguly.
rul[88][3][0]=3; rul[88][3][1]=2; 
rul[88][3][2]=1.368; rul[88][3][3]=max; 
// 5. sekcja AND 89 reguly.
rul[88][4][0]=6; rul[88][4][1]=2; 
rul[88][4][2]=8.215; rul[88][4][3]=max; 
// 6. sekcja AND 89 reguly.
rul[88][5][0]=8; rul[88][5][1]=2; 
rul[88][5][2]=1.0185; rul[88][5][3]=max; 
// 7. sekcja AND 89 reguly.
rul[88][6][0]=4; rul[88][6][1]=2; 
rul[88][6][2]=0.6655; rul[88][6][3]=max; 
// 8. sekcja AND 89 reguly.
rul[88][7][0]=16; rul[88][7][1]=4; 
rul[88][7][2]=min; rul[88][7][3]=0.8145; rul[88][7][4]=0.8145; rul[88][7][5]=max; 
// 9. sekcja AND 89 reguly.
rul[88][8][0]=26; rul[88][8][1]=4; 
rul[88][8][2]=0.3215; rul[88][8][3]=0.6065; rul[88][8][4]=0.6065; rul[88][8][5]=0.8585; 
// 10. sekcja AND 89 reguly.
rul[88][9][0]=34; rul[88][9][1]=2; 
rul[88][9][2]=240.981; rul[88][9][3]=max; 
// 11. sekcja AND 89 reguly.
rul[88][10][0]=7; rul[88][10][1]=2; 
rul[88][10][2]=8.48; rul[88][10][3]=14.437; 
// 12. sekcja AND 89 reguly.
rul[88][11][0]=20; rul[88][11][1]=4; 
rul[88][11][2]=650.372; rul[88][11][3]=max; rul[88][11][4]=488.907; rul[88][11][5]=548.425; 
dl_reg[88]=12;
dec[88]=3; 
// 89. Koniec reguly
// 90. Regula
// 1. sekcja AND 90 reguly.
rul[89][0][0]=35; rul[89][0][1]=4; 
rul[89][0][2]=1; rul[89][0][3]=1; rul[89][0][4]=2; rul[89][0][5]=2; 
// 2. sekcja AND 90 reguly.
rul[89][1][0]=18; rul[89][1][1]=2; 
rul[89][1][2]=0.9085; rul[89][1][3]=max; 
// 3. sekcja AND 90 reguly.
rul[89][2][0]=15; rul[89][2][1]=2; 
rul[89][2][2]=min; rul[89][2][3]=18.43; 
// 4. sekcja AND 90 reguly.
rul[89][3][0]=16; rul[89][3][1]=2; 
rul[89][3][2]=0.8145; rul[89][3][3]=max; 
// 5. sekcja AND 90 reguly.
rul[89][4][0]=3; rul[89][4][1]=2; 
rul[89][4][2]=1.368; rul[89][4][3]=max; 
// 6. sekcja AND 90 reguly.
rul[89][5][0]=6; rul[89][5][1]=2; 
rul[89][5][2]=8.215; rul[89][5][3]=max; 
// 7. sekcja AND 90 reguly.
rul[89][6][0]=4; rul[89][6][1]=4; 
rul[89][6][2]=0.6655; rul[89][6][3]=max; rul[89][6][4]=min; rul[89][6][5]=0.6655; 
// 8. sekcja AND 90 reguly.
rul[89][7][0]=26; rul[89][7][1]=2; 
rul[89][7][2]=0.6065; rul[89][7][3]=0.8585; 
// 9. sekcja AND 90 reguly.
rul[89][8][0]=8; rul[89][8][1]=4; 
rul[89][8][2]=min; rul[89][8][3]=1.0185; rul[89][8][4]=1.0185; rul[89][8][5]=max; 
// 10. sekcja AND 90 reguly.
rul[89][9][0]=10; rul[89][9][1]=2; 
rul[89][9][2]=min; rul[89][9][3]=1.5705; 
// 11. sekcja AND 90 reguly.
rul[89][10][0]=27; rul[89][10][1]=2; 
rul[89][10][2]=0.6905; rul[89][10][3]=max; 
// 12. sekcja AND 90 reguly.
rul[89][11][0]=32; rul[89][11][1]=4; 
rul[89][11][2]=234.086; rul[89][11][3]=max; rul[89][11][4]=198.694; rul[89][11][5]=234.086; 
dl_reg[89]=12;
dec[89]=3; 
// 90. Koniec reguly
// 91. Regula
// 1. sekcja AND 91 reguly.
rul[90][0][0]=35; rul[90][0][1]=4; 
rul[90][0][2]=1; rul[90][0][3]=1; rul[90][0][4]=2; rul[90][0][5]=2; 
// 2. sekcja AND 91 reguly.
rul[90][1][0]=18; rul[90][1][1]=4; 
rul[90][1][2]=0.9085; rul[90][1][3]=max; rul[90][1][4]=min; rul[90][1][5]=0.9085; 
// 3. sekcja AND 91 reguly.
rul[90][2][0]=15; rul[90][2][1]=2; 
rul[90][2][2]=min; rul[90][2][3]=18.43; 
// 4. sekcja AND 91 reguly.
rul[90][3][0]=7; rul[90][3][1]=2; 
rul[90][3][2]=min; rul[90][3][3]=6.171; 
// 5. sekcja AND 91 reguly.
rul[90][4][0]=6; rul[90][4][1]=2; 
rul[90][4][2]=min; rul[90][4][3]=8.215; 
// 6. sekcja AND 91 reguly.
rul[90][5][0]=8; rul[90][5][1]=2; 
rul[90][5][2]=min; rul[90][5][3]=1.0185; 
// 7. sekcja AND 91 reguly.
rul[90][6][0]=27; rul[90][6][1]=2; 
rul[90][6][2]=0.6905; rul[90][6][3]=max; 
// 8. sekcja AND 91 reguly.
rul[90][7][0]=10; rul[90][7][1]=4; 
rul[90][7][2]=1.5705; rul[90][7][3]=max; rul[90][7][4]=min; rul[90][7][5]=1.5705; 
// 9. sekcja AND 91 reguly.
rul[90][8][0]=3; rul[90][8][1]=2; 
rul[90][8][2]=min; rul[90][8][3]=1.368; 
// 10. sekcja AND 91 reguly.
rul[90][9][0]=26; rul[90][9][1]=2; 
rul[90][9][2]=0.8585; rul[90][9][3]=max; 
// 11. sekcja AND 91 reguly.
rul[90][10][0]=4; rul[90][10][1]=2; 
rul[90][10][2]=0.6655; rul[90][10][3]=max; 
// 12. sekcja AND 91 reguly.
rul[90][11][0]=16; rul[90][11][1]=4; 
rul[90][11][2]=min; rul[90][11][3]=0.8145; rul[90][11][4]=0.8145; rul[90][11][5]=max; 
// 13. sekcja AND 91 reguly.
rul[90][12][0]=32; rul[90][12][1]=2; 
rul[90][12][2]=234.086; rul[90][12][3]=max; 
// 14. sekcja AND 91 reguly.
rul[90][13][0]=20; rul[90][13][1]=6; 
rul[90][13][2]=min; rul[90][13][3]=220.22; rul[90][13][4]=220.22; rul[90][13][5]=356.734; rul[90][13][6]=488.907; rul[90][13][7]=548.425; 
dl_reg[90]=14;
dec[90]=3; 
// 91. Koniec reguly
// 92. Regula
// 1. sekcja AND 92 reguly.
rul[91][0][0]=35; rul[91][0][1]=2; 
rul[91][0][2]=1; rul[91][0][3]=1; 
// 2. sekcja AND 92 reguly.
rul[91][1][0]=18; rul[91][1][1]=2; 
rul[91][1][2]=0.9085; rul[91][1][3]=max; 
// 3. sekcja AND 92 reguly.
rul[91][2][0]=3; rul[91][2][1]=2; 
rul[91][2][2]=1.368; rul[91][2][3]=max; 
// 4. sekcja AND 92 reguly.
rul[91][3][0]=6; rul[91][3][1]=2; 
rul[91][3][2]=8.215; rul[91][3][3]=max; 
// 5. sekcja AND 92 reguly.
rul[91][4][0]=8; rul[91][4][1]=2; 
rul[91][4][2]=1.0185; rul[91][4][3]=max; 
// 6. sekcja AND 92 reguly.
rul[91][5][0]=21; rul[91][5][1]=4; 
rul[91][5][2]=0.1245; rul[91][5][3]=max; rul[91][5][4]=min; rul[91][5][5]=0.1245; 
// 7. sekcja AND 92 reguly.
rul[91][6][0]=34; rul[91][6][1]=2; 
rul[91][6][2]=min; rul[91][6][3]=189.705; 
// 8. sekcja AND 92 reguly.
rul[91][7][0]=15; rul[91][7][1]=2; 
rul[91][7][2]=18.43; rul[91][7][3]=max; 
// 9. sekcja AND 92 reguly.
rul[91][8][0]=26; rul[91][8][1]=4; 
rul[91][8][2]=0.3215; rul[91][8][3]=0.6065; rul[91][8][4]=0.6065; rul[91][8][5]=0.8585; 
// 10. sekcja AND 92 reguly.
rul[91][9][0]=10; rul[91][9][1]=2; 
rul[91][9][2]=1.5705; rul[91][9][3]=max; 
// 11. sekcja AND 92 reguly.
rul[91][10][0]=33; rul[91][10][1]=2; 
rul[91][10][2]=73.918; rul[91][10][3]=137.781; 
dl_reg[91]=11;
dec[91]=3; 
// 92. Koniec reguly
// 93. Regula
// 1. sekcja AND 93 reguly.
rul[92][0][0]=35; rul[92][0][1]=2; 
rul[92][0][2]=1; rul[92][0][3]=1; 
// 2. sekcja AND 93 reguly.
rul[92][1][0]=15; rul[92][1][1]=2; 
rul[92][1][2]=min; rul[92][1][3]=18.43; 
// 3. sekcja AND 93 reguly.
rul[92][2][0]=7; rul[92][2][1]=2; 
rul[92][2][2]=min; rul[92][2][3]=6.171; 
// 4. sekcja AND 93 reguly.
rul[92][3][0]=6; rul[92][3][1]=2; 
rul[92][3][2]=min; rul[92][3][3]=8.215; 
// 5. sekcja AND 93 reguly.
rul[92][4][0]=27; rul[92][4][1]=2; 
rul[92][4][2]=0.6905; rul[92][4][3]=max; 
// 6. sekcja AND 93 reguly.
rul[92][5][0]=8; rul[92][5][1]=2; 
rul[92][5][2]=min; rul[92][5][3]=1.0185; 
// 7. sekcja AND 93 reguly.
rul[92][6][0]=16; rul[92][6][1]=2; 
rul[92][6][2]=0.8145; rul[92][6][3]=max; 
// 8. sekcja AND 93 reguly.
rul[92][7][0]=21; rul[92][7][1]=2; 
rul[92][7][2]=min; rul[92][7][3]=0.1245; 
// 9. sekcja AND 93 reguly.
rul[92][8][0]=18; rul[92][8][1]=2; 
rul[92][8][2]=min; rul[92][8][3]=0.9085; 
// 10. sekcja AND 93 reguly.
rul[92][9][0]=3; rul[92][9][1]=2; 
rul[92][9][2]=min; rul[92][9][3]=1.368; 
// 11. sekcja AND 93 reguly.
rul[92][10][0]=26; rul[92][10][1]=2; 
rul[92][10][2]=0.6065; rul[92][10][3]=0.8585; 
// 12. sekcja AND 93 reguly.
rul[92][11][0]=34; rul[92][11][1]=2; 
rul[92][11][2]=min; rul[92][11][3]=189.705; 
// 13. sekcja AND 93 reguly.
rul[92][12][0]=4; rul[92][12][1]=2; 
rul[92][12][2]=0.6655; rul[92][12][3]=max; 
dl_reg[92]=13;
dec[92]=3; 
// 93. Koniec reguly
// 94. Regula
// 1. sekcja AND 94 reguly.
rul[93][0][0]=35; rul[93][0][1]=2; 
rul[93][0][2]=1; rul[93][0][3]=1; 
// 2. sekcja AND 94 reguly.
rul[93][1][0]=18; rul[93][1][1]=2; 
rul[93][1][2]=0.9085; rul[93][1][3]=max; 
// 3. sekcja AND 94 reguly.
rul[93][2][0]=6; rul[93][2][1]=2; 
rul[93][2][2]=8.215; rul[93][2][3]=max; 
// 4. sekcja AND 94 reguly.
rul[93][3][0]=8; rul[93][3][1]=2; 
rul[93][3][2]=1.0185; rul[93][3][3]=max; 
// 5. sekcja AND 94 reguly.
rul[93][4][0]=3; rul[93][4][1]=2; 
rul[93][4][2]=1.368; rul[93][4][3]=max; 
// 6. sekcja AND 94 reguly.
rul[93][5][0]=10; rul[93][5][1]=2; 
rul[93][5][2]=min; rul[93][5][3]=1.5705; 
// 7. sekcja AND 94 reguly.
rul[93][6][0]=16; rul[93][6][1]=2; 
rul[93][6][2]=min; rul[93][6][3]=0.8145; 
// 8. sekcja AND 94 reguly.
rul[93][7][0]=26; rul[93][7][1]=2; 
rul[93][7][2]=0.3215; rul[93][7][3]=0.6065; 
// 9. sekcja AND 94 reguly.
rul[93][8][0]=4; rul[93][8][1]=2; 
rul[93][8][2]=0.6655; rul[93][8][3]=max; 
// 10. sekcja AND 94 reguly.
rul[93][9][0]=15; rul[93][9][1]=2; 
rul[93][9][2]=18.43; rul[93][9][3]=max; 
// 11. sekcja AND 94 reguly.
rul[93][10][0]=32; rul[93][10][1]=2; 
rul[93][10][2]=min; rul[93][10][3]=198.694; 
dl_reg[93]=11;
dec[93]=3; 
// 94. Koniec reguly
// 95. Regula
// 1. sekcja AND 95 reguly.
rul[94][0][0]=18; rul[94][0][1]=2; 
rul[94][0][2]=0.9085; rul[94][0][3]=max; 
// 2. sekcja AND 95 reguly.
rul[94][1][0]=6; rul[94][1][1]=2; 
rul[94][1][2]=8.215; rul[94][1][3]=max; 
// 3. sekcja AND 95 reguly.
rul[94][2][0]=8; rul[94][2][1]=2; 
rul[94][2][2]=1.0185; rul[94][2][3]=max; 
// 4. sekcja AND 95 reguly.
rul[94][3][0]=3; rul[94][3][1]=2; 
rul[94][3][2]=1.368; rul[94][3][3]=max; 
// 5. sekcja AND 95 reguly.
rul[94][4][0]=4; rul[94][4][1]=2; 
rul[94][4][2]=min; rul[94][4][3]=0.6655; 
// 6. sekcja AND 95 reguly.
rul[94][5][0]=21; rul[94][5][1]=2; 
rul[94][5][2]=0.1245; rul[94][5][3]=max; 
// 7. sekcja AND 95 reguly.
rul[94][6][0]=33; rul[94][6][1]=2; 
rul[94][6][2]=137.781; rul[94][6][3]=max; 
// 8. sekcja AND 95 reguly.
rul[94][7][0]=35; rul[94][7][1]=2; 
rul[94][7][2]=2; rul[94][7][3]=2; 
// 9. sekcja AND 95 reguly.
rul[94][8][0]=34; rul[94][8][1]=2; 
rul[94][8][2]=240.981; rul[94][8][3]=max; 
// 10. sekcja AND 95 reguly.
rul[94][9][0]=10; rul[94][9][1]=2; 
rul[94][9][2]=1.5705; rul[94][9][3]=max; 
// 11. sekcja AND 95 reguly.
rul[94][10][0]=16; rul[94][10][1]=2; 
rul[94][10][2]=0.8145; rul[94][10][3]=max; 
// 12. sekcja AND 95 reguly.
rul[94][11][0]=32; rul[94][11][1]=2; 
rul[94][11][2]=234.086; rul[94][11][3]=max; 
// 13. sekcja AND 95 reguly.
rul[94][12][0]=15; rul[94][12][1]=2; 
rul[94][12][2]=min; rul[94][12][3]=18.43; 
dl_reg[94]=13;
dec[94]=3; 
// 95. Koniec reguly
// 96. Regula
// 1. sekcja AND 96 reguly.
rul[95][0][0]=18; rul[95][0][1]=2; 
rul[95][0][2]=0.9085; rul[95][0][3]=max; 
// 2. sekcja AND 96 reguly.
rul[95][1][0]=3; rul[95][1][1]=2; 
rul[95][1][2]=1.368; rul[95][1][3]=max; 
// 3. sekcja AND 96 reguly.
rul[95][2][0]=6; rul[95][2][1]=2; 
rul[95][2][2]=8.215; rul[95][2][3]=max; 
// 4. sekcja AND 96 reguly.
rul[95][3][0]=8; rul[95][3][1]=2; 
rul[95][3][2]=1.0185; rul[95][3][3]=max; 
// 5. sekcja AND 96 reguly.
rul[95][4][0]=21; rul[95][4][1]=2; 
rul[95][4][2]=0.1245; rul[95][4][3]=max; 
// 6. sekcja AND 96 reguly.
rul[95][5][0]=4; rul[95][5][1]=2; 
rul[95][5][2]=min; rul[95][5][3]=0.6655; 
// 7. sekcja AND 96 reguly.
rul[95][6][0]=27; rul[95][6][1]=2; 
rul[95][6][2]=min; rul[95][6][3]=0.5825; 
// 8. sekcja AND 96 reguly.
rul[95][7][0]=32; rul[95][7][1]=2; 
rul[95][7][2]=min; rul[95][7][3]=198.694; 
// 9. sekcja AND 96 reguly.
rul[95][8][0]=34; rul[95][8][1]=2; 
rul[95][8][2]=240.981; rul[95][8][3]=max; 
// 10. sekcja AND 96 reguly.
rul[95][9][0]=15; rul[95][9][1]=2; 
rul[95][9][2]=18.43; rul[95][9][3]=max; 
// 11. sekcja AND 96 reguly.
rul[95][10][0]=33; rul[95][10][1]=2; 
rul[95][10][2]=137.781; rul[95][10][3]=max; 
// 12. sekcja AND 96 reguly.
rul[95][11][0]=35; rul[95][11][1]=2; 
rul[95][11][2]=2; rul[95][11][3]=2; 
dl_reg[95]=12;
dec[95]=3; 
// 96. Koniec reguly
// 97. Regula
// 1. sekcja AND 97 reguly.
rul[96][0][0]=18; rul[96][0][1]=2; 
rul[96][0][2]=0.9085; rul[96][0][3]=max; 
// 2. sekcja AND 97 reguly.
rul[96][1][0]=15; rul[96][1][1]=2; 
rul[96][1][2]=min; rul[96][1][3]=18.43; 
// 3. sekcja AND 97 reguly.
rul[96][2][0]=16; rul[96][2][1]=2; 
rul[96][2][2]=0.8145; rul[96][2][3]=max; 
// 4. sekcja AND 97 reguly.
rul[96][3][0]=3; rul[96][3][1]=2; 
rul[96][3][2]=1.368; rul[96][3][3]=max; 
// 5. sekcja AND 97 reguly.
rul[96][4][0]=6; rul[96][4][1]=2; 
rul[96][4][2]=8.215; rul[96][4][3]=max; 
// 6. sekcja AND 97 reguly.
rul[96][5][0]=8; rul[96][5][1]=2; 
rul[96][5][2]=1.0185; rul[96][5][3]=max; 
// 7. sekcja AND 97 reguly.
rul[96][6][0]=26; rul[96][6][1]=2; 
rul[96][6][2]=0.6065; rul[96][6][3]=0.8585; 
// 8. sekcja AND 97 reguly.
rul[96][7][0]=21; rul[96][7][1]=4; 
rul[96][7][2]=0.1245; rul[96][7][3]=max; rul[96][7][4]=min; rul[96][7][5]=0.1245; 
// 9. sekcja AND 97 reguly.
rul[96][8][0]=4; rul[96][8][1]=2; 
rul[96][8][2]=min; rul[96][8][3]=0.6655; 
// 10. sekcja AND 97 reguly.
rul[96][9][0]=7; rul[96][9][1]=2; 
rul[96][9][2]=8.48; rul[96][9][3]=14.437; 
dl_reg[96]=10;
dec[96]=3; 
// 97. Koniec reguly
// 98. Regula
// 1. sekcja AND 98 reguly.
rul[97][0][0]=15; rul[97][0][1]=2; 
rul[97][0][2]=min; rul[97][0][3]=18.43; 
// 2. sekcja AND 98 reguly.
rul[97][1][0]=7; rul[97][1][1]=2; 
rul[97][1][2]=min; rul[97][1][3]=6.171; 
// 3. sekcja AND 98 reguly.
rul[97][2][0]=6; rul[97][2][1]=2; 
rul[97][2][2]=min; rul[97][2][3]=8.215; 
// 4. sekcja AND 98 reguly.
rul[97][3][0]=16; rul[97][3][1]=4; 
rul[97][3][2]=0.8145; rul[97][3][3]=max; rul[97][3][4]=min; rul[97][3][5]=0.8145; 
// 5. sekcja AND 98 reguly.
rul[97][4][0]=27; rul[97][4][1]=2; 
rul[97][4][2]=0.6905; rul[97][4][3]=max; 
// 6. sekcja AND 98 reguly.
rul[97][5][0]=8; rul[97][5][1]=2; 
rul[97][5][2]=min; rul[97][5][3]=1.0185; 
// 7. sekcja AND 98 reguly.
rul[97][6][0]=3; rul[97][6][1]=2; 
rul[97][6][2]=min; rul[97][6][3]=1.368; 
// 8. sekcja AND 98 reguly.
rul[97][7][0]=4; rul[97][7][1]=2; 
rul[97][7][2]=0.6655; rul[97][7][3]=max; 
// 9. sekcja AND 98 reguly.
rul[97][8][0]=26; rul[97][8][1]=2; 
rul[97][8][2]=0.8585; rul[97][8][3]=max; 
// 10. sekcja AND 98 reguly.
rul[97][9][0]=10; rul[97][9][1]=4; 
rul[97][9][2]=1.5705; rul[97][9][3]=max; rul[97][9][4]=min; rul[97][9][5]=1.5705; 
// 11. sekcja AND 98 reguly.
rul[97][10][0]=20; rul[97][10][1]=6; 
rul[97][10][2]=min; rul[97][10][3]=220.22; rul[97][10][4]=220.22; rul[97][10][5]=356.734; rul[97][10][6]=488.907; rul[97][10][7]=548.425; 
// 12. sekcja AND 98 reguly.
rul[97][11][0]=32; rul[97][11][1]=2; 
rul[97][11][2]=234.086; rul[97][11][3]=max; 
dl_reg[97]=12;
dec[97]=3; 
// 98. Koniec reguly
// 99. Regula
// 1. sekcja AND 99 reguly.
rul[98][0][0]=35; rul[98][0][1]=2; 
rul[98][0][2]=1; rul[98][0][3]=1; 
// 2. sekcja AND 99 reguly.
rul[98][1][0]=18; rul[98][1][1]=2; 
rul[98][1][2]=0.9085; rul[98][1][3]=max; 
// 3. sekcja AND 99 reguly.
rul[98][2][0]=15; rul[98][2][1]=2; 
rul[98][2][2]=min; rul[98][2][3]=18.43; 
// 4. sekcja AND 99 reguly.
rul[98][3][0]=16; rul[98][3][1]=2; 
rul[98][3][2]=0.8145; rul[98][3][3]=max; 
// 5. sekcja AND 99 reguly.
rul[98][4][0]=33; rul[98][4][1]=4; 
rul[98][4][2]=min; rul[98][4][3]=73.918; rul[98][4][4]=73.918; rul[98][4][5]=137.781; 
// 6. sekcja AND 99 reguly.
rul[98][5][0]=20; rul[98][5][1]=2; 
rul[98][5][2]=650.372; rul[98][5][3]=max; 
// 7. sekcja AND 99 reguly.
rul[98][6][0]=21; rul[98][6][1]=2; 
rul[98][6][2]=min; rul[98][6][3]=0.1245; 
// 8. sekcja AND 99 reguly.
rul[98][7][0]=7; rul[98][7][1]=2; 
rul[98][7][2]=min; rul[98][7][3]=6.171; 
// 9. sekcja AND 99 reguly.
rul[98][8][0]=6; rul[98][8][1]=2; 
rul[98][8][2]=min; rul[98][8][3]=8.215; 
// 10. sekcja AND 99 reguly.
rul[98][9][0]=8; rul[98][9][1]=2; 
rul[98][9][2]=min; rul[98][9][3]=1.0185; 
// 11. sekcja AND 99 reguly.
rul[98][10][0]=3; rul[98][10][1]=4; 
rul[98][10][2]=1.368; rul[98][10][3]=max; rul[98][10][4]=min; rul[98][10][5]=1.368; 
// 12. sekcja AND 99 reguly.
rul[98][11][0]=4; rul[98][11][1]=2; 
rul[98][11][2]=min; rul[98][11][3]=0.6655; 
// 13. sekcja AND 99 reguly.
rul[98][12][0]=10; rul[98][12][1]=2; 
rul[98][12][2]=1.5705; rul[98][12][3]=max; 
// 14. sekcja AND 99 reguly.
rul[98][13][0]=26; rul[98][13][1]=2; 
rul[98][13][2]=0.8585; rul[98][13][3]=max; 
dl_reg[98]=14;
dec[98]=2; 
// 99. Koniec reguly
// 100. Regula
// 1. sekcja AND 100 reguly.
rul[99][0][0]=35; rul[99][0][1]=2; 
rul[99][0][2]=1; rul[99][0][3]=1; 
// 2. sekcja AND 100 reguly.
rul[99][1][0]=18; rul[99][1][1]=4; 
rul[99][1][2]=0.9085; rul[99][1][3]=max; rul[99][1][4]=min; rul[99][1][5]=0.9085; 
// 3. sekcja AND 100 reguly.
rul[99][2][0]=6; rul[99][2][1]=2; 
rul[99][2][2]=8.215; rul[99][2][3]=max; 
// 4. sekcja AND 100 reguly.
rul[99][3][0]=8; rul[99][3][1]=4; 
rul[99][3][2]=1.0185; rul[99][3][3]=max; rul[99][3][4]=min; rul[99][3][5]=1.0185; 
// 5. sekcja AND 100 reguly.
rul[99][4][0]=3; rul[99][4][1]=2; 
rul[99][4][2]=1.368; rul[99][4][3]=max; 
// 6. sekcja AND 100 reguly.
rul[99][5][0]=33; rul[99][5][1]=2; 
rul[99][5][2]=min; rul[99][5][3]=73.918; 
// 7. sekcja AND 100 reguly.
rul[99][6][0]=4; rul[99][6][1]=2; 
rul[99][6][2]=min; rul[99][6][3]=0.6655; 
// 8. sekcja AND 100 reguly.
rul[99][7][0]=10; rul[99][7][1]=4; 
rul[99][7][2]=min; rul[99][7][3]=1.5705; rul[99][7][4]=1.5705; rul[99][7][5]=max; 
// 9. sekcja AND 100 reguly.
rul[99][8][0]=27; rul[99][8][1]=2; 
rul[99][8][2]=min; rul[99][8][3]=0.5825; 
// 10. sekcja AND 100 reguly.
rul[99][9][0]=15; rul[99][9][1]=4; 
rul[99][9][2]=min; rul[99][9][3]=18.43; rul[99][9][4]=18.43; rul[99][9][5]=max; 
// 11. sekcja AND 100 reguly.
rul[99][10][0]=7; rul[99][10][1]=6; 
rul[99][10][2]=min; rul[99][10][3]=6.171; rul[99][10][4]=6.171; rul[99][10][5]=8.48; rul[99][10][6]=14.437; rul[99][10][7]=max; 
// 12. sekcja AND 100 reguly.
rul[99][11][0]=20; rul[99][11][1]=8; 
rul[99][11][2]=650.372; rul[99][11][3]=max; rul[99][11][4]=548.425; rul[99][11][5]=650.372; rul[99][11][6]=488.907; rul[99][11][7]=548.425; 
rul[99][11][8]=356.734; rul[99][11][9]=488.907; 
// 13. sekcja AND 100 reguly.
rul[99][12][0]=34; rul[99][12][1]=4; 
rul[99][12][2]=min; rul[99][12][3]=189.705; rul[99][12][4]=189.705; rul[99][12][5]=240.981; 
dl_reg[99]=13;
dec[99]=2; 
// 100. Koniec reguly
// 101. Regula
// 1. sekcja AND 101 reguly.
rul[100][0][0]=35; rul[100][0][1]=2; 
rul[100][0][2]=1; rul[100][0][3]=1; 
// 2. sekcja AND 101 reguly.
rul[100][1][0]=18; rul[100][1][1]=4; 
rul[100][1][2]=0.9085; rul[100][1][3]=max; rul[100][1][4]=min; rul[100][1][5]=0.9085; 
// 3. sekcja AND 101 reguly.
rul[100][2][0]=6; rul[100][2][1]=4; 
rul[100][2][2]=8.215; rul[100][2][3]=max; rul[100][2][4]=min; rul[100][2][5]=8.215; 
// 4. sekcja AND 101 reguly.
rul[100][3][0]=8; rul[100][3][1]=4; 
rul[100][3][2]=1.0185; rul[100][3][3]=max; rul[100][3][4]=min; rul[100][3][5]=1.0185; 
// 5. sekcja AND 101 reguly.
rul[100][4][0]=3; rul[100][4][1]=2; 
rul[100][4][2]=1.368; rul[100][4][3]=max; 
// 6. sekcja AND 101 reguly.
rul[100][5][0]=33; rul[100][5][1]=2; 
rul[100][5][2]=min; rul[100][5][3]=73.918; 
// 7. sekcja AND 101 reguly.
rul[100][6][0]=4; rul[100][6][1]=2; 
rul[100][6][2]=min; rul[100][6][3]=0.6655; 
// 8. sekcja AND 101 reguly.
rul[100][7][0]=21; rul[100][7][1]=4; 
rul[100][7][2]=0.1245; rul[100][7][3]=max; rul[100][7][4]=min; rul[100][7][5]=0.1245; 
// 9. sekcja AND 101 reguly.
rul[100][8][0]=32; rul[100][8][1]=2; 
rul[100][8][2]=min; rul[100][8][3]=198.694; 
// 10. sekcja AND 101 reguly.
rul[100][9][0]=10; rul[100][9][1]=4; 
rul[100][9][2]=1.5705; rul[100][9][3]=max; rul[100][9][4]=min; rul[100][9][5]=1.5705; 
// 11. sekcja AND 101 reguly.
rul[100][10][0]=16; rul[100][10][1]=4; 
rul[100][10][2]=0.8145; rul[100][10][3]=max; rul[100][10][4]=min; rul[100][10][5]=0.8145; 
// 12. sekcja AND 101 reguly.
rul[100][11][0]=7; rul[100][11][1]=6; 
rul[100][11][2]=8.48; rul[100][11][3]=14.437; rul[100][11][4]=6.171; rul[100][11][5]=8.48; rul[100][11][6]=min; rul[100][11][7]=6.171; 
// 13. sekcja AND 101 reguly.
rul[100][12][0]=26; rul[100][12][1]=2; 
rul[100][12][2]=0.3215; rul[100][12][3]=0.6065; 
dl_reg[100]=13;
dec[100]=2; 
// 101. Koniec reguly
// 102. Regula
// 1. sekcja AND 102 reguly.
rul[101][0][0]=35; rul[101][0][1]=2; 
rul[101][0][2]=1; rul[101][0][3]=1; 
// 2. sekcja AND 102 reguly.
rul[101][1][0]=18; rul[101][1][1]=2; 
rul[101][1][2]=0.9085; rul[101][1][3]=max; 
// 3. sekcja AND 102 reguly.
rul[101][2][0]=15; rul[101][2][1]=4; 
rul[101][2][2]=min; rul[101][2][3]=18.43; rul[101][2][4]=18.43; rul[101][2][5]=max; 
// 4. sekcja AND 102 reguly.
rul[101][3][0]=16; rul[101][3][1]=2; 
rul[101][3][2]=0.8145; rul[101][3][3]=max; 
// 5. sekcja AND 102 reguly.
rul[101][4][0]=21; rul[101][4][1]=2; 
rul[101][4][2]=min; rul[101][4][3]=0.1245; 
// 6. sekcja AND 102 reguly.
rul[101][5][0]=20; rul[101][5][1]=2; 
rul[101][5][2]=650.372; rul[101][5][3]=max; 
// 7. sekcja AND 102 reguly.
rul[101][6][0]=33; rul[101][6][1]=2; 
rul[101][6][2]=min; rul[101][6][3]=73.918; 
// 8. sekcja AND 102 reguly.
rul[101][7][0]=8; rul[101][7][1]=2; 
rul[101][7][2]=1.0185; rul[101][7][3]=max; 
// 9. sekcja AND 102 reguly.
rul[101][8][0]=7; rul[101][8][1]=2; 
rul[101][8][2]=6.171; rul[101][8][3]=8.48; 
// 10. sekcja AND 102 reguly.
rul[101][9][0]=6; rul[101][9][1]=2; 
rul[101][9][2]=8.215; rul[101][9][3]=max; 
// 11. sekcja AND 102 reguly.
rul[101][10][0]=3; rul[101][10][1]=2; 
rul[101][10][2]=1.368; rul[101][10][3]=max; 
// 12. sekcja AND 102 reguly.
rul[101][11][0]=26; rul[101][11][1]=2; 
rul[101][11][2]=0.6065; rul[101][11][3]=0.8585; 
dl_reg[101]=12;
dec[101]=2; 
// 102. Koniec reguly
// 103. Regula
// 1. sekcja AND 103 reguly.
rul[102][0][0]=35; rul[102][0][1]=2; 
rul[102][0][2]=1; rul[102][0][3]=1; 
// 2. sekcja AND 103 reguly.
rul[102][1][0]=18; rul[102][1][1]=2; 
rul[102][1][2]=0.9085; rul[102][1][3]=max; 
// 3. sekcja AND 103 reguly.
rul[102][2][0]=15; rul[102][2][1]=2; 
rul[102][2][2]=min; rul[102][2][3]=18.43; 
// 4. sekcja AND 103 reguly.
rul[102][3][0]=16; rul[102][3][1]=2; 
rul[102][3][2]=0.8145; rul[102][3][3]=max; 
// 5. sekcja AND 103 reguly.
rul[102][4][0]=3; rul[102][4][1]=4; 
rul[102][4][2]=min; rul[102][4][3]=1.368; rul[102][4][4]=1.368; rul[102][4][5]=max; 
// 6. sekcja AND 103 reguly.
rul[102][5][0]=6; rul[102][5][1]=4; 
rul[102][5][2]=min; rul[102][5][3]=8.215; rul[102][5][4]=8.215; rul[102][5][5]=max; 
// 7. sekcja AND 103 reguly.
rul[102][6][0]=7; rul[102][6][1]=4; 
rul[102][6][2]=6.171; rul[102][6][3]=8.48; rul[102][6][4]=8.48; rul[102][6][5]=14.437; 
// 8. sekcja AND 103 reguly.
rul[102][7][0]=4; rul[102][7][1]=2; 
rul[102][7][2]=min; rul[102][7][3]=0.6655; 
// 9. sekcja AND 103 reguly.
rul[102][8][0]=8; rul[102][8][1]=2; 
rul[102][8][2]=min; rul[102][8][3]=1.0185; 
// 10. sekcja AND 103 reguly.
rul[102][9][0]=21; rul[102][9][1]=2; 
rul[102][9][2]=0.1245; rul[102][9][3]=max; 
// 11. sekcja AND 103 reguly.
rul[102][10][0]=32; rul[102][10][1]=2; 
rul[102][10][2]=min; rul[102][10][3]=198.694; 
dl_reg[102]=11;
dec[102]=2; 
// 103. Koniec reguly
// 104. Regula
// 1. sekcja AND 104 reguly.
rul[103][0][0]=35; rul[103][0][1]=2; 
rul[103][0][2]=1; rul[103][0][3]=1; 
// 2. sekcja AND 104 reguly.
rul[103][1][0]=18; rul[103][1][1]=2; 
rul[103][1][2]=0.9085; rul[103][1][3]=max; 
// 3. sekcja AND 104 reguly.
rul[103][2][0]=15; rul[103][2][1]=2; 
rul[103][2][2]=min; rul[103][2][3]=18.43; 
// 4. sekcja AND 104 reguly.
rul[103][3][0]=16; rul[103][3][1]=2; 
rul[103][3][2]=0.8145; rul[103][3][3]=max; 
// 5. sekcja AND 104 reguly.
rul[103][4][0]=21; rul[103][4][1]=2; 
rul[103][4][2]=min; rul[103][4][3]=0.1245; 
// 6. sekcja AND 104 reguly.
rul[103][5][0]=20; rul[103][5][1]=2; 
rul[103][5][2]=650.372; rul[103][5][3]=max; 
// 7. sekcja AND 104 reguly.
rul[103][6][0]=33; rul[103][6][1]=2; 
rul[103][6][2]=min; rul[103][6][3]=73.918; 
// 8. sekcja AND 104 reguly.
rul[103][7][0]=6; rul[103][7][1]=2; 
rul[103][7][2]=min; rul[103][7][3]=8.215; 
// 9. sekcja AND 104 reguly.
rul[103][8][0]=7; rul[103][8][1]=2; 
rul[103][8][2]=min; rul[103][8][3]=6.171; 
// 10. sekcja AND 104 reguly.
rul[103][9][0]=10; rul[103][9][1]=2; 
rul[103][9][2]=min; rul[103][9][3]=1.5705; 
// 11. sekcja AND 104 reguly.
rul[103][10][0]=26; rul[103][10][1]=2; 
rul[103][10][2]=0.6065; rul[103][10][3]=0.8585; 
// 12. sekcja AND 104 reguly.
rul[103][11][0]=8; rul[103][11][1]=2; 
rul[103][11][2]=min; rul[103][11][3]=1.0185; 
// 13. sekcja AND 104 reguly.
rul[103][12][0]=4; rul[103][12][1]=2; 
rul[103][12][2]=0.6655; rul[103][12][3]=max; 
dl_reg[103]=13;
dec[103]=2; 
// 104. Koniec reguly
// 105. Regula
// 1. sekcja AND 105 reguly.
rul[104][0][0]=35; rul[104][0][1]=2; 
rul[104][0][2]=1; rul[104][0][3]=1; 
// 2. sekcja AND 105 reguly.
rul[104][1][0]=18; rul[104][1][1]=2; 
rul[104][1][2]=0.9085; rul[104][1][3]=max; 
// 3. sekcja AND 105 reguly.
rul[104][2][0]=6; rul[104][2][1]=2; 
rul[104][2][2]=8.215; rul[104][2][3]=max; 
// 4. sekcja AND 105 reguly.
rul[104][3][0]=8; rul[104][3][1]=2; 
rul[104][3][2]=1.0185; rul[104][3][3]=max; 
// 5. sekcja AND 105 reguly.
rul[104][4][0]=3; rul[104][4][1]=2; 
rul[104][4][2]=1.368; rul[104][4][3]=max; 
// 6. sekcja AND 105 reguly.
rul[104][5][0]=4; rul[104][5][1]=2; 
rul[104][5][2]=min; rul[104][5][3]=0.6655; 
// 7. sekcja AND 105 reguly.
rul[104][6][0]=21; rul[104][6][1]=2; 
rul[104][6][2]=0.1245; rul[104][6][3]=max; 
// 8. sekcja AND 105 reguly.
rul[104][7][0]=26; rul[104][7][1]=2; 
rul[104][7][2]=0.6065; rul[104][7][3]=0.8585; 
// 9. sekcja AND 105 reguly.
rul[104][8][0]=16; rul[104][8][1]=2; 
rul[104][8][2]=0.8145; rul[104][8][3]=max; 
// 10. sekcja AND 105 reguly.
rul[104][9][0]=7; rul[104][9][1]=4; 
rul[104][9][2]=min; rul[104][9][3]=6.171; rul[104][9][4]=14.437; rul[104][9][5]=max; 
dl_reg[104]=10;
dec[104]=2; 
// 105. Koniec reguly
// 106. Regula
// 1. sekcja AND 106 reguly.
rul[105][0][0]=35; rul[105][0][1]=2; 
rul[105][0][2]=1; rul[105][0][3]=1; 
// 2. sekcja AND 106 reguly.
rul[105][1][0]=15; rul[105][1][1]=2; 
rul[105][1][2]=min; rul[105][1][3]=18.43; 
// 3. sekcja AND 106 reguly.
rul[105][2][0]=18; rul[105][2][1]=4; 
rul[105][2][2]=0.9085; rul[105][2][3]=max; rul[105][2][4]=min; rul[105][2][5]=0.9085; 
// 4. sekcja AND 106 reguly.
rul[105][3][0]=21; rul[105][3][1]=4; 
rul[105][3][2]=min; rul[105][3][3]=0.1245; rul[105][3][4]=0.1245; rul[105][3][5]=max; 
// 5. sekcja AND 106 reguly.
rul[105][4][0]=3; rul[105][4][1]=2; 
rul[105][4][2]=1.368; rul[105][4][3]=max; 
// 6. sekcja AND 106 reguly.
rul[105][5][0]=7; rul[105][5][1]=4; 
rul[105][5][2]=min; rul[105][5][3]=6.171; rul[105][5][4]=8.48; rul[105][5][5]=14.437; 
// 7. sekcja AND 106 reguly.
rul[105][6][0]=33; rul[105][6][1]=2; 
rul[105][6][2]=min; rul[105][6][3]=73.918; 
// 8. sekcja AND 106 reguly.
rul[105][7][0]=20; rul[105][7][1]=8; 
rul[105][7][2]=650.372; rul[105][7][3]=max; rul[105][7][4]=548.425; rul[105][7][5]=650.372; rul[105][7][6]=356.734; rul[105][7][7]=488.907; 
rul[105][7][8]=488.907; rul[105][7][9]=548.425; 
// 9. sekcja AND 106 reguly.
rul[105][8][0]=34; rul[105][8][1]=4; 
rul[105][8][2]=min; rul[105][8][3]=189.705; rul[105][8][4]=189.705; rul[105][8][5]=240.981; 
// 10. sekcja AND 106 reguly.
rul[105][9][0]=6; rul[105][9][1]=2; 
rul[105][9][2]=8.215; rul[105][9][3]=max; 
// 11. sekcja AND 106 reguly.
rul[105][10][0]=16; rul[105][10][1]=2; 
rul[105][10][2]=min; rul[105][10][3]=0.8145; 
// 12. sekcja AND 106 reguly.
rul[105][11][0]=10; rul[105][11][1]=4; 
rul[105][11][2]=1.5705; rul[105][11][3]=max; rul[105][11][4]=min; rul[105][11][5]=1.5705; 
// 13. sekcja AND 106 reguly.
rul[105][12][0]=4; rul[105][12][1]=2; 
rul[105][12][2]=min; rul[105][12][3]=0.6655; 
dl_reg[105]=13;
dec[105]=2; 
// 106. Koniec reguly
// 107. Regula
// 1. sekcja AND 107 reguly.
rul[106][0][0]=35; rul[106][0][1]=2; 
rul[106][0][2]=1; rul[106][0][3]=1; 
// 2. sekcja AND 107 reguly.
rul[106][1][0]=18; rul[106][1][1]=2; 
rul[106][1][2]=0.9085; rul[106][1][3]=max; 
// 3. sekcja AND 107 reguly.
rul[106][2][0]=15; rul[106][2][1]=2; 
rul[106][2][2]=min; rul[106][2][3]=18.43; 
// 4. sekcja AND 107 reguly.
rul[106][3][0]=3; rul[106][3][1]=2; 
rul[106][3][2]=1.368; rul[106][3][3]=max; 
// 5. sekcja AND 107 reguly.
rul[106][4][0]=6; rul[106][4][1]=2; 
rul[106][4][2]=8.215; rul[106][4][3]=max; 
// 6. sekcja AND 107 reguly.
rul[106][5][0]=4; rul[106][5][1]=2; 
rul[106][5][2]=min; rul[106][5][3]=0.6655; 
// 7. sekcja AND 107 reguly.
rul[106][6][0]=26; rul[106][6][1]=4; 
rul[106][6][2]=0.3215; rul[106][6][3]=0.6065; rul[106][6][4]=0.6065; rul[106][6][5]=0.8585; 
// 8. sekcja AND 107 reguly.
rul[106][7][0]=7; rul[106][7][1]=2; 
rul[106][7][2]=min; rul[106][7][3]=6.171; 
// 9. sekcja AND 107 reguly.
rul[106][8][0]=8; rul[106][8][1]=2; 
rul[106][8][2]=min; rul[106][8][3]=1.0185; 
// 10. sekcja AND 107 reguly.
rul[106][9][0]=20; rul[106][9][1]=4; 
rul[106][9][2]=548.425; rul[106][9][3]=650.372; rul[106][9][4]=650.372; rul[106][9][5]=max; 
// 11. sekcja AND 107 reguly.
rul[106][10][0]=33; rul[106][10][1]=2; 
rul[106][10][2]=min; rul[106][10][3]=73.918; 
dl_reg[106]=11;
dec[106]=2; 
// 107. Koniec reguly
// 108. Regula
// 1. sekcja AND 108 reguly.
rul[107][0][0]=35; rul[107][0][1]=4; 
rul[107][0][2]=1; rul[107][0][3]=1; rul[107][0][4]=2; rul[107][0][5]=2; 
// 2. sekcja AND 108 reguly.
rul[107][1][0]=3; rul[107][1][1]=2; 
rul[107][1][2]=1.368; rul[107][1][3]=max; 
// 3. sekcja AND 108 reguly.
rul[107][2][0]=6; rul[107][2][1]=2; 
rul[107][2][2]=8.215; rul[107][2][3]=max; 
// 4. sekcja AND 108 reguly.
rul[107][3][0]=8; rul[107][3][1]=2; 
rul[107][3][2]=1.0185; rul[107][3][3]=max; 
// 5. sekcja AND 108 reguly.
rul[107][4][0]=16; rul[107][4][1]=2; 
rul[107][4][2]=min; rul[107][4][3]=0.8145; 
// 6. sekcja AND 108 reguly.
rul[107][5][0]=21; rul[107][5][1]=4; 
rul[107][5][2]=0.1245; rul[107][5][3]=max; rul[107][5][4]=min; rul[107][5][5]=0.1245; 
// 7. sekcja AND 108 reguly.
rul[107][6][0]=15; rul[107][6][1]=2; 
rul[107][6][2]=18.43; rul[107][6][3]=max; 
// 8. sekcja AND 108 reguly.
rul[107][7][0]=18; rul[107][7][1]=4; 
rul[107][7][2]=min; rul[107][7][3]=0.9085; rul[107][7][4]=0.9085; rul[107][7][5]=max; 
// 9. sekcja AND 108 reguly.
rul[107][8][0]=4; rul[107][8][1]=2; 
rul[107][8][2]=min; rul[107][8][3]=0.6655; 
// 10. sekcja AND 108 reguly.
rul[107][9][0]=26; rul[107][9][1]=6; 
rul[107][9][2]=0.3215; rul[107][9][3]=0.6065; rul[107][9][4]=0.6065; rul[107][9][5]=0.8585; rul[107][9][6]=0.8585; rul[107][9][7]=max; 
// 11. sekcja AND 108 reguly.
rul[107][10][0]=10; rul[107][10][1]=2; 
rul[107][10][2]=min; rul[107][10][3]=1.5705; 
// 12. sekcja AND 108 reguly.
rul[107][11][0]=32; rul[107][11][1]=4; 
rul[107][11][2]=234.086; rul[107][11][3]=max; rul[107][11][4]=198.694; rul[107][11][5]=234.086; 
dl_reg[107]=12;
dec[107]=2; 
// 108. Koniec reguly
// 109. Regula
// 1. sekcja AND 109 reguly.
rul[108][0][0]=6; rul[108][0][1]=2; 
rul[108][0][2]=8.215; rul[108][0][3]=max; 
// 2. sekcja AND 109 reguly.
rul[108][1][0]=8; rul[108][1][1]=2; 
rul[108][1][2]=1.0185; rul[108][1][3]=max; 
// 3. sekcja AND 109 reguly.
rul[108][2][0]=3; rul[108][2][1]=2; 
rul[108][2][2]=1.368; rul[108][2][3]=max; 
// 4. sekcja AND 109 reguly.
rul[108][3][0]=18; rul[108][3][1]=2; 
rul[108][3][2]=0.9085; rul[108][3][3]=max; 
// 5. sekcja AND 109 reguly.
rul[108][4][0]=21; rul[108][4][1]=2; 
rul[108][4][2]=0.1245; rul[108][4][3]=max; 
// 6. sekcja AND 109 reguly.
rul[108][5][0]=32; rul[108][5][1]=2; 
rul[108][5][2]=234.086; rul[108][5][3]=max; 
// 7. sekcja AND 109 reguly.
rul[108][6][0]=15; rul[108][6][1]=2; 
rul[108][6][2]=18.43; rul[108][6][3]=max; 
// 8. sekcja AND 109 reguly.
rul[108][7][0]=4; rul[108][7][1]=2; 
rul[108][7][2]=min; rul[108][7][3]=0.6655; 
// 9. sekcja AND 109 reguly.
rul[108][8][0]=20; rul[108][8][1]=4; 
rul[108][8][2]=356.734; rul[108][8][3]=488.907; rul[108][8][4]=488.907; rul[108][8][5]=548.425; 
// 10. sekcja AND 109 reguly.
rul[108][9][0]=33; rul[108][9][1]=2; 
rul[108][9][2]=137.781; rul[108][9][3]=max; 
// 11. sekcja AND 109 reguly.
rul[108][10][0]=34; rul[108][10][1]=2; 
rul[108][10][2]=240.981; rul[108][10][3]=max; 
// 12. sekcja AND 109 reguly.
rul[108][11][0]=35; rul[108][11][1]=2; 
rul[108][11][2]=2; rul[108][11][3]=2; 
// 13. sekcja AND 109 reguly.
rul[108][12][0]=27; rul[108][12][1]=4; 
rul[108][12][2]=min; rul[108][12][3]=0.5825; rul[108][12][4]=0.5825; rul[108][12][5]=0.6905; 
dl_reg[108]=13;
dec[108]=2; 
// 109. Koniec reguly
// 110. Regula
// 1. sekcja AND 110 reguly.
rul[109][0][0]=21; rul[109][0][1]=2; 
rul[109][0][2]=0.1245; rul[109][0][3]=max; 
// 2. sekcja AND 110 reguly.
rul[109][1][0]=35; rul[109][1][1]=2; 
rul[109][1][2]=1; rul[109][1][3]=1; 
// 3. sekcja AND 110 reguly.
rul[109][2][0]=18; rul[109][2][1]=2; 
rul[109][2][2]=0.9085; rul[109][2][3]=max; 
// 4. sekcja AND 110 reguly.
rul[109][3][0]=6; rul[109][3][1]=2; 
rul[109][3][2]=8.215; rul[109][3][3]=max; 
// 5. sekcja AND 110 reguly.
rul[109][4][0]=8; rul[109][4][1]=2; 
rul[109][4][2]=1.0185; rul[109][4][3]=max; 
// 6. sekcja AND 110 reguly.
rul[109][5][0]=16; rul[109][5][1]=2; 
rul[109][5][2]=0.8145; rul[109][5][3]=max; 
// 7. sekcja AND 110 reguly.
rul[109][6][0]=34; rul[109][6][1]=2; 
rul[109][6][2]=min; rul[109][6][3]=189.705; 
// 8. sekcja AND 110 reguly.
rul[109][7][0]=27; rul[109][7][1]=2; 
rul[109][7][2]=min; rul[109][7][3]=0.5825; 
// 9. sekcja AND 110 reguly.
rul[109][8][0]=3; rul[109][8][1]=2; 
rul[109][8][2]=min; rul[109][8][3]=1.368; 
// 10. sekcja AND 110 reguly.
rul[109][9][0]=15; rul[109][9][1]=2; 
rul[109][9][2]=18.43; rul[109][9][3]=max; 
dl_reg[109]=10;
dec[109]=5; 
// 110. Koniec reguly
// 111. Regula
// 1. sekcja AND 111 reguly.
rul[110][0][0]=3; rul[110][0][1]=2; 
rul[110][0][2]=1.368; rul[110][0][3]=max; 
// 2. sekcja AND 111 reguly.
rul[110][1][0]=6; rul[110][1][1]=2; 
rul[110][1][2]=8.215; rul[110][1][3]=max; 
// 3. sekcja AND 111 reguly.
rul[110][2][0]=8; rul[110][2][1]=2; 
rul[110][2][2]=1.0185; rul[110][2][3]=max; 
// 4. sekcja AND 111 reguly.
rul[110][3][0]=16; rul[110][3][1]=2; 
rul[110][3][2]=min; rul[110][3][3]=0.8145; 
// 5. sekcja AND 111 reguly.
rul[110][4][0]=27; rul[110][4][1]=2; 
rul[110][4][2]=min; rul[110][4][3]=0.5825; 
// 6. sekcja AND 111 reguly.
rul[110][5][0]=7; rul[110][5][1]=2; 
rul[110][5][2]=min; rul[110][5][3]=6.171; 
// 7. sekcja AND 111 reguly.
rul[110][6][0]=4; rul[110][6][1]=2; 
rul[110][6][2]=min; rul[110][6][3]=0.6655; 
// 8. sekcja AND 111 reguly.
rul[110][7][0]=20; rul[110][7][1]=2; 
rul[110][7][2]=650.372; rul[110][7][3]=max; 
// 9. sekcja AND 111 reguly.
rul[110][8][0]=10; rul[110][8][1]=2; 
rul[110][8][2]=1.5705; rul[110][8][3]=max; 
// 10. sekcja AND 111 reguly.
rul[110][9][0]=18; rul[110][9][1]=2; 
rul[110][9][2]=min; rul[110][9][3]=0.9085; 
// 11. sekcja AND 111 reguly.
rul[110][10][0]=35; rul[110][10][1]=2; 
rul[110][10][2]=1; rul[110][10][3]=1; 
// 12. sekcja AND 111 reguly.
rul[110][11][0]=26; rul[110][11][1]=2; 
rul[110][11][2]=min; rul[110][11][3]=0.3215; 
// 13. sekcja AND 111 reguly.
rul[110][12][0]=15; rul[110][12][1]=2; 
rul[110][12][2]=18.43; rul[110][12][3]=max; 
// 14. sekcja AND 111 reguly.
rul[110][13][0]=33; rul[110][13][1]=2; 
rul[110][13][2]=min; rul[110][13][3]=73.918; 
// 15. sekcja AND 111 reguly.
rul[110][14][0]=21; rul[110][14][1]=2; 
rul[110][14][2]=min; rul[110][14][3]=0.1245; 
dl_reg[110]=15;
dec[110]=1; 
// 111. Koniec reguly
// 112. Regula
// 1. sekcja AND 112 reguly.
rul[111][0][0]=3; rul[111][0][1]=2; 
rul[111][0][2]=1.368; rul[111][0][3]=max; 
// 2. sekcja AND 112 reguly.
rul[111][1][0]=6; rul[111][1][1]=2; 
rul[111][1][2]=8.215; rul[111][1][3]=max; 
// 3. sekcja AND 112 reguly.
rul[111][2][0]=35; rul[111][2][1]=4; 
rul[111][2][2]=1; rul[111][2][3]=1; rul[111][2][4]=2; rul[111][2][5]=2; 
// 4. sekcja AND 112 reguly.
rul[111][3][0]=8; rul[111][3][1]=2; 
rul[111][3][2]=1.0185; rul[111][3][3]=max; 
// 5. sekcja AND 112 reguly.
rul[111][4][0]=16; rul[111][4][1]=2; 
rul[111][4][2]=min; rul[111][4][3]=0.8145; 
// 6. sekcja AND 112 reguly.
rul[111][5][0]=18; rul[111][5][1]=2; 
rul[111][5][2]=min; rul[111][5][3]=0.9085; 
// 7. sekcja AND 112 reguly.
rul[111][6][0]=4; rul[111][6][1]=2; 
rul[111][6][2]=min; rul[111][6][3]=0.6655; 
// 8. sekcja AND 112 reguly.
rul[111][7][0]=34; rul[111][7][1]=2; 
rul[111][7][2]=240.981; rul[111][7][3]=max; 
// 9. sekcja AND 112 reguly.
rul[111][8][0]=10; rul[111][8][1]=4; 
rul[111][8][2]=1.5705; rul[111][8][3]=max; rul[111][8][4]=min; rul[111][8][5]=1.5705; 
// 10. sekcja AND 112 reguly.
rul[111][9][0]=7; rul[111][9][1]=4; 
rul[111][9][2]=min; rul[111][9][3]=6.171; rul[111][9][4]=8.48; rul[111][9][5]=14.437; 
// 11. sekcja AND 112 reguly.
rul[111][10][0]=15; rul[111][10][1]=4; 
rul[111][10][2]=min; rul[111][10][3]=18.43; rul[111][10][4]=18.43; rul[111][10][5]=max; 
// 12. sekcja AND 112 reguly.
rul[111][11][0]=20; rul[111][11][1]=4; 
rul[111][11][2]=650.372; rul[111][11][3]=max; rul[111][11][4]=220.22; rul[111][11][5]=356.734; 
dl_reg[111]=12;
dec[111]=1; 
// 112. Koniec reguly 

}
