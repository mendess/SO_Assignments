#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/wait.h>

int main(){
    printf("Starting server...\n");
    mkfifo("pip", 0644);
    printf("Forking..\n");
    if(!fork()){

        printf("Opening pipe\n");
        int input = open("pip", O_RDONLY);
        if(input < 0) printf("Cona no pipe");

        printf("Opening log\n");
        int log = open("log.txt", O_CREAT|O_WRONLY, 0644);
        if(log < 0) printf("Cona no log");


        printf("Reading\n");

        while(1){
            char buf[1024];
            int n = read(input,buf,1024);
            if(read > 0)
              write(log, buf, n);
        }
    }else{
      wait(NULL);
    }
    return 0;

}
