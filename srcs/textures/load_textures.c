/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 08:17:42 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/21 11:28:09 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	load_single_texture(void *mlx, char *path, t_img *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		return (0);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	return (1);
}

int	init_wall_textures(t_data *data, t_walls *walls)
{
	if (!load_single_texture(data->mlx, walls->north, &data->tex_north))
		return (0);
	if (!load_single_texture(data->mlx, walls->south, &data->tex_south))
		return (0);
	if (!load_single_texture(data->mlx, walls->west, &data->tex_west))
		return (0);
	if (!load_single_texture(data->mlx, walls->east, &data->tex_east))
		return (0);
	return (1);
}
