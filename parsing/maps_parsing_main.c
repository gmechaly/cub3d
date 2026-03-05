/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maps_parsing_main.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 16:54:49 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/29 00:39:50 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	handle_map_line(char *trimmed_line, bool *map_start, t_map *map)
{
	if (!*map_start && valid_map(trimmed_line))
	{
		*map_start = true;
		append_line_to_map(map, trimmed_line);
	}
	else
	{
		if (!valid_map(trimmed_line))
		{
			printf("error: invalid line in map: %s\n", trimmed_line);
			free(trimmed_line);
			exit(EXIT_FAILURE);
		}
		append_line_to_map(map, trimmed_line);
	}
}

static void	read_map_lines(int fd, t_map *map)
{
	char	*line;
	char	*trimmed_line;
	bool	map_start;

	map_start = false;
	line = get_next_line(fd);
	while (line)
	{
		trimmed_line = ft_strtrim(line, "\n");
		free (line);
		if (!trimmed_line || trimmed_line[0] == '\0')
		{
			free(trimmed_line);
			line = get_next_line(fd);
			continue ;
		}
		handle_map_line(trimmed_line, &map_start, map);
		free(trimmed_line);
		line = get_next_line(fd);
	}
}

char	**parse_map(char *path, t_map *map)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening .cub file");
		exit(EXIT_FAILURE);
	}
	map->map = NULL;
	read_map_lines(fd, map);
	close(fd);
	if (!map->map)
	{
		perror("error: no map found in file");
		exit(EXIT_FAILURE);
	}
	return (map->map);
}

bool	validate_map(t_map *map)
{
	if (!map)
		return (printf("Error: Map is empty\n"), false);
	if (!all_textures_defined(map))
		return (printf("Error: textures missing\n"), false);
	if (!all_colors_defined(map))
		return (printf("Error: colors missing\n"), false);
	return (true);
}
