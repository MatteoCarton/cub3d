/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_paths_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	free_texture_paths(t_walls *walls)
{
	if (!walls)
		return ;
	free(walls->north);
	walls->north = NULL;
	free(walls->south);
	walls->south = NULL;
	free(walls->west);
	walls->west = NULL;
	free(walls->east);
	walls->east = NULL;
	free(walls->sprite);
	walls->sprite = NULL;
}

void	cleanup_and_exit(t_data *data, t_grid *grid,
						t_walls *walls, int exit_code)
{
	cleanup_game(data, grid, walls);
	exit(exit_code);
}
