#include "guiao2.h"
#include <stdio.h>
/*
 * Implemente um programa que crie uma descendência em profundidade de dez processos, ou
 * seja, o processo cria um filho, este filho cria outro, e assim por diante até ao décimo
 * nı́vel de descendência.
 * Cada processo deverá imprimir o seu pid e o pid do seu pai. Se desejar, poderá obrigar
 * cada processo a esperar pelo fim da execução do seu (eventualmente) único filho.
 */
int main()
{
    for (int i = 1; i < 11; i++) {
        if (fork()) {
            break;
        } else {
            printf("Sou o %d, e sou filho do %d\n", getpid(), getppid());
        }
    }
    int pid, status;
    while ((pid = wait(&status)) != -1) {
        printf("Sou o %d e o %d morreu\n", getpid(), pid);
    }
    return 0;
}
