/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	rotate_camera(t_cam *cam, int right)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	if (!right)
		rot_speed = -rot_speed;
	old_dir_x = cam->dir_x;
	cam->dir_x = cam->dir_x * cos(rot_speed)
		- cam->dir_y * sin(rot_speed);
	cam->dir_y = old_dir_x * sin(rot_speed)
		+ cam->dir_y * cos(rot_speed);
	old_plane_x = cam->plane_x;
	cam->plane_x = cam->plane_x * cos(rot_speed)
		- cam->plane_y * sin(rot_speed);
	cam->plane_y = old_plane_x * sin(rot_speed)
		+ cam->plane_y * cos(rot_speed);
}

int	handle_keypress(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		close_window(data);
	else if (keycode == KEY_LEFT)
		rotate_camera(&data->cam, 0);
	else if (keycode == KEY_RIGHT)
		rotate_camera(&data->cam, 1);
	else
		move_player(&data->cam, data->grid, keycode);
	return (0);
}
