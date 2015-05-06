DisplayManager      -   główna procedura umożliwiająca wyświetlenie radiogramu z
                        naniesionymi obiektami w 6 grupach oznaczonych różnymi
                        kolorami
--------------------------------------------------------------------------------                        
buildColorArray     -   helper - tworzy ciągłą tablicę kolorów na podstawie
                        z indeksami obiektów w poszczególnych grupach. Tworzona
                        tablica kolorów zawiera kolory w zakresach
                        [c1 c1 c1 c2 c2 c3 ....], gdzie ilość wpisów cx zależy
                        od rozmiaru tablic wejsciowych z indeksami obiektów 
                        w każdej grupie
clearArray          -   helper - 
grayToColor         -   helper - konwertuje obiekt IMAQ na odpowiadający mu inny
                        obiekt IMAQ oraz tablicę 2D zakodowaną za pomocą UINT32
                        co odpowida kodowaniu RGB. Obiekt wejściowy musi być w 
                        formacie UINT16. PRzy kodowaniu obraz wejściowy jest 
                        konwertowany do 8 bitów.
joinFilledROI       -   helper - nanosi na obraz wejściowy (w postai tablicy 2D)
                        obiekty o określonych indeksach. Nanoszone ROI jest 
                        wypełnione i jest to operacja niszcząca obraz wejściowy.
joinROI             -   helper - nanosi na obraz wejściowy obrysy obiektów o 
                        okreslonych indeksach. Jest to operacja nieniszcząca.
scaleImage          -   helper - konwertuje obraz z UINT16 do UINT8 wykonując
                        skalowanie liniowe jasności.      
imCut               -   przycina obraz używając maski spawu                                                                                                                                                       