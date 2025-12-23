/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/07 09:30:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/08 11:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

// Les formules viennet de l'algo DDA (utilsie dans Wolfenstein3d)
void	init_ray(t_ray *ray, t_player *player, int x) // pour x, calculer dans quelle direction part le rayon
{
	double	camera_x; // coefficient entre -1 et +1 qui dit "où on est sur l'écran" pour calculer la direction du rayon correspondant

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	ray->ray_dir_x = player->dir_x + player->plane_x * camera_x;
	ray->ray_dir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x); // fabs() = valeur absolue pour les nombres à virgule
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y); // le  1 / ray_dir c'est pour calculer combien de distance le rayon doit parcourir pour traverser une case complète. Plus la direction est grande, moins il faut de distance.
}

void	init_ray_step(t_ray *ray, t_player *player) // Calculer comment avancer et quelle est la première bordure
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_direction_x = -1; // va-t-on à gauche/droite ? haut/bas ?
		ray->dist_to_bord_x = (player->pos_x - ray->map_x) * ray->delta_dist_x; // distance jusqu'au premier bord
	}
	else
	{
		ray->step_direction_x = 1;
		ray->dist_to_bord_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_direction_y = -1;
		ray->dist_to_bord_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_direction_y = 1;
		ray->dist_to_bord_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
	}
}


/* Vérifie si on a touché un mur ou une porte fermée */
static int	is_wall_or_closed_door(t_map *map, int x, int y)
{
	if (map->grid[y][x] == '1')
		return (1);
	if (map->grid[y][x] == 'D' && map->doors[y][x] == 0)
		return (1);
	return (0);
}

/* RESUME DE L'ALGO =
1. Compare dist_to_bord_x et dist_to_bord_y
2. Prend le plus petit (= le bord le plus proche)
3. Avance jusqu'à ce bord
4. Vérifie si c'est un mur
5. Si oui → stop, sinon → retour à l'étape 1
*/
void	algo_dda(t_ray *ray, t_map *map)
{
	int	hit;

	hit = 0;
	ray->hit_door = 0;
	while (hit == 0)
	{
		if (ray->dist_to_bord_x < ray->dist_to_bord_y)
		{
			ray->dist_to_bord_x += ray->delta_dist_x;
			ray->map_x += ray->step_direction_x;
			ray->side = 0;
		}
		else
		{
			ray->dist_to_bord_y += ray->delta_dist_y;
			ray->map_y += ray->step_direction_y;
			ray->side = 1;
		}
		if (is_wall_or_closed_door(map, ray->map_x, ray->map_y))
		{
			if (map->grid[ray->map_y][ray->map_x] == 'D')
				ray->hit_door = 1;
			hit = 1;
		}
	}
}

void	calculate_wall_distance(t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - player->pos_x
				+ (1 - ray->step_direction_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - player->pos_y
				+ (1 - ray->step_direction_y) / 2) / ray->ray_dir_y;
	ray->line_height = (int)(WIN_HEIGHT / ray->perp_wall_dist);
	if (ray->side == 0)
		ray->wall_x = player->pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = player->pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
}
