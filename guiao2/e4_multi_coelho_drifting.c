#include "guiao2.h"
#include <stdio.h>
/**
 * Implemente um programa que crie dez processos filhos que deverão executar
 * (potencialmente) em concorrência. O pai deverá esperar pelo fim da execução de todos os
 * seus filhos, imprimindo os respectivos códigos de saı́da.
 */
int main(){
    for(int i=1; i<11; i++){
        if(!fork()){
            _exit(i);
        }
    }
    int pid, status;
    while((pid = wait(&status))!=-1){
        printf("O filho %d morreu com codigo de saida %d\n",pid,WEXITSTATUS(status));
    }
    return 0;
}
