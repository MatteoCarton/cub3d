/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../libft/inc/libft.h"
# include "../libft/inc/get_next_line.h"

# define WIN_WIDTH 1280
# define WIN_HEIGHT 720
# define FOV 0.99

# define KEY_ESC	65307
# define KEY_W		119
# define KEY_A		97
# define KEY_S		115
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363

# define MOVE_SPEED	0.2
# define ROT_SPEED	0.05

/* Bonus : collision, souris, minimap, sprites animes */
# define WALL_PAD 0.2
# define MOUSE_SENS 0.0022
# define MINIMAP_TILE 8
# define MINIMAP_VIEW 8
# define MINIMAP_X 20
# define MINIMAP_Y 20
# define MINIMAP_SIZE (MINIMAP_TILE * MINIMAP_VIEW * 2)
# define MINIMAP_BG 0x1A1A1A
# define MINIMAP_WALL 0xC8C8C8
# define MINIMAP_FLOOR 0x3C3C3C
# define MINIMAP_SPRITE 0xE0B040
# define MINIMAP_PLAYER 0xE03030
# define MAX_FRAMES 64
# define ANIM_DELAY 3
# define SPRITE_PREFIX "./textures/pack/coins/tile"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_grid
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_grid;

typedef struct s_walls
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
	int		floor[3];
	int		ceiling[3];
}	t_walls;

typedef struct s_cam
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_cam;

/* Un sprite pose sur la map (case '2') */
typedef struct s_sprite
{
	double	x;
	double	y;
	double	distance;
}	t_sprite;

/* Geometrie ecran d'un sprite, calculee une fois par frame */
typedef struct s_spr
{
	double	depth;
	int		center;
	int		size;
	int		top;
}	t_spr;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_img		tex_north;
	t_img		tex_south;
	t_img		tex_west;
	t_img		tex_east;
	t_img		frames[MAX_FRAMES];
	int			frame_count;
	int			frame;
	int			tick;
	t_sprite	*sprites;
	int			sprite_count;
	double		z_buffer[WIN_WIDTH];
	t_cam		cam;
	t_grid		*grid;
	t_walls		*walls;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_data;

typedef struct s_cast
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_x;
	double	side_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	double	distance;
	int		side;
	int		wall_h;
	double	wall_x;
}	t_cast;

void	free_texture_paths(t_walls *walls);
int		check_args(int argc, char **argv);
int		check_map(int argc, char **argv, t_walls *walls, t_grid *grid);
int		parse_color(char *line, int *color_array);
int		parse_textures(char *line, t_walls *walls);
void	init_textures(t_walls *walls);
int		is_map_line(char *line);
int		validate_map_closed(t_grid *grid);
int		validate_textures(t_walls *walls);
int		parse_config_line(char *line, t_walls *walls);
char	**store_map_lines(char *filename, int *line_count);
void	free_map_lines(char **lines, int line_count);
void	free_map_grid(t_grid *grid);
int		parse_map_grid(char **lines, int start, t_grid *grid);
int		init_wall_textures(t_data *data, t_walls *walls);
int		init_sprite_frames(t_data *data, t_walls *walls);
void	init_player(t_cam *cam, t_grid *grid);
void	prepare_ray(t_cast *cast, t_cam *cam, int x);
void	setup_step(t_cast *cast, t_cam *cam);
void	algo_dda(t_cast *cast, t_grid *grid);
void	calculate_wall_distance(t_cast *cast, t_cam *cam);
void	render_frame(t_data *data, t_walls *walls, t_grid *grid);
int		render_hook(t_data *data);
void	set_pixel(t_data *data, int x, int y, int color);
void	draw_vline(t_data *data, int x, int y_range[2], int color);
void	draw_column(t_data *data, t_cast *cast, t_walls *walls, int x);
int		rgb_to_color(int *rgb);
int		get_tex_color(t_img *tex, int tex_x, int tex_y);
void	draw_wall_tex(t_data *data, t_cast *cast, int x, int st_end[2]);
int		handle_keypress(int keycode, t_data *data);
int		close_window(t_data *data);
void	cleanup_game(t_data *data, t_grid *grid, t_walls *walls);
void	cleanup_and_exit(t_data *data, t_grid *grid, t_walls *walls,
			int exit_code);
int		parse_sprite_path(char *line, t_walls *walls);
int		parse_sprites(t_data *data, t_grid *grid);
void	render_sprites(t_data *data);
void	draw_sprite_column(t_data *data, t_spr *spr, int x);
void	advance_animation(t_data *data);
void	draw_minimap(t_data *data);
void	draw_minimap_bg(t_data *data);
void	draw_tile(t_data *data, int pos[2], int color);
int		in_minimap(int x, int y);
int		minimap_tile_color(t_grid *grid, int x, int y);
void	move_player(t_cam *cam, t_grid *grid, int keycode);
int		mouse_move(int x, int y, t_data *data);

#endif
