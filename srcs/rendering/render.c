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
		draw_column(game, &ray, textures, x);
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}

/* Fonction appelée à chaque frame par mlx_loop_hook
Re-rend l'image à chaque fois (pour voir les mouvements) */
int	render_loop(t_game *game)
{
	render_frame(game, game->textures, game->map);
	return (0);
}
