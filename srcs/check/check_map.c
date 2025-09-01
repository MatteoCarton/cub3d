#include "../includes/cub3d.h"

int check_map(int argc, char **argv)
{
    (void)argc;
    int fd;
    char *line;

    fd = open(argv[1], O_RDONLY);
    line = get_next_line(fd);
    while(line != NULL)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (1);
}