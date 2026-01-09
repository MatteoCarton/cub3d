/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/12/04 09:47:13 by mcastrat          #+#    #+#             */
/*   Updated: 2026/01/02 17:46:26 by mcastrat         ###   ########.fr       */
=======
/*   Created: 2025/12/04 11:30:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/05 14:00:00 by mcastrat         ###   ########.fr       */
>>>>>>> ae1e321c442674b4e557df73ddd8c2b49159b347
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static t_img	*select_texture(t_data *data, t_cast *cast)
{
	if (cast->side == 0)
	{
		if (cast->step_x > 0)
			return (&data->tex_east);
		else
			return (&data->tex_west);
	}
	else
	{
		if (cast->step_y > 0)
			return (&data->tex_south);
		else
			return (&data->tex_north);
	}
}

static void	init_tex_params(t_cast *cast, t_img *tex, int *tx, double *st)
{
	*tx = (int)(cast->wall_x * (double)tex->width);
	if ((cast->side == 0 && cast->step_x < 0)
		|| (cast->side == 1 && cast->step_y > 0))
		*tx = tex->width - *tx - 1;
	*st = 1.0 * tex->height / cast->wall_h;
}

static void	draw_tex_pixels(t_data *data, t_img *tex, int coords[3], int end)
{
	int		tex_y;
	double	tex_pos;
	double	step;

	step = 1.0 * tex->height / coords[2];
	tex_pos = (end - WIN_HEIGHT / 2 + coords[2] / 2) * step;
	while (end <= coords[1])
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		set_pixel(data, coords[0], end, get_tex_color(tex, coords[3], tex_y));
		end++;
	}
}

void	draw_wall_tex(t_data *data, t_cast *cast, int x, int st_end[2])
{
	t_img	*tex;
	int		coords[4];
	double	step;

	tex = select_texture(data, cast);
	init_tex_params(cast, tex, &coords[3], &step);
	coords[0] = x;
	coords[1] = st_end[1];
	coords[2] = cast->wall_h;
	draw_tex_pixels(data, tex, coords, st_end[0]);
}
