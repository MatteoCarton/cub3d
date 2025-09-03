#include "../includes/cub3d.h"

static void parse_color(char *line, int *color_array)
{
    char *color;
    char **rgb;
    int i = 0;
    int j = 0;
    int k = 0;
    int m = 0;
    int value;
    
    color = ft_strtrim(line + 2, " \t\n\r\v\f");
    if (!color || !*color)
    {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    rgb = ft_split(color, ',');

    // on verifie que y'a bien QUE 3 elements
    while (rgb[i])
        i++;
    if (i != 3)
    {
        printf("Error\nInvalid color format\n");
        free(color);
        if (rgb)
            free(rgb);
        exit(EXIT_FAILURE);
    }

    // Verifier que chaque valeur est bien un nombre
    j = 0;
    while (j < 3)
    {
        m = 0;
        while (rgb[j][m])
        {
            if (!ft_isdigit(rgb[j][m]))
            {
                printf("Error\nColor values must be numbers only\n");
                free(color);
                k = 0;
                while (k < i)
                {
                    free(rgb[k]);
                    k++;
                }
                free(rgb);
                exit(EXIT_FAILURE);
            }
            m++;
        }
        j++;
    }
    
    // On verifie que chaque valeur est entre 0 et 255
    j = 0;
    while(j < 3)
    {
        value = ft_atoi(rgb[j]);
        if (value < 0 || value > 255)
        {
            printf("Error\nColor values must be between 0 and 255\n");
            free(color);
            while (k < i)
            {
                free(rgb[k]);
                k++;
            }
            free(rgb);
            exit(EXIT_FAILURE);
        }
        color_array[j] = value;
        j++;
    }
    
    // Free a la fin
    k = 0;
    while (k < i)
    {
        free(rgb[k]);
        k++;
    }
    free(rgb);
    free(color);
}

static void parse_textures(char *line, t_textures *textures)
{
    char *path_texture;
    int fd;
    
    // Extraire le path après le "NO "
    path_texture = ft_strtrim(line + 3, " \t\n\r\v\f");
    if (!path_texture || !*path_texture)
    {
        printf("Error\nEmpty texture path\n");
        if (path_texture)
            free(path_texture);
        exit(EXIT_FAILURE);
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

static void parse_line(char *line, t_textures *textures)
{
    if (ft_strncmp(line, "NO ", 3) == 0 ||
        ft_strncmp(line, "SO ", 3) == 0 ||
        ft_strncmp(line, "WE ", 3) == 0 ||
        ft_strncmp(line, "EA ", 3) == 0)
        parse_textures(line, textures);
    else if (ft_strncmp(line, "F ", 2) == 0)
        parse_color(line, textures->floor);
    else if (ft_strncmp(line, "C ", 2) == 0)
        parse_color(line, textures->ceiling);
    
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
        parse_line(line, textures);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (1);
}
