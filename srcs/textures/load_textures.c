#include "../../includes/cub3d.h"


/* mlx_xpm_file_to_image() : Fonction MLX qui charge un fichier XPM
Elle prend 4 parametres :
mlx : Le pointeur MLX
texture_path : Chemin du fichier
&width : MLX va ecrire la largeur ici
&height : MLX va ecrire la hauteur ici
Retour : Un pointeur vers l'image (ou NULL si échec) */

static void	*load_single_texture(void *mlx, char *texture_path)
{
	void	*img;
	int		width;
	int		height;

	img = mlx_xpm_file_to_image(mlx, texture_path, &width, &height);
	if (!img)
	{
		printf("Error\nFailed to load texture: %s\n", texture_path);
		exit(EXIT_FAILURE);
	}
	return (img);
}

void	load_all_textures(t_game *game, t_textures *textures)
{
	game->img_north = load_single_texture(game->mlx, textures->north);
	game->img_south = load_single_texture(game->mlx, textures->south);
	game->img_west = load_single_texture(game->mlx, textures->west);
	game->img_east = load_single_texture(game->mlx, textures->east);
}
