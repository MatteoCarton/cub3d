NAME = cub3D

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLXDIR = minilibx_opengl_20191021
MLXFLAGS = -L$(MLXDIR) -lmlx -framework OpenGL -framework AppKit -lz
LIBFTDIR = libft
LIBFT = $(LIBFTDIR)/libft.a

SRCSDIR = srcs
INCDIR = includes
OBJDIR = obj

SRCS = $(SRCSDIR)/main.c \
       $(SRCSDIR)/check/check_args.c \
       $(SRCSDIR)/parsing/parse_file.c \
       $(SRCSDIR)/parsing/parse_colors.c \
       $(SRCSDIR)/parsing/parse_textures.c \
       $(SRCSDIR)/parsing/map_validator.c \
       $(SRCSDIR)/parsing/map_reader.c \
       $(SRCSDIR)/parsing/map_grid.c \
	   $(SRCSDIR)/textures/load_textures.c \
	   $(SRCSDIR)/player/init_player.c \
	   $(SRCSDIR)/raycasting/init_ray.c \
	   $(SRCSDIR)/rendering/render.c \
	   $(SRCSDIR)/rendering/draw.c \
	   $(SRCSDIR)/rendering/texture.c \
	   $(SRCSDIR)/rendering/minimap.c \
	   $(SRCSDIR)/events/handle_input.c \
	   $(SRCSDIR)/events/mouse_input.c \

OBJS = $(patsubst $(SRCSDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

all: mlx libft $(NAME)

mlx:
	@$(MAKE) -C $(MLXDIR)

libft:
	@$(MAKE) -C $(LIBFTDIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -L$(LIBFTDIR) -lft -o $(NAME)

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	@$(MAKE) -C $(MLXDIR) clean
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re mlx libft