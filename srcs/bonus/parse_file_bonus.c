/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	init_textures(t_walls *walls)
{
	int	i;

	walls->north = NULL;
	walls->south = NULL;
	walls->west = NULL;
	walls->east = NULL;
	walls->sprite = NULL;
	i = 0;
	while (i < 3)
	{
		walls->floor[i] = -1;
		walls->ceiling[i] = -1;
		i++;
	}
}

static int	parse_color_line(char *line, t_walls *walls)
{
	static int	check1 = 0;
	static int	check2 = 0;

	if (ft_strncmp(line, "F ", 2) == 0 && check1 == 0)
	{
		if (!parse_color(line, walls->floor))
			return (-1);
		check1 = 1;
		return (1);
	}
	if (ft_strncmp(line, "C ", 2) == 0 && check2 == 0)
	{
		if (!parse_color(line, walls->ceiling))
			return (-1);
		check2 = 1;
		return (1);
	}
	return (0);
}

int	parse_config_line(char *line, t_walls *walls)
{
	if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
	{
		if (!parse_textures(line, walls))
			return (-1);
		return (1);
	}
	if (ft_strncmp(line, "SP ", 3) == 0)
	{
		if (!parse_sprite_path(line, walls))
			return (-1);
		return (1);
	}
	return (parse_color_line(line, walls));
}

static int	find_map_start(char **lines, int line_count, t_walls *walls)
{
	int	i;
	int	result;

	i = 0;
	while (i < line_count)
	{
		result = parse_config_line(lines[i], walls);
		if (lines[i][0] != '\n' && result == 0)
		{
			if (is_map_line(lines[i]))
				return (i);
			else if (lines[i][0] != '\n')
				return (printf("Error\nInvalid line: %s", lines[i]), -1);
		}
		else if (result == -1)
			return (-1);
		i++;
	}
	return (-1);
}

int	check_map(int argc, char **argv, t_walls *walls, t_grid *grid)
{
	char	**lines;
	int		line_count;
	int		map_start;

	(void)argc;
	init_textures(walls);
	lines = store_map_lines(argv[1], &line_count);
	if (!lines)
		return (0);
	map_start = find_map_start(lines, line_count, walls);
	if (!validate_textures(walls) || map_start == -1
		|| !parse_map_grid(lines, map_start, grid)
		|| !validate_map_closed(grid))
	{
		free_map_lines(lines, line_count);
		return (0);
	}
	return (free_map_lines(lines, line_count), 1);
}
