/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:42:55 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/03 19:45:25 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	display_p(t_var *c, t_pline *var, double *percent)
{
	int		dx;
	dx = c->b.x - c->a.x;
	while (++var->x <= c->b.x)
	{
		*percent = ABS(c->a.x - c->b.x) > ABS(c->a.y - c->b.y) ?
			ft_ilerp(var->x, c->a.x, c->b.x) :
			ft_ilerp(var->y, c->a.y, c->b.y);
		(var->steep) ?
			set_pixel(c, var->y, var->x, get_color(c->a.color, c->b.color, *percent))
			: set_pixel(c, var->x, var->y, get_color(c->a.color, c->b.color, *percent));
		var->error += var->derror;
		if (var->error > dx)
		{
			var->y += (c->b.y > c->a.y) ? 1 : -1;
			var->error -= dx * 2;
		}
	}
}

void		put_line(t_var *c)
{
	t_pline	var;
	double	percent;

	var.steep = 0;
	if (ABS(c->a.x - c->b.x) < ABS(c->a.y - c->b.y))
	{
		ft_swap_d(&c->a.x, &c->a.y);
		ft_swap_d(&c->b.x, &c->b.y);
		var.steep = 1;
	}
	if (c->a.x > c->b.x)
	{
		ft_swap_d(&c->a.x, &c->b.x);
		ft_swap_d(&c->a.y, &c->b.y);
		ft_swap(&c->a.color, &c->b.color);
	}
	var.derror = ABS((c->b.y - c->a.y)) * 2;
	var.error = 0;
	var.y = c->a.y;
	var.x = c->a.x - 1;
	display_p(c, &var, &percent);
}

void		print_map(t_var c)
{
	while (c.seg)
	{
		c.a = *((t_line *)c.seg->content)->a;
		c.b = *((t_line *)c.seg->content)->b;
		rotation_matrix(&c.a, c.ang, &c);
		rotation_matrix(&c.b, c.ang, &c);
		put_line(&c);
		c.seg = c.seg->next;
	}
	mlx_put_image_to_window(c.mlx, c.win, c.image, 0, 0);
}

void		init_map(t_var *c)
{
	(c->ang).x = 0.;
	(c->ang).y = 0.;
	(c->ang).z = 0.;
	c->scale = c->w > c->h ? (W_WIDTH / c->w) / 2 : (W_HEIGHT / c->h) / 2;
	c->scale = c->scale < 1 ? 1 : c->scale;
	c->hor = 0;
	c->vert = 0;
	c->ms.pressed = 0;
}
