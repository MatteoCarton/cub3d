/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcastrat <mcastrat@student.42belgium.be    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/13 09:00:00 by mcastrat          #+#    #+#             */
/*   Updated: 2026/08/13 09:00:00 by mcastrat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	free_texture_images(t_data *data)
{
	if (data->tex_north.img)
		mlx_destroy_image(data->mlx, data->tex_north.img);
	if (data->tex_south.img)
		mlx_destroy_image(data->mlx, data->tex_south.img);
	if (data->tex_west.img)
		mlx_destroy_image(data->mlx, data->tex_west.img);
	if (data->tex_east.img)
		mlx_destroy_image(data->mlx, data->tex_east.img);
}

static void	free_sprites(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->frame_count)
	{
		if (data->frames[i].img)
			mlx_destroy_image(data->mlx, data->frames[i].img);
		i++;
	}
	data->frame_count = 0;
	if (data->sprites)
		free(data->sprites);
	data->sprites = NULL;
	data->sprite_count = 0;
}

static void	free_map_grid_array(t_grid *grid)
{
	int	i;

	if (!grid || !grid->grid)
		return ;
	i = 0;
	while (i < grid->height)
	{
		if (grid->grid[i])
			free(grid->grid[i]);
		i++;
	}
	free(grid->grid);
	grid->grid = NULL;
}

void	cleanup_game(t_data *data, t_grid *grid, t_walls *walls)
{
	if (!data)
		return ;
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	free_texture_images(data);
	free_sprites(data);
	free_map_grid_array(grid);
	free_texture_paths(walls);
	if (data->win && data->mlx)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
}
