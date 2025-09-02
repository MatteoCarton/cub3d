#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    void    *mlx;
    void    *win;
    t_textures textures;

    ft_bzero(&textures, sizeof(t_textures)); // Initialiser tous les pointeurs à NULL
    if (check_args(argc, argv) == 0)
        exit(EXIT_FAILURE);
    if (check_map(argc, argv, &textures) == 0)
        exit(EXIT_FAILURE);
    printf("textures->NO: %s\n", textures.north);
    printf("textures->SO: %s\n", textures.south);
    printf("textures->WE: %s\n", textures.west);
    printf("textures->EA: %s\n", textures.east);
    printf("Floor color: R=%d, G=%d, B=%d\n", textures.floor[0], textures.floor[1], textures.floor[2]);
    printf("Ceiling color: R=%d, G=%d, B=%d\n", textures.ceiling[0], textures.ceiling[1], textures.ceiling[2]);

    mlx = mlx_init();
    if (!mlx)
    {
        printf("Error\nFailed to initialize MLX\n");
        return (1);
    }
    
    win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!win)
    {
        printf("Error\nFailed to create window\n");
        return (1);
    }

    mlx_loop(mlx); /* boucle infini qui maintient la fenetre ouverte et
    ecoute les evenements (clics, touche, mouvements de fenetres, ...) */
    return (0);
}