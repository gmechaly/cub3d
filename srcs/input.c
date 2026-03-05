/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 19:05:54 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/30 22:11:11 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	e_press(t_data *data)
{
	float	next_px;
	float	next_py;
	float	too_close_x;
	float	too_close_y;

	next_px = data->player->px + 6.5 * data->player->dx;
	next_py = data->player->py + 6.5 * data->player->dy;
	too_close_x = data->player->px + data->player->dx;
	too_close_y = data->player->py + data->player->dy;
	if (data->map->map[(int)(next_py / data->map->tile_size)][(int) \
	(next_px / data->map->tile_size)] == 'D')
	{
		data->map->map[(int)(next_py / data->map->tile_size)][(int) \
	(next_px / data->map->tile_size)] = '0';
	}
	else if (data->map->map[(int)(too_close_y / data->map->tile_size)] \
	[(int)(too_close_x / data->map->tile_size)] == 'D')
	{
		data->map->map[(int)(too_close_y / data->map->tile_size)][(int) \
	(too_close_x / data->map->tile_size)] = '0';
	}
	return (1);
}

static int	handle_key_press(int keysim, t_data *data)
{
	if (keysim == XK_Escape)
		quit_program(data);
	if (keysim == 119)
		data->player->move_straight = 1;
	if (keysim == 115)
		data->player->move_straight = -1;
	if (keysim == 97)
		data->player->move_side = -1;
	if (keysim == 100)
		data->player->move_side = 1;
	if (keysim == XK_Right)
		data->player->rotate = 1;
	if (keysim == XK_Left)
		data->player->rotate = -1;
	if (keysim == XK_e)
		data->player->e_pressed = 1;
	return (0);
}

static int	handle_key_release(int keysim, t_data *data)
{
	if (keysim == XK_Escape)
		quit_program(data);
	if (keysim == 119 && data->player->move_straight == 1)
		data->player->move_straight = 0;
	if (keysim == 115 && data->player->move_straight == -1)
		data->player->move_straight = 0;
	if (keysim == 97 && data->player->move_side == -1)
		data->player->move_side = 0;
	if (keysim == 100 && data->player->move_side == 1)
		data->player->move_side = 0;
	if (keysim == XK_Right && data->player->rotate >= 1)
		data->player->rotate = 0;
	if (keysim == XK_Left && data->player->rotate <= -1)
		data->player->rotate = 0;
	if (keysim == XK_e && data->player->e_pressed == 1)
		data->player->e_pressed = 0;
	return (0);
}

static int	handle_mouse(int x, int y, t_data *data)
{
	static int	x_save;

	(void)y;
	if (!x_save)
		x_save = x;
	if (x < x_save)
		move_angle(data, -0.03);
	if (x > x_save)
		move_angle(data, 0.03);
	x_save = x;
	data->player->mouse_moved = 1;
	return (0);
}

void	handle_input(t_data *data)
{
	mlx_mouse_move(data->mlx, data->window, LSIZE / 2, HSIZE / 2);
	mlx_hook(data->window, KeyPress, KeyPressMask, handle_key_press, data);
	mlx_hook(data->window, MotionNotify, PointerMotionMask, \
	&handle_mouse, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, \
	handle_key_release, data);
}
