/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_draw_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

/* Le noir pur (#000000) sert de couleur de transparence dans les frames */
void	draw_sprite_column(t_data *data, t_spr *spr, int x)
{
	t_img	*tex;
	int		tex_x;
	int		y;
	int		color;

	if (spr->depth >= data->z_buffer[x])
		return ;
	tex = &data->frames[data->frame];
	tex_x = (x - (spr->center - spr->size / 2)) * tex->width / spr->size;
	if (tex_x < 0 || tex_x >= tex->width)
		return ;
	y = spr->top;
	if (y < 0)
		y = 0;
	while (y < spr->top + spr->size && y < WIN_HEIGHT)
	{
		color = get_tex_color(tex, tex_x,
				(y - spr->top) * tex->height / spr->size);
		if ((color & 0x00FFFFFF) != 0)
			set_pixel(data, x, y, color);
		y++;
	}
}

void	advance_animation(t_data *data)
{
	if (data->frame_count <= 0)
		return ;
	data->tick++;
	if (data->tick < ANIM_DELAY)
		return ;
	data->tick = 0;
	data->frame++;
	if (data->frame >= data->frame_count)
		data->frame = 0;
}
