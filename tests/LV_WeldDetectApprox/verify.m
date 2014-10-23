%% test LV_WeldDetect
% Weryfikuje wyjœcie z testów

% Wyniki testu
p  = '..\..\bin\tests\LV_WeldDetectApprox\';
if exist(p,'dir')~=7
    error('Nie mo¿na znlaeœc folderu z testem')
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