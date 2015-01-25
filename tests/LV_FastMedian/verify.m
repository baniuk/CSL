%% test LV_FastMedian
% Weryfikuje wyjœcie z testów
% sprawdzanie czy wyniki sa w debug czy w g?ównym katalogu - zalezy czy
% by?o budowane z VC czy z CMD


% Wyniki testu
p  = '..\..\build\tests\LV_FastMedian\Debug\';
addpath(p);
addpath('..\..\build\Externals\PBToolset-prefix\src\PBToolset\src\MatlabExchange\')
%% TEST DLL_Tests,_FastMedian_imag2
figure
% dane wejœciowe
im = readbinarymatrix([p 'imag2.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'imag2.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag1
figure
% dane wejœciowe
im = readbinarymatrix([p 'testimag1.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'testimag1.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag6
figure
% dane wejœciowe
im = readbinarymatrix([p 'testimag6.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'testimag6.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag9
figure
% dane wejœciowe
im = readbinarymatrix([p 'testimag9.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'testimag9.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag17_m31
figure
% dane wejœciowe
im = readbinarymatrix([p 'testimag17.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'testimag17m31.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag17_m51
figure
% dane wejœciowe
im = readbinarymatrix([p 'testimag17.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'testimag17m51.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag17_m91
figure
% dane wejœciowe
im = readbinarymatrix([p 'testimag17.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'testimag17m91.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag17_m3
figure
% dane wejœciowe
im = readbinarymatrix([p 'testimag17.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyjœciowe
ImportDumpFile([p 'testimag17m3.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')