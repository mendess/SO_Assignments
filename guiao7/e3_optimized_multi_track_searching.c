#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <limits.h>

#define NUM_LINES 5
#define NUM_COLS  INT_MAX
#define NUM_CELLS (NUM_LINES*NUM_COLS)
int main(int argc, const char **argv){
    srand(time(NULL));
    int target;
    int range = NUM_COLS/4;
    if(argc < 2)
        target = rand() % range;
    else
        target = atoi(argv[1]);
    if(target > range){
        printf("Number is too big (max is %d)\n",range);
        return 0;
    }
    // Matrix
    printf("Initializing matrix [-] ");
    char bars[] = "|/-\\";
    int *matrix[NUM_LINES];
    for(int i = 0; i<NUM_LINES;i++)
        matrix[i] = malloc(sizeof(int)*NUM_COLS);
    int progress = 0;
    for(int i=0;i<NUM_LINES;i++){
        for(int j=0;j<NUM_COLS;j++){
            if(!(progress%4000)){
                printf("\b\b\b%c] ",bars[(progress/4000)%4]);
                fflush(stdout);
            }
            matrix[i][j]=rand() % range;
            //usleep(10);
            progress++;
        }
    }
    printf("\nSearching for %d in matrix\n",target);
    // Forks
    int childs[NUM_LINES];
    for(int i=0;i<NUM_LINES;i++){
        if(!(childs[i] = fork())){
            for(int j=0;j<NUM_COLS;j++){
                if(matrix[i][j] == target){
                    _exit(1);
                }
                usleep(1000);
            }
            _exit(0);
        }
    }
    // Waiting
    int pid, status;
    while((pid=wait(&status))!=-1){
        int i;
        for(i=0;i<NUM_LINES && pid!=childs[i];i++);
        childs[i] = 0;
        if(WEXITSTATUS(status)){
            printf("Child %d found the target on line %d\n",pid,i);
            for(int j = 0; j < NUM_LINES; j++){
                if(childs[i])
                    kill(childs[i],SIGINT);
            }
        }else{
            printf("Child %d didn't find notin on line %d\n",pid,i);
        }
    }
    return 0;
}
