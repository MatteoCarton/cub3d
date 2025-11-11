#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/errno.h>

void alarm_handler(int sig)
{
    (void)sig;
}

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    struct sigaction sa;
    int status;
    pid_t pid;

    sa.sa_handler = alarm_handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);
    sigaction(SIGALRM, &sa, NULL);

    pid = fork();
    if(pid == -1)
        return (-1);
    if (pid == 0)
    {
        f();
        exit(0);
    }
    
    alarm(timeout);
    if(waitpid(pid, &status, 0) == -1)
    {
        if(errno == EINTR)
        {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);
            if (verbose)
                printf("%u\n", timeout);
            return (0);
        }
       return(-1);
    }

    if (WIFEXITED(status))
    {
        if (WEXITSTATUS(status))
    }

    if (WIFSIGNALED(status))
    {
        if(verbose)
            
    }
}