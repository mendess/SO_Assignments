#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char* argv[])
{
    int res;
    srand(time(NULL));
    res = rand() % 3;
    printf("%s: %d\n", argv[0], res);
    return res;
}
