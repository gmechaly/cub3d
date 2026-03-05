/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:18:58 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/25 17:14:54 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	process_wall_hit(t_player *player, t_ray *ray)
{
	if (!ray->side)
		ray->hdist = (player->mapx - player->px / player->map->tile_size + \
			(1 - player->xoff) / 2) / ray->dx;
	else
		ray->hdist = (player->mapy - player->py / player->map->tile_size + \
			(1 - player->yoff) / 2) / ray->dy;
	player->rx = player->px + ray->dx * ray->hdist * player->map->tile_size;
	player->ry = player->py + ray->dy * ray->hdist * player->map->tile_size;
}

static void	cast_ray3(t_player *player, t_ray *ray)
{
	while (!ray->hit)
	{
		ray->x_bwall = player->mapx;
		ray->y_bwall = player->mapy;
		if (ray->sdx < ray->sdy)
		{
			ray->sdx += ray->ddx;
			player->mapx += player->xoff;
			ray->side = 0;
		}
		else
		{
			ray->sdy += ray->ddy;
			player->mapy += player->yoff;
			ray->side = 1;
		}
		if (is_wall(player->mapx, player->mapy, player->map))
			ray->hit = 1;
	}
	process_wall_hit(player, ray);
}

static void	cast_ray2(t_player *player, t_ray *ray)
{
	if (ray->dx < 0)
	{
		player->xoff = -1;
		ray->sdx = (player->px - player->mapx * player->map->tile_size) \
		/ player->map->tile_size * ray->ddx;
	}
	else
	{
		player->xoff = 1;
		ray->sdx = ((player->mapx + 1) * player->map->tile_size - player->px) \
		/ player->map->tile_size * ray->ddx;
	}
	if (ray->dy < 0)
	{
		player->yoff = -1;
		ray->sdy = (player->py - player->mapy * player->map->tile_size) \
		/ player->map->tile_size * ray->ddy;
	}
	else
	{
		player->yoff = 1;
		ray->sdy = ((player->mapy + 1) * player->map->tile_size - player->py) \
		/ player->map->tile_size * ray->ddy;
	}
	cast_ray3(player, ray);
}

static t_ray	*cast_ray(t_player *player, float angle)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->hit = 0;
	player->mapx = (int)player->px / player->map->tile_size;
	player->mapy = (int)player->py / player->map->tile_size;
	ray->dx = cosf(angle);
	ray->dy = sinf(angle);
	if (ray->dx == 0.0)
		ray->ddx = 1e30;
	else
		ray->ddx = fabsf(1 / ray->dx);
	if (ray->dy == 0.0)
		ray->ddy = 1e30;
	else
		ray->ddy = fabsf(1 / ray->dy);
	cast_ray2(player, ray);
	return (ray);
}

void	*cast_rays(t_data *data)
{
	t_ray	*ray;
	float	ray_angle;
	int		i;

	ray_angle = data->player->angle - 30 * DEG;
	i = 0;
	while (i < 240)
	{
		if (ray_angle < 0)
			ray_angle += 2 * PI;
		else if (ray_angle > 2 * PI)
			ray_angle -= 2 * PI;
		ray = cast_ray(data->player, ray_angle);
		if (!ray)
			return (NULL);
		ray->ray_angle = ray_angle;
		compute_wall_3d(data, ray, i);
		free(ray);
		i++;
		ray_angle += DEG / 4;
	}
	return (data);
}
