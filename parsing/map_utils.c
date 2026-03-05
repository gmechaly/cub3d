/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:21:52 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/30 21:15:43 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	has_one_player(t_map *map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' ||
				map->map[i][j] == 'E' || map->map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count == 1);
}

static bool	valid_map_chars(t_map *map)
{
	int	i;
	int	j;

	if (!map || !map->map)
		return (false);
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '0' && map->map[i][j] != '1' &&
				map->map[i][j] != ' ' && map->map[i][j] != 'N' &&
				map->map[i][j] != 'S' && map->map[i][j] != 'E' &&
				map->map[i][j] != 'W' && map->map[i][j] != 'D')
			{
				printf("invalid char found: %c (ASCII: %d) at [%d][%d]\n", \
					map->map[i][j], map->map[i][j], i, j);
				return (false);
			}
			j++;
		}
		i++;
	}
	return (true);
}

static bool	has_door(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'D')
				return (true);
			j++;
		}
		i++;
	}
	return (false);
}

bool	validate_full_map(t_map *map)
{
	if (!valid_map_chars(map))
	{
		printf("Invalid chars in map\n");
		return (false);
	}
	if (!has_one_player(map))
	{
		printf("Map needs one player\n");
		return (false);
	}
	if (!is_enclosed(map))
	{
		printf("Map is not valid\n");
		return (false);
	}
	if (has_door(map) && !map->texture_door)
	{
		printf("Insert door texture DO in .cub file\n");
		return (false);
	}
	if (!has_door(map) && map->texture_door)
	{
		printf("Insert door in the map or DO texture will be ignored\n");
	}
	return (true);
}
