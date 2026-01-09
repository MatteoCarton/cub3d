/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/11/26 08:53:41 by mcastrat          #+#    #+#             */
/*   Updated: 2026/01/02 17:34:59 by mcastrat         ###   ########.fr       */
=======
/*   Created: 2025/12/19 15:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/21 16:45:00 by mcastrat         ###   ########.fr       */
>>>>>>> ae1e321c442674b4e557df73ddd8c2b49159b347
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_window(t_data *data)
{
	cleanup_game(data, data->grid, data->walls);
	exit(0);
	return (0);
}

static void	init_structures(t_data *data, t_walls *walls, t_grid *grid)
{
	ft_bzero(data, sizeof(t_data));
	ft_bzero(walls, sizeof(t_walls));
	ft_bzero(grid, sizeof(t_grid));
}

static void	init_mlx(t_data *data, t_walls *walls, t_grid *grid)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("Error\nFailed to initialize MLX\n");
		cleanup_and_exit(data, grid, walls, EXIT_FAILURE);
	}
	data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	if (!data->win)
	{
		printf("Error\nFailed to create window\n");
		cleanup_and_exit(data, grid, walls, EXIT_FAILURE);
	}
	data->img = mlx_new_image(data->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!data->img)
	{
		printf("Error\nFailed to create image\n");
		cleanup_and_exit(data, grid, walls, EXIT_FAILURE);
	}
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_walls	walls;
	t_grid	grid;

<<<<<<< HEAD
	init_structures(&data, &walls, &grid);
	if (check_args(argc, argv) == 0)
		cleanup_and_exit(&data, &grid, &walls, EXIT_FAILURE);
	if (check_map(argc, argv, &walls, &grid) == 0)
		cleanup_and_exit(&data, &grid, &walls, EXIT_FAILURE);
	init_mlx(&data, &walls, &grid);
	if (!init_wall_textures(&data, &walls))
		cleanup_and_exit(&data, &grid, &walls, EXIT_FAILURE);
	init_player(&data.cam, &grid);
	data.grid = &grid;
	data.walls = &walls;
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_hook(data.win, 2, 1L << 0, handle_keypress, &data);
	mlx_loop_hook(data.mlx, render_hook, &data);
	mlx_loop(data.mlx);
	cleanup_game(&data, &grid, &walls);
	return (0);
}
=======
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
>>>>>>> ae1e321c442674b4e557df73ddd8c2b49159b347
