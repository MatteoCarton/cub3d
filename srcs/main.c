#include "../includes/cub3d.h"

int main(int argc, char **argv)
{
    t_game      game;
    t_textures  textures;
    t_map       map;

    ft_bzero(&textures, sizeof(t_textures));
    if (check_args(argc, argv) == 0)
        exit(EXIT_FAILURE);
    if (check_map(argc, argv, &textures, &map) == 0)
        exit(EXIT_FAILURE);
    printf("textures->NO: %s\n", textures.north);
    printf("textures->SO: %s\n", textures.south);
    printf("textures->WE: %s\n", textures.west);
    printf("textures->EA: %s\n", textures.east);
    printf("Floor color: R=%d, G=%d, B=%d\n", textures.floor[0], textures.floor[1], textures.floor[2]);
    printf("Ceiling color: R=%d, G=%d, B=%d\n", textures.ceiling[0], textures.ceiling[1], textures.ceiling[2]);

    game.mlx = mlx_init();
    if (!game.mlx)
    {
        printf("Error\nFailed to initialize MLX\n");
        return (1);
    }

    load_all_textures(&game, &textures);
    printf("All textures loaded successfully!\n");

    init_player(&game.player, &map);
    printf("Player initialized at (%.2f, %.2f) dir=(%.2f, %.2f)\n",
        game.player.pos_x, game.player.pos_y,
        game.player.dir_x, game.player.dir_y);

    game.win = mlx_new_window(game.mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
    if (!game.win)
    {
        printf("Error\nFailed to create window\n");
        return (1);
    }

    game.img = mlx_new_image(game.mlx, WIN_WIDTH, WIN_HEIGHT);
    if (!game.img)
    {
        printf("Error\nFailed to create image\n");
        return (1);
    }
    game.addr = mlx_get_data_addr(game.img, &game.bits_per_pixel,
            &game.line_length, &game.endian);

    render_frame(&game, &textures, &map);

    mlx_loop(game.mlx); /* boucle infini qui maintient la fenetre ouverte et
    ecoute les evenements (clics, touche, mouvements de fenetres, ...) */
    free_map_grid(&map);
    return (0);
}