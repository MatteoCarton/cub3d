#include "../../includes/cub3d.h"

/* Fonction principale de rendu - Lance le raycasting et dessine l'image
Boucle sur chaque colonne de l'écran (x = 0 à WIN_WIDTH-1) :
1. Lance un rayon pour la colonne x
2. Calcule la distance au mur et la hauteur du mur
3. Dessine plafond + mur + sol pour cette colonne */
void	render_frame(t_game *game, t_textures *textures, t_map *map)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		init_ray(&ray, &game->player, x);
		init_ray_step(&ray, &game->player);
		algo_dda(&ray, map);
		calculate_wall_distance(&ray, &game->player);
		game->z_buffer[x] = ray.perp_wall_dist;
		draw_column(game, &ray, textures, x);
		x++;
	}
	render_sprites(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/* Met à jour l'animation des sprites */
static void	update_sprite_animation(t_game *game)
{
	int	i;

	game->frame_count++;
	if (game->frame_count % 10 == 0)
	{
		i = 0;
		while (i < game->sprite_count)
		{
			game->sprites[i].current_frame++;
			if (game->sprites[i].current_frame >= 4)
				game->sprites[i].current_frame = 0;
			i++;
		}
	}
}

/* Fonction appelée à chaque frame par mlx_loop_hook
Re-rend l'image à chaque fois (pour voir les mouvements) */
int	render_loop(t_game *game)
{
	update_sprite_animation(game);
	render_frame(game, game->textures, game->map);
	return (0);
}
