/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmechaly <gmechaly@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 17:24:38 by gmechaly          #+#    #+#             */
/*   Updated: 2025/07/25 17:15:42 by gmechaly         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > 1024 || y > 512)
		return (NULL);
	dst = img->ptr_image + \
	(y * img->size_line + x * (img->bpp / 8));
	*(unsigned int *) dst = color;
	return (img);
}

void	copy_image(t_img *src, t_img *dst, int width, int height)
{
	int		x;
	int		y;
	int		offset_src;
	int		offset_dst;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			offset_src = y * src->size_line + x * (src->bpp / 8);
			offset_dst = y * dst->size_line + x * (dst->bpp / 8);
			ft_memcpy(dst->ptr_image + offset_dst, \
			src->ptr_image + offset_src, src->bpp / 8);
			x++;
		}
		y++;
	}
}

int	is_valid_coordinates(int x, int y)
{
	if (x < 0 || y < 0)
		return (0);
	if (x > LSIZE || y > HSIZE)
		return (0);
	return (1);
}

float	min(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

int	get_texture_pixel(t_tex *texture, int x, int y)
{
	char	*dst;

	if (x < 0)
		x = 0;
	if (x >= texture->wall_width)
		x = texture->wall_width - 1;
	if (y < 0)
		y = 0;
	if (y >= texture->wall_height)
		y = texture->wall_height - 1;
	dst = texture->img_struct->ptr_image + \
	(y * texture->img_struct->size_line + x * (texture->img_struct->bpp / 8));
	return (*(unsigned int *)dst);
}
