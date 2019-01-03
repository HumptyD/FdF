/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/28 15:59:17 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/03 16:46:51 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		init_image(t_var c)
{
	c.image = mlx_new_image(c.mlx, W_WIDTH, W_HEIGHT);
	c.ptr = mlx_get_data_addr(c.image, &c.bpp, &c.size_line, &c.endian);
	c.bpp /= 8;
	print_map(c);
}

void		set_pixel(t_var *c, int x, int y, int color)
{
	if (x < 0 || x >= W_WIDTH || y < 0 || y >= W_HEIGHT)
		return ;
	*(int *)(c->ptr + (x + y * W_WIDTH) * c->bpp) = color;
}
