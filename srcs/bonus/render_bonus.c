/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	render_frame(t_data *data, t_walls *walls, t_grid *grid)
{
	t_cast	cast;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		prepare_ray(&cast, &data->cam, x);
		setup_step(&cast, &data->cam);
		algo_dda(&cast, grid);
		calculate_wall_distance(&cast, &data->cam);
		data->z_buffer[x] = cast.distance;
		draw_column(data, &cast, walls, x);
		x++;
	}
	render_sprites(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	render_hook(t_data *data)
{
	advance_animation(data);
	render_frame(data, data->walls, data->grid);
	return (0);
}
