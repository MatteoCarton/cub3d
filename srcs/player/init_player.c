#include "../../includes/cub3d.h"

static void	set_direction_north(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = -1;
	player->plane_x = FOV;
	player->plane_y = 0;
}

static void	set_direction_south(t_player *player)
{
	player->dir_x = 0;
	player->dir_y = 1;
	player->plane_x = -FOV;
	player->plane_y = 0;
}

static void	set_direction_east(t_player *player)
{
	player->dir_x = 1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = FOV;
}

static void	set_direction_west(t_player *player)
{
	player->dir_x = -1;
	player->dir_y = 0;
	player->plane_x = 0;
	player->plane_y = -FOV;
}

void	init_player(t_player *player, t_map *map)
{
	player->pos_x = (double)map->player_x + 0.5; // Le +0.5 centre le joueur au milieu de la case au lieu du coin
	player->pos_y = (double)map->player_y + 0.5;
	if (map->player_dir == 'N')
		set_direction_north(player);
	else if (map->player_dir == 'S')
		set_direction_south(player);
	else if (map->player_dir == 'E')
		set_direction_east(player);
	else if (map->player_dir == 'W')
		set_direction_west(player);
}
