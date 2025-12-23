/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/21 16:45:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

    game.map = &map;
    game.textures = &textures;
    game.frame_count = 0;

    if (!parse_sprites(&game))
    {
        printf("Error\nFailed to parse sprites\n");
        return (1);
    }
    printf("Parsed %d sprites\n", game.sprite_count);

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

    mlx_mouse_hide(game.mlx, game.win);
    mlx_mouse_move(game.mlx, game.win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
    mlx_hook(game.win, 17, 1L<<17, close_window, &game);
    mlx_hook(game.win, 2, 1L<<0, handle_keypress, &game);
    mlx_hook(game.win, 6, 1L<<6, mouse_move, &game);
    mlx_loop_hook(game.mlx, render_loop, &game);
    mlx_loop(game.mlx);
    free_map_grid(&map);
    return (0);
}