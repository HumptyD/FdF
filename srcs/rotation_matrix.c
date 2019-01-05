/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:31:59 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/05 17:52:34 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	apply_scale(t_point *dot, t_var *c)
{
	c->opt->scale = c->w > c->h ? ((double)W_WIDTH / c->w) / 2 :
		((double)W_HEIGHT / c->h) / 2;
	dot->x *= c->opt->scale * c->opt->size;
	dot->y *= c->opt->scale * c->opt->size;
	dot->z *= c->opt->scale * c->opt->size;
	dot->x = dot->x + W_WIDTH / 2 + c->opt->hor;
	dot->y = dot->y + W_HEIGHT / 2 + c->opt->vert;
}

static void apply_scale_iso(t_point *dot, t_var *c)
{
	dot->x *= c->opt->iso_scale * c->opt->size;
	dot->y *= c->opt->iso_scale * c->opt->size;
	dot->z *= c->opt->iso_scale * c->opt->size;
	dot->x = dot->x + W_WIDTH / 2 + c->opt->hor;
	dot->y = dot->y + W_HEIGHT / 2 + c->opt->vert;
}

void		rotation_matrix(t_point *dot, t_point ang, t_var *c)
{
	t_point v;

	dot->x -= c->opt->x0;
	dot->y -= c->opt->y0;
	if (c->opt->min >= 0)
		dot->z -= c->opt->z0 / 2;
	v.x = dot->x;
	v.z = dot->z;
	dot->x = cos(ang.y) * v.x + sin(ang.y) * v.z;
	dot->z = -sin(ang.y) * v.x + cos(ang.y) * v.z;
	v.y = dot->y;
	v.z = dot->z;
	dot->y = cos(ang.x) * v.y - sin(ang.x) * v.z;
	dot->z = sin(ang.x) * v.y + cos(ang.x) * v.z;
	v.x = dot->x;
	v.y = dot->y;
	dot->x = cos(ang.z) * v.x - sin(ang.z) * v.y;
	dot->y = sin(ang.z) * v.x + cos(ang.z) * v.y;
	v.x = dot->x;
	v.y = dot->y;
	v.z = dot->z;
	if (c->opt->proection % 3 == 1)
	{
		dot->x = v.x * 0.8660 - v.y * 0.8660;
		dot->y = v.x / 2 + v.y / 2 - v.z;
		apply_scale_iso(dot, c);
	}
	else if (c->opt->proection % 3 == 2)
	{
		dot->x = v.x * c->opt->w / (c->opt->w - v.z);
		dot->y = v.y * c->opt->w / (c->opt->w - v.z);
		apply_scale_iso(dot, c);
	}
	else
		apply_scale(dot, c);
}
