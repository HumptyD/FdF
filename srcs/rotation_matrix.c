/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 18:31:59 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/03 19:45:27 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	init_ang_mid(t_point *mid, t_var *c)
{
	mid->x = c->w / 2;
	mid->y = c->h / 2;
	mid->z = 0.;
}

void		rotation_matrix(t_point *dot, t_point ang, t_var *c)
{
	t_point	mid;
	t_point v;
//	int		scale;

	init_ang_mid(&mid, c);
	v.x = mid.x + cos(ang.y) * (dot->x - mid.x) + sin(ang.y) * (dot->z - mid.z);
	v.z = mid.z - sin(ang.y) * (dot->x - mid.x) + cos(ang.y) * (dot->z - mid.z);
	dot->z = v.z;
	v.y = mid.y + cos(ang.x) * (dot->y - mid.y) - sin(ang.x) * (dot->z - mid.z);
	v.z = mid.z + sin(ang.x) * (dot->y - mid.y) - cos(ang.x) * (dot->z - mid.z);


/*    one.x = mid.x + cos(ang.y) * cos(ang.z) * (dot->x - mid.x) -
            cos(ang.y) * sin(ang.z) * (dot->y - mid.y) + sin(ang.y) * (dot->z - mid.z);
   	one.y  = mid.y + (sin(ang.x) * sin(ang.y) * cos(ang.z) +
            cos(ang.x) * sin(ang.z)) * (dot->x - mid.x) + (cos(ang.x) * cos(ang.z) -
            sin(ang.x) * sin(ang.y) * sin(ang.z)) * (dot->y - mid.y) -
            sin(ang.x) * cos(ang.y) * (dot->z - mid.z);

*/
/*	one.x = dot->x;
	one.z = dot->z;
	dot->x = mid.x + cos(ang.y) * (one.x - mid.x) +
		sin(ang.y) * (one.z - mid.z);
	dot->z = mid.z - sin(ang.y) * (one.x - mid.x) +
		cos(ang.y) * (one.z - mid.z);
	one.y = dot->y;
	one.z = dot->z;
	dot->y = mid.y + cos(ang.x) * (one.y - mid.y) -
		sin(ang.x) * (one.z - mid.z);
	dot->z = mid.z + sin(ang.x) * (one.y - mid.y) +
		cos(ang.x) * (one.z - mid.z);
	one.x = dot->x;
	one.y = dot->y;
	dot->x = mid.x + cos(ang.z) * (one.x - mid.x) -
		sin(ang.z) * (one.y - mid.y);
	dot->y = mid.y + sin(ang.z) * (one.x - mid.x) +
		cos(ang.z) * (one.y - mid.y);
*/
	dot->x = v.x;
	dot->y = v.y;
	dot->z = v.z;
//	scale = c->w > c->h ? (W_WIDTH / c->w) / 2 :
//		(W_HEIGHT / c->h) / 2;
	dot->x *= c->scale;
	dot->y *= c->scale;
	dot->z *= c->scale;
//	dot->x = dot->x + (W_WIDTH - scale * c->w) / 2 + c->hor;
//	dot->y = dot->y + (W_HEIGHT - scale * c->h) / 2 + c->vert;
	dot->x = dot->x + (W_WIDTH / 2) - (c->w * c->scale) / 2 + c->hor;
	dot->y = dot->y + (W_HEIGHT / 2) - (c->h * c->scale) / 2 + c->vert;
}
