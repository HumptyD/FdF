/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 14:41:18 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/04 20:03:55 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keyboard(int key, t_var *c)
{
	clear_image(c->img);
	if (key == 53)
		exit(0);
	if (key == 49)
	{
		init_default(c);
		c->opt->proection = c->opt->proection == 1 ? 0 : 1;
	}
	if (key == 87)
		c->ang.y += 0.0523599;
	if (key == 84)
		c->ang.y -= 0.0523599;
	if (key == 86)
		c->ang.x += 0.0523599;
	if (key == 83)
		c->ang.x -= 0.0523599;
	if (key == 88)
		c->ang.z += 0.0523599;
	if (key == 85)
		c->ang.z -= 0.0523599;
	if (key == 69)
		c->opt->size *= 1.1;
	if (key == 78)
		c->opt->size *= 0.9;
	if (key == 13)
		c->opt->vert -= 10;
	if (key == 1)
		c->opt->vert += 10;
	if (key == 0)
		c->opt->hor -= 10;
	if (key == 2)
		c->opt->hor += 10;
	print_map(*c);
	return (0);
}

int		mouse_press(int	button, int x, int y, t_var *c)
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

int		mouse_release(int button, int x, int y, t_var *c)
{
	(void)button;
	(void)x;
	(void)y;
	c->ms.pressed = 0;
	return (0);
}

int		mouse_move(int x, int y, t_var *c)
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
