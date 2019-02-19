#include "guiao3.h"

int main()
{
    if (!fork()) {
        execlp("ls", "ls", "-l", NULL);
    }
    return 0;
}
