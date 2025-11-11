#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

void alarm_handler(int sig)
{
    (void)sig;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    int status;
    struct sigaction sa;
    pid_t pid;

    sa.sa_handler = alarm_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    pid = fork();
    if (pid == -1)
        return (-1);

}