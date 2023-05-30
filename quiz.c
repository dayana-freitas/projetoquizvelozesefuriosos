#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

// Função para identificar o sistema operacional e incluir a biblioteca
#ifdef __linux__
	#include <unistd.h>
#elif _WIN32
	#include <windows.h>
#endif

// Função clean conforme o sistema operacional
void clear() {
	#ifdef __linux__
		system("clear");
	#elif _WIN32
		system("cls");
	#else
	#endif
}


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

// Função para imprimir uma pergunta
void imprimirPergunta(char matpergs[][100], char matresp1[][100], char matresp2[][100], char matresp3[][100], char matresp4[][100], int matvalores[][4], int i) {
	printf("\n\n  Pergunta : %s \n", matpergs[i]);
	printf("\n\t1 - %s", matresp1[i]);
	printf("\n\t2 - %s", matresp2[i]);
	printf("\n\t3 - %s", matresp3[i]);
	printf("\n\t4 - %s", matresp4[i]);
}

// Gerador de números aleatórios
int randomInteger (int low, int high) {
	int k;
	double d;
	srand(time(NULL));
	d = (double) rand() / ((double) RAND_MAX + 1);
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

int main() {
	// Define a língua na qual serão apresentados os caracteres especiais
	setlocale(LC_ALL, "Portuguese");

	// REC_ABERTURA
	//Matrizes e vetores para armazenar os dado
	int tam=20, session;
	char matpergs[tam][100], matresp1[tam][100], matresp2[tam][100], matresp3[tam][100], matresp4[tam][100];
	int matvalores[tam][4];

	inicializarDados(matvalores,tam);

	/*Esta função carrega os dados gravados no arquivo dados.txt e coloca as informações nos vetores.*/
	carregarDadosArquivo(matpergs, matresp1, matresp2, matresp3, matresp4, matvalores, tam);

	do {
	// ASCIIART DE ABERTURA
	printf("                __                                                              __  \n");
	printf("  ___  __ ____ |  |   ____________ ____   ______   ____      ____  __ _________|__| ____  __________  ______ \n");
	printf("  \\  \\/ // __ \\|  |  /  _ \\___   // __ \\ /  ___/ _/ __ \\   _/ ___\\|  |  \\_  __ \\  |/  _ \\/  ___/  _ \\/  ___/ \n");
	printf("   \\   /\\  ___/|  |_(  <_> )    /\\  ___/ \\___ \\  \\  ___/   \\  \\___|  |  /|  | \\/  (  <_> )___ (  <_> )___ \\  \n");
	printf("    \\_/  \\___  >____/\\____/_____ \\___  >____  >   \\___  >   \\___  >____/ |__|  |__|\\____/____  >____/____  > \n");
	printf("\n\n"); 

	printf("  Bem vindo(a) ao Velozes e Curiosos \n");
	printf("  Um quiz que vai te mostrar com qual personagem da saga Velozes e Furiosos você mais se parece. \n\n");
	printf("  O quiz funciona da seguinte forma:\n\n");
	printf("  Vão lhe ser apresentadas algumas perguntas com quatro opções de resposta.\n");
	printf("  Você deverá digitar um número de 1 a 4, conforme a resposta com a qual mais se identifique. \n");
	printf("  Ao final, será mostrado com qual ou quais dos personagens você mais se parece sendo eles:\n\n");
	printf("\t- Toretto: O líder e personagem principal do filme\n");
	printf("\t- Brian: O oficial que abandona o FBI para ajudar Toretto\n");
	printf("\t- Roman: O parceiro de Brian \n");
	printf("\t- Han: O personagem que \"morreu\" e \"reviveu\"\n");

		// REC_NOME e REC_CHECKS
		int n;
		char nome[30];
		printf("\n  Mas antes de começar, insira seu nome: ");
		do {
			n = 0;
			setbuf(stdin, NULL);
			scanf("%[^\n]s", nome);

			if (strlen(nome) < 2 || strlen(nome) > 30) {
				n = 1;
				if (strlen(nome) <=2 ) {
					printf("\n  Nome muito pequeno, insira um nome com 2 ou mais caracteres: ");
				}
				else {
					printf("\n  Nome muito grande, insira um nome com menos de 30 caracteres: ");
				}
			}
		} while (n == 1);

		//REC_FILTROS
		int modojogo, numquestoes;
		printf("\n  %s antes de começar o quiz, escolha um modo de jogo:\n\n\t0 - jogo rápido (3 questões)\n\t1 - jogo completo (10 questões)\n\n", nome);	
		do {
			printf("  Digite 0 ou 1: ");
			scanf("%d", &modojogo);
			if (modojogo == 0) {
				printf("\n  OK você escolheu o modo de jogo rápido e terá que responder a 3 questões!\n  ");
				numquestoes = 3;
			}
			else if (modojogo == 1) {
				printf("\n  OK você escolheu o modo de jogo completo e terá que responder a 10 questões!\n  ");
				numquestoes = 10;
			}
			else {
				printf("\n  Você não escolheu um modo de jogo válido.\n\t0 - jogo rápido (3 questões)\n\t1 - jogo completo (10 questões)\n\n");
			}
		} while (modojogo != 0 && modojogo != 1);

		// REC_ALEATORIO
		int vet[numquestoes], resposta, roman = 0, toretto = 0, brian = 0, han = 0, personagem = 0;
		generate(vet, numquestoes);

		// REC_PERG
		for (int i = 1; i <= numquestoes; i++) {
			imprimirPergunta(matpergs, matresp1, matresp2, matresp3, matresp4, matvalores, vet[i-1]);
			printf("\n\n  Digite sua resposta: ");

			// variavel que recebe o índice da pergunta para apresentar a resposta escolhida pelo usuário
			int alternativa = vet[i-1];
			do {
				setbuf(stdin, NULL);
				scanf("%d", &resposta);
				
				// Definir o personagem "escolhido" na resposta a pergunta
				switch (resposta) {
					case 1: printf("\n\tSua resposta foi: 1 - %s", matresp1[alternativa]);
						personagem = matvalores[alternativa][0];
						break;
					case 2: printf("\n\tSua resposta foi:2 - %s", matresp2[alternativa]);
						personagem = matvalores[alternativa][1];
						break;
					case 3: printf("\n\tSua resposta foi:3 - %s", matresp3[alternativa]);
						personagem = matvalores[alternativa][2];
						break;
					case 4: printf("\n\tSua resposta foi:4 - %s", matresp4[alternativa]);
						personagem = matvalores[alternativa][3];
						break;
					default: 
						personagem = 0;
						printf(" \n  Resposta inválida, digite sua resposta novamente: ");
				}

				//REC_CALC
				// Atribuir a pontuação para cada personagem conforme as respostas
				switch (personagem) {
					case 1: roman++;
						break;
					case 2: toretto++;
						break;
					case 3: brian++;
						break;
					case 4: han++;
						break;
					default:
						break;
				}
				
				// REC_CHECKS
			} while (resposta > 4 || resposta < 1);   
		}

		// REC_RES
		// Apenas um personagem como resposta
		printf("\n\n  ---------------------------------------------------------------------------------------------------------------------------------------");
		if (roman > toretto && roman > brian && roman > han) {
			printf("\n\n\tUAU! O personagem do filme com o qual você mais se parece é o Roman!\n");
		}
		else if (toretto > brian && toretto > han && toretto> roman) {
			printf("\n\n\tUAU! O personagem do filme com o qual você mais se parece é o Toretto!\n");
		} 
		else if (brian > toretto && brian > roman && brian > han) {
			printf("\n\n\tUAU! O personagem do filme com o qual você mais se parece é o Brian!\n");
		}
		else if (han > toretto && han > roman && han > brian) {
			printf("\n\n\tUAU! O personagem do filme com o qual você mais se parece é o Han!\n");
		}

		// Dois personagens como resposta 
		else if (roman == toretto && roman > brian && roman > han) {
			printf("\n\n\tQue legal, você se tem caracteristicas em comum com dois personagens do filme: Roman e Toretto\n");
		}
		else if (roman == brian && roman > toretto && roman > han) {
			printf("\n\n\tQue legal, você se tem caracteristicas em comum com dois personagens do filme: Roman e Brian\n");
		}
		else if (roman == han && roman > toretto && roman > brian) {
			printf("\n\n\tQue legal, você se tem caracteristicas em comum com dois personagens do filme: Roman e Han\n");
		}
		else if (toretto == han && toretto > roman && toretto > brian) {
			printf("\n\n\tQue legal, você se tem caracteristicas em comum com dois personagens do filme: Toretto e Han\n");
		}
		else if (toretto == brian && toretto > roman && toretto > han) {
			printf("\n\n\tQue legal, você se tem caracteristicas em comum com dois personagens do filme: Toretto e Brian\n");
		}
		else if (han == brian && han > roman && han > toretto) {
			printf("\n\n\tQue legal, você se tem caracteristicas em comum com dois personagens do filme: Han e Brian\n");
		}

		// Três personagens como resposta
		else if (roman == toretto && roman == brian && roman != han) {
			printf("\n\n\tOlhá só, você se parece com o Roman, o Toretto e o Brian!!!\n");
		}
		else if (roman == toretto && roman == han && roman != brian) {
			printf("\n\n\tOlhá só, você se parece com o Han, o Roman e o Toretto!!!\n");
		}
		else if (roman == brian && roman == han && roman != toretto) {
			printf("\n\n\tOlhá só, você se parece com o Brian, o Han e Roman!!!\n");
		}
		else if (toretto == brian && toretto == han && roman != toretto) {
			printf("\n\n\tOlhá só, você se parece com o Toretto, o Brian e Han!!!\n");
		}
		printf("\n  ---------------------------------------------------------------------------------------------------------------------------------------");
		
		// REC_SESS
		printf("\n\n  %s deseja responder o quiz outra vez? Digite 1 para responder novamente ou qualquer outro número para sair do quiz: ", nome);
		scanf("%d", &session);
		if (session != 1)
		{
		printf("\n\n  Espero que tenha gostado do quiz! Até uma próxima, bye\n\n");
		}
		else clear();
	} while (session == 1);
	return 0;
}