/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   serp_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/13 12:12:27 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/13 23:14:37 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		serp_expose_hook(t_fractol *fractol)
{
	t_tr t;

	mlx_clear_window(fractol->mlx, fractol->win);
	t.a.x = fractol->ox + fractol->cx + fractol->shiftx;
	t.a.y = 1 + fractol->cy - fractol->zoom + fractol->shifty;
	t.b.x = 1 + fractol->cx - fractol->zoom + fractol->shiftx;
	t.b.y = fractol->oy * 2 + fractol->cy - 1 + fractol->shifty;
	t.c.x = fractol->ox * 2 + fractol->cx + fractol->zoom - 1 + fractol->shiftx;
	t.c.y = fractol->oy * 2 + fractol->cy - 1 + fractol->shifty;
	draw_tr(t, fractol);
	serp(t, fractol->iter, fractol);
	return (0);
}

int		serp_key_hook(int key, t_fractol *fractol)
{
	if (key == 69)
		fractol->iter++;
	if (key == 78)
		fractol->iter--;
	if (fractol->iter < 0)
		fractol->iter = 0;
	if (key == 53)
		exit(3);
	if (key == 124)
		fractol->cx += 60;
	if (key == 123)
		fractol->cx -= 60;
	if (key == 126)
		fractol->cy -= 60;
	if (key == 125)
		fractol->cy += 60;
	serp_expose_hook(fractol);
	return (0);
}

int		serp_mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	if (button == 1 || button == 5)
	{
		fractol->shiftx = (fractol->ox - x);
		fractol->shifty = (fractol->oy - y);
		fractol->zoom = fractol->zoom + fractol->zoom / 10;
	}
	if (button == 2 || button == 4)
	{
		fractol->shiftx = fractol->ox - x;
		fractol->shifty = fractol->oy - y;
		fractol->zoom = fractol->zoom - fractol->zoom / 5;
	}
	serp_expose_hook(fractol);
	return (0);
}
