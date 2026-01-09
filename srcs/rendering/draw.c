/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:28:51 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/24 15:39:22 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	rgb_to_color(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

int	get_tex_color(t_img *tex, int tex_x, int tex_y)
{
	char	*pixel;

	pixel = tex->addr + (tex_y * tex->line_length + tex_x
			* (tex->bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	set_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel
				/ 8));
	*(unsigned int *)dst = color;
}

void	draw_vline(t_data *data, int x, int y_range[2], int color)
{
	int	y;

	y = y_range[0];
	while (y <= y_range[1])
	{
		set_pixel(data, x, y, color);
		y++;
	}
}

void	draw_column(t_data *data, t_cast *cast, t_walls *walls, int x)
{
	int	lim[2];
	int	rng[2];

	lim[0] = -cast->wall_h / 2 + WIN_HEIGHT / 2;
	if (lim[0] < 0)
		lim[0] = 0;
	lim[1] = cast->wall_h / 2 + WIN_HEIGHT / 2;
	if (lim[1] >= WIN_HEIGHT)
		lim[1] = WIN_HEIGHT - 1;
	rng[0] = 0;
	rng[1] = lim[0] - 1;
	draw_vline(data, x, rng, rgb_to_color(walls->ceiling));
	draw_wall_tex(data, cast, x, lim);
	rng[0] = lim[1] + 1;
	rng[1] = WIN_HEIGHT - 1;
	draw_vline(data, x, rng, rgb_to_color(walls->floor));
}
