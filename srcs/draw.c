/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdalal <rdalal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 20:03:10 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/30 22:10:34 by rdalal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw(t_data *data)
{
	static int	i;

	if (!move_player(data) && i != 0)
		return (draw_gun(&data->gun, data->win_img), 0);
	if (i == 0)
		i = 1;
	draw_background(data);
	copy_image(data->map_img, data->win_img, LSIZE, HSIZE);
	cast_rays(data);
	draw_minimap(data);
	update_gun_animation(&data->gun);
	draw_gun(&data->gun, data->win_img);
	mlx_put_image_to_window((*data).mlx, (*data).window, \
	(*(*data).win_img).image, 0, 0);
	return (0);
}

void	draw_line_from_player(int xb, int yb, t_data *data)
{
	int		xa;
	int		ya;
	int		ix;
	int		iy;
	float	i;

	i = 0.0;
	xa = data->player->px;
	ya = data->player->py;
	if (xa == xb && ya == yb)
		return ;
	while (i <= 1.0)
	{
		ix = (int)(xa + (xb - xa) * i);
		iy = (int)(ya + (yb - ya) * i);
		if (!ft_mlx_pixel_put(data->win_img, ix, iy, RED))
			return ;
		i += 0.01;
	}
}
