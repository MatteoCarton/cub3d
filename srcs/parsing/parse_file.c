#include "../../includes/cub3d.h"

static int	find_map_start(char **lines, int line_count, t_textures *textures)
{
	int	i;

	i = 0;
	while (i < line_count)
	{
		if (lines[i][0] != '\n' && !parse_config_line(lines[i], textures))
		{
			if (is_map_line(lines[i]))
				return (i);
			else if (lines[i][0] != '\n')
			{
				printf("Error\nInvalid line: %s", lines[i]);
				return (-1);
			}
		}
		i++;
	}
	return (-1);
}

static void	print_map_info(t_map *map)
{
	printf("Map successfully parsed!\n");
	printf("Map size: %dx%d\n", map->width, map->height);
	printf("Player at (%d, %d) facing %c\n",
		map->player_x, map->player_y, map->player_dir);
}

int	check_map(int argc, char **argv, t_textures *textures)
{
	char	**lines;
	int		line_count;
	int		map_start;
	t_map	map;
	int		i;

	(void)argc;
	init_textures(textures);
	lines = store_map_lines(argv[1], &line_count);
	if (!lines)
		return (0);

		//[DEBUG
	printf("\n Total lines stored = %d\n", line_count);
	i = 0;
	while (i < line_count)
	{
		printf("[%d]: %s", i, lines[i]);
		i++;
	}
		// DEBUG]

	map_start = find_map_start(lines, line_count, textures);
	if (!validate_textures(textures) || map_start == -1
		|| !parse_map_grid(lines, map_start, &map)
		|| !validate_map_closed(&map))
	{
		free_map_lines(lines, line_count);
		return (0);
	}
	print_map_info(&map);
	free_map_lines(lines, line_count);
	free_map_grid(&map);
	return (1);
}