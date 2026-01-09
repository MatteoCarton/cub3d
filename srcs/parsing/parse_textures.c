/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/12/01 10:41:29 by mcastrat          #+#    #+#             */
/*   Updated: 2026/01/02 17:40:43 by mcastrat         ###   ########.fr       */
=======
/*   Created: 2025/11/27 15:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/11/28 10:15:00 by mcastrat         ###   ########.fr       */
>>>>>>> ae1e321c442674b4e557df73ddd8c2b49159b347
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*extract_texture_path(char *line)
{
	char	*path_texture;

	path_texture = ft_strtrim(line + 3, " \t\n\r\v\f");
	if (!path_texture || !*path_texture)
	{
		printf("Error\nEmpty texture path\n");
		if (path_texture)
			free(path_texture);
		return (NULL);
	}
	return (path_texture);
}

static int	validate_texture_file(char *path_texture)
{
	int	fd;

	fd = open(path_texture, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nTexture %s not found\n", path_texture);
		free(path_texture);
		return (0);
	}
	close(fd);
	return (1);
}

static int	store_texture(char *line, char *path_texture, t_walls *walls)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (walls->north)
			return (printf("Error\nDuplicate NO\n"), free(path_texture), 0);
		return (walls->north = path_texture, 1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (walls->south)
			return (printf("Error\nDuplicate SO\n"), free(path_texture), 0);
		return (walls->south = path_texture, 1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (walls->west)
			return (printf("Error\nDuplicate WE\n"), free(path_texture), 0);
		return (walls->west = path_texture, 1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (walls->east)
			return (printf("Error\nDuplicate EA\n"), free(path_texture), 0);
		return (walls->east = path_texture, 1);
	}
	return (printf("Error\nInvalid texture ID\n"), free(path_texture), 0);
}

int	parse_textures(char *line, t_walls *walls)
{
	char	*path_texture;

	path_texture = extract_texture_path(line);
	if (!path_texture)
		return (0);
	if (!validate_texture_file(path_texture))
		return (0);
	if (!store_texture(line, path_texture, walls))
		return (0);
	return (1);
}
