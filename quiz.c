#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

// Carregar perguntas de dados.txt
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

// Função para imprimir todas as perguntas e seus valores

void imprimirTudo(char matpergs[][100], char matresp1[][100], char matresp2[][100], char matresp3[][100], char matresp4[][100], int matvalores[][4], int tam) {
    int i; //int i,j;
    for(i=0; i<tam; i++) {
        if (matvalores[i][0] < 0) break;
        printf("\n\nPergunta %d: %s", i+1, matpergs[i]);
        printf("\n\ta) %s - Valor: %d", matresp1[i], matvalores[i][0]);
        printf("\n\tb) %s - Valor: %d", matresp2[i], matvalores[i][1]);
        printf("\n\tc) %s - Valor: %d", matresp3[i], matvalores[i][2]);
        printf("\n\td) %s - Valor: %d", matresp4[i], matvalores[i][3]);
    }
}

// Função para imprimir uma pergunta sem valores
void imprimirPergunta(char matpergs[][100], char matresp1[][100], char matresp2[][100], char matresp3[][100], char matresp4[][100], int tam) {
    int i; //int i,j;
    for(i=0; i<tam; i++) {
        //if (matvalores[i][0] < 0) break;
        printf("\n\nPergunta %d: %s", i+1, matpergs[i]);
        printf("\n\ta - %s", matresp1[i]);
        printf("\n\tb - %s", matresp2[i]);
        printf("\n\tc - %s", matresp3[i]);
        printf("\n\td - %s", matresp4[i]);
    }
}

// Função para imprimir uma pergunta especifica sem valores
void imprimirPerguntaEspecifica(char matpergs[][100], char matresp1[][100], char matresp2[][100], char matresp3[][100], char matresp4[][100], int indicepergunta) {

    int i = indicepergunta;
    printf("\n\nPergunta %d: %s", i+1, matpergs[i]);
    printf("\n\ta - %s", matresp1[i]);
    printf("\n\tb - %s", matresp2[i]);
    printf("\n\tc - %s", matresp3[i]);
    printf("\n\td - %s", matresp4[i]);
}


// Gerador de números aleatórios

int randomInteger (int low, int high) {
    int k;
    double d;

    d = (double) rand () / ((double) RAND_MAX + 1);
    k = d * (high - low + 1);

    return low + k;
}

int repeated (int vet[], int num, int tam) {
    int i;
    for (i=0; i<tam; i++) {
        if (vet[i] == num)
            return 1;
    }
  return 0;
}

int printvet(int vet[], int tam) {
    int i;
    printf("Valores gerados %d: ", tam);
    for (i=0; i<tam; i++) {
        printf("[ %d ]", vet[i]);
    }
}

int generate(int vet[], int tam) {
    int i=0, tmp;
    do {
        tmp = randomInteger(0,19);
        if (!repeated(vet, tmp, tam)) {
            vet[i] = tmp;
            i++;
        }
    } while(i < tam);
}

// Inicio main

int main() {
    // Define a língua na qual serão apresentados os caracteres especiais
    setlocale(LC_ALL, "Portuguese");

    // INICIO DO PROJETO

    // REC_ABERTURA

    int tam=20;

    //Matrizes e vetores para armazenar os dado
    char matpergs[tam][100], matresp1[tam][100], matresp2[tam][100], matresp3[tam][100], matresp4[tam][100];
    int matvalores[tam][4];

    inicializarDados(matvalores,tam);

    /*Esta função carrega os dados gravados no arquivo dados.txt e coloca as informações nos vetores.*/
    carregarDadosArquivo(matpergs, matresp1, matresp2, matresp3, matresp4, matvalores, tam);

    // ASCIIART de abertura COLOCAR AQUI!!!

    printf(" Bem vindo(a) ao Velozes e Curiosos \n Um quiz que vai te mostrar qual personagem da saga velozes e furiosos mais se parece com você. \n\n O quiz funciona da seguinte forma:\n\n Vão ser apresentadas algumas perguntas com 4 opções de resposta, cada resposta direciona a um personagem. \n Ao final, será mostrado com qual personagem você teve mais respostas relacionadas. \n\n");

    // REC_NOME

    int n;
    char nome[30];
    printf("\n Para começar, insira seu nome: ");
    do {
        setbuf(stdin, NULL);
        scanf("%[^\n]s", nome);

        if (strlen(nome) <= 2 || strlen(nome) > 30) {
            n = 1;
            if (strlen(nome) <=2 ) {
            printf("\n Nome muito pequeno, insira um nome com mais de 2 caracteres: ");
            }
            else {
            printf("\n Nome muito grande, insira um nome com menos de 30 caracteres: ");
            }
        }
        else {
            //printf("\n Tenha um bom jogo %s!\n\n", nome);
            n = 0;
        }
    } while (n == 1);

    //REC_FILTROS

    int modojogo, numquestoes;

    printf("\n %s para começar a jogar, escolha um modo de jogo:\n\n 0 - modo de jogo rápido (3 questões)\n 1 - modo de jogo completo (10 questões)\n\n ", nome);
    
    do {
        printf("Digite 0 ou 1: ");
        scanf("%d", &modojogo);
        if (modojogo == 0) {
            printf("\n OK você escolheu o modo de jogo rápido e terá que responder a 3 questões!\n\n");
            numquestoes = 3;
        }
        else if (modojogo == 1) {
            printf("\n OK você escolheu o modo de jogo completo e terá que responder a 10 questões!\n\n");
        numquestoes = 10;
        }
        else {
            printf("\n Você não escolheu um modo de jogo válido. \n\n 0 - modo de jogo rápido (3 questões)\n 1 - modo de jogo completo (10 questões)\n\n ");
        }
    } while (modojogo != 0 && modojogo != 1);

    // REC_ALEATORIO

    int at = numquestoes;

        if (at > 0 && at <= 20) {
          int vet[at];
          generate(vet, at);
          printvet(vet, at);
        }

    for (int i = 1; i <= numquestoes; i++) {
        imprimirPerguntaEspecifica(matpergs, matresp1, matresp2, matresp3, matresp4, i);
        printf("%d", i);
    }

    // FIM DO PROJETO

    /*Esta função pode ser usada por vocês somente para conferir se a leitura dos dados deu certo.*/
    //imprimirTudo(matpergs, matresp1, matresp2, matresp3, matresp4, matvalores, tam);
    //imprimirPergunta(matpergs, matresp1, matresp2, matresp3, matresp4, tam);

    return 0;
}