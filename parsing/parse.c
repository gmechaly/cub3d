/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:54:02 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/29 01:07:54 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	process_texture_colors(char *trimmed, t_map *map)
{
	if (is_texture_line(trimmed))
		return (parse_texture_line(trimmed, map));
	if (is_color_line(trimmed))
		return (parse_color_line(trimmed, map));
	return (-1);
}

void	append_to_map(char **map_str, char *line)
{
	char	*temp;

	temp = ft_strjoin(*map_str, line);
	free(*map_str);
	*map_str = ft_strjoin(temp, "\n");
	free(temp);
}

static int	read_file_lines(int fd, t_map *map, char **map_str)
{
	char	*line;
	bool	in_map;
	int		status;

	in_map = false;
	line = get_next_line(fd);
	while (line)
	{
		status = process_line(line, map, &in_map, map_str);
		free(line);
		if (status == -1)
			return (-1);
		line = get_next_line(fd);
	}
	return (0);
}

int	parse_file(char *filename, t_map *map)
{
	int		fd;
	char	*map_str;
	int		status;

	map_str = ft_strdup("");
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (perror("error opening file"), -1);
	status = read_file_lines(fd, map, &map_str);
	close (fd);
	if (status == -1)
		return (free(map_str), -1);
	if (!all_textures_defined(map) || !all_colors_defined(map))
		return (free(map_str), printf("error: missing texture defs\n"), -1);
	if (!map_str || map_str[0] == '\0')
		return (free(map_str), printf("error: no map found\n"), -1);
	if (map->map)
		free_map_array(map->map);
	map->map = ft_split(map_str, '\n');
	if (!validate_full_map(map))
		return (free(map_str), -1);
	return (free(map_str), 0);
}
