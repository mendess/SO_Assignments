#include "guiao3.h"
#include <stdio.h>
#include <string.h>

int mySystem(char *command){
    if(command == NULL || command[0] == '\0'){
        printf("Bash is ok \n");
        return 0;
    }else{
        if(!fork())
             execlp("sh","sh","-c",command,NULL);
        int status;
        wait(&status);
        if(WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return -1;
    }
}

int main(int argc, char **argv){
    int len=1;
    for(int i = 1; i< argc; i++)
        len+=strlen(argv[i]);
    char command[len];
    int offset = 1;
    for(int i = 1;i<argc;i++)
        offset += sprintf(command+offset-1," %s",argv[i]);
    int err;
    err = mySystem(command);
    if(!err)
        printf("Succ\n");
    else
        printf("Error: %d\n",err);
    return 0;
}
