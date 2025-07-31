#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    void    *mlx;
    void    *win;

    if (check_map(argc, argv) == 0)
        exit(EXIT_FAILURE);

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