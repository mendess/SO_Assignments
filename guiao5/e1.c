#include <unistd.h>
#include <string.h>

/*
 * Escreva um programa que crie um pipe anónimo e de seguida crie um processo filho. Relembre que as
 * associações dos descritores de ficheiros são preservadas na criação do processo filho. Experimente o pai
 * enviar uma linha de texto através do descritor de escrita do pipe, e o filho receber uma linha a partir do
 * respectivo descritor de leitura. Note que a informação foi transferida do pai para o filho. Experimente
 * de seguida provocar um atraso antes do pai enviar a linha de texto (p. ex., sleep(5)). Note agora que
 * a leitura do filho bloqueia enquanto o pai não realizar a operação de escrita no pipe. Experimente agora
 * inverter os papeis de modo à informação ser transmitida do filho para o pai
 */

int main(){
    int pfd[2];
    char buf[10];
    pipe(pfd);

    if(!fork()){
        int n;
        while((n=read(pfd[0],buf,10)) > 0)
                write(1,buf,n);
    }else{
        sleep(2);
        int n;
        write(pfd[1], "Hello Luke\n", 11);
        sleep(2);
        write(pfd[1], "I am your father\n", strlen("I am your father\n"));
    }
    return 0;
}
