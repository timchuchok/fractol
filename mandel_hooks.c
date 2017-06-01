/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandel_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 14:21:53 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/13 23:24:38 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mandel_expose_hook(t_fractol *fractol)
{
	mandel(fractol);
	return (0);
}

int		mandel_mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	if (button == 1 || button == 5)
	{
		fractol->zoom = fractol->zoom + fractol->zoom / 5;
		fractol->ox = fractol->ox + (fractol->ox - x) / 5;
		fractol->oy = fractol->oy + (fractol->oy - y) / 5;
	}
	else if (button == 2 || button == 4)
	{
		fractol->zoom = fractol->zoom - fractol->zoom / 5;
		fractol->ox = fractol->ox - (fractol->ox - x) / 5;
		fractol->oy = fractol->oy - (fractol->oy - y) / 5;
	}
	mandel_expose_hook(fractol);
	return (0);
}

int		mandel_key_hook(int key, t_fractol *fractol)
{
	iter_add_color_rot(key, fractol);
	if (key == 123)
		fractol->cx += (0.1 / fractol->zoom);
	if (key == 124)
		fractol->cx -= (0.1 / fractol->zoom);
	if (key == 125)
		fractol->cy -= (0.1 / fractol->zoom);
	if (key == 126)
		fractol->cy += (0.1 / fractol->zoom);
	mandel_expose_hook(fractol);
	return (0);
}
