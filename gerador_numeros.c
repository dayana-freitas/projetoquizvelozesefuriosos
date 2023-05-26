#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

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

int main () {
    int at;
    setlocale(LC_ALL, "Portuguese");

    do {
        printf("\nGERADOR DE NÚMEROS ALEATÓRIOS: ");
        printf("\n\nInforme a quantidade de números aleatórios que deseja gerar.\n\t(máximo 20).");
        printf("\n\tQuantidade: ");
        scanf("%d", &at);
        if (at > 0 && at <= 20) {
          int vet[at];
          generate(vet, at);
          printvet(vet, at);

        } else {
          printf("Valor inválido");
        }
        printf("\n\nDeseja gerais mais valores? (1-sim, outro valor-não) :");
        scanf("%d", &at);

    } while (at == 1);
    return 0;
}