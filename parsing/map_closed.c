/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_closed.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 18:14:35 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/28 20:54:24 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	flood_fill(t_map *map, char **visited, int y, int x)
{
	char	current;

	if (out_of_bounds(map, y, x))
		return (0);
	current = map->map[y][x];
	if (current == ' ')
		return (0);
	if (current == '1')
		return (1);
	if (!is_valid_fill_char(current))
		return (0);
	if (visited[y][x])
		return (1);
	visited[y][x] = 1;
	if (!flood_fill(map, visited, y - 1, x))
		return (0);
	if (!flood_fill(map, visited, y + 1, x))
		return (0);
	if (!flood_fill(map, visited, y, x - 1))
		return (0);
	if (!flood_fill(map, visited, y, x + 1))
		return (0);
	return (1);
}

static void	free_visited(char **visited, int h)
{
	int	i;

	i = 0;
	while (i < h)
	{
		free(visited[i]);
		i++;
	}
	free (visited);
}

static char	**alloc_visited(t_map *map)
{
	int		y;
	char	**visited;

	visited = malloc(sizeof(char *) * map->height);
	if (!visited)
		return (NULL);
	y = 0;
	while (y < map->height)
	{
		visited[y] = ft_calloc(ft_strlen(map->map[y]) + 1, sizeof(char));
		if (!visited[y])
		{
			free_visited(visited, y);
			return (NULL);
		}
		y++;
	}
	return (visited);
}

bool	is_enclosed(t_map *map)
{
	int		y;
	int		x;
	char	**visited;

	y = 0;
	visited = alloc_visited(map);
	if (!visited)
		return (false);
	while (map->map[y])
	{
		x = 0;
		while (map->map[y][x])
		{
			if (map->map[y][x] == 'N' || map->map[y][x] == 'S' || \
				map->map[y][x] == 'E' || map->map[y][x] == 'W')
			{
				if (!flood_fill(map, visited, y, x))
					return (free_visited(visited, map->height), false);
				return (free_visited(visited, map->height), true);
			}
			x++;
		}
		y++;
	}
	return (free_visited(visited, map->height), false);
}
