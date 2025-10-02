#include "../../includes/cub3d.h"

/* Calcule la distance entre le joueur et chaque sprite */
static void	calculate_sprite_distance(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		game->sprites[i].distance = ((game->player.pos_x - game->sprites[i].x)
				* (game->player.pos_x - game->sprites[i].x)
				+ (game->player.pos_y - game->sprites[i].y)
				* (game->player.pos_y - game->sprites[i].y));
		i++;
	}
}

/* Trie les sprites par distance (bubble sort) */
static void	sort_sprites(t_game *game)
{
	int			i;
	int			j;
	t_sprite	tmp;

	calculate_sprite_distance(game);
	i = 0;
	while (i < game->sprite_count - 1)
	{
		j = 0;
		while (j < game->sprite_count - i - 1)
		{
			if (game->sprites[j].distance < game->sprites[j + 1].distance)
			{
				tmp = game->sprites[j];
				game->sprites[j] = game->sprites[j + 1];
				game->sprites[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

/* Dessine une colonne du sprite */
static void	draw_sprite_stripe(t_game *game, t_texture_img *tex,
	int stripe_x, int sprite_screen_x, int sprite_height, double transform_y)
{
	int	tex_x;
	int	y;
	int	d;
	int	tex_y;
	int	color;

	tex_x = (int)((stripe_x - (-sprite_height / 2 + sprite_screen_x))
		* tex->width / sprite_height);
	y = -sprite_height / 2 + WIN_HEIGHT / 2;
	if (y < 0)
		y = 0;
	while (y < sprite_height / 2 + WIN_HEIGHT / 2 && y < WIN_HEIGHT)
	{
		d = y * 256 - WIN_HEIGHT * 128 + sprite_height * 128;
		tex_y = ((d * tex->height) / sprite_height) / 256;
		color = get_texture_color(tex, tex_x, tex_y);
		if ((color & 0x00FFFFFF) != 0 && stripe_x >= 0
			&& stripe_x < WIN_WIDTH
			&& transform_y < game->z_buffer[stripe_x])
			put_pixel(game, stripe_x, y, color);
		y++;
	}
}

/* Transforme les coordonnées du sprite en coordonnées caméra */
static void	transform_sprite(t_game *game, t_sprite *sprite,
	double *transform_x, double *transform_y)
{
	double	sprite_x;
	double	sprite_y;
	double	inv_det;

	sprite_x = sprite->x - game->player.pos_x;
	sprite_y = sprite->y - game->player.pos_y;
	inv_det = 1.0 / (game->player.plane_x * game->player.dir_y
			- game->player.dir_x * game->player.plane_y);
	*transform_x = inv_det * (game->player.dir_y * sprite_x
			- game->player.dir_x * sprite_y);
	*transform_y = inv_det * (-game->player.plane_y * sprite_x
			+ game->player.plane_x * sprite_y);
}

/* Dessine le sprite stripe par stripe */
static void	draw_sprite_columns(t_game *game, t_sprite *sprite,
	int screen_x, int height, double transform_y)
{
	int				start_x;
	int				end_x;
	int				stripe;
	t_texture_img	*tex;

	start_x = -height / 2 + screen_x;
	if (start_x < 0)
		start_x = 0;
	end_x = height / 2 + screen_x;
	if (end_x >= WIN_WIDTH)
		end_x = WIN_WIDTH - 1;
	tex = &game->bear_trap_frames[sprite->current_frame];
	stripe = start_x;
	while (stripe < end_x)
	{
		draw_sprite_stripe(game, tex, stripe, screen_x, height, transform_y);
		stripe++;
	}
}

/* Calcule et dessine un sprite */
static void	render_single_sprite(t_game *game, t_sprite *sprite)
{
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;

	transform_sprite(game, sprite, &transform_x, &transform_y);
	if (transform_y <= 0)
		return ;
	sprite_screen_x = (int)((WIN_WIDTH / 2) * (1 + transform_x / transform_y));
	sprite_height = abs((int)(WIN_HEIGHT / transform_y));
	draw_sprite_columns(game, sprite, sprite_screen_x, sprite_height,
		transform_y);
}

/* Rend tous les sprites */
void	render_sprites(t_game *game)
{
	int	i;

	sort_sprites(game);
	i = 0;
	while (i < game->sprite_count)
	{
		render_single_sprite(game, &game->sprites[i]);
		i++;
	}
}
