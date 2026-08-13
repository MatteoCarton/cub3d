/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	count_sprites(t_grid *grid)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			if (grid->grid[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/* Chaque case '2' devient un sprite pose au centre de la case */
int	parse_sprites(t_data *data, t_grid *grid)
{
	int	i;
	int	x;
	int	y;

	data->sprite_count = count_sprites(grid);
	if (data->sprite_count == 0)
		return (1);
	data->sprites = malloc(sizeof(t_sprite) * data->sprite_count);
	if (!data->sprites)
		return (printf("Error\nSprite allocation failed\n"), 0);
	i = 0;
	y = -1;
	while (++y < grid->height)
	{
		x = -1;
		while (++x < grid->width)
		{
			if (grid->grid[y][x] == '2')
			{
				data->sprites[i].x = x + 0.5;
				data->sprites[i++].y = y + 0.5;
			}
		}
	}
	return (1);
}
