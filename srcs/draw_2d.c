/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:22:17 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/30 20:38:24 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_square(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map->tile_size / 4)
	{
		j = 0;
		while (j < data->map->tile_size / 4)
		{
			if (!ft_mlx_pixel_put(data->win_img, x + i, y + j, color))
				return ;
			j++;
		}
		i++;
	}
}

static void	draw_map_line(int y, char **map, int size, t_data *data)
{
	int	line_size;
	int	x;

	line_size = ft_strlen(map[y]);
	x = 0;
	while (x < data->map->width)
	{
		if (x == (int)(data->player->px / data->map->tile_size) && \
			y == (int)(data->player->py / data->map->tile_size))
			draw_square(data, x * size, y * size, RED);
		else if (x < line_size && map[y][x] == '1')
			draw_square(data, x * size, y * size, WHITE);
		else if (x < line_size && map[y][x] == '0')
			draw_square(data, x * size, y * size, BLACK);
		else if (x < line_size && map[y][x] == 'D')
			draw_square(data, x * size, y * size, BLUE);
		else
			draw_square(data, x * size, y * size, GRAY);
		x++;
	}
}

void	draw_minimap(t_data *data)
{
	int		y;
	int		size;
	char	**map;

	map = data->player->map->map;
	y = 0;
	size = (int)(data->map->tile_size / 4);
	while (y < data->map->height)
	{
		draw_map_line(y, map, size, data);
		y++;
	}
}

void	draw_background(t_data *data)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	color = data->map->ceiling_color;
	while (y < HSIZE)
	{
		x = 0;
		if (y > HSIZE / 2)
			color = data->map->floor_color;
		while (x < LSIZE)
		{
			if (!ft_mlx_pixel_put(data->map_img, x, y, color))
				return ;
			x++;
		}
		y++;
	}
}
