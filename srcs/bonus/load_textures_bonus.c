/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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

/* Construit "<prefixe><nnn>.xpm" : SP ./textures/pack/coins/tile -> tile000 */
static char	*frame_path(char *prefix, int n)
{
	char	*joined;
	char	*path;
	char	num[4];

	num[0] = '0' + (n / 100) % 10;
	num[1] = '0' + (n / 10) % 10;
	num[2] = '0' + n % 10;
	num[3] = '\0';
	joined = ft_strjoin(prefix, num);
	if (!joined)
		return (NULL);
	path = ft_strjoin(joined, ".xpm");
	free(joined);
	return (path);
}

/* Charge la frame n, ou renvoie 0 si le fichier n'existe pas (fin de serie) */
static int	load_frame(t_data *data, char *prefix, int n)
{
	char	*path;
	int		fd;

	path = frame_path(prefix, n);
	if (!path)
		return (0);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (free(path), 0);
	close(fd);
	if (!load_single_texture(data->mlx, path, &data->frames[n]))
		return (free(path), 0);
	return (free(path), 1);
}

int	init_sprite_frames(t_data *data, t_walls *walls)
{
	char	*prefix;

	data->frame_count = 0;
	if (data->sprite_count == 0)
		return (1);
	prefix = walls->sprite;
	if (!prefix)
		prefix = SPRITE_PREFIX;
	while (data->frame_count < MAX_FRAMES
		&& load_frame(data, prefix, data->frame_count))
		data->frame_count++;
	if (data->sprite_count > 0 && data->frame_count == 0)
		return (printf("Error\nNo sprite frame for prefix %s\n", prefix), 0);
	return (1);
}
