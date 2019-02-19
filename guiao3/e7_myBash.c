#include "guiao3.h"
#include "../guiao1/e5_readln.c"
#include <string.h>
#include <stdlib.h>

int changeDir(char **argv){
    if(strcmp(argv[0], "cd")) return 0;
    if(!argv[1]){
        chdir(getenv("HOME"));
        return 1;
    }
    chdir(argv[1]);
    return 1;
}

int runCmd(char *cmd, ssize_t size){
    char command[size];
    strncpy(command,cmd,size);
    command[size-1] = '\0';
    int argc = 5;
    char **argv = malloc(argc*sizeof(char *));
    int i=0;
    char *token = strtok(command," ");
    do{
        if(i>=argc)
            argv = realloc(argv,(argc*=2)*sizeof(char *));

        argv[i++] = token;

        token = strtok(NULL," ");
    }while(token);
    if(changeDir(argv)) return 0;
    int background = argv[i-1][0] == '&' && argv[i-1][1] == '\0';
    if(background) argv[i-1][0] = '\0';
    if(!fork()){
        execvp(argv[0],argv);
    }
    free(argv);
    if(!background){
        int status;
        wait(&status);
        if(WIFEXITED(status))
            return WEXITSTATUS(status);
        return -1;
    }
    return 0;
}

int main(){
    int bufferSize = 4096;
    char *buffer = malloc(bufferSize);
    int offset = 0;
    char *bashPrefix = "€ ";
    while(1){
        if(!offset){
            printf("%s",bashPrefix);
            fflush(stdout);
        }
        int n = readln(0,buffer+offset,bufferSize-offset);

        if(n<1 || !strncmp(buffer,"exit\n",n)) break;

        if(buffer[n-1]!='\n'){
            buffer = realloc(buffer,bufferSize*2);
            offset += bufferSize;
            bufferSize*=2;
        }else{
            runCmd(buffer,n+offset);
            offset = 0;
        }
    }
    free(buffer);
    return 0;
}
