%% test LV_WeldDetect
% Weryfikuje wyjœcie z testów
% sprawdzanie czy wyniki sa w debug czy w g³ównym katalogu - zalezy czy
% by³o budowane z VC czy z CMD


% Wyniki testu
p  = '..\..\bin\tests\LV_WeldDetectApprox\';
if exist([p 'Debug\'],'dir')==7
    fprintf('------ Uwaga istnieje kalaog Debug - build z VC --------\n');
    fprintf('Jeœli nie to skasuj katalog Debug\n');
    p = [p 'Debug\'];
end
%% TEST STATIC_WeldDetexApprox._WeldDetexApprox_1

% dane wejœciowe
rtg1 = readbinarymatrix([p 'testimag1.dat']);

% dane wyjœciowe
ImportDumpFile([p 'WeldDetectApprox_1.out']);

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