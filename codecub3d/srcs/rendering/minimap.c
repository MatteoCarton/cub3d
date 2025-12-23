/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 00:20:19 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/22 00:20:20 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Dessine un carré plein (pour une case de la minimap) */
static void	draw_square(t_game *game, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_TILE_SIZE)
	{
		j = 0;
		while (j < MINIMAP_TILE_SIZE)
		{
			put_pixel(game, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

/* Dessine le fond de la minimap (rectangle semi-transparent) */
static void	draw_minimap_bg(t_game *game)
{
	int	x;
	int	y;

	y = MINIMAP_Y;
	while (y < MINIMAP_Y + MINIMAP_SIZE)
	{
		x = MINIMAP_X;
		while (x < MINIMAP_X + MINIMAP_SIZE)
		{
			put_pixel(game, x, y, 0x333333);
			x++;
		}
		y++;
	}
}

/* Choisit la couleur d'une case de la minimap */
static int	get_tile_color(t_game *game, int map_x, int map_y)
{
	if (game->map->grid[map_y][map_x] == '1')
		return (0xFFFFFF);
	else if (game->map->grid[map_y][map_x] == 'D')
	{
		if (game->map->doors[map_y][map_x] == 0)
			return (0x00FF00);
		else
			return (0x0000FF);
	}
	else
		return (0x111111);
}

/* Dessine les cases de la map autour du joueur */
static void	draw_minimap_tiles(t_game *game)
{
	int		tile_x;
	int		tile_y;
	int		map_x;
	int		map_y;
	double	offset_x;
	double	offset_y;

	offset_x = game->player.pos_x - (int)game->player.pos_x;
	offset_y = game->player.pos_y - (int)game->player.pos_y;
	tile_y = -10;
	while (tile_y < 10)
	{
		tile_x = -10;
		while (tile_x < 10)
		{
			map_x = (int)game->player.pos_x + tile_x;
			map_y = (int)game->player.pos_y + tile_y;
			if (map_x >= 0 && map_x < game->map->width
				&& map_y >= 0 && map_y < game->map->height)
				draw_square(game, MINIMAP_X + (tile_x + 10 - offset_x)
					* MINIMAP_TILE_SIZE, MINIMAP_Y + (tile_y + 10 - offset_y)
					* MINIMAP_TILE_SIZE, get_tile_color(game, map_x, map_y));
			tile_x++;
		}
		tile_y++;
	}
}

/* Dessine le joueur au centre de la minimap (petit carré rouge) */
static void	draw_player(t_game *game)
{
	int	center_x;
	int	center_y;
	int	i;
	int	j;

	center_x = MINIMAP_X + MINIMAP_SIZE / 2;
	center_y = MINIMAP_Y + MINIMAP_SIZE / 2;
	i = -3;
	while (i < 3)
	{
		j = -3;
		while (j < 3)
		{
			put_pixel(game, center_x + i, center_y + j, 0xFF0000);
			j++;
		}
		i++;
	}
}

/* Dessine la minimap centrée sur le joueur */
void	draw_minimap(t_game *game)
{
	draw_minimap_bg(game);
	draw_minimap_tiles(game);
	draw_player(game);
}
