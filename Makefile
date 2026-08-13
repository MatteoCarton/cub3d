NAME = cub3D
BONUS_NAME = cub3D_bonus

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLXDIR = minilibx-linux
MLXFLAGS = -L$(MLXDIR) -lmlx -lXext -lX11 -lm -lz
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
	   $(SRCSDIR)/events/handle_input.c \
	   $(SRCSDIR)/cleanup/cleanup.c \

BONUSDIR = $(SRCSDIR)/bonus

BONUS_SRCS = $(BONUSDIR)/main_bonus.c \
	   $(BONUSDIR)/check_args_bonus.c \
	   $(BONUSDIR)/parse_file_bonus.c \
	   $(BONUSDIR)/parse_colors_bonus.c \
	   $(BONUSDIR)/parse_textures_bonus.c \
	   $(BONUSDIR)/parse_sprites_bonus.c \
	   $(BONUSDIR)/map_validator_bonus.c \
	   $(BONUSDIR)/map_reader_bonus.c \
	   $(BONUSDIR)/map_grid_bonus.c \
	   $(BONUSDIR)/load_textures_bonus.c \
	   $(BONUSDIR)/init_player_bonus.c \
	   $(BONUSDIR)/init_ray_bonus.c \
	   $(BONUSDIR)/render_bonus.c \
	   $(BONUSDIR)/draw_bonus.c \
	   $(BONUSDIR)/texture_bonus.c \
	   $(BONUSDIR)/sprite_bonus.c \
	   $(BONUSDIR)/sprite_draw_bonus.c \
	   $(BONUSDIR)/minimap_bonus.c \
	   $(BONUSDIR)/minimap_draw_bonus.c \
	   $(BONUSDIR)/mouse_bonus.c \
	   $(BONUSDIR)/move_bonus.c \
	   $(BONUSDIR)/handle_input_bonus.c \
	   $(BONUSDIR)/cleanup_bonus.c \
	   $(BONUSDIR)/cleanup_paths_bonus.c \

OBJS = $(patsubst $(SRCSDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
BONUS_OBJS = $(patsubst $(SRCSDIR)/%.c,$(OBJDIR)/%.o,$(BONUS_SRCS))

all: mlx libft $(NAME)

bonus: mlx libft $(BONUS_NAME)

mlx:
	@$(MAKE) -C $(MLXDIR) > /dev/null 2>&1

libft:
	@$(MAKE) -C $(LIBFTDIR) > /dev/null 2>&1

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) $(MLXFLAGS) -L$(LIBFTDIR) -lft -o $(NAME)
	@echo "\033[0;32m"
	@echo "   _____ _    _ ____  ____  _____  "
	@echo "  / ____| |  | |  _ \|___ \|  __ \ "
	@echo " | |    | |  | | |_) | __) | |  | |"
	@echo " | |    | |  | |  _ < |__ <| |  | |"
	@echo " | |____| |__| | |_) |___) | |__| |"
	@echo "  \_____|\____/|____/|____/|_____/ "
	@echo "\033[0m"

$(BONUS_NAME): $(BONUS_OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(MLXFLAGS) -L$(LIBFTDIR) -lft \
		-o $(BONUS_NAME)
	@echo "\033[0;32mcub3D_bonus : sprites animes, minimap, souris\033[0m"

$(OBJDIR)/%.o: $(SRCSDIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(INCDIR) -I$(MLXDIR) -I$(LIBFTDIR)/inc -c $< -o $@

textures:
	@./tools/gen_textures.sh

textures-re:
	@./tools/gen_textures.sh -f

clean:
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(MLXDIR) clean > /dev/null 2>&1
	@$(MAKE) -C $(LIBFTDIR) clean > /dev/null 2>&1
	@echo "\033[0;33mCleaned object files\033[0m"

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean > /dev/null 2>&1
	@echo "\033[0;31mFull clean completed\033[0m"

re: fclean all

.PHONY: all bonus clean fclean re mlx libft textures textures-re