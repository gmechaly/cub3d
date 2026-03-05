/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:53:22 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/28 22:08:58 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_texture_line(char *line)
{
	if (!line)
		return (false);
	return (ft_strncmp(line, "NO ", 3) == 0 || \
			ft_strncmp(line, "SO ", 3) == 0 || \
			ft_strncmp(line, "WE ", 3) == 0 || \
			ft_strncmp(line, "EA ", 3) == 0 || \
			ft_strncmp(line, "DO ", 3) == 0);
}

static int	dup_check_no_so_do(t_map *map, char *id, char *path)
{
	if (ft_strncmp(id, "NO", 2) == 0)
	{
		if (map->texture_no)
			return (printf("error: dup NO texture\n"), -1);
		map->texture_no = ft_strdup(path);
		return (0);
	}
	else if (ft_strncmp(id, "SO", 2) == 0)
	{
		if (map->texture_so)
			return (printf("error: dup SO texture\n"), -1);
		map->texture_so = ft_strdup(path);
		return (0);
	}
	else if (ft_strncmp(id, "DO", 2) == 0)
	{
		if (map->texture_door)
			return (-1);
		map->texture_door = ft_strdup(path);
		return (0);
	}
	return (2);
}

int	dup_check(t_map *map, char *id, char *path)
{
	if (access(path, F_OK) != 0)
		return (printf("error: texture file not found\n"), -1);
	if (dup_check_no_so_do(map, id, path) == 0)
		return (0);
	if (ft_strncmp(id, "EA", 2) == 0)
	{
		if (map->texture_ea)
			return (-1);
		map->texture_ea = ft_strdup(path);
		return (0);
	}
	else if (ft_strncmp(id, "WE", 2) == 0)
	{
		if (map->texture_we)
			return (-1);
		map->texture_we = ft_strdup(path);
		return (0);
	}
	return (-1);
}
