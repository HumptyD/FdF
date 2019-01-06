/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 15:59:17 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/06 13:26:21 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		init_image(t_var *c)
{
	c->img->image = mlx_new_image(c->mlx, W_WIDTH, W_HEIGHT);
	c->img->ptr = mlx_get_data_addr(c->img->image,
			&c->img->bpp, &c->img->size_line, &c->img->endian);
	c->img->bpp /= 8;
	print_map(*c);
}

void		set_pixel(t_var *c, int x, int y, int color)
{
	if (x < 0 || x >= W_WIDTH || y < 0 || y >= W_HEIGHT)
		return ;
	*(int *)(c->img->ptr + (x + y * W_WIDTH) * c->img->bpp) = color;
}

void		clear_image(t_img *img)
{
	ft_bzero(img->ptr, W_WIDTH * W_HEIGHT * img->bpp);
}
