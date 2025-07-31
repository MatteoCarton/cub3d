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

typedef struct s_data
{
	void	*mlx;
	void	*win;
}	t_data;

#endif