#include "../../includes/cub3d.h"

/* Codes des touches sur macOS (minilibx) */
#define KEY_ESC     53
#define KEY_W       13
#define KEY_A       0
#define KEY_S       1
#define KEY_D       2
#define KEY_LEFT    123
#define KEY_RIGHT   124

#define MOVE_SPEED  0.1    // Vitesse de déplacement
#define ROT_SPEED   0.05   // Vitesse de rotation (en radians)

/* Ferme la fenêtre proprement quand on appuie sur ESC ou clique sur la croix */
int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
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
	if (map->grid[(int)new_y][(int)new_x] != '1')
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
	if (map->grid[(int)new_y][(int)new_x] != '1')
	{
		player->pos_x = new_x;
		player->pos_y = new_y;
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
	else if (keycode == KEY_LEFT)
		rotate_camera(&game->player, 0);
	else if (keycode == KEY_RIGHT)
		rotate_camera(&game->player, 1);
	return (0);
}
