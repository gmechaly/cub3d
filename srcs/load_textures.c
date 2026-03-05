/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 17:27:47 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/29 00:48:35 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	get_right_orientation(t_data *data, t_ray *ray)
{
	if (ray->x_bwall == data->player->mapx && \
		ray->y_bwall > data->player->mapy)
		return (1);
	if (ray->x_bwall < data->player->mapx && \
		ray->y_bwall == data->player->mapy)
		return (2);
	if (ray->x_bwall == data->player->mapx && \
		ray->y_bwall < data->player->mapy)
		return (3);
	if (ray->x_bwall > data->player->mapx && \
		ray->y_bwall == data->player->mapy)
		return (4);
	return (0);
}

void	*load_textures(t_data *data)
{
	data->north = load_one_texture(data, data->map->texture_so, 1);
	if (!data->north)
		return (NULL);
	data->east = load_one_texture(data, data->map->texture_we, 2);
	if (!data->east)
		return (NULL);
	data->south = load_one_texture(data, data->map->texture_no, 3);
	if (!data->south)
		return (NULL);
	data->west = load_one_texture(data, data->map->texture_ea, 4);
	if (!data->west)
		return (NULL);
	if (data->map->texture_door)
		data->door = load_one_texture(data, data->map->texture_door, 0);
	if (data->map->texture_door && !data->door)
		return (NULL);
	return (data);
}

t_tex	*load_one_texture(t_data *data, char *path_to_texture, int orientation)
{
	t_tex	*texture;

	texture = malloc(sizeof(t_tex));
	if (!texture)
		return (NULL);
	texture->img_struct = malloc(sizeof(t_img));
	if (!texture->img_struct)
		return (NULL);
	texture->orientation = orientation;
	texture->img_struct->image = mlx_xpm_file_to_image((*data).mlx, \
	path_to_texture, &texture->wall_width, &texture->wall_height);
	if (!texture->img_struct->image)
	{
		printf("Error : texture %s doesn't exist\n", path_to_texture);
		quit_program(data);
	}
	texture->img_struct->ptr_image = mlx_get_data_addr(\
		texture->img_struct->image, &texture->img_struct->bpp, \
		&texture->img_struct->size_line, &texture->img_struct->endian);
	if (!texture->img_struct->ptr_image)
	{
		printf("Error : texture file is wrong, somehow...\n");
		quit_program(data);
	}
	return (texture);
}
