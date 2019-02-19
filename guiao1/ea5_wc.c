#include <unistd.h>
#include <stdio.h>

#include "e5_readln.c"

int isLetter(char c){
	char notChars[] = {'\n',' ','\t','\0'};
	for(int i=0;i<4;i++)
		if(c == notChars[i]) return 0;
	return 1;
}

int wordCount(char *string, ssize_t size){
	int count = 0;
	int inWord = 0;
	for(int i = 0; i < size; ++i){
		if(!inWord && isLetter(string[i])){
			inWord = 1;
			count++;
		}else if(inWord && !isLetter(string[i])){
			inWord = 0;
		}
	}
	return count;
}

int main(int argc, const char **argv){
	int fd = 0;
	int counts[argc][3];
	for(int i = 0; i< argc;i++){
		counts[i][0] = 0;
		counts[i][1] = 0;
		counts[i][2] = 0;
	}
	for(int i = 1;i<argc;i++){
		fd = open(argv[i],O_RDONLY);
		if(fd == -1) continue;
		int n;
		char buf[1024];
		while((n=readln(fd,buf,1024))>0){
			if(buf[n-1] == '\n') counts[i][0]++;
			counts[i][1] += wordCount(buf,n);
			counts[i][2] += n;
		}
		counts[0][0] += counts[i][0];
		counts[0][1] += counts[i][1];
		counts[0][2] += counts[i][2];
	}
	if(argc>1){
		for(int i = 1; i < argc; i++){
			printf("%8d  %8d  %8d %s\n",
					counts[i][0],
					counts[i][1],
					counts[i][2],
					argv[i]);
		}
	}
	if(argc>2){
		printf("%8d  %8d  %8d total\n",
				counts[0][0],
				counts[0][1],
				counts[0][2]);
	}
	return 0;
}
