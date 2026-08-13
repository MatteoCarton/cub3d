/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* Fenetre de MINIMAP_VIEW cases autour du joueur, centree sur lui */
static void	draw_tiles(t_data *data)
{
	int	map[2];
	int	pos[2];
	int	tile[2];

	tile[1] = -MINIMAP_VIEW;
	while (tile[1] < MINIMAP_VIEW)
	{
		tile[0] = -MINIMAP_VIEW;
		while (tile[0] < MINIMAP_VIEW)
		{
			map[0] = (int)data->cam.pos_x + tile[0];
			map[1] = (int)data->cam.pos_y + tile[1];
			pos[0] = MINIMAP_X + (tile[0] + MINIMAP_VIEW) * MINIMAP_TILE;
			pos[1] = MINIMAP_Y + (tile[1] + MINIMAP_VIEW) * MINIMAP_TILE;
			draw_tile(data, pos, minimap_tile_color(data->grid, map[0],
					map[1]));
			tile[0]++;
		}
		tile[1]++;
	}
}

static void	draw_player(t_data *data)
{
	int	center[2];
	int	i;
	int	j;

	center[0] = MINIMAP_X + MINIMAP_SIZE / 2;
	center[1] = MINIMAP_Y + MINIMAP_SIZE / 2;
	i = -2;
	while (i <= 2)
	{
		j = -2;
		while (j <= 2)
		{
			if (in_minimap(center[0] + i, center[1] + j))
				set_pixel(data, center[0] + i, center[1] + j, MINIMAP_PLAYER);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	draw_minimap_bg(data);
	draw_tiles(data);
	draw_player(data);
}
