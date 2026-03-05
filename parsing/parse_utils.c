/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:54:09 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/28 22:14:35 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	all_textures_defined(t_map *map)
{
	if (!map->texture_no)
		printf("Missing NO texture\n");
	if (!map->texture_so)
		printf("Missing SO texture\n");
	if (!map->texture_we)
		printf("Missing WE texture\n");
	if (!map->texture_ea)
		printf("Missing EA texture\n");
	if (map->floor_color == -1)
		printf("Missing floor color\n");
	if (map->ceiling_color == -1)
		printf("Missing ceiling color\n");
	return (map->texture_no && map->texture_so && \
		map->texture_we && map->texture_ea \
		&& map->floor_color != -1 && map->ceiling_color != -1);
}

bool	all_colors_defined(t_map *map)
{
	return (map->floor_color != -1 && map->ceiling_color != -1);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (!split)
		return ;
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
