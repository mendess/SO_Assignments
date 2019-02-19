#include <unistd.h>
/*
 * Escreva um programa que execute o comando wc num processo filho. O processo pai
 * deve enviar ao filho através de um pipe anónimo uma sequência de linhas de texto
 * introduzidas pelo utilizador no seu standard input. Recorra à técnica de redireccionamento
 * estudada no guião anterior de modo a associar o standard input do processo filho
 * ao descritor de leitura do pipe anónimo criado pelo pai. Recorde a necessidade de fechar
 * o(s) descritor(es) de escrita no pipe de modo a verificar-se a situação de end of file
 */

int main(){
    int pfd[2];
    char buf[1024];
    pipe(pfd);
    if(!fork()){
        dup2(pfd[0],0);
        close(pfd[1]);
        execlp("wc","wc",NULL);
    }
    int n;
    close(pfd[0]);
    while((n=read(0,buf,1024)) > 0)
        write(pfd[1],buf,n);
    close(pfd[1]);
    return 0;
}
