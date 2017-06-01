/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:45:02 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/14 17:45:52 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		julia_mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	if (x && y)
		x = y;
	if (button == 1 || button == 5 || button == 2 || button == 4)
		julia_zoom(fractol, button);
	julia_expose_hook(fractol);
	return (0);
}

void	julia_zoom(t_fractol *fractol, int button)
{
	if (button == 1 || button == 5)
	{
		fractol->zoom = 0.9;
		fractol->xmin *= fractol->zoom;
		fractol->xmax *= fractol->zoom;
		fractol->ymin *= fractol->zoom;
		fractol->ymax *= fractol->zoom;
		fractol->dx = (fractol->xmax - fractol->xmin) / WW;
		fractol->dy = (fractol->ymax - fractol->ymin) / WH;
	}
	else if (button == 2 || button == 4)
	{
		fractol->zoom = 1.1;
		fractol->xmin *= fractol->zoom;
		fractol->xmax *= fractol->zoom;
		fractol->ymin *= fractol->zoom;
		fractol->ymax *= fractol->zoom;
		fractol->dx = (fractol->xmax - fractol->xmin) / WW;
		fractol->dy = (fractol->ymax - fractol->ymin) / WH;
	}
}

int		julia_expose_hook(t_fractol *fractol)
{
	julia(fractol);
	return (0);
}

int		julia_hook(int x, int y, t_fractol *fractol)
{
	static int prevx = 0;
	static int prevy = 0;

	if (x >= 0 && x <= WW && y >= 0 && y <= WH)
	{
		if (abs(x - prevx) > 10 || abs(y - prevy) > 10)
		{
			fractol->cx = x * (2.0 / WW) - 1.0;
			fractol->cy = y * (2.0 / WH) - 1.0;
			julia_expose_hook(fractol);
			prevx = x;
			prevy = y;
		}
	}
	return (0);
}

int		julia_key_hook(int key, t_fractol *fractol)
{
	if (key == 123)
	{
		fractol->xmin += fractol->dx * 10;
		fractol->xmax += fractol->dx * 10;
	}
	if (key == 124)
	{
		fractol->xmin -= fractol->dx * 10;
		fractol->xmax -= fractol->dx * 10;
	}
	if (key == 125)
	{
		fractol->ymin -= fractol->dy * 10;
		fractol->ymax -= fractol->dy * 10;
	}
	if (key == 126)
	{
		fractol->ymin += fractol->dy * 10;
		fractol->ymax += fractol->dy * 10;
	}
	iter_add_color_rot(key, fractol);
	julia_expose_hook(fractol);
	return (0);
}
