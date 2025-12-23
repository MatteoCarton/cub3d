/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/04 11:30:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/12/05 14:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

/* Sélectionne quelle texture utiliser selon l'orientation du mur */
static t_texture_img	*select_texture(t_game *game, t_ray *ray)
{
	if (ray->hit_door)
		return (&game->tex_door);
	if (ray->side == 0)
	{
		if (ray->step_direction_x > 0)
			return (&game->tex_east);
		else
			return (&game->tex_west);
	}
	else
	{
		if (ray->step_direction_y > 0)
			return (&game->tex_south);
		else
			return (&game->tex_north);
	}
}

/* Dessine un mur texturé pixel par pixel
Pour chaque pixel Y du mur :
1. Calcule quelle ligne de la texture (tex_y) correspond
2. Récupère la couleur du pixel (tex_x, tex_y) de la texture
3. Affiche ce pixel à l'écran */
void	draw_textured_wall(t_game *game, t_ray *ray, int x, int start, int end)
{
	t_texture_img	*tex;
	int				tex_x;
	int				tex_y;
	int				y;
	double			step;
	double			tex_pos;

	tex = select_texture(game, ray);
	tex_x = (int)(ray->wall_x * (double)tex->width);
	if ((ray->side == 0 && ray->step_direction_x < 0)
		|| (ray->side == 1 && ray->step_direction_y > 0))
		tex_x = tex->width - tex_x - 1;
	step = 1.0 * tex->height / ray->line_height;
	tex_pos = (start - WIN_HEIGHT / 2 + ray->line_height / 2) * step;
	y = start;
	while (y <= end)
	{
		tex_y = (int)tex_pos & (tex->height - 1);
		tex_pos += step;
		put_pixel(game, x, y, get_texture_color(tex, tex_x, tex_y));
		y++;
	}
}
