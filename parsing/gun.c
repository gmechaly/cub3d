/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gun.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:52:44 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/28 21:44:58 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_gun_frames(int i)
{
	if (i >= 0)
		return ("./sprites/gun_01.xpm");
	else
		return (NULL);
}

void	init_gun(t_gun *gun, void *mlx)
{
	int		i;
	char	*path;

	i = 0;
	while (i < GUN_FRAME_COUNT)
	{
		path = get_gun_frames(i);
		gun->frames[i] = mlx_xpm_file_to_image(mlx, path, &gun->width \
			, &gun->height);
		if (!gun->frames[i])
			printf("Error loading gun\n");
		i++;
	}
	gun->current_frame = 0;
	gun->frame_timer = 0;
	gun->frame_count = 0;
	gun->breath_phase = 0;
	gun->is_walking = 0;
	gun->frame_delay = GUN_FRAME_DELAY;
}

void	update_gun_animation(t_gun *gun)
{
	if (++gun->frame_timer >= gun->frame_delay)
	{
		gun->current_frame++;
		if (gun->current_frame >= GUN_FRAME_COUNT)
			gun->current_frame = 0;
		gun->frame_timer = 0;
	}
}

int	get_transparent_color(void *img)
{
	int		bpp;
	int		size_line;
	int		endian;
	char	*data;
	int		color;

	data = mlx_get_data_addr(img, &bpp, &size_line, &endian);
	color = *(unsigned int *)(data);
	return (color);
}
