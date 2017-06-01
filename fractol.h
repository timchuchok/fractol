/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:40:46 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/14 17:44:36 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "minilibx_macos/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# define WH 480
# define WW 640

typedef struct	s_fractol
{
	void	*mlx;
	void	*win;
	double	xmin;
	double	xmax;
	double	ymin;
	double	ymax;
	double	cx;
	double	cy;
	double	dx;
	double	dy;
	double	zoom;
	double	ox;
	double	oy;
	int		iter;
	void	*mouse_hook;
	void	*key_hook;
	void	*expose_hook;
	void	*hook;
	int		scheme;
	double	shiftx;
	double	shifty;
}				t_fractol;

typedef struct	s_point
{
	double x;
	double y;
}				t_point;

typedef struct	s_tr
{
	t_point a;
	t_point	b;
	t_point c;
}				t_tr;

void			julia(t_fractol *fractol);
t_fractol		*init_julia();
int				julia_expose_hook(t_fractol *fractol);
int				julia_mouse_hook(int button, int x, int y, t_fractol *fractol);
void			julia_zoom(t_fractol *f, int button);
int				julia_hook(int x, int y, t_fractol *fractol);
int				julia_key_hook(int key, t_fractol *fractol);
int				julia2(t_fractol *fractol, double x, double y);
int				color(int n, t_fractol *fractol);
void			iter_add_color_rot(int key, t_fractol *f);
t_fractol		*init_mandel();
void			mandel(t_fractol *fractol);
int				mandel_expose_hook(t_fractol *fractol);
int				mandel2(double x, double y, t_fractol *fractol);
int				mandel_mouse_hook(int b, int x, int y, t_fractol *fractol);
int				mandel_key_hook(int key, t_fractol *fractol);
void			line(t_point *a, t_point *b, t_fractol *fractol);
t_fractol		*init_serp();
void			draw_tr(t_tr tr, t_fractol *fractol);
t_tr			*create_tr();
void			serp(t_tr tr, int n, t_fractol *fractol);
t_point			get_point(double x, double y);
int				serp_expose_hook(t_fractol *fractol);
int				serp_key_hook(int key, t_fractol *fractol);
int				serp_mouse_hook(int key, int x, int y, t_fractol *fractol);
#endif
