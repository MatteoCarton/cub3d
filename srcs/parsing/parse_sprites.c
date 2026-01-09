/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sprites.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/02 14:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/03 11:30:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Compte le nombre de sprites dans la map */
static int	count_sprites(t_map *map)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '2')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

/* Extrait les sprites de la map et les stocke dans game->sprites */
int	parse_sprites(t_game *game)
{
	int	i;
	int	x;
	int	y;

	game->sprite_count = count_sprites(game->map);
	if (game->sprite_count == 0)
		return (1);
	game->sprites = malloc(sizeof(t_sprite) * game->sprite_count);
	if (!game->sprites)
		return (0);
	i = 0;
	y = -1;
	while (++y < game->map->height)
	{
		x = -1;
		while (++x < game->map->width)
		{
			if (game->map->grid[y][x] == '2')
			{
				game->sprites[i].x = x + 0.5;
				game->sprites[i].y = y + 0.5;
				game->sprites[i].type = 0;
				game->sprites[i].current_frame = 0;
				i++;
			}
		}
	}
	return (1);
}
