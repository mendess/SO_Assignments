#include <unistd.h>
#include <fcntl.h>
int main(int argc, char const *argv[]){
	int fd = 0;
	for(int i = 1; i<argc; i++){
		fd = open(argv[i],O_RDONLY);
		char buf[1024];
		int n;
		while((n=read(fd,buf,1024))){
			write(1,buf,n);
		}
	}
	return 0;
}
