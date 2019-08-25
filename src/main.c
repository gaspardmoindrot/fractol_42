/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:15:26 by gmoindro          #+#    #+#             */
/*   Updated: 2019/08/24 16:35:55 by gmoindro         ###   ########.fr       */
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
		return (error("usage : ./fractol fractal_name\n"));
	else if (ft_strcmp(argv[1], "mandelbrot") == 0)
		ft_mandelbrot();
	else if (ft_strcmp(argv[1], "julia") == 0)
		;
	else
		return (error("fractal_name false, test with mandelbrot / julia\n"));
	return (0);
}
