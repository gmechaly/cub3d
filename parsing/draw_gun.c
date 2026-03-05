/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 22:55:52 by rdalal            #+#    #+#             */
/*   Updated: 2025/07/28 20:52:33 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_gun_ani(t_gun *gun, int *sx, int *sy)
{
	float	breath;
	float	walk_bob;
	float	sway;

	gun->breath_phase += BREATH_SPEED;
	breath = sinf(gun->breath_phase) * 2.0f * BREATH_AMPLITUDE;
	walk_bob = 0.0f;
	sway = sinf(gun->frame_count * 0.1f) * 12.0f;
	if (gun->is_walking)
		walk_bob = (sinf(gun->frame_count * 0.3f) + 1.0f) / 2.0f * BOB_HEIGHT;
	*sx = (LSIZE / 2) - (gun->width / 2) + (int)sway;
	*sy = HSIZE - gun->height + 3 + (int)(breath + walk_bob + 0.5f);
}

static int	get_color(char *data, int x, int y, t_gun *gun)
{
	int	offset;

	offset = y * gun->size_line + x * (gun->bpp / 8);
	return (*(unsigned int *)(data + offset));
}

static void	draw_pixels(t_gun *gun, t_img *img, int sx, int sy)
{
	int		x;
	int		y;
	int		color;
	char	*data;

	data = mlx_get_data_addr(gun->frames[gun->current_frame], \
		&gun->bpp, &gun->size_line, &gun->endian);
	gun->transp = get_transparent_color(gun->frames[gun->current_frame]);
	y = -1;
	while (++y < gun->height)
	{
		x = -1;
		while (++x < gun->width)
		{
			color = get_color(data, x, y, gun);
			if (color != gun->transp && sy + y < HSIZE)
				ft_mlx_pixel_put(img, sx + x, sy + y, color);
		}
	}
}

void	draw_gun(t_gun *gun, t_img *img)
{
	int		sx;
	int		sy;

	get_gun_ani(gun, &sx, &sy);
	draw_pixels(gun, img, sx, sy);
	gun->frame_count++;
}
