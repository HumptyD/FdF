/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlucas-l <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 16:08:26 by jlucas-l          #+#    #+#             */
/*   Updated: 2019/01/03 18:52:16 by jlucas-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft.h"
# include "fcntl.h"
# include <stdio.h>
# include <math.h>
# include <time.h>

# define W_WIDTH 2560
# define W_HEIGHT 1300

typedef struct	s_point
{
	double		x;
	double		y;
	double		z;
	int			color;
}				t_point;

typedef struct	s_pline
{
	int			derror;
	int			error;
	int			x;
	int			y;
	int			steep;
}				t_pline;

typedef struct	s_line
{
	t_point		*a;
	t_point		*b;
}				t_line;

typedef struct	s_seg
{
	t_line		s;
	t_list		*segment;
	t_list		*obj;
	t_list		*copy;
	int			n;
}				t_seg;

typedef struct	s_mouse
{
	double		p_x;
	double		p_y;
	double		c_x;
	double		c_y;
	int			pressed;
}				t_mouse;

typedef struct	s_var
{
	void		*mlx;
	void		*win;
	t_point		ang;
	t_point		a;
	t_point		b;
	t_list		*seg;
	t_mouse		ms;
	int			w;
	int			h;
	double		scale;
	int			hor;
	int			vert;
	void		*image;
	char		*ptr;
	int			bpp;
	int			size_line;
	int			endian;
}				t_var;

void			put_line(t_var *c);
void			init_map(t_var *c);
void			rotation_matrix(t_point *dot, t_point ang, t_var *c);
void			display_error(int cond, char *str);
void			free_arr(char ***arr, int size);
void			read_map(int fd, t_list **lst, t_var *c);
int				keyboard(int key, t_var *c);
int				mouse_press(int button, int x, int y, t_var *c);
int				mouse_release(int button, int x, int y, t_var *c);
int				mouse_move(int x, int y, t_var *c);
void			print_map(t_var c);
void			init_image(t_var c);
void			set_pixel(t_var *c, int x, int y, int color);
int				get_color(int start, int end, double percent);
int				ft_lerpi(int first, int second, double percent);
double			ft_ilerp(double val, double first, double second);

#endif
