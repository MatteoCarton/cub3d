/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 14:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/17 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Ferme la fenêtre proprement quand on appuie sur ESC ou clique sur la croix */
int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
}

/* Vérifie si une position est valide (pas un mur ou porte fermée) */
static int	is_valid_position(t_map *map, int x, int y)
{
	if (map->grid[y][x] == '1')
		return (0);
	if (map->grid[y][x] == 'D' && map->doors[y][x] == 0)
		return (0);
	return (1);
}

/* Déplace le joueur vers l'avant (W) ou l'arrière (S)
Multiplie la direction par MOVE_SPEED pour avancer doucement */
static void	move_forward_backward(t_player *player, t_map *map, int forward)
{
	double	new_x;
	double	new_y;

	if (forward)
	{
		new_x = player->pos_x + player->dir_x * MOVE_SPEED;
		new_y = player->pos_y + player->dir_y * MOVE_SPEED;
	}
	else
	{
		new_x = player->pos_x - player->dir_x * MOVE_SPEED;
		new_y = player->pos_y - player->dir_y * MOVE_SPEED;
	}
	if (is_valid_position(map, (int)new_x, (int)new_y))
	{
		player->pos_x = new_x;
		player->pos_y = new_y;
	}
}

/* Déplace le joueur vers la gauche (A) ou la droite (D)
Utilise le vecteur perpendiculaire à dir (= plane) */
static void	move_left_right(t_player *player, t_map *map, int right)
{
	double	new_x;
	double	new_y;

	if (right)
	{
		new_x = player->pos_x + player->plane_x * MOVE_SPEED;
		new_y = player->pos_y + player->plane_y * MOVE_SPEED;
	}
	else
	{
		new_x = player->pos_x - player->plane_x * MOVE_SPEED;
		new_y = player->pos_y - player->plane_y * MOVE_SPEED;
	}
	if (is_valid_position(map, (int)new_x, (int)new_y))
	{
		player->pos_x = new_x;
		player->pos_y = new_y;
	}
}

/* Toggle l'état d'une porte devant le joueur */
static void	toggle_door(t_game *game)
{
	int	door_x;
	int	door_y;

	door_x = (int)(game->player.pos_x + game->player.dir_x);
	door_y = (int)(game->player.pos_y + game->player.dir_y);
	if (door_x >= 0 && door_x < game->map->width
		&& door_y >= 0 && door_y < game->map->height)
	{
		if (game->map->grid[door_y][door_x] == 'D')
			game->map->doors[door_y][door_x]
				= !game->map->doors[door_y][door_x];
	}
}

/* Rotation de la caméra (flèches gauche/droite)
Utilise une matrice de rotation 2D :
old_dir_x = dir_x * cos(angle) - dir_y * sin(angle)
old_dir_y = dir_x * sin(angle) + dir_y * cos(angle) */
static void	rotate_camera(t_player *player, int right)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = ROT_SPEED;
	if (!right)
		rot_speed = -rot_speed;
	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * cos(rot_speed)
		- player->dir_y * sin(rot_speed);
	player->dir_y = old_dir_x * sin(rot_speed)
		+ player->dir_y * cos(rot_speed);
	old_plane_x = player->plane_x;
	player->plane_x = player->plane_x * cos(rot_speed)
		- player->plane_y * sin(rot_speed);
	player->plane_y = old_plane_x * sin(rot_speed)
		+ player->plane_y * cos(rot_speed);
}

/* Gère les touches pressées */
int	handle_keypress(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_window(game);
	else if (keycode == KEY_W)
		move_forward_backward(&game->player, game->map, 1);
	else if (keycode == KEY_S)
		move_forward_backward(&game->player, game->map, 0);
	else if (keycode == KEY_A)
		move_left_right(&game->player, game->map, 0);
	else if (keycode == KEY_D)
		move_left_right(&game->player, game->map, 1);
	else if (keycode == KEY_E)
		toggle_door(game);
	else if (keycode == KEY_LEFT)
		rotate_camera(&game->player, 0);
	else if (keycode == KEY_RIGHT)
		rotate_camera(&game->player, 1);
	return (0);
}
