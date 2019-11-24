/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:15:26 by gmoindro          #+#    #+#             */
/*   Updated: 2019/11/24 12:42:06 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	error(char *str)
{
	ft_putstr(str);
	return (0);
}

int			main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr("fractal_name : [mandelbrot, julia, burningship]\n");
		return (error("usage : ./fractol fractal_name\n"));
	}
	else if (ft_strcmp(argv[1], "mandelbrot") == 0)
		ft_mandelbrot(1280, 720);
	else if (ft_strcmp(argv[1], "julia") == 0)
		ft_julia(1280, 720);
	else if (ft_strcmp(argv[1], "burningship") == 0)
		ft_burningship(1280, 720);
	else
	{
		ft_putstr("fractal_name : [mandelbrot, julia, burningship]\n");
		return (error("usage : ./fractol fractal_name\n"));
	}
	return (0);
}
