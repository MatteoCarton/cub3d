#include "../../includes/cub3d.h"

/* Convertit RGB (tableau de 3 ints) en un seul int couleur
Format : 0x00RRGGBB (hexadécimal)
Exemple : R=220, G=100, B=111 → 0x00DC646F */
static int	rgb_to_int(int *rgb)
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT) // verifie que x, y est dans l'ecran
		return ;
	
	// "Où est le pixel (x, y) dans la mémoire ?"
	// dst = game->addr + (y * largeur_ligne + x * taille_pixel);
	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	// dst est un char * (pointeur sur 1 octet)
	// (unsigned int *) le transforme en pointeur sur 4 octets (32 bits)
	// 
	*(unsigned int *)dst = color; // *()deferencement pour ecrire la couleur a l'adresse pointee par dst

}

/* Dessine une ligne verticale de 'start_y' à 'end_y' pour la colonne 'x'
Utilisé pour dessiner un segment de mur à l'écran */
void	draw_vertical_line(t_game *game, int x, int start_y, int end_y, int color)
{
	int	y;

	y = start_y;
	while (y <= end_y)
	{
		put_pixel(game, x, y, color);
		y++;
	}
}

/* Calcule où commence et finit le mur sur l'écran
start = où commence le mur (haut de l'écran = 0)
end = où finit le mur (bas de l'écran = WIN_HEIGHT) */
static void	calculate_draw_limits(t_ray *ray, int *start, int *end)
{
	*start = -ray->line_height / 2 + WIN_HEIGHT / 2;
	if (*start < 0)
		*start = 0;
	*end = ray->line_height / 2 + WIN_HEIGHT / 2;
	if (*end >= WIN_HEIGHT)
		*end = WIN_HEIGHT - 1;
}

/* Dessine une colonne complète : plafond, mur, sol
Pour chaque colonne X de l'écran (0 à 799), on dessine du haut en bas */
static void	draw_column(t_game *game, t_ray *ray, t_textures *textures, int x)
{
	int	start;
	int	end;
	int	color;

	calculate_draw_limits(ray, &start, &end);
	draw_vertical_line(game, x, 0, start - 1, rgb_to_int(textures->ceiling));
	if (ray->side == 0)
		color = (ray->step_direction_x > 0) ? 0xFF0000 : 0x0000FF;
	else
		color = (ray->step_direction_y > 0) ? 0x00FF00 : 0xFFFF00;
	draw_vertical_line(game, x, start, end, color);
	draw_vertical_line(game, x, end + 1, WIN_HEIGHT - 1, rgb_to_int(textures->floor));
}

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
