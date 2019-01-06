/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 18:44:59 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/06 13:36:57 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	display_error(int cond, char *str)
{
	if (cond)
	{
		ft_putendl(str);
		exit(0);
	}
}

void	free_arr(char ***arr, int size)
{
	while (size--)
	{
		free(arr[0][size]);
		arr[0][size] = NULL;
	}
	free(arr[0]);
	arr[0] = NULL;
}

double	ft_ilerp(double val, double first, double second)
{
	if (val == first)
		return (0.0);
	if (val == second)
		return (1.0);
	return ((val - first) / (second - first));
}

int		ft_lerpi(int first, int second, double percent)
{
	if (first == second)
		return (first);
	return ((int)((double)first + (second - first) * percent));
}

int		get_color(int start, int end, double percent)
{
	int	r;
	int	g;
	int	b;

	if (start == end)
		return (start);
	r = ft_lerpi((start >> 16) & 0xFF, (end >> 16) & 0xFF, percent);
	g = ft_lerpi((start >> 8) & 0xFF, (end >> 8) & 0xFF, percent);
	b = ft_lerpi((start) & 0xFF, (end) & 0xFF, percent);
	return (r << 16 | g << 8 | b);
}
