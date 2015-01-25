%% test LV_FastMedian
% Weryfikuje wyj�cie z test�w
% sprawdzanie czy wyniki sa w debug czy w g?�wnym katalogu - zalezy czy
% by?o budowane z VC czy z CMD


% Wyniki testu
p  = '..\..\build\tests\LV_FastMedian\Debug\';
addpath(p);
addpath('..\..\build\Externals\PBToolset-prefix\src\PBToolset\src\MatlabExchange\')
%% TEST DLL_Tests,_FastMedian_imag2
figure
% dane wej�ciowe
im = readbinarymatrix([p 'imag2.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyj�ciowe
ImportDumpFile([p 'imag2.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag1
figure
% dane wej�ciowe
im = readbinarymatrix([p 'testimag1.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyj�ciowe
ImportDumpFile([p 'testimag1.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag6
figure
% dane wej�ciowe
im = readbinarymatrix([p 'testimag6.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyj�ciowe
ImportDumpFile([p 'testimag6.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag9
figure
% dane wej�ciowe
im = readbinarymatrix([p 'testimag9.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyj�ciowe
ImportDumpFile([p 'testimag9.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag17_m31
figure
% dane wej�ciowe
im = readbinarymatrix([p 'testimag17.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyj�ciowe
ImportDumpFile([p 'testimag17m31.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag17_m51
figure
% dane wej�ciowe
im = readbinarymatrix([p 'testimag17.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyj�ciowe
ImportDumpFile([p 'testimag17m51.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag17_m91
figure
% dane wej�ciowe
im = readbinarymatrix([p 'testimag17.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyj�ciowe
ImportDumpFile([p 'testimag17m91.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')
%% TEST DLL_Tests,_FastMedian_testimag17_m3
figure
% dane wej�ciowe
im = readbinarymatrix([p 'testimag17.dat']);
subplot(2,1,1)
imshow(im,[]);
title('input image')

% dane wyj�ciowe
ImportDumpFile([p 'testimag17m3.out']);
subplot(2,1,2)
imshow(filtered_image,[]);
title('output image')