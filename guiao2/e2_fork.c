#include "guiao2.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char **argv){
    int pid = fork();
    if(pid){
        printf("sou o pai, o meu filho é %d e eu sou %d\n",pid, getpid());
    }
    printf("o meu pai é %d e eu sou %d\n",getppid(),getpid());
    return 0;
}
