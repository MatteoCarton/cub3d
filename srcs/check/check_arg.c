#include "../includes/cub3d.h"

static int open_file(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        perror("Error\nOpening file");
        return (0);
    }
    close(fd);
    return (1);
}
static int check_name_map(char *map_name)
{
    int len;

    len = 0;

    while (map_name[len] != '\0')
        len++;
    if (len < 4 || map_name[len - 4] != '.' || map_name[len - 3] != 'c' ||
        map_name[len - 2] != 'u' || map_name[len - 1] != 'b')
        return (0);
    return (1);
}
int check_map(int argc, char **argv)
{
    if (argc < 2)
        return (printf("Error\nNo map provided\n"), 0);
    if (argc > 2)
        return (printf("Error\nToo many arguments\n"), 0);
    if (check_name_map(argv[1]) == 0)
        return (printf("Error\nInvalid extension, not a .cub file\n"), 0);
    if (open_file(argv[1]) == 0)
        return (printf("Error\nCould not open map file\n"), 0);
    
    return (1);
}