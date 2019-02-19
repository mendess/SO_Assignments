#include "guiao2.h"
#include <stdio.h>

int main(){
    for(int i=1;i<11;i++){
        if(!fork()){
            printf("O meu pid é %d e o meu pai é %d\n",getpid(),getppid());
            _exit(i);
        }
        int pid,status;
        pid = wait(&status);
        status = WEXITSTATUS(status);
        printf("O filho %d teminou com o codigo %d\n",pid,status);
    }
    return 0;
}
