NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLXDIR = minilibx_opengl_20191021
MLXFLAGS = -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -lz

SRCDIR = src
INCDIR = includes
OBJDIR = obj

SRCS = $(SRCDIR)/main.c

OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: mlx $(NAME)

mlx:
	@$(MAKE) -C $(MLXDIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MLXDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(MLXDIR) clean

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re mlx