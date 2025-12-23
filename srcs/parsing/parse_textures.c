/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 15:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/11/28 10:15:00 by mcastrat         ###   ########.fr       */
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
		exit(EXIT_FAILURE);
	}
	return (path_texture);
}

static void	validate_texture_file(char *path_texture)
{
	int	fd;

	fd = open(path_texture, O_RDONLY);
	if (fd == -1)
	{
		printf("Error\nTexture %s not found\n", path_texture);
		free(path_texture);
		exit(EXIT_FAILURE);
	}
	close(fd);
}

static void	store_texture(char *line, char *path_texture, t_textures *textures)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		textures->north = path_texture;
	else if (ft_strncmp(line, "SO ", 3) == 0)
		textures->south = path_texture;
	else if (ft_strncmp(line, "WE ", 3) == 0)
		textures->west = path_texture;
	else if (ft_strncmp(line, "EA ", 3) == 0)
		textures->east = path_texture;
	else if (ft_strncmp(line, "DO ", 3) == 0)
		textures->door = path_texture;
}

void	parse_textures(char *line, t_textures *textures)
{
	char	*path_texture;

	path_texture = extract_texture_path(line);
	validate_texture_file(path_texture);
	store_texture(line, path_texture, textures);
}

void	init_textures(t_textures *textures)
{
	int	i;

	textures->north = NULL;
	textures->south = NULL;
	textures->west = NULL;
	textures->east = NULL;
	textures->door = NULL;
	i = 0;
	while (i < 3)
	{
		textures->floor[i] = -1;
		textures->ceiling[i] = -1;
		i++;
	}
}