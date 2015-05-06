// wykrywanie t�a z wykorzystaniem funkcji grabCut opencv
void detekcja_grabcut();


// funkcja normalizacji kolor�w
void norm_color();

// funkcja Leszek do wywo�ania biblioteki z obrazami
int mainold(int argc, char** argv);

// przyk�ad u�ycia BackgroundSubtractorMOG oraz BackgroundSubtractorMOG2
int main_background(int argc, char* argv[]);

// przyk�ad segmentacji obrazu OTSU
void watershed1();

// przyk�ad segmentacji obrazu OTSU + usuniecie szumow + otwarcie + dylatacja + t�o
void watershed2();

// algorytm wykrywania tla - wcze�niejsza wersja opencv
void tlo();

//regulacja jasno�ci oraz kontrastu
int main_jasnosc(int argc, char** argv);

// dyskretna transformata fouriera
int main_fourier(int argc, char ** argv);

// watershed1
int main_watershed1(int argc, char** argv);

//demonstracja threshold
int main_threshold(int argc, char** argv);

// funkcje morfologiczne
int main_morphology(int argc, char** argv);

// funkcja erozji oraz dylatacji
int main_erozja(int argc, char** argv);

// kontury obrazow
int main_kontury(int argc, char** argv);

// wygladzanie
int main_smooth(int argc, char** argv);

// moja konwulsja
void convolvelm(char **argv);

//algorytm watershed2
int main_watershed2(int argc, char* argv[]);

// watershed_2a
int main_watershed2a(int argc, char **argv);
