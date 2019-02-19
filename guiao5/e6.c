#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
/*
 * Implemente uma função semelhante ao popen(), mas que em
 * vez de retornar um valor do tipo FILE * ,
 * retorne o descritor apropriado do descritor de um pfd anónimo.
 * Nota: se desejar pode converter um descritor num endereço de uma
 * estrutura FILE usando para o efeito a função fdopen(). Reflicta sobre
 * a necessidade da função pclose() da biblioteca de C e como poderia
 * proceder para suportar essa funcionalidade.
 */
char** words(const char *string){
    char *command = strdup(string);
    int argc = 5;
    char **argv = malloc(argc*sizeof(char *));
    int i=0;
    char *token = strtok(command," ");
    do{
        if(!(i<argc))
            argv = realloc(argv,(argc*=2)*sizeof(char *));

        argv[i++] = token;

        token = strtok(NULL," ");
    }while(token);
    argv[i] = NULL;
    return argv;
}

int contains(const char* string, char chr){
    for(;*string;string++)
        if(*string==chr) return 1;
    return 0;
}

int myPOpen(const char* command, const char* type){
    char **argv = words(command);
    int pfd[2];
    pipe(pfd);
    if(!fork()){
        if(contains(type, 'r'))
            dup2(pfd[1],1);
        else if(contains(type, 'w'))
            dup2(pfd[0],0);
        else _exit(1);
        close(pfd[0]);
        close(pfd[1]);
        execvp(argv[0],argv);
        _exit(1);
    }
    if(contains(type,'r')){
        close(pfd[1]);
        return pfd[0];
    }
    if(contains(type,'w')){
        close(pfd[0]);
        return pfd[1];
    }
    return -1;
}

int main(){
    int wc = myPOpen("wc", "w");
    write(wc,"abc\n",4);
    close(wc);
    int ls = myPOpen("ls", "r");
    int n;
    char buf[10];
    while((n=read(ls,buf,10)) > 0)
        write(1,buf,n);
    close(ls);
    return 0;
}
