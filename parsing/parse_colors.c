/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:04:46 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/21 18:28:35 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_valid_rgb_value(int val)
{
	return (val >= 0 && val <= 255);
}

bool	is_color_line(char *line)
{
	if (!line)
		return (false);
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

int	check_rgb_split(char **rgb)
{
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
	{
		ft_free_split(rgb);
		return (-1);
	}
	return (0);
}
