/*
 * Using SIGINT, SIGQUIT, and SIGALRM, write a program that counts the time
 * in seconds since it started and prints the time elapsed whenever the user
 * presses Ctrl-C. If the user presses Ctrl- your program
 * should indicate how many times the user has pressed Ctr-C and exit.
 */

#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

typedef void (*sighandler_t)(int);

int time;
int timesBooped;

void boop(int i)
{
    (void)i;
    printf("Time elapsed: %d\n", time);
    timesBooped++;
}

void sepuku(int i)
{
    (void)i;
    printf("Times booped: %d\n", timesBooped);
    _exit(0);
}

void alarmS(int i)
{
    (void)i;
    alarm(1);
    time++;
}

int main()
{
    printf("%d\n", getpid());
    signal(SIGINT, boop);
    signal(SIGQUIT, sepuku);
    signal(SIGALRM, alarmS);

    alarm(1);

    while (1) {
        pause();
    }
    return 0;
}
