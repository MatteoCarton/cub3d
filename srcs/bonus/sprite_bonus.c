/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	compute_distances(t_data *data)
{
	double	dx;
	double	dy;
	int		i;

	i = 0;
	while (i < data->sprite_count)
	{
		dx = data->cam.pos_x - data->sprites[i].x;
		dy = data->cam.pos_y - data->sprites[i].y;
		data->sprites[i].distance = dx * dx + dy * dy;
		i++;
	}
}

/* Les plus eloignes d'abord : ils sont dessines en premier */
static void	sort_sprites(t_data *data)
{
	t_sprite	tmp;
	int			i;
	int			j;

	compute_distances(data);
	i = 0;
	while (i < data->sprite_count - 1)
	{
		j = 0;
		while (j < data->sprite_count - i - 1)
		{
			if (data->sprites[j].distance < data->sprites[j + 1].distance)
			{
				tmp = data->sprites[j];
				data->sprites[j] = data->sprites[j + 1];
				data->sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/* out[0] : decalage lateral camera, out[1] : profondeur perpendiculaire */
static void	transform_sprite(t_data *data, t_sprite *sprite, double *out)
{
	double	rel_x;
	double	rel_y;
	double	inv_det;

	rel_x = sprite->x - data->cam.pos_x;
	rel_y = sprite->y - data->cam.pos_y;
	inv_det = 1.0 / (data->cam.plane_x * data->cam.dir_y
			- data->cam.dir_x * data->cam.plane_y);
	out[0] = inv_det * (data->cam.dir_y * rel_x - data->cam.dir_x * rel_y);
	out[1] = inv_det * (data->cam.plane_x * rel_y
			- data->cam.plane_y * rel_x);
}

/* Sprite d'une demi-case de haut, pose au sol : son sommet tombe a l'horizon */
static void	project_sprite(t_data *data, double *tr)
{
	t_spr	spr;
	int		full;
	int		x;

	full = (int)(WIN_HEIGHT / tr[1]);
	spr.depth = tr[1];
	spr.size = full / 2;
	spr.top = WIN_HEIGHT / 2 + full / 2 - spr.size;
	spr.center = (int)((WIN_WIDTH / 2) * (1.0 + tr[0] / tr[1]));
	if (spr.size <= 0)
		return ;
	x = spr.center - spr.size / 2;
	if (x < 0)
		x = 0;
	while (x < spr.center + spr.size / 2 && x < WIN_WIDTH)
	{
		draw_sprite_column(data, &spr, x);
		x++;
	}
}

void	render_sprites(t_data *data)
{
	double	tr[2];
	int		i;

	if (data->sprite_count <= 0 || data->frame_count <= 0)
		return ;
	sort_sprites(data);
	i = 0;
	while (i < data->sprite_count)
	{
		transform_sprite(data, &data->sprites[i], tr);
		if (tr[1] > 0.05)
			project_sprite(data, tr);
		i++;
	}
}
