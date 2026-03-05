/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:54:06 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/29 01:14:16 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_direction(t_player *player, char dir)
{
	if (dir == 'N')
		player->angle = 3 * PI / 2;
	else if (dir == 'S')
		player->angle = PI / 2;
	else if (dir == 'E')
		player->angle = 0;
	else if (dir == 'W')
		player->angle = PI;
	player->dx = cos(player->angle) * 5;
	player->dy = sin(player->angle) * 5;
	player->move_straight = 0;
	player->rotate = 0;
	player->move_side = 0;
	player->mouse_moved = 0;
	player->e_pressed = 0;
}

int	init_player_from_map(t_player *plr)
{
	int	y;
	int	x;

	if (!plr->map->map || !plr)
		return (-1);
	y = 0;
	while (plr->map->map[y])
	{
		x = 0;
		while (plr->map->map[y][x])
		{
			if (plr->map->map[y][x] == 'N' || plr->map->map[y][x] == 'S' ||
				plr->map->map[y][x] == 'E' || plr->map->map[y][x] == 'W')
			{
				plr->px = x * plr->map->tile_size + (plr->map->tile_size / 2);
				plr->py = y * plr->map->tile_size + (plr->map->tile_size / 2);
				set_player_direction(plr, plr->map->map[y][x]);
				plr->map->map[y][x] = '0';
				return (0);
			}
			x++;
		}
		y++;
	}
	return (-1);
}
