/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:39:53 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/29 01:03:54 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_struct(t_map *map, t_data *data)
{
	if (!map)
		return ;
	if (map->map)
		free_map_array(map->map);
	free(map->texture_ea);
	free(map->texture_no);
	free(map->texture_we);
	free(map->texture_so);
	if (map->texture_door)
		free(map->texture_door);
	if (data->door)
	{
		mlx_destroy_image(data->mlx, data->door->img_struct->image);
		free(data->door->img_struct);
		free(data->door);
	}
	free(data->map);
	data->map = NULL;
}

static void	free_textures(t_data *data)
{
	if (data->north)
	{
		mlx_destroy_image(data->mlx, data->north->img_struct->image);
		free(data->north->img_struct);
		free(data->north);
	}
	if (data->east)
	{
		mlx_destroy_image(data->mlx, data->east->img_struct->image);
		free(data->east->img_struct);
		free(data->east);
	}
	if (data->south)
	{
		mlx_destroy_image(data->mlx, data->south->img_struct->image);
		free(data->south->img_struct);
		free(data->south);
	}
	if (data->west)
	{
		mlx_destroy_image(data->mlx, data->west->img_struct->image);
		free(data->west->img_struct);
		free(data->west);
	}
}

static void	free_gun(t_data *data)
{
	int	i;

	i = 0;
	while (i < GUN_FRAME_COUNT && data->gun.frames[i])
		mlx_destroy_image(data->mlx, data->gun.frames[i++]);
}

static int	free_mlx_and_quit(t_data *data)
{
	if (data->mlx)
	{
		if (data->win_img)
		{
			mlx_destroy_image(data->mlx, data->win_img->image);
			free(data->win_img);
		}
		if (data->map_img)
		{
			mlx_destroy_image(data->mlx, data->map_img->image);
			free(data->map_img);
		}
		if (data->window)
			mlx_destroy_window(data->mlx, data->window);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free(data);
	exit(0);
	return (0);
}

int	quit_program(t_data *data)
{
	if (!data)
		exit(0);
	if (data->player)
		free(data->player);
	if (data->map)
		free_textures(data);
	if (data->map)
		free_map_struct(data->map, data);
	free_gun(data);
	free_mlx_and_quit(data);
	return (0);
}
