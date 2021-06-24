#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>

#define Normal 0;
#define NIden 1;
#define Objeto 2;
#define Quebrado 3;

struct problema{
    float X1;
    float X2;
    float Y1;
    float Y2;
    int status;
};

typedef struct problema problema;

void roofmap(float X, float Y, float x, float y, std::vector<problema> problemas, int Nproblemas){

    int NH; //número de telhas por linha horizontal
    int NV; //número de telhas por linha vertical

    NH = int(X/x);
    NV = int(Y/y);

    //no caso da medida do telhado não ser múltiplo da medida da telha, adicionar mais uma telha à contagem
    if(x*NH != X)
        NH = NH+1;

    if(y*NV != Y)
        NV = NV+1;

    //matriz com o estatus de cada telha
    int status[NH][NV];

    //pré-definindo todas as telhas como situação normal
    for(int i=0; i<NH; i++){
        for(int j=0; j<NV; j++)
            status[i][j] = Normal;
    }

    int a,b,c,d; //variáveis de apoio para localização dos problemas

    for(int k = 0; k<Nproblemas; k++){

        a = int(problemas[k].X1/x);
        b = int(problemas[k].X2/x);
        c = int(problemas[k].Y1/y);
        d = int(problemas[k].Y2/y);;

        //resolvendo problema de fronteira
        if(x*b == problemas[k].X2)
            b = b-1;

        if(y*d == problemas[k].Y2)
            d = d-1;

        for(int i = a; i<=b; i++){
            for (int j = c; j <=d ; j++) {
                if (status[i][j] < problemas[k].status)
                    status[i][j] = problemas[k].status;
            }
        }
    }
    
    FILE *fp;
    fp = fopen("Matrix.txt","w");
    for(int j = 0; j < NV; j++) {
        for(int i = 0; i < NH; i++) {
            fprintf(fp,"%d  ",status[i][j]);
        }
        
        printf("\n");
    }

}

void getdata(std::string file, std::vector<problema> & problemas, int *Nproblemas){

    FILE *fp;
    char valor[20];

    fp = fopen(file.c_str(),"r");

    if(fp != NULL) {

        fgets(valor, 20, fp);

        *Nproblemas = atoi(valor);

        problemas.resize(*Nproblemas);

        for (int i = 0; i < *Nproblemas; i++) {

            fgets(valor, 20, fp);

            fgets(valor, 20, fp);
            problemas[i].X1 = strtof(valor,nullptr);

            fgets(valor, 20, fp);
            problemas[i].X2 = strtof(valor,nullptr);

            fgets(valor, 20, fp);
            problemas[i].Y1 = strtof(valor,nullptr);

            fgets(valor, 20, fp);
            problemas[i].Y2 = strtof(valor,nullptr);

            fgets(valor, 20, fp);
            problemas[i].status = atoi(valor);
        }
    }
    else
        printf("problema na leitura do arquivo\n");

    fclose(fp);
}


int main() {

    float X,Y,x,y;
    std::vector<problema> problemas;
    int Nproblemas;

    X=10.5;
    Y=20;
    x=1;
    y=2;

    getdata("entrada.txt",problemas, &Nproblemas);

    roofmap(X,Y,x,y,problemas,Nproblemas);

    return 0;
}
