#include <cstdlib>
#include <iostream>
#include <float.h>
#include <fstream>
#include "C_Error.h"

class RulInter
{
 long dlugosc; //ilosc regul
 double rul[150][200][1000]; //nr reguly, nr sekcji OR, pozycje sekcji OR
 long dec[150]; //nr klasy dla **dane
 long dl_reg[200]; //ilosc sekcji AND dla [n] tej reguly
 long dl_inx; //ilosc regul
 double **dane;
 long wier,kol; //ilosc kolumn i wierszy dla danych
 bool logic[150]; // zmienna pomocnicza do okreslenia wyniku (trafiony, chybiony) dla reguly 
 long wybor; //wybor rodzaju regul, 4 - reguly momentowe jednoatrybutowe, 1 - reguly niemomentowe
 
 bool check1; //zmienna do odznaczenia potrzeby zwalniania pamieci w **dane

 
 long X1,X2,X3,X4,X5,X6,X7,X8,X9;
 long X10,X11,X12,X13,X14,X15,X16,X17,X18,X19;
 long X20,X21,X22,X23,X24,X25,X26,X27,X28,X29;
 long X30,X31,X32,X33,X34,X35,X36,X37,X38,X39;
 long X40,X41,X42,X43,X44,X45,X46,X47,X48,X49;
 long X50,X51,X52,X53,X54,X55,X56,X57,X58,X59;
 long X60,X61,X62,X63,X64,X65,X66,X67,X68,X69;
 long X70,X71,X72,X73,X74,X75,X76,X77,X78,X79;
 

 public:
  //wybor zestawu regul 1 - reguly niemomentowe, 4 - reguly momentowe
  RulInter(long wyb);
  ~RulInter();
  // sluzy do przypisania faktycznego parametru do indeksu przekazywanej tablicy
  void configuration();
  void WyswietlRule();
  void TestLogic();
  void ZapiszRule4();
  void ZapiszRule1();
  //funkcje zwracaj¹ca odpowiedni wiersz i kolumne (mapujac) map(3,0) zwraca parametr X3 w pierwszej kolumnie
  //wejscie wiersz, kolumna)
  double map(long w, long k);
  //funkcja transformujaca format WE do wlasnego
  void transform(double *dane1,long row, long col);
  //funkcja przypisujaca klasy
  //*out wskaznik na wyniki przypisania do klasy
  void induct(int *out,long opt);
  //  void RSS(double *in, long row, long col, int *out, C_Error *err);
  // in - tablica wejœciowa zawierajaca cechy was spawow
  // row - iloœæ wierszy tablicy in
  // col - iloœæ kolumn tablicy in
  // out - tablica wyjœciowa z wynikiem okreslajacym klase wady
  // err - wskaŸnik do obiektu C_Error obs³uguj¹cego b³êdy
  void RSS(double *in, long row, long col, int *out,C_Error *err);
  //metody pomocnicze
  void alocDane(long wys,long szer);
  void dealocDane(long wys,long szer);
  int loadFile(char *name);
  void show();
  void showWierszdane();
};
