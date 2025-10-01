#include "../../includes/cub3d.h"

/* Charge une texture et récupère toutes ses infos (img, addr, width, height)
Pour pouvoir ensuite lire les pixels de la texture */
static void	load_single_texture(void *mlx, char *path, t_texture_img *tex)
{
	tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
	if (!tex->img)
	{
		printf("Error\nFailed to load texture: %s\n", path);
		exit(EXIT_FAILURE);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
}

void	load_all_textures(t_game *game, t_textures *textures)
{
	load_single_texture(game->mlx, textures->north, &game->tex_north);
	load_single_texture(game->mlx, textures->south, &game->tex_south);
	load_single_texture(game->mlx, textures->west, &game->tex_west);
	load_single_texture(game->mlx, textures->east, &game->tex_east);
}
