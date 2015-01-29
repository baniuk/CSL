%% test LV_WeldDetect
% Weryfikuje wyjœcie z testów
% spradziæ czy wyniki sa w debug czy w g³ównym katalogu - zalezy czy
% by³o budowane z VC czy z CMD

% skrypt musi byæ uruchomiony z katalogu tests/case
% matlab tools
tools = '..\..\build\Externals\PBToolset-prefix\src\PBToolset\src\MatlabExchange\';
addpath(tools);
% Wyniki testu
p  = '..\..\build\tests\LV_WeldDetectApprox\';
% p  = '..\..\build\tests\LV_WeldDetectApprox\Debug\'; % VC
% p  = '..\..\build\tests\LV_WeldDetectApprox\Release\'; % VC
%% Przygotowanie danych ------------
% TEST STATIC_WeldPostProcess, _getRawPointer
% przygotowanie danych - uruchomiæ TEST STATIC_WeldDetexApprox._WeldDetexApprox_1
ImportDumpFile([p 'WeldDetectApprox_1.out']);
D = weldpos(1:2,:)';
S = weldpos(3:4,:)';
G = weldpos(5:6,:)';
% ExportArrayToFile('D_WeldDetexApprox_1.dat',D);
% ExportArrayToFile('G_WeldDetexApprox_1.dat',G);
% ExportArrayToFile('lineok_WeldDetexApprox_1.dat',lineok);

% TEST Parametric DLL_Tests,_LV_WeldDetectApprox
% f:\Dokumenty\Dysk Google\Praca\Granty\CASELOT
load originals
% originals{1} = imcrop(originals{1},[1798.5 1102.5 4948 1152]);
% originals{2} = imcrop(originals{2},[2346.5 778.5 3840 1032]);
% originals{3} = imcrop(originals{3},[1594.5 1010.5 5292 1008]);
% originals{4} = imcrop(originals{4},[1418.5 826.5 5168 1152]);
% originals{5} = imcrop(originals{5},[1274.5 1050.5 5600 908]);
% originals{6} = imcrop(originals{6},[3050.5 1054.5 3064 868]);
% originals{7} = imcrop(originals{7},[1942.5 1078.5 4932 532]);
% originals{8} = imcrop(originals{8},[1866.5 1002.5 4592 800]);
% originals{9} = imcrop(originals{9},[1450.5 1038.5 4988 1100]);
% originals{10} = imcrop(originals{10},[1934.5 942.5 4272 1044]);
% originals{11} = imcrop(originals{11},[1806.5 930.5 4804 860]);
% originals{12} = imcrop(originals{12},[1778.5 1106.5 4448 804]);
% originals{13} = imcrop(originals{13},[2326.5 1114.5 3632 908]);
% originals{14} = imcrop(originals{14},[1938.5 1138.5 4700 864]);
% originals{15} = imcrop(originals{15},[1798.5 782.5 4760 1392]);
% originals{16} = imcrop(originals{16},[1098.5 962.5 5680 1056]);
% originals{17} = imcrop(originals{17},[1266.5 822.5 5776 1448]);
% originals{18} = imcrop(originals{18},[1222.5 866.5 5640 1360]);
% originals{19} = imcrop(originals{19},[1250.5 878.5 5728 1160]);
% originals{20} = imcrop(originals{20},[1582.5 830.5 5488 1172]);
% originals{21} = imcrop(originals{21},[1206.5 842.5 5544 1180]);
% ExportArrayToFile('testimag1.dat',originals{1});
% ExportArrayToFile('testimag2.dat',originals{2});
% ExportArrayToFile('testimag3.dat',originals{3});
% ExportArrayToFile('testimag4.dat',originals{4});
% ExportArrayToFile('testimag5.dat',originals{5});
% ExportArrayToFile('testimag6.dat',originals{6});
% ExportArrayToFile('testimag7.dat',originals{7});
% ExportArrayToFile('testimag8.dat',originals{8});
% ExportArrayToFile('testimag9.dat',originals{9});
% ExportArrayToFile('testimag10.dat',originals{10});
% ExportArrayToFile('testimag11.dat',originals{11});
% ExportArrayToFile('testimag12.dat',originals{12});
% ExportArrayToFile('testimag13.dat',originals{13});
% ExportArrayToFile('testimag14.dat',originals{14});
% ExportArrayToFile('testimag15.dat',originals{15});
% ExportArrayToFile('testimag16.dat',originals{16});
% ExportArrayToFile('testimag17.dat',originals{17});
% ExportArrayToFile('testimag18.dat',originals{18});
% ExportArrayToFile('testimag19.dat',originals{19});
% ExportArrayToFile('testimag20.dat',originals{20});
% ExportArrayToFile('testimag21.dat',originals{21});

% set 2
% f:\Dokumenty\Dysk Google\Praca\Granty\CASELOT
load 'd:\Dokumenty\Dysk Google\Praca\Granty\CASELOT\new_originals.mat'
for a=1:length(new_originals)
    new_originals{a} = imcomplement(new_originals{a}');
end
new_originals{1} = imcrop(new_originals{1},[17.5 72.5 1509 642]);
new_originals{2} = imcrop(new_originals{2},[12.5 109.5 1516 538]);
new_originals{3} = imcrop(new_originals{3},[28.5 92.5 1322 709]);
new_originals{4} = imcrop(new_originals{4},[34.5 52.5 1482 736]);
new_originals{5} = imcrop(new_originals{5},[16.5 63.5 1504 736]);
new_originals{6} = imcrop(new_originals{6},[29.5 39.5 1465 808]);
new_originals{7} = imcrop(new_originals{7},[10.5 41.5 1509 801]);
new_originals{8} = imcrop(new_originals{8},[25.5 26.5 1499 824]);
new_originals{9} = imcrop(new_originals{9},[11.5 79.5 1515 744]);
new_originals{10} = imcrop(new_originals{10},[65.5 63.5 1459 765]);
new_originals{11} = imcrop(new_originals{11},[12.5 71.5 1507 782]);
new_originals{12} = imcrop(new_originals{12},[13.5 22.5 1507 831]);
new_originals{13} = imcrop(new_originals{13},[55.5 16.5 1473 838]);
new_originals{14} = imcrop(new_originals{14},[85.5 36.5 1445 798]);
new_originals{15} = imcrop(new_originals{15},[42.5 37.5 1486 817]);
new_originals{16} = imcrop(new_originals{16},[11.5 22.5 1512 837]);
new_originals{17} = imcrop(new_originals{17},[263.5 281.5 1057 288]);
new_originals{18} = imcrop(new_originals{18},[12.5 160.5 1517 563]);
new_originals{19} = imcrop(new_originals{19},[57.5 298.5 1471 275]);
new_originals{20} = imcrop(new_originals{20},[144.5 53.5 1385 781]);
new_originals{21} = imcrop(new_originals{21},[35.5 144.5 1493 577]);
new_originals{22} = imcrop(new_originals{22},[17.5 138.5 1511 596]);
new_originals{23} = imcrop(new_originals{23},[63.5 151.5 1240 592]);
for a=1:length(new_originals)
    figure;imshow(new_originals{a},[]);
    ExportArrayToFile([new_originals_names(a).name,'.dat'], new_originals{a})
end


%% TEST STATIC_WeldDetexApprox._WeldDetexApprox_7
figure
% dane wejœciowe
rtg1 = readbinarymatrix([p 'testimag7.dat']);

% dane wyjœciowe
ImportDumpFile([p 'WeldDetectApprox_7.out']);

% analiza
start = 10+1;% piksel od którego starujemy z testu
lineoke = [NaN(1,start-1) lineok];
lineoke = repmat(lineoke,size(rtg1,1),1);
subplot(2,1,1)
imshow(rtg1,[]); hold on
D = weldpos(1:2,:)';
S = weldpos(3:4,:)';
G = weldpos(5:6,:)';
plot(D(:,1),D(:,2),'marker','.','markerfacecolor','r','markersize',4,'LineStyle','none')
plot(S(:,1),S(:,2),'marker','.','markerfacecolor','g','markersize',4,'LineStyle','none')
plot(G(:,1),G(:,2),'marker','.','markerfacecolor','r','markersize',4,'LineStyle','none')
subplot(2,1,2)
imshow(rtg1,[]);hold on
for aa=1:length(lineok)
    if lineok(aa)==0
        plot(aa,size(rtg1,1)/2,'x','markerfacecolor','r','markersize',10)
    end
end
%% TEST STATIC_WeldDetexApprox._WeldDetexApprox_2
figure
% dane wejœciowe
rtg1 = readbinarymatrix([p 'testimag2.dat']);

% dane wyjœciowe
ImportDumpFile([p 'WeldDetectApprox_2.out']);

% analiza
start = 10+1;% piksel od którego starujemy z testu
lineoke = [NaN(1,start-1) lineok];
lineoke = repmat(lineoke,size(rtg1,1),1);
subplot(2,1,1)
imshow(rtg1,[]); hold on
D = weldpos(1:2,:)';
S = weldpos(3:4,:)';
G = weldpos(5:6,:)';
plot(D(:,1),D(:,2),'marker','.','markerfacecolor','r','markersize',4,'LineStyle','none')
plot(S(:,1),S(:,2),'marker','.','markerfacecolor','g','markersize',4,'LineStyle','none')
plot(G(:,1),G(:,2),'marker','.','markerfacecolor','r','markersize',4,'LineStyle','none')
subplot(2,1,2)
imshow(rtg1,[]);hold on
for aa=1:length(lineok)
    if lineok(aa)==0
        plot(aa,size(rtg1,1)/2,'x','markerfacecolor','r','markersize',10)
    end
end
%% TEST STATIC_WeldDetexApprox._WeldDetexApprox_16
figure
% dane wejœciowe
rtg1 = readbinarymatrix([p 'testimag16.dat']);

% dane wyjœciowe
ImportDumpFile([p 'WeldDetectApprox_16.out']);

% analiza
start = 10+1;% piksel od którego starujemy z testu
lineoke = [NaN(1,start-1) lineok];
lineoke = repmat(lineoke,size(rtg1,1),1);
subplot(2,1,1)
imshow(rtg1,[]); hold on
D = weldpos(1:2,:)';
S = weldpos(3:4,:)';
G = weldpos(5:6,:)';
plot(D(:,1),D(:,2),'marker','.','markerfacecolor','r','markersize',4,'LineStyle','none')
plot(S(:,1),S(:,2),'marker','.','markerfacecolor','g','markersize',4,'LineStyle','none')
plot(G(:,1),G(:,2),'marker','.','markerfacecolor','r','markersize',4,'LineStyle','none')
subplot(2,1,2)
imshow(rtg1,[]);hold on
for aa=1:length(lineok)
    if lineok(aa)==0
        plot(aa,size(rtg1,1)/2,'x','markerfacecolor','r','markersize',10)
    end
end
%% TEST STATIC_ParamEstimation, _ParamEstimation_1
ImportDumpFile([p 'ParamEstimation_1.out']);
max(paramEstimationImage(:,11))
median(paramEstimationImage(:,11))
%% TEST STATIC_WeldPostProcess, _getRawPointer
ImportDumpFile([p 'weldpostprocess.out']);imshow(fillpolygon,[])
%% TEST DLL_Tests,_LV_WeldDetectApprox,dataSet1

for a=1:21
    figure
    rtg1 = ImportArrayfromFile([p ['testimag' num2str(a) '.dat']]);
    ImportDumpFile([p ['DLL_testimag' num2str(a) '.dat.out']]);
    subplot(2,1,1)
    imshow(rtg1,[]);
    subplot(2,1,2)
    imshow(eval(['testimag' num2str(a)]),[]);
end
%% TEST DLL_Tests,_LV_WeldDetectApprox,dataSet2
cases = dir([p,'DLL_Sample*']);
if isempty(cases)
    error('No test cases found');
end
for a=1:length(cases)
    figure
    name = cases(a).name;
    rtg1 = ImportArrayfromFile([p name(5:end-4)]); % bez .out (orginal) i DLL_
    ImportDumpFile([p name]);
    subplot(2,1,1);
    imshow(rtg1,[]);
    subplot(2,1,2)
    imshow(eval(fixNames(name(5:end-8))),[]);
    title(name)
end