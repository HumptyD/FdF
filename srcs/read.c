/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 19:46:48 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/05 21:04:23 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#define ME "error: memory is not allocated"

static int		read_color(char *str, t_var *c)
{
	int	res;

	res = 0xFFFFFF;
	if (str)
	{
		res = ft_atoi_base(++str, 16);
		c->opt->is_color = 1;
	}
	return (res);
}

static t_list	*get_segments(t_list **lst, int size)
{
	t_seg	v;

	v.n = 1;
	v.copy = *lst;
	v.segment = NULL;
	while (v.copy)
	{
		v.s.a = v.copy->content;
		if ((v.obj = ft_lst_n(v.copy, size)))
		{
			v.s.b = v.obj->content;
			display_error(!(v.temp = ft_lstnew(&v.s, sizeof(t_line))), ME);
			ft_lstadd(&v.segment, v.temp);
		}
		if (v.n % size != 0)
			if ((v.obj = ft_lst_n(v.copy, 1)))
			{
				v.s.b = v.obj->content;
				display_error(!(v.temp = ft_lstnew(&v.s, sizeof(t_line))), ME);
				ft_lstadd(&v.segment, v.temp);
			}
		v.n++;
		v.copy = v.copy->next;
	}
	return (v.segment);
}

static void		save_coords(char **td_arr, t_list **lst, int y, t_var *c)
{
	int		x;
	t_point	point;
	t_list	*temp;

	x = -1;
	while (td_arr[++x])
	{
		point.x = x;
		point.y = y;
		point.z = ft_atoi(td_arr[x]);
		if (point.z > c->opt->max)
			c->opt->max = point.z;
		if (point.z < c->opt->min)
			c->opt->min = point.z;
		point.color = read_color(ft_strchr(td_arr[x], ','), c);
		temp = ft_lstnew(&point, sizeof(t_point));
		display_error(!temp, ME);
		ft_lstadd(lst, temp);
	}
}

static int		count_points(char **td_arr)
{
	int	i;

	i = 0;
	while (td_arr[i])
		i++;
	return (i);
}

void			read_map(int fd, t_list **lst, t_var *c)
{
	char	*line;
	char	**td_arr;

	while (get_next_line(fd, &line))
	{
		display_error(!(td_arr = ft_strsplit(line, ' ')), ME);
		if (c->w == -1)
			c->w = count_points(td_arr);
		display_error((c->w != count_points(td_arr)), "error: invalid file");
		save_coords(td_arr, lst, c->h, c);
		free_arr(&td_arr, c->w);
		c->h++;
	}
	c->seg = get_segments(lst, c->w);
}
