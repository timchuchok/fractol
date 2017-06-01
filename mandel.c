/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:19:57 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/13 23:22:51 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractol	*init_mandel(void)
{
	t_fractol *fractol;

	fractol = (t_fractol *)malloc(sizeof(t_fractol));
	if (!fractol)
		exit(3);
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, WW, WH, "Mandelbrot set");
	fractol->zoom = 1.0;
	fractol->iter = 100;
	fractol->ox = WW / 2.0;
	fractol->oy = WH / 2.0;
	fractol->scheme = 1;
	fractol->cx = -0.5;
	fractol->cy = 0.0;
	fractol->expose_hook = mandel_expose_hook;
	fractol->mouse_hook = mandel_mouse_hook;
	fractol->key_hook = mandel_key_hook;
	fractol->hook = NULL;
	return (fractol);
}

void		mandel(t_fractol *fractol)
{
	int		i;
	int		j;
	double	x0;
	double	y0;
	int		n;

	j = 0;
	while (j < WH)
	{
		i = 0;
		y0 = (j - fractol->oy) / (WH * fractol->zoom / 2) + fractol->cy;
		while (i < WW)
		{
			x0 = 1.5 * (i - fractol->ox) / (WW * fractol->zoom / 2);
			x0 = x0 + fractol->cx;
			n = mandel2(x0, y0, fractol);
			mlx_pixel_put(fractol->mlx, fractol->win, i, j, n);
			i++;
		}
		j++;
	}
}

int			mandel2(double x0, double y0, t_fractol *fractol)
{
	int		iter;
	double	x;
	double	y;
	double	xtemp;

	x = 0.0;
	y = 0.0;
	iter = 0;
	while (iter < fractol->iter && x * x + y * y < 4)
	{
		xtemp = x * x - y * y + x0;
		y = 2.0 * x * y + y0;
		x = xtemp;
		iter++;
	}
	return (color(iter, fractol));
}
