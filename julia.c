/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/31 15:18:00 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/14 08:55:25 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractol	*init_julia(void)
{
	t_fractol *fractol;

	fractol = (t_fractol *)malloc(sizeof(t_fractol));
	if (!fractol)
		exit(3);
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, WW, WH, "Julia");
	fractol->zoom = 1.0;
	fractol->xmin = -1.5;
	fractol->xmax = 1.5;
	fractol->ymin = -1.0;
	fractol->ymax = 1.0;
	fractol->cx = -0.4;
	fractol->cy = 0.6;
	fractol->iter = 100;
	fractol->dx = (fractol->xmax - fractol->xmin) / WW;
	fractol->dy = (fractol->ymax - fractol->ymin) / WH;
	fractol->mouse_hook = julia_mouse_hook;
	fractol->expose_hook = julia_expose_hook;
	fractol->hook = julia_hook;
	fractol->key_hook = julia_key_hook;
	fractol->scheme = 1;
	return (fractol);
}

void		julia(t_fractol *fractol)
{
	int		i;
	int		j;
	int		n;
	double	x;
	double	y;

	y = fractol->ymin;
	j = 0;
	while (j < WH)
	{
		i = 0;
		x = fractol->xmin;
		while (i < WW)
		{
			n = julia2(fractol, x, y);
			mlx_pixel_put(fractol->mlx, fractol->win, i, j, n);
			x += fractol->dx;
			i++;
		}
		j++;
		y += fractol->dy;
	}
}

int			julia2(t_fractol *fractol, double x, double y)
{
	int		iter;
	double	xx;
	double	yy;
	double	twoab;

	iter = 0;
	while (iter < fractol->iter)
	{
		xx = x * x;
		yy = y * y;
		twoab = 2.0 * x * y;
		x = xx - yy + fractol->cx;
		y = twoab + fractol->cy;
		if (x * x + y * y > 4)
			break ;
		iter++;
	}
	return (color(iter, fractol));
}

void		iter_add_color_rot(int key, t_fractol *fractol)
{
	if (key == 69)
		fractol->iter += 50;
	if (key == 53)
		exit(3);
	if (key == 49)
	{
		if (fractol->scheme == 3)
			fractol->scheme = 1;
		else
			fractol->scheme++;
	}
}

int			color(int n, t_fractol *fractol)
{
	int r;
	int g;
	int b;

	if (fractol->scheme == 1)
	{
		r = n * 10;
		g = n * log(n);
		b = n + n % 10;
	}
	if (fractol->scheme == 2)
	{
		r = log(n) * n;
		g = n + n % 10;
		b = n * 10;
	}
	if (fractol->scheme == 3)
	{
		b = log(n) * n;
		g = n * 10;
		r = n + n % 10;
	}
	return (r << 16 | g << 8 | b);
}
