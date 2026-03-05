/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:57:10 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/28 21:44:45 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_fill_char(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || \
		c == 'E' || c == 'W' || c == 'D');
}

bool	out_of_bounds(t_map *map, int y, int x)
{
	return (y < 0 || x < 0 || !map->map[y] || x >= (int)ft_strlen(map->map[y]));
}

int	count_map_rows(t_map *map)
{
	int	i;

	i = 0;
	while (map->map && map->map[i])
		i++;
	return (i);
}

int	longest_row_len(t_map *map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map->map && map->map[i])
	{
		len = ft_strlen(map->map[i]);
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}
