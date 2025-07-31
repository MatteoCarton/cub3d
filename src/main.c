#include "../includes/cub3d.h"

int main(void)
{
    void    *mlx;
    void    *win;

    mlx = mlx_init();
    if (!mlx)
    {
        printf("Error: Failed to initialize MLX\n");
        return (1);
    }
    
    win = mlx_new_window(mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!win)
    {
        printf("Error: Failed to create window\n");
        return (1);
    }

    mlx_loop(mlx);
    return (0);
}