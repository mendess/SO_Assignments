#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const* argv[])
{
    int buffSize = 1;
    if (argc > 1) {
        buffSize = atoi(*(argv + 1));
        if (buffSize == 0) {
            printf("Please provide a non-zero number\n");
            return 1;
        }
    }
    int n;
    char buff[buffSize];
    while ((n = read(0, buff, buffSize)) > 0)
        write(1, buff, n);
    return 0;
}
