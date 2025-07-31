#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

typedef struct s_game // structure principale qui contient tout
{
	void	*mlx;
	void	*win;
}	t_game;

typedef struct s_map // pour stocker la carte
{

}	t_map;

typedef struct s_player // position et direction du joueur
{

}	t_player;

typedef struct s_textures
{
	char *north;
	char *south;
	char *west;
	char *east;

	int floor[3]; // (R, G, B)
	int ceiling[3]; // (R, G, B)
}	t_textures;

int check_map(int argc, char **argv);

#endif