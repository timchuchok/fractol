/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 09:09:18 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/13 22:32:55 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		line(t_point *a, t_point *b, t_fractol *f)
{
	double x;
	double y;

	x = (a->x < b->x ? a->x : b->x);
	while (x < (a->x > b->x ? a->x : b->x))
	{
		y = a->y + (x - a->x) * (b->y - a->y) / (b->x - a->x);
		mlx_pixel_put(f->mlx, f->win, x, y, 0xffffff);
		x++;
	}
	y = a->y < b->y ? a->y : b->y;
	while (y < (a->y > b->y ? a->y : b->y))
	{
		x = a->x + (y - a->y) * (b->x - a->x) / (b->y - a->y);
		mlx_pixel_put(f->mlx, f->win, x, y, 0xffffff);
		y++;
	}
}

t_fractol	*init_serp(void)
{
	t_fractol *fractol;

	fractol = (t_fractol *)malloc(sizeof(t_fractol));
	if (!fractol)
		exit(3);
	fractol->mlx = mlx_init();
	fractol->win = mlx_new_window(fractol->mlx, WW, WH, "Sierpinski triangle");
	fractol->zoom = 1.0;
	fractol->ox = WW / 2;
	fractol->oy = WH / 2;
	fractol->iter = 3;
	fractol->cx = 0.0;
	fractol->cy = -1.0;
	fractol->expose_hook = serp_expose_hook;
	fractol->hook = NULL;
	fractol->key_hook = serp_key_hook;
	fractol->mouse_hook = serp_mouse_hook;
	fractol->shiftx = 0.;
	fractol->shifty = 0;
	return (fractol);
}

void		draw_tr(t_tr tr, t_fractol *fractol)
{
	line(&tr.a, &tr.b, fractol);
	line(&tr.a, &tr.c, fractol);
	line(&tr.b, &tr.c, fractol);
}

void		serp(t_tr tr, int n, t_fractol *fractol)
{
	t_tr new_tr;
	t_tr s;

	if (n > 0)
	{
		new_tr.a = get_point(tr.a.x / 2 + tr.b.x / 2, tr.a.y / 2 + tr.b.y / 2);
		new_tr.b = get_point((tr.b.x + tr.c.x) / 2, (tr.b.y + tr.c.y) / 2);
		new_tr.c = get_point((tr.c.x + tr.a.x) / 2, (tr.c.y + tr.a.y) / 2);
		draw_tr(new_tr, fractol);
		s.a = tr.a;
		s.b = new_tr.a;
		s.c = new_tr.c;
		serp(s, n - 1, fractol);
		s.a = tr.b;
		s.b = new_tr.a;
		s.c = new_tr.b;
		serp(s, n - 1, fractol);
		s.a = tr.c;
		s.b = new_tr.b;
		s.c = new_tr.c;
		serp(s, n - 1, fractol);
	}
}

t_point		get_point(double x, double y)
{
	t_point point;

	point.x = x;
	point.y = y;
	return (point);
}
