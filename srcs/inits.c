/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 17:24:42 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/30 21:20:49 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*init_mlx(t_data *data)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!data || !player)
		return (free(data), NULL);
	data->win_img = malloc(sizeof(t_img));
	if (!data->win_img)
		return (free(data), free(player), NULL);
	data->map_img = malloc(sizeof(t_img));
	if (!data->map_img)
		return (free(data->win_img), free(data), free(player), NULL);
	data->player = player;
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (NULL);
	data->win_img->image = mlx_new_image(data->mlx, LSIZE, HSIZE);
	data->win_img->ptr_image = mlx_get_data_addr(data->win_img->image, \
	&data->win_img->bpp, &data->win_img->size_line, &data->win_img->endian);
	data->map_img->image = mlx_new_image(data->mlx, LSIZE, HSIZE);
	data->map_img->ptr_image = mlx_get_data_addr(data->map_img->image, \
	&data->map_img->bpp, &data->map_img->size_line, &data->map_img->endian);
	data->window = mlx_new_window(data->mlx, LSIZE, HSIZE, "cub3D");
	if (!data->window)
		return (quit_program(data), NULL);
	return (data);
}

t_map	*init_map_file(t_data *data, char *filename)
{
	int		fd;
	t_map	*map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		return (close(fd), NULL);
	map->map = create_map_array(fd);
	if (!map->map)
		return (free(map), close(fd), NULL);
	map->texture_no = NULL;
	map->texture_so = NULL;
	map->texture_ea = NULL;
	map->texture_we = NULL;
	map->texture_door = NULL;
	map->floor_color = -1;
	map->ceiling_color = -1;
	map->width = longest_row_len(map);
	map->height = count_map_rows(map);
	map->tile_size = min(HSIZE / map->height, LSIZE / map->width);
	close(fd);
	data->map = map;
	return (map);
}

void	create_window(t_data *data)
{
	draw_background(data);
	copy_image(data->map_img, data->win_img, LSIZE, HSIZE);
}
