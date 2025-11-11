#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int    picoshell(char *cmds[])
{
    int i = 0;
    int in_fd = 0;
    int result = 0;
    int status;
    int fd[2];
    pid_t pid;

    while (cmds[i])
    {
        if (cmds[i+1])
        {
            if (pipe(fd) == -1)
                return (-1);
        }
        else
            fd[0] = fd[1] = -1;
        
        pid = fork();
        if (pid == -1)
        {
            if (fd[0] == -1)
                close(fd[0]);
            if (fd[1] == -1)
                close(fd[1]);
            if (in_fd == 0)
                close(in_fd);
            return (1);
        }
        if (pid == 0)
        {
            if (in_fd != 0)
            {
                if (dup2(in_fd, 0) == -1)
                    exit (1);
                close(in_fd);
            }
            if (fd[1] != -1)
            {
                if (dup2(fd[1], 0) == -1)
                    exit (1);
                close(fd[1]);
                close(fd[0]);
            }
            execvp(cmds[i][0], cmds[i]);
            exit (1);
        }
    }

    while (wait(&status) > 0)
    {
        if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
            result = 1;
        else if (!WIFEXITED(status))
            result = 1;
    }
    return (result);
}