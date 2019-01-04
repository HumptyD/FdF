/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 16:08:01 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/04 22:17:38 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	get_iso_scale(t_var *c)
{
	double	x;
	double	y;

	x = sqrt(c->w * c->w + c->h * c->h + 2 * c->w * c->h * cos(2.0944));
	y = c->opt->z0 + sqrt(c->w * c->w + c->h * c->h + 2 * c->w * c->h * cos(1.0472)) / 2;
	x = W_WIDTH / x * 0.9;
	y = W_HEIGHT / y * 0.9;
	c->opt->iso_scale = x > y ? y : x;
}

void		init_var(t_var *c)
{
	c->ang.x = 0.;
	c->ang.y = 0.;
	c->ang.z = 0.;
	c->img = ft_memalloc(sizeof(t_img));
	c->opt = ft_memalloc(sizeof(t_options));
	c->opt->size = 1;
	c->opt->hor = 0;
	c->opt->vert = 0;
	c->opt->min = 2147483647;
	c->opt->max = -2147483648;
	c->opt->is_color = 0;
	c->opt->proection = 0;
	c->opt->z0 = 0.;
	c->ms.pressed = 0;
	c->h = 0;
	c->w = -1;
	c->seg = NULL;
}

void		init_map(t_var *c)
{
	c->opt->z0 = c->opt->max + ABS(c->opt->min);
	c->opt->x0 = c->w / 2;
	c->opt->y0 = c->h / 2;
	get_iso_scale(c);
}

void		init_default(t_var *c)
{
	c->ang.x = 0.;
	c->ang.y = 0.;
	c->ang.z = 0.;
	c->opt->size = 1;
	c->opt->hor = 0;
	c->opt->vert = 0;
}
