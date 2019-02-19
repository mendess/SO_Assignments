#include "e5_readln.c"
#include <stdlib.h>

int contains(const char *needle, const char *haystack, int size){
	int r;
	int i=0;
	while(i<size){
		int j = i;
		int ne = 0;
		while(j<size && needle[ne] == haystack[j]){
			ne++;
			j++;
		}
		if(!needle[ne]) return 1;
		i++;
	}
	return 0;
}

int main(int argc, char const *argv[]){
	if(argc < 3){
		printf("Use: my_grep <filter> <file_name>\n");
		return 1;
	}
	int buffsize = 1;
	char *buf = (char *) malloc(buffsize);

	for(int i = 2; i < argc ; i++){
		int fd = open(argv[i], O_RDONLY);
		int n;
		int offset = 0;
		while((n = readln(fd,buf+offset,buffsize))){
			if(buf[n-1] != '\n'){
				buf = realloc(buf,buffsize*2);
				offset = buffsize;
				buffsize *=2;
				continue;
			}else{
				offset = 0;
			}
			if(contains(argv[1],buf,n)){
				write(1,buf,n);
			}
		}
		close(fd);
	}
	free(buf);
	return 0;
}
