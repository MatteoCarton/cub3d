#include "../includes/cub3d.h"

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
        return (printf("Error: No map provided\n"), 0);
    if (argc > 2)
        return (printf("Error: Too many arguments\n"), 0);
    if (check_name_map(argv[1]) == 0)
        return (printf("Error: Invalid extension, not a .cub file\n"), 0);
    
    return (1);
}