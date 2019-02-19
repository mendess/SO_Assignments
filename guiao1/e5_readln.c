#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

ssize_t readln(int fildes, void* buf, size_t nbyte)
{
    ssize_t size = 0;
    char c;
    char* buff = (char*)buf;
    while (size < nbyte && read(fildes, &c, 1) == 1) {
        if (c == '\0')
            return size;
        buff[size++] = c;
        if (c == '\n')
            return size;
    }
    return size;
}

// int main(){
//	char buf[10];
//	readln(0,buf,10);
//	printf("%s",buf);
//}
