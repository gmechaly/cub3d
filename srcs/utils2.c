/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 17:11:13 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/25 17:11:54 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(int x, int y, t_map *map)
{
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (1);
	if (map->map[y][x] == '1' || map->map[y][x] == 'D')
		return (1);
	return (0);
}
