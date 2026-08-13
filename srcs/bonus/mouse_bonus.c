/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	apply_rotation(t_cam *cam, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cam->dir_x;
	cam->dir_x = cam->dir_x * cos(rot) - cam->dir_y * sin(rot);
	cam->dir_y = old_dir_x * sin(rot) + cam->dir_y * cos(rot);
	old_plane_x = cam->plane_x;
	cam->plane_x = cam->plane_x * cos(rot) - cam->plane_y * sin(rot);
	cam->plane_y = old_plane_x * sin(rot) + cam->plane_y * cos(rot);
}

/* Rotation a la souris ; le curseur est recentre avant d'atteindre le bord */
int	mouse_move(int x, int y, t_data *data)
{
	static int	last_x = -1;
	int			delta;

	(void)y;
	if (last_x == -1)
		last_x = x;
	delta = x - last_x;
	last_x = x;
	if (x < 100 || x > WIN_WIDTH - 100)
	{
		mlx_mouse_move(data->mlx, data->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		last_x = WIN_WIDTH / 2;
		return (0);
	}
	if (delta != 0)
		apply_rotation(&data->cam, delta * MOUSE_SENS);
	return (0);
}
