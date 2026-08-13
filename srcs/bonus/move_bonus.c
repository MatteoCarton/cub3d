/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	is_free(t_grid *grid, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= grid->width || map_y < 0
		|| map_y >= grid->height)
		return (0);
	return (grid->grid[map_y][map_x] != '1' && grid->grid[map_y][map_x] != ' ');
}

/* Bonus : le joueur a un rayon, il ne peut plus coller ni traverser un mur */
static int	can_move(t_grid *grid, double x, double y)
{
	if (!is_free(grid, x + WALL_PAD, y) || !is_free(grid, x - WALL_PAD, y))
		return (0);
	if (!is_free(grid, x, y + WALL_PAD) || !is_free(grid, x, y - WALL_PAD))
		return (0);
	return (1);
}

/* Chaque axe est teste separement : on glisse le long des murs */
static void	try_move(t_cam *cam, t_grid *grid, double dx, double dy)
{
	if (can_move(grid, cam->pos_x + dx, cam->pos_y))
		cam->pos_x += dx;
	if (can_move(grid, cam->pos_x, cam->pos_y + dy))
		cam->pos_y += dy;
}

void	move_player(t_cam *cam, t_grid *grid, int keycode)
{
	if (keycode == KEY_W)
		try_move(cam, grid, cam->dir_x * MOVE_SPEED, cam->dir_y * MOVE_SPEED);
	else if (keycode == KEY_S)
		try_move(cam, grid, -cam->dir_x * MOVE_SPEED,
			-cam->dir_y * MOVE_SPEED);
	else if (keycode == KEY_A)
		try_move(cam, grid, -cam->plane_x * MOVE_SPEED,
			-cam->plane_y * MOVE_SPEED);
	else if (keycode == KEY_D)
		try_move(cam, grid, cam->plane_x * MOVE_SPEED,
			cam->plane_y * MOVE_SPEED);
}
