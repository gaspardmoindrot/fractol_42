/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_burningship_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 13:17:06 by gmoindro          #+#    #+#             */
/*   Updated: 2019/11/24 13:23:08 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			fractol_burningship(t_ptr *ptr)
{
	ptr->x = 0;
	while (ptr->x < (ptr->im_x - 200))
	{
		ptr->y = 0;
		while (ptr->y < ptr->im_y)
		{
			ptr->c_r = ptr->x / ptr->para.zoom + ptr->para.x1 / ptr->para.zoom;
			ptr->c_i = ptr->y / ptr->para.zoom + ptr->para.y1 / ptr->para.zoom;
			ptr->z_r = 0;
			ptr->z_i = 0;
			ptr->i = 0;
			while (ptr->z_r * ptr->z_r + ptr->z_i * ptr->z_i < 8 &&
					ptr->i < ptr->para.int_max)
			{
				ptr->tmp = ptr->z_r * ptr->z_r - ptr->z_i * ptr->z_i + ptr->c_r;
				ptr->z_r = fabs(2 * ptr->z_r * ptr->z_i) + ptr->c_i;
				ptr->z_i = ptr->tmp;
				ptr->i++;
			}
			fractol_mandelbrot_color(ptr);
			ptr->y++;
		}
		ptr->x++;
	}
}

void			color_key_burning(int key, t_ptr *ptr)
{
	if (key == 18)
		ptr->para.nb_col = 1;
	else if (key == 19)
		ptr->para.nb_col = 2;
	else if (key == 20)
		ptr->para.nb_col = 3;
	else if (key == 21)
		ptr->para.nb_col = 4;
	else if (key == 22)
		ptr->para.nb_col = 6;
	else if (key == 23)
		ptr->para.nb_col = 5;
	else if (key == 25)
		ptr->para.nb_col = 9;
	else if (key == 26)
		ptr->para.nb_col = 7;
	else if (key == 28)
		ptr->para.nb_col = 8;
	else if (key == 29)
		ptr->para.nb_col = 0;
	fractol_burningship(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
}

void			arrow_key_burning(int key, t_ptr *ptr)
{
	if (key == 123)
		ptr->para.x1 = ptr->para.x1 - 100;
	else if (key == 124)
		ptr->para.x1 = ptr->para.x1 + 100;
	else if (key == 125)
		ptr->para.y1 = ptr->para.y1 + 100;
	else if (key == 126)
		ptr->para.y1 = ptr->para.y1 - 100;
	fractol_burningship(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
}

void			int_key_burning(int key, t_ptr *ptr)
{
	if (key == 16 && ptr->para.int_max > 10)
		ptr->para.int_max = ptr->para.int_max - 10;
	else if (key == 17)
		ptr->para.int_max = ptr->para.int_max + 10;
	fractol_burningship(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
}

int				key_push_burning(int key, t_ptr *ptr)
{
	if ((key > 17 && key < 30) && key != 24 && key != 27)
		color_key_burning(key, ptr);
	else if (key > 122 && key < 127)
		arrow_key_burning(key, ptr);
	else if (key == 16 || key == 17)
		int_key_burning(key, ptr);
	else if (key == 53)
	{
		mlx_destroy_image(ptr->mlx, ptr->img.img);
		mlx_destroy_window(ptr->mlx, ptr->win);
		exit(EXIT_SUCCESS);
	}
	else if (key == 1 && ptr->move == 1)
		ptr->move = 0;
	else if (key == 1 && ptr->move == 0)
		ptr->move = 1;
	return (0);
}
