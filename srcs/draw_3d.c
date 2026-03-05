/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 17:32:27 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/29 00:50:51 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	shade_color(int base_color, float brightness)
{
	int	r;
	int	g;
	int	b;

	r = ((base_color / 0x10000) % 0x100) * brightness;
	g = ((base_color / 0x100) % 0x100) * brightness;
	b = (base_color % 0x100) * brightness;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r * 0x10000) + (g * 0x100) + b);
}

static int	process_tex_x(t_data *data, t_tex *texture, t_ray *ray)
{
	int	tex_x;

	if (texture == data->door)
		texture->orientation = get_right_orientation(data, ray);
	if (texture->orientation % 2 == 0)
	{
		tex_x = (int)((data->player->ry / data->map->tile_size) * \
		texture->wall_width) % texture->wall_width;
	}
	else
	{
		tex_x = (int)((data->player->rx / data->map->tile_size) * \
		texture->wall_width) % texture->wall_width;
	}
	if (texture->orientation == 2 || texture->orientation == 3)
		tex_x = texture->wall_width - tex_x - 1;
	return (tex_x);
}

static void	draw_wall_3d(t_data *data, int col, t_ray *ray, t_tex *texture)
{
	int		y;
	float	brightness;
	int		color;
	int		tex_x;
	int		tex_y;

	brightness = 1 / (1 + ray->ray_size * 0.008);
	if (brightness > 1)
		brightness = 1;
	else if (brightness < 0.2)
		brightness = 0.2;
	tex_x = process_tex_x(data, texture, ray);
	y = (int)((HSIZE - ray->wall_size) / 2);
	if (y < 0)
		y = 0;
	while (y < HSIZE - (int)((HSIZE - ray->wall_size) / 2) && y < HSIZE)
	{
		tex_y = ((y - (int)((HSIZE - ray->wall_size) / 2)) * \
		texture->wall_height) / ray->wall_size;
		color = shade_color(get_texture_pixel(texture, tex_x, tex_y), \
			brightness);
		if (!ft_mlx_pixel_put(data->win_img, col, y, color))
			return ;
		y++;
	}
}

static t_tex	*get_right_texture(t_data *data, t_ray *ray)
{
	if (data->map->map[data->player->mapy][data->player->mapx] == 'D')
		return (data->door);
	if (ray->x_bwall == data->player->mapx && \
		ray->y_bwall > data->player->mapy)
		return (data->north);
	if (ray->x_bwall < data->player->mapx && \
		ray->y_bwall == data->player->mapy)
		return (data->east);
	if (ray->x_bwall == data->player->mapx && \
		ray->y_bwall < data->player->mapy)
		return (data->south);
	if (ray->x_bwall > data->player->mapx && \
		ray->y_bwall == data->player->mapy)
		return (data->west);
	return (NULL);
}

void	compute_wall_3d(t_data *data, t_ray *ray, int i)
{
	float	screen_dist;
	int		column_start;
	int		column_end;
	t_tex	*texture;

	ray->ray_size = sqrtf(powf(data->player->rx - data->player->px, 2) + \
		powf(data->player->ry - data->player->py, 2)) * \
		cosf(ray->ray_angle - data->player->angle);
	screen_dist = LSIZE / (2 * tanf((PI / 3) / 2));
	ray->wall_size = (int)((data->map->tile_size * screen_dist) / \
		ray->ray_size);
	column_start = (int)(((float)i / 240.0f) * LSIZE);
	column_end = (int)(((float)(i + 1) / 240.0f) * LSIZE);
	if (column_end > LSIZE)
		column_end = LSIZE;
	while (column_start < column_end)
	{
		texture = get_right_texture(data, ray);
		if (!texture)
			return ;
		draw_wall_3d(data, column_start++, ray, texture);
	}
}
