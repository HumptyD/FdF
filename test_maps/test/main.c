/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ejommy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 13:21:38 by ejommy            #+#    #+#             */
/*   Updated: 2018/12/25 14:15:47 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"



int	main()
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_dot	a;;
	t_dot	b;
	t_dot	c;
	t_dot	d;


	a.x = 250;
	a.y = 250;
	b.x = 450;
	b.y = 250;
	c.x = 250;
	c.y = 450;
	d.x = 450;
	d.y = 450;
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1200 , 800, "my first window");
	ft_draw_line(mlx_ptr, win_ptr, a, b);
	ft_draw_line(mlx_ptr, win_ptr, a, c);
	ft_draw_line(mlx_ptr, win_ptr, b, d);
	ft_draw_line(mlx_ptr, win_ptr, c, d);
	mlx_loop(mlx_ptr);
	return (0);
}
