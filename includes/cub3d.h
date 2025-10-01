#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../libft/libft.h"
# include <stdbool.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600
# define FOV 0.66

typedef struct s_player // position et direction du joueur
{
	double  pos_x;      // Position X dans la map (coordonnees)
    double  pos_y;      // Position Y dans la map
    double  dir_x;      // Vecteur direction X (où regarde le joueur)
    double  dir_y;      // Vecteur direction Y
    double  plane_x;    // Vecteur plan caméra X (pour le FOV)
    double  plane_y;    // Vecteur plan caméra Y
}	t_player;

typedef struct s_game // structure principale qui contient tout
{
	void	*mlx;
	void	*win;

	void    *img_north;
    void    *img_south;
    void    *img_west;
    void    *img_east;

	t_player    player;
}	t_game;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_map;

typedef struct s_textures
{
	char *north; // juste le chemin "./textures/north.xpm"
	char *south;
	char *west;
	char *east;

	int floor[3]; // (R, G, B)
	int ceiling[3]; // (R, G, B)
}	t_textures;

int		check_args(int argc, char **argv);
int		check_map(int argc, char **argv, t_textures *textures, t_map *map);

void	parse_color(char *line, int *color_array);
void	parse_textures(char *line, t_textures *textures);
void	init_textures(t_textures *textures);

int		is_map_line(char *line);
int		validate_map_closed(t_map *map);
int		validate_textures(t_textures *textures);
int		parse_config_line(char *line, t_textures *textures);

char	**store_map_lines(char *filename, int *line_count);
void	free_map_lines(char **lines, int line_count);
void	free_map_grid(t_map *map);

int		parse_map_grid(char **lines, int start, t_map *map);

//src/textures
void    load_all_textures(t_game *game, t_textures *textures);

//src/player
void	init_player(t_player *player, t_map *map);

#endif