/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/29 09:45:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/11/30 16:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != 'D' && line[i] != '2')
			return (0);
		i++;
	}
	return (1);
}

static int	check_border(t_map *map, int x, int y)
{
	if (y == 0 || y == map->height - 1 || x == 0 || x == map->width - 1)
	{
		printf("Error\nMap not closed at borders\n");
		return (0);
	}
	if (map->grid[y - 1][x] == ' ' || map->grid[y + 1][x] == ' '
		|| map->grid[y][x - 1] == ' ' || map->grid[y][x + 1] == ' ')
	{
		printf("Error\nMap not properly enclosed\n");
		return (0);
	}
	return (1);
}

int	validate_map_closed(t_map *map)
{
	int	x;
	int	y;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0' || map->grid[y][x] == 'D'
				|| map->grid[y][x] == '2')
			{
				if (!check_border(map, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_textures(t_textures *textures)
{
	if (!textures->north || !textures->south
		|| !textures->west || !textures->east)
	{
		printf("Error\nMissing texture\n");
		return (0);
	}
	if (textures->floor[0] == -1 || textures->ceiling[0] == -1)
	{
		printf("Error\nMissing floor or ceiling color\n");
		return (0);
	}
	return (1);
}

int	parse_config_line(char *line, t_textures *textures)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "DO ", 3) == 0)
	{
		parse_textures(line, textures);
		return (1);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		parse_color(line, textures->floor);
		return (1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		parse_color(line, textures->ceiling);
		return (1);
	}
	return (0);
}