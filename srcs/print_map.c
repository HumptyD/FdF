/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:42:55 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/06 13:38:20 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_color(t_var *c)
{
	double	third;

	if (!c->opt->is_color)
	{
		third = c->opt->z0 / 3;
		if (c->a.z < 0)
			c->a.color = 0x4C2908;
		else if (c->a.z <= third)
			c->a.color = 0xDB4A4A;
		else if (c->a.z <= third * 2)
			c->a.color = 0xD67022;
		else if (c->a.z <= c->opt->z0)
			c->a.color = 0xE5D120;
		if (c->b.z < 0)
			c->b.color = 0x4C2908;
		else if (c->b.z <= third)
			c->b.color = 0xDB4A4A;
		else if (c->b.z <= third * 2)
			c->b.color = 0xD67022;
		else if (c->b.z <= c->opt->z0)
			c->b.color = 0xE5D120;
	}
}

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
			set_pixel(c, var->y, var->x,
					get_color(c->a.color, c->b.color, *percent))
			: set_pixel(c, var->x, var->y,
					get_color(c->a.color, c->b.color, *percent));
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
		set_color(&c);
		rotation_matrix(&c.a, c.ang, &c);
		rotation_matrix(&c.b, c.ang, &c);
		put_line(&c);
		c.seg = c.seg->next;
	}
	mlx_put_image_to_window(c.mlx, c.win, c.img->image, 0, 0);
	mlx_string_put(c.mlx, c.win,
			50, 50, 0xFFFFFF, "Move the figure - W, A, S, D");
	mlx_string_put(c.mlx, c.win,
			50, 65, 0xFFFFFF, "X rotation - num 4, 1");
	mlx_string_put(c.mlx, c.win, 50, 80, 0xFFFFFF, "Y rotation - num 5, 2");
	mlx_string_put(c.mlx, c.win, 50, 95, 0xFFFFFF, "Z rotation - num 6, 3");
	mlx_string_put(c.mlx, c.win,
			50, 110, 0xFFFFFF, "Scale - num +, num -, mouse scroll");
	mlx_string_put(c.mlx, c.win,
			50, 125, 0xFFFFFF, "Change proection - 1, 2, 3");
	mlx_string_put(c.mlx, c.win,
			50, 140, 0xFFFFFF, "X, Y rotation - mouse left button");
	mlx_string_put(c.mlx, c.win, 50, 155, 0xFFFFFF, "Distance - +, -");
}
