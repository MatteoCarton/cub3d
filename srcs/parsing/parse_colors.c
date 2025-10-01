#include "../../includes/cub3d.h"

static int	validate_rgb_count(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
	{
		printf("Error\nInvalid color format\n");
		return (0);
	}
	return (1);
}

static int	validate_rgb_digits(char **rgb)
{
	int	j;
	int	m;

	j = 0;
	while (j < 3)
	{
		m = 0;
		while (rgb[j][m])
		{
			if (!ft_isdigit(rgb[j][m]))
			{
				printf("Error\nColor values must be numbers only\n");
				return (0);
			}
			m++;
		}
		j++;
	}
	return (1);
}

static int	validate_rgb_range(char **rgb, int *color_array)
{
	int	j;
	int	value;

	j = 0;
	while (j < 3)
	{
		value = ft_atoi(rgb[j]);
		if (value < 0 || value > 255)
		{
			printf("Error\nColor values must be between 0 and 255\n");
			return (0);
		}
		color_array[j] = value;
		j++;
	}
	return (1);
}

static void	free_rgb_array(char **rgb)
{
	int	i;

	i = 0;
	while (rgb[i])
	{
		free(rgb[i]);
		i++;
	}
	free(rgb);
}

void	parse_color(char *line, int *color_array)
{
	char	*color;
	char	**rgb;

	color = ft_strtrim(line + 2, " \t\n\r\v\f");
	if (!color || !*color)
	{
		printf("Error\nEmpty color value\n");
		if (color)
			free(color);
		exit(EXIT_FAILURE);
	}
	rgb = ft_split(color, ',');
	if (!validate_rgb_count(rgb) || !validate_rgb_digits(rgb)
		|| !validate_rgb_range(rgb, color_array))
	{
		free(color);
		free_rgb_array(rgb);
		exit(EXIT_FAILURE);
	}
	free(color);
	free_rgb_array(rgb);
}