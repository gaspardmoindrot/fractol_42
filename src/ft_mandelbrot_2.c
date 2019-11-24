/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 13:10:40 by gmoindro          #+#    #+#             */
/*   Updated: 2019/11/24 13:13:07 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			fractol_mandelbrot(t_ptr *ptr)
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
				ptr->tmp = ptr->z_r;
				ptr->z_r = ptr->z_r * ptr->z_r - ptr->z_i * ptr->z_i + ptr->c_r;
				ptr->z_i = 2 * ptr->tmp * ptr->z_i + ptr->c_i;
				ptr->i++;
			}
			fractol_mandelbrot_color(ptr);
			ptr->y++;
		}
		ptr->x++;
	}
}

t_ptr			init_para(t_ptr ptr)
{
	ptr.para.zoom = 200;
	ptr.para.int_max = 100;
	ptr.para.x1 = -((ptr.im_x - 100) / 2);
	ptr.para.y1 = -(ptr.im_y / 2);
	ptr.para.color[0] = 0xFF0000;
	ptr.para.color[1] = 0xFF00;
	ptr.para.color[2] = 0xFF;
	ptr.para.color[3] = 0xF0F0F0;
	ptr.para.color[4] = 0xF0F0F;
	ptr.para.color[5] = 0xF0F0;
	ptr.para.color[6] = 0xF0F;
	ptr.para.color[7] = 0xF0;
	ptr.para.color[8] = 0xAAAA;
	ptr.para.color[9] = 0xABCD;
	ptr.para.nb_col = 0;
	return (ptr);
}

void			color_key(int key, t_ptr *ptr)
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
	fractol_mandelbrot(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
}

void			arrow_key(int key, t_ptr *ptr)
{
	if (key == 123)
		ptr->para.x1 = ptr->para.x1 - 100;
	else if (key == 124)
		ptr->para.x1 = ptr->para.x1 + 100;
	else if (key == 125)
		ptr->para.y1 = ptr->para.y1 + 100;
	else if (key == 126)
		ptr->para.y1 = ptr->para.y1 - 100;
	fractol_mandelbrot(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
}

void			int_key(int key, t_ptr *ptr)
{
	if (key == 16 && ptr->para.int_max > 10)
		ptr->para.int_max = ptr->para.int_max - 10;
	else if (key == 17)
		ptr->para.int_max = ptr->para.int_max + 10;
	fractol_mandelbrot(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
}
