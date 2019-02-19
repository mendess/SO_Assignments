#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "e5_readln.c"

int main(int argc, char const *argv[]){
	if(argc == 1){
		printf("provide file name\n");
		return -1;
	}
	int line = 1;
	int n = 0;
	int fd = open(*(argv+1),O_CREAT|O_RDONLY);
	char buf[1024];
	while((n = readln(fd,buf,1024)) > 0){
		if(n!=1){
			char lineNum[12];
			sprintf(lineNum, "%6d  ", line);
			write(1,lineNum,strlen(lineNum));
			if(buf[n-1] == '\n'){
				line++;
			}
		}
		write(1,buf,n);
	}
}
