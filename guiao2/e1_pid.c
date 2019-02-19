#include "guiao2.h"
#include <stdio.h>

int main(int argc, const char *argv){
	printf("Pai: %d - Filho: %d\n",getppid(),getpid());
	return 0;
}
