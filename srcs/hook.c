/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 14:41:18 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/05 21:18:11 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		keyboard2(int key, t_var *c)
{
	key == 87 ? c->ang.y += 0.0523599 : 0;
	key == 84 ? c->ang.y -= 0.0523599 : 0;
	key == 86 ? c->ang.x += 0.0523599 : 0;
	key == 83 ? c->ang.x -= 0.0523599 : 0;
	key == 88 ? c->ang.z += 0.0523599 : 0;
	key == 85 ? c->ang.z -= 0.0523599 : 0;
	key == 69 ? c->opt->size *= 1.1 : 0;
	key == 78 ? c->opt->size *= 0.9 : 0;
	key == 13 ? c->opt->vert -= 10 : 0;
	key == 1 ? c->opt->vert += 10 : 0;
	key == 0 ? c->opt->hor -= 10 : 0;
	key == 2 ? c->opt->hor += 10 : 0;
	key == 27 ? c->opt->w *= 1.1 : 0;
	if (key == 24)
	{
		c->opt->w *= 0.9;
		if (c->opt->w < c->opt->z0)
			c->opt->w = c->opt->z0;
		if (c->opt->w < c->w || c->opt->w < c->h)
			c->opt->w = c->w < c->h ? c->h : c->w;
	}
}

int			keyboard(int key, t_var *c)
{
	clear_image(c->img);
	key == 53 ? exit(0) : 0;
	if (key == 18)
	{
		init_default(c);
		c->opt->proection = 0;
	}
	if (key == 19)
	{
		init_default(c);
		c->opt->proection = 1;
	}
	if (key == 20)
	{
		init_default(c);
		c->opt->proection = 2;
	}
	keyboard2(key, c);
	print_map(*c);
	return (0);
}

int			mouse_press(int button, int x, int y, t_var *c)
{
	clear_image(c->img);
	if (x >= 0 && x <= W_WIDTH && y >= 0 && y <= W_HEIGHT)
	{
		if (button == 1)
		{
			c->ms.pressed = 1;
			c->ms.c_x = x;
			c->ms.c_y = y;
		}
		if (button == 5)
			c->opt->size *= 1.1;
		if (button == 4)
			c->opt->size *= 0.9;
		if (button == 4 || button == 5)
			print_map(*c);
	}
	return (0);
}

int			mouse_release(int button, int x, int y, t_var *c)
{
	(void)button;
	(void)x;
	(void)y;
	c->ms.pressed = 0;
	return (0);
}

int			mouse_move(int x, int y, t_var *c)
{
	clear_image(c->img);
	if (x >= 0 && x <= W_WIDTH && y >= 0 && y <= W_HEIGHT)
	{
		c->ms.p_x = c->ms.c_x;
		c->ms.p_y = c->ms.c_y;
		c->ms.c_x = x;
		c->ms.c_y = y;
		if (c->ms.pressed)
		{
			c->ang.x += (c->ms.p_y - y) / 150;
			c->ang.y -= (c->ms.p_x - x) / 150;
		}
		if (c->ms.pressed)
			print_map(*c);
	}
	return (0);
}
