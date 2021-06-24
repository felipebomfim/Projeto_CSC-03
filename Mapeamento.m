clear;

M = [
    0 0 1 1 1 1 1 0 0 0 0;
    0 0 1 1 1 1 1 0 0 0 0;
    0 0 1 1 1 1 1 0 0 0 0;
    0 0 2 2 2 2 2 0 0 0 0;
    0 0 3 3 3 0 0 0 1 1 0;
    0 0 0 0 0 3 0 3 0 0 0;
    0 0 0 0 0 0 0 0 0 0 0;
];

M = readmatrix("matrix");

M = M +1;

figure
subplot 121;
image(M);

[height,width] = size(M);

colormap([0 1 0; 0 0 0; 1 1 0; 1 0 0])
axis off;
hold on;

for row = 1 : 1 : height+1
  line([1-0.5, width+0.5], [row-0.5, row-0.5], 'Color', 'b');
end
for col = 1 : 1 : width+1
  line([col-0.5, col-0.5], [1-0.5, height+0.5], 'Color', 'b');
end
title("Mapa de calor das Telhas");

A = scatter([],[],1, [0 1 0], 'filled', 'DisplayName', 'Normal');  
B = scatter([],[],1, [0 0 0], 'filled', 'DisplayName', 'Não Identificado');
C = scatter([],[],1, [1 1 0], 'filled', 'DisplayName', 'Objeto');
D = scatter([],[],1, [1 0 0], 'filled', 'DisplayName', 'Buraco');

legend([A B C D],'Location', 'southeastoutside');

NTelhas = height*width;
NNormais = 0;
NBuracos = 0;
NObjetos = 0;
NNIdenti = 0;

for i = 1 : 1 : height
    for j = 1 : 1 : width
        if M(i,j) == 1
            NNormais = NNormais + 1;
        end
        if M(i,j) == 2
            NNIdenti = NNIdenti + 1;
        end
        if M(i,j) == 3
            NObjetos = NObjetos + 1;
        end
        if M(i,j) == 4
            NBuracos = NBuracos + 1;
        end
    end
end


subplot 122;
y = [NTelhas, NNormais, NBuracos, NObjetos, NNIdenti];
b = bar(y,'FaceColor','flat');
b.CData(2,:) = [0 1 0];
b.CData(3,:) = [1 0 0];
b.CData(4,:) = [1 1 0];
b.CData(5,:) = [0 0 0];
title("Resumo das Telhas")
text(1:5,y,num2str(y'),'vert','bottom','horiz','center');
ylabel("Quantidade de telhas",'FontSize',12,'FontWeight','bold','Color','r')
set(gcf, 'Position', [10, 250, 2000, 600]);
xticklabels({'TOTAL \newlineDE TELHAS','TELHAS \newlineNORMAIS','TELHAS COM\newline BURACOS', 'TELHAS COM \newlineOBJETOS', '      PROBLEMAS \newlineNÃO IDENTIFICADOS'})


