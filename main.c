/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtymchen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 10:42:43 by vtymchen          #+#    #+#             */
/*   Updated: 2017/02/14 18:06:49 by vtymchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_fractol	*get_fractol1(char **av)
{
	t_fractol *fractol;

	if (av[1][0] == '1')
		fractol = init_mandel();
	else if (av[1][0] == '2')
		fractol = init_julia();
	else if (av[1][0] == '3')
		fractol = init_serp();
	else
	{
		write(1, "1 - mandel\n2 - julia\n3 - serp\n", 31);
		exit(3);
	}
	return (fractol);
}

void		check(int ac, char **av)
{
	if (ac < 2 || ac > 3)
	{
		write(1, "1 - mandel\n2 - julia\n3 - serp\n", 31);
		exit(1);
	}
	if (ac == 3)
	{
		if (av[1][0] == '1' || av[1][0] == '2' || av[1][0] == '3')
		{
			if (av[2][0] == '1' || av[2][0] == '2' || av[2][0] == '3')
				;
			else
			{
				write(1, "1 - mandel\n2 - julia\n3 - serp\n", 31);
				exit(1);
			}
		}
		else
		{
			write(1, "1 - mandel\n2 - julia\n3 - serp\n", 31);
			exit(3);
		}
	}
}

int			main(int ac, char **av)
{
	pid_t		pid;
	t_fractol	*fractol;

	fractol = NULL;
	check(ac, av);
	if (ac == 2)
		fractol = get_fractol1(av);
	if (ac == 3)
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		if (pid == 0)
			fractol = get_fractol1(av);
		else if (pid > 0)
			fractol = get_fractol1(&av[1]);
	}
	mlx_key_hook(fractol->win, fractol->key_hook, fractol);
	mlx_hook(fractol->win, 6, 0, fractol->hook, fractol);
	mlx_mouse_hook(fractol->win, fractol->mouse_hook, fractol);
	mlx_expose_hook(fractol->win, fractol->expose_hook, fractol);
	mlx_loop(fractol->mlx);
	return (0);
}
