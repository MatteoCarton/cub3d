/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_draw_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	in_minimap(int x, int y)
{
	return (x >= MINIMAP_X && x < MINIMAP_X + MINIMAP_SIZE
		&& y >= MINIMAP_Y && y < MINIMAP_Y + MINIMAP_SIZE);
}

void	draw_tile(t_data *data, int pos[2], int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_TILE)
	{
		j = 0;
		while (j < MINIMAP_TILE)
		{
			if (in_minimap(pos[0] + i, pos[1] + j))
				set_pixel(data, pos[0] + i, pos[1] + j, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_bg(t_data *data)
{
	int	x;
	int	y;

	y = MINIMAP_Y;
	while (y < MINIMAP_Y + MINIMAP_SIZE)
	{
		x = MINIMAP_X;
		while (x < MINIMAP_X + MINIMAP_SIZE)
		{
			set_pixel(data, x, y, MINIMAP_BG);
			x++;
		}
		y++;
	}
}

int	minimap_tile_color(t_grid *grid, int x, int y)
{
	if (x < 0 || x >= grid->width || y < 0 || y >= grid->height)
		return (MINIMAP_BG);
	if (grid->grid[y][x] == '1')
		return (MINIMAP_WALL);
	if (grid->grid[y][x] == '2')
		return (MINIMAP_SPRITE);
	if (grid->grid[y][x] == ' ')
		return (MINIMAP_BG);
	return (MINIMAP_FLOOR);
}
