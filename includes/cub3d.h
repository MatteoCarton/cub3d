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
	t_map       *map;           // Pointeur vers la map (pour les collisions)
	t_textures  *textures;      // Pointeur vers les textures

	void        *img;           // Pointeur vers l'image
    char        *addr;          // Adresse des données de l'image
    int         bits_per_pixel; // Bits par pixel (bits_per_pixel, line_length, endian : Infos techniques nécessaires pour MLX)
    int         line_length;    // Longueur d'une ligne
    int         endian;         // Ordre des octets

}	t_game;

typedef struct s_ray
{
    // Direction du rayon
    double  ray_dir_x;
    double  ray_dir_y;
    
    // Position dans la map (quelle case on vérifie)
    int     map_x;
    int     map_y;
    
    // Distance jusqua la prochaine bordure (vertical/horizontal)
    double  dist_to_bord_x;
    double  dist_to_bord_y;
    
    // Distance pour avancer d'une case complète (calculer au debut, ne change pas)
    double  delta_dist_x;
    double  delta_dist_y;
    
    // Dans quelle direction on avance (-1 ou +1)
    int     step_direction_x; // -1 si on va à gauche, +1 si on va à droite
    int     step_direction_y; // -1 si on va en haut, +1 si on va en bas
    
    // Distance perpendiculaire au mur (évite l'effet fish-eye)
    double  perp_wall_dist;

    // Quel côté du mur on a touché (0 = vertical, 1 = horizontal)
    int     side;

    // Hauteur du mur à dessiner (en pixels)
    int     line_height;
}   t_ray;

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

//src/raycasting
void    init_ray(t_ray *ray, t_player *player, int x);
void    init_ray_step(t_ray *ray, t_player *player);
void    algo_dda(t_ray *ray, t_map *map);
void    calculate_wall_distance(t_ray *ray, t_player *player);

//src/rendering
void    render_frame(t_game *game, t_textures *textures, t_map *map);
int     render_loop(t_game *game);
void    put_pixel(t_game *game, int x, int y, int color);
void    draw_vertical_line(t_game *game, int x, int start_y, int end_y,
			int color);
void    calculate_draw_limits(t_ray *ray, int *start, int *end);
void    draw_column(t_game *game, t_ray *ray, t_textures *textures, int x);
int     rgb_to_int(int *rgb);

//src/events
int     handle_keypress(int keycode, t_game *game);
int     close_window(t_game *game);

#endif