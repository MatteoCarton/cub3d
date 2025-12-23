/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/22 00:20:42 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/22 00:20:43 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Charge une texture et récupère toutes ses infos (img, addr, width, height)
Pour pouvoir ensuite lire les pixels de la texture */
static void	load_single_texture(void *mlx, char *path, t_texture_img *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		exit(EXIT_FAILURE);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

static void	load_sprite_textures(t_game *game)
{
	char	path[50];
	int		i;

	i = 0;
	while (i < 4)
	{
		ft_memset(path, 0, 50);
		ft_strlcpy(path, "./textures/bear_trap00", 50);
		path[22] = '0' + i;
		ft_strlcat(path, ".xpm", 50);
		load_single_texture(game->mlx, path, &game->bear_trap_frames[i]);
		i++;
	}
}

void	load_all_textures(t_game *game, t_textures *textures)
{
	load_single_texture(game->mlx, textures->north, &game->tex_north);
	load_single_texture(game->mlx, textures->south, &game->tex_south);
	load_single_texture(game->mlx, textures->west, &game->tex_west);
	load_single_texture(game->mlx, textures->east, &game->tex_east);
	if (textures->door)
		load_single_texture(game->mlx, textures->door, &game->tex_door);
	load_sprite_textures(game);
}
