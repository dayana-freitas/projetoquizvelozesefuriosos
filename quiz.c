#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

/* Exemplo de linha para o arquivo texto
Nobreza é ...?;Viver pelo próximo.;Sobreviver a qualquer custo.;Lutar bravamente pelo que você acredita.;Trazer ordem.;2;4;1;3;
*/

void inicializarDados(int vet[][4], int tam) {
    int i;
    for(i=0; i<tam; i++) {
        vet[i][0]=-1;
        vet[i][1]=-1;
        vet[i][2]=-1;
        vet[i][3]=-1;
    }
}

void carregarDadosArquivo(char matpergs[][100], char matresp1[][100], char matresp2[][100], char matresp3[][100], char matresp4[][100], int matvalores[][4], int tam) {
    FILE *arq = fopen("dados.txt", "r");
    int linha=0, parte;
    char frase[1000];

    while (fscanf(arq, "%[^\n] ", frase) != EOF){
        char *token = strtok(frase, ";");
        parte=0;
        while(token != NULL && linha <= tam) {
            switch (parte) {
            case 0: /*pergunta*/
                    strcpy(matpergs[linha], token);
                    break;
            case 1: /*resp1*/
                    strcpy(matresp1[linha], token);
                    break;
            case 2: /*resp2*/
                    strcpy(matresp2[linha], token);
                    break;
            case 3: /*resp3*/
                    strcpy(matresp3[linha], token);
                    break;
            case 4: /*resp4*/
                    strcpy(matresp4[linha], token);
                    break;
            case 5: /*val1*/
                    matvalores[linha][0] = atoi(token);
                    break;
            case 6: /*val2*/
                    matvalores[linha][1] = atoi(token);
                    break;
            case 7: /*val3*/
                    matvalores[linha][2] = atoi(token);
                    break;
            case 8: /*val4*/
                    matvalores[linha][3] = atoi(token);
                    break;

            }

            token = strtok(NULL, ";");
            parte++;
        }
        linha++;
    };
}

void imprimirTudo(char matpergs[][100], char matresp1[][100], char matresp2[][100], char matresp3[][100], char matresp4[][100], int matvalores[][4], int tam) {
    int i,j;
    for(i=0; i<tam; i++) {
        if (matvalores[i][0] < 0) break;
        printf("\n\nPergunta %d: %s", i+1, matpergs[i]);
        printf("\n\ta) %s - Valor: %d", matresp1[i], matvalores[i][0]);
        printf("\n\tb) %s - Valor: %d", matresp2[i], matvalores[i][1]);
        printf("\n\tc) %s - Valor: %d", matresp3[i], matvalores[i][2]);
        printf("\n\td) %s - Valor: %d", matresp4[i], matvalores[i][3]);
    }
}

int main() {
    int tam=20;
    setlocale(LC_ALL, "Portuguese");

    //Matrizes e vetores para armazenar os dados
    char matpergs[tam][100], matresp1[tam][100], matresp2[tam][100], matresp3[tam][100], matresp4[tam][100];
    int matvalores[tam][4];

    inicializarDados(matvalores,tam);

    /*Esta função carrega os dados gravados no arquivo dados.txt e coloca as informações nos vetores.*/
    carregarDadosArquivo(matpergs, matresp1, matresp2, matresp3, matresp4, matvalores, tam);

    /*Esta função pode ser usada por vocês somente para conferir se a leitura dos dados deu certo.*/
    imprimirTudo(matpergs, matresp1, matresp2, matresp3, matresp4, matvalores, tam);

    

    return 0;
}