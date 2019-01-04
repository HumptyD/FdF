/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 15:18:45 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/04 22:17:33 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int argc, char **argv)
{
	int		fd;
	t_list	*lst;
	t_var	c;


	display_error(argc != 2, "error: wrong amount of arguments");
	fd = open(argv[1], O_RDONLY);
	display_error((fd < 0), "error: invalid file");
	init_var(&c);
	read_map(fd, &lst, &c);
	c.mlx = mlx_init();
	c.win = mlx_new_window(c.mlx, W_WIDTH, W_HEIGHT, argv[1]);
	init_map(&c);
	init_image(&c);
//	mlx_key_hook(c.win, keyboard, &c);
	mlx_hook(c.win, 2, 0, keyboard, &c);
	mlx_hook(c.win, 4, 0, mouse_press, &c);
	mlx_hook(c.win, 5, 0, mouse_release, &c);
	mlx_hook(c.win, 6, 0, mouse_move, &c);
	mlx_loop(c.mlx);
	return (0);
}
