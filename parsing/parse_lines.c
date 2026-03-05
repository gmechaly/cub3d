/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lines.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 20:24:48 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/30 20:58:52 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_line(char *line, t_map *map, bool *in_map, char **map_str)
{
	char	*trimmed;
	int		result;

	trimmed = ft_strtrim(line, " \t\n\r");
	if (!line || !map || !trimmed)
		return (-1);
	if (*in_map)
	{
		if (valid_map(line))
			return (free(trimmed), append_to_map(map_str, line), 0);
		else if (line[0] == '\n' || line[0] == '\0')
			return (free(trimmed), printf("error: blank line in map\n"), -1);
	}
	if (trimmed[0] == '\0')
		return (free(trimmed), 0);
	result = process_texture_colors(trimmed, map);
	if (result != -1)
		return (free(trimmed), result);
	if (valid_map(trimmed))
	{
		*in_map = true;
		append_to_map(map_str, line);
		return (free(trimmed), 0);
	}
	return (printf("error line in map: %s\n", trimmed), free(trimmed), -1);
}
