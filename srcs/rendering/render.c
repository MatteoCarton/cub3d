/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 14:22:53 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/24 10:17:44 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		draw_column(data, &cast, walls, x);
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int	render_hook(t_data *data)
{
	render_frame(data, data->walls, data->grid);
	return (0);
}
