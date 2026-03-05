/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 16:41:26 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/25 16:57:33 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	move_straight(t_data *data)
{
	float	next_px;
	float	next_py;

	next_px = data->player->px + 0.1 * data->player->dx * \
	data->player->move_straight;
	next_py = data->player->py + 0.1 * data->player->dy * \
	data->player->move_straight;
	if (data->map->map[(int)(data->player->py / data->map->tile_size)][(int) \
	(next_px / data->map->tile_size)] == '0')
		data->player->px = next_px;
	if (data->map->map[(int)(next_py / data->map->tile_size)][(int) \
	(data->player->px / data->map->tile_size)] == '0')
		data->player->py = next_py;
	return (1);
}

int	move_angle(t_data *data, float da)
{
	data->player->angle += da;
	if (data->player->angle < 0)
		data->player->angle += 2 * PI;
	else if (data->player->angle > 2 * PI)
		data->player->angle -= 2 * PI;
	data->player->dx = cos(data->player->angle) * 5;
	data->player->dy = sin(data->player->angle) * 5;
	return (1);
}

static int	move_side(t_data *data)
{
	float	next_px;
	float	next_py;
	float	side_dx;
	float	side_dy;

	side_dx = data->player->dy;
	side_dy = -data->player->dx;
	next_px = data->player->px + 0.08 * side_dx * \
	(-data->player->move_side);
	next_py = data->player->py + 0.08 * side_dy * \
	(-data->player->move_side);
	if (data->map->map[(int)(data->player->py / data->map->tile_size)][(int) \
	(next_px / data->map->tile_size)] == '0')
		data->player->px = next_px;
	if (data->map->map[(int)(next_py / data->map->tile_size)][(int) \
	(data->player->px / data->map->tile_size)] == '0')
		data->player->py = next_py;
	return (1);
}

int	move_player(t_data *data)
{
	int	moved;

	moved = 0;
	if (data->player->move_straight == 1)
		moved += move_straight(data);
	if (data->player->move_straight == -1)
		moved += move_straight(data);
	if (data->player->move_side == 1)
		moved += move_side(data);
	if (data->player->move_side == -1)
		moved += move_side(data);
	if (data->player->rotate == 1)
		moved += move_angle(data, 0.015);
	if (data->player->rotate == -1)
		moved += move_angle(data, -0.015);
	if (data->player->mouse_moved == 1)
	{
		moved++;
		data->player->mouse_moved = 0;
	}
	if (data->player->e_pressed)
		moved += e_press(data);
	return (moved);
}
