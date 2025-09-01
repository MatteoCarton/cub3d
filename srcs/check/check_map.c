#include "../includes/cub3d.h"

static bool is_texture_line(char *line)
{
    if (line == NULL)
        return (false);
    if (ft_strncmp(line, "NO", 2) == 0 ||
            ft_strncmp(line, "SO", 2) == 0 || 
            ft_strncmp(line, "WE", 2) == 0 || 
            ft_strncmp(line, "EA", 2) == 0)
        return (true);
    return (false);
}

static void check_textures(char *line, t_textures *textures)
{
    char *path_texture;
    int fd;
    
    // Verifier qu'on a au moins 4 caractères "NO x"
    if (ft_strlen(line) <= 3)
    {
        printf("Error\n");
        return;
    }
    
    // Extraire le path après le "NO "
    path_texture = ft_strtrim(line + 3, " \t\n\r\v\f");
    if (!path_texture || !*path_texture)
    {
        printf("Error\nEmpty texture path\n");
        if (path_texture)
            free(path_texture);
        return;
    }
    
    // Verifier que le fichier existe
    fd = open(path_texture, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nTexture %s not found\n", path_texture);
        free(path_texture);
        exit(EXIT_FAILURE);
    }
    close(fd);
    
    // Stocker la texture
    if (ft_strncmp(line, "NO ", 3) == 0)
        textures->north = path_texture;
    else if (ft_strncmp(line, "SO ", 3) == 0)
        textures->south = path_texture;
    else if (ft_strncmp(line, "WE ", 3) == 0)
        textures->west = path_texture;
    else if (ft_strncmp(line, "EA ", 3) == 0)
        textures->east = path_texture;
}

int check_map(int argc, char **argv, t_textures *textures)
{
    (void)argc;
    int fd;
    char *line;

    fd = open(argv[1], O_RDONLY);
    line = get_next_line(fd);
    while(line != NULL)
    {
        if (is_texture_line(line))
        {
            check_textures(line, textures);
        }
        // printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (1);
}
