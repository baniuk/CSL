%% test LV_FastMedian
% Weryfikuje wyjœcie z testów
% sprawdzanie czy wyniki sa w debug czy w g?ównym katalogu - zalezy czy
% by?o budowane z VC czy z CMD


% Wyniki testu
p  = '..\..\bin\tests\LV_Threshold\';
%% TEST STATIC_Test,_Threshold_1
figure
% dane wejœciowe
im = readbinarymatrix([p 'im8bit.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'LV_Threshold_tests.out']);
subplot(2,1,2)
imshow(Sauv,[]);
title('output image')
%% TEST STATIC_Test,_Threshold_2
figure
% dane wejœciowe
im = readbinarymatrix([p 'imag2.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'LV_Threshold_tests_2.out']);
subplot(2,1,2)
imshow(imag2,[]);
title('output image')
%% TEST STATIC_Test,_Threshold_3
figure
% dane wejœciowe
im = readbinarymatrix([p '100_01_91_005.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'LV_Threshold_tests_3.out']);
subplot(2,1,2)
imshow(im_100_01,[]);
title('output image')
