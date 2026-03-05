/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 18:26:33 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/28 20:57:02 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	valid_map(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '0' && line[i] != '1' && line[i] != ' ' \
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E' \
			&& line[i] != 'W' && line[i] != '\n' && line[i] != 'D')
			return (false);
		i++;
	}
	if (!ft_strcmp(line, "\n"))
		return (false);
	return (true);
}

static int	get_map_length(char **map)
{
	int	count;

	count = 0;
	if (!map)
		return (0);
	while (map[count])
		count++;
	return (count);
}

void	append_line_to_map(t_map *map, char *line)
{
	char	**new_map;
	int		count;
	int		i;
	char	*trimmed_line;

	trimmed_line = ft_strdup(line);
	remove_trailing_newline(trimmed_line);
	count = get_map_length(map->map);
	new_map = malloc(sizeof(char *) * (count + 2));
	if (!new_map)
		return (free(trimmed_line));
	i = -1;
	while (++i < count)
		new_map[i] = map->map[i];
	new_map[count] = trimmed_line;
	new_map[count + 1] = NULL;
	free(map->map);
	map->map = new_map;
}
