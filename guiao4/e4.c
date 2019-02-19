#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>

/*
 * Escreva um programa redir que permita executar um comando, opcionalmente redireccionando a en-
 * trada e/ou a saı́da. O programa poderá ser invocado, com:
 * redir [-i fich_entrada] [-o fich_saida] comando arg1 arg2 ...
 */
int main(int argc, char** argv){
    (void) argc;
    for(int i=1;argv[i];++i){
        if(argv[i][0] == '-'){
            switch(argv[i][1]){
                case 'i':{
                    int fd = open(argv[++i],O_RDONLY);
                    dup2(fd,0);
                    close(fd);
                    break;
                }
                case 'o':{
                    int fd = open(argv[++i],O_CREAT|O_WRONLY|O_TRUNC);
                    dup2(fd,1);
                    close(fd);
                    break;
                }
                default: printf("Invalid option: %s\n", argv[i]); return -1;
            }
        }else{
            execvp(argv[i],argv+i);
        }
    }
}
