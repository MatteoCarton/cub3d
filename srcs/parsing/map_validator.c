/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/11/29 14:52:33 by mcastrat          #+#    #+#             */
/*   Updated: 2026/01/02 17:37:11 by mcastrat         ###   ########.fr       */
=======
/*   Created: 2025/11/29 09:45:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/11/30 16:00:00 by mcastrat         ###   ########.fr       */
>>>>>>> ae1e321c442674b4e557df73ddd8c2b49159b347
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
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

static int	check_border(t_grid *grid, int x, int y)
{
	if (y == 0 || y == grid->height - 1 || x == 0 || x == grid->width - 1)
		return (printf("Error\nMap not closed at borders\n"), 0);
	if (grid->grid[y - 1][x] == ' ' || grid->grid[y + 1][x] == ' '
		|| grid->grid[y][x - 1] == ' ' || grid->grid[y][x + 1] == ' ')
		return (printf("Error\nMap not properly enclosed\n"), 0);
	return (1);
}

int	validate_map_closed(t_grid *grid)
{
	int	x;
	int	y;

	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			if (grid->grid[y][x] == '0')
			{
				if (!check_border(grid, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	validate_textures(t_walls *walls)
{
	if (!walls->north || !walls->south
		|| !walls->west || !walls->east)
		return (printf("Error\nMissing texture\n"), 0);
	if (walls->floor[0] == -1 || walls->ceiling[0] == -1)
		return (printf("Error\nMissing floor or ceiling color\n"), 0);
	return (1);
}
