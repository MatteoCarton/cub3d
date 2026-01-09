/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2025/11/26 15:08:54 by mcastrat          #+#    #+#             */
/*   Updated: 2026/01/03 19:00:33 by mcastrat         ###   ########.fr       */
=======
/*   Created: 2025/11/24 14:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2025/11/24 16:30:00 by mcastrat         ###   ########.fr       */
>>>>>>> ae1e321c442674b4e557df73ddd8c2b49159b347
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	open_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	return (close(fd), 1);
}
/*	i = 0;
	while (i < length)
	{
		if (map_name[i] == '.')
			check++;
		i++;
	}
	if (check > 1)
		return (0);*/

static int	check_name_map(char *map_name)
{
	int			length;

	length = 0;
	while (map_name[length] != '\0')
		length++;
	if (length < 4 || map_name[length - 4] != '.'
		|| map_name[length - 3] != 'c' || map_name[length - 2] != 'u'
		|| map_name[length - 1] != 'b')
		return (0);
	return (1);
}

int	check_args(int argc, char **argv)
{
	if (argc < 2)
		return (printf("Error\nNo map provided\n"), 0);
	if (argc > 2)
		return (printf("Error\nToo many arguments\n"), 0);
	if (check_name_map(argv[1]) == 0)
		return (printf("Error\nInvalid extension, not a .cub file\n"), 0);
	if (open_file(argv[1]) == 0)
		return (printf("Error\nCould not open map file\n"), 0);
	return (1);
}
