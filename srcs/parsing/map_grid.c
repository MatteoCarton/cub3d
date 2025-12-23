/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 10:30:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/01 13:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_map_dimensions(char **lines, int start, t_map *map)
{
	int	i;
	int	j;
	int	width;
	int	height;

	i = start;
	width = 0;
	height = 0;
	while (lines[i] && is_map_line(lines[i]))
	{
		j = ft_strlen(lines[i]);
		if (lines[i][j - 1] == '\n')
			j--;
		if (j > width)
			width = j;
		height++;
		i++;
	}
	if (height == 0)
	{
		printf("Error\nNo map found\n");
		return (0);
	}
	map->width = width;
	map->height = height;
	return (1);
}

static int	allocate_doors(t_map *map)
{
	int	i;
	int	j;

	map->doors = malloc(sizeof(int *) * map->height);
	if (!map->doors)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->doors[i] = malloc(sizeof(int) * map->width);
		if (!map->doors[i])
			return (0);
		j = 0;
		while (j < map->width)
		{
			map->doors[i][j] = 0;
			j++;
		}
		i++;
	}
	return (1);
}

static int	allocate_map_grid(t_map *map)
{
	int	i;

	map->grid = malloc(sizeof(char *) * (map->height + 1));
	if (!map->grid)
		return (0);
	i = 0;
	while (i < map->height)
	{
		map->grid[i] = malloc(sizeof(char) * (map->width + 1));
		if (!map->grid[i])
			return (0);
		i++;
	}
	map->grid[i] = NULL;
	if (!allocate_doors(map))
		return (0);
	return (1);
}

static void	handle_player_position(t_map *map, char c, int x, int y)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (map->player_x != -1)
		{
			printf("Error\nMultiple player positions\n");
			exit(EXIT_FAILURE);
		}
		map->player_x = x;
		map->player_y = y;
		map->player_dir = c;
		map->grid[y][x] = '0';
	}
	else
		map->grid[y][x] = c;
}

static void	fill_map_row(t_map *map, char *line, int y)
{
	int	x;

	x = 0;
	while (line[x] && line[x] != '\n')
	{
		handle_player_position(map, line[x], x, y);
		x++;
	}
	while (x < map->width)
	{
		map->grid[y][x] = ' ';
		x++;
	}
	map->grid[y][x] = '\0';
}

int	parse_map_grid(char **lines, int start, t_map *map)
{
	int	i;

	map->player_x = -1;
	map->player_y = -1;
	if (!get_map_dimensions(lines, start, map))
		return (0);
	if (!allocate_map_grid(map))
		return (0);
	i = 0;
	while (i < map->height)
	{
		fill_map_row(map, lines[start + i], i);
		i++;
	}
	if (map->player_x == -1)
	{
		printf("Error\nNo player position found\n");
		return (0);
	}
	return (1);
}