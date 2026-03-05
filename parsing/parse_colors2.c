/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 18:23:20 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/30 21:07:18 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_color(t_map *map, char *id, int color)
{
	if (ft_strncmp(id, "F", 1) == 0)
	{
		if (map->floor_color != -1)
			return (-1);
		map->floor_color = color;
	}
	else if (ft_strncmp(id, "C", 1) == 0)
	{
		if (map->ceiling_color != -1)
			return (-1);
		map->ceiling_color = color;
	}
	else
		return (-1);
	return (0);
}

static int	are_numbers(char **rgb)
{
	int	j;
	int	i;

	j = 0;
	while (rgb[j])
	{
		i = 0;
		while (rgb[j][i])
		{
			if (!ft_isdigit(rgb[j][i]))
				return (0);
			i++;
		}
		j++;
	}
	return (1);
}

static int	get_rgb_values(char *str, int *r, int *g, int *b)
{
	char	**rgb;

	rgb = ft_split(str, ',');
	if (check_rgb_split(rgb) == -1)
		return (ft_free_split(rgb), -1);
	if (!are_numbers(rgb))
		return (ft_free_split(rgb), -1);
	*r = ft_atoi(rgb[0]);
	*g = ft_atoi(rgb[1]);
	*b = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (!is_valid_rgb_value(*r) || !is_valid_rgb_value(*g) \
		|| !is_valid_rgb_value(*b))
		return (ft_free_split(rgb), -1);
	return (0);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

int	parse_color_line(char *line, t_map *map)
{
	char	**split;
	int		r;
	int		g;
	int		b;
	int		color;

	remove_trailing_newline(line);
	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (ft_free_split(split), -1);
	if (get_rgb_values(split[1], &r, &g, &b) == -1)
		return (ft_free_split(split), -1);
	color = rgb_to_int(r, g, b);
	if (set_color(map, split[0], color) == -1)
		return (ft_free_split(split), -1);
	ft_free_split(split);
	return (0);
}
