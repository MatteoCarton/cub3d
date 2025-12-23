/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 10:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/18 11:30:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	apply_rotation(t_player *player, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot) - player->dir_y * sin(rot);
	player->dir_y = old_dir_x * sin(rot) + player->dir_y * cos(rot);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot) - player->plane_y * sin(rot);
	player->plane_y = old_plane_x * sin(rot) + player->plane_y * cos(rot);
}

int	mouse_move(int x, int y, t_game *game)
{
	static int	last_x = -1;
	int			delta_x;
	double		rot;

	(void)y;
	if (last_x == -1)
		last_x = WIN_WIDTH / 2;
	delta_x = x - last_x;
	if (x < 100 || x > WIN_WIDTH - 100)
	{
		mlx_mouse_move(game->mlx, game->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		last_x = WIN_WIDTH / 2;
		return (0);
	}
	last_x = x;
	rot = delta_x * MOUSE_SENSITIVITY;
	apply_rotation(&game->player, rot);
	return (0);
}
