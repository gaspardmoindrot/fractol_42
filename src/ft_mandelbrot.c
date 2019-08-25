/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mandelbrot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 16:36:02 by gmoindro          #+#    #+#             */
/*   Updated: 2019/08/25 16:09:55 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			fractol_mandelbrot(t_ptr *ptr)
{
	double	x;
	double	y;
	double	c_r, c_i, z_r, z_i, i, tmp;
	
	x = 0;
	while (x < (ptr->im_x - 200))
	{
		y = 0;
		while (y < ptr->im_y)
		{
			c_r = x / ptr->para.zoom + ptr->para.x1 / ptr->para.zoom;
			c_i = y / ptr->para.zoom + ptr->para.y1 / ptr->para.zoom;
			z_r = 0;
			z_i = 0;
			i = 0;
			while (z_r * z_r + z_i * z_i < 8 && i < ptr->para.int_max)
			{
				tmp = z_r;
				z_r = z_r * z_r - z_i * z_i + c_r;
				z_i = 2 * tmp * z_i + c_i;
				i++;
			}
			if (i == ptr->para.int_max)
				*(int *)(ptr->img.p_img + (((int)y * (ptr->im_x - 200) +
								(int)x) * ptr->img.bpp)) = 0;
			else
				*(int *)(ptr->img.p_img + (((int)y * (ptr->im_x - 200) +
									(int)x) * ptr->img.bpp))
								= ptr->para.color[ptr->para.nb_col] * i / 8;
			y++;
		}
		x++;
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

int				key_push(int key, t_ptr *ptr)
{
	if ((key > 17 && key < 30) && key != 24 && key != 27)
		color_key(key, ptr);
	else if (key > 122 && key < 127)
		arrow_key(key, ptr);
	else if (key == 16 || key == 17)
		int_key(key, ptr);
	else if (key == 53)
	{
		mlx_destroy_window(ptr->mlx, ptr->win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int				mouse_push(int button, int x, int y, t_ptr *ptr)
{
	double	c_r;
	double	x_r;
	double	c_i;
	double	y_r;

	if (button == 4 && x >= 0 && x <= ptr->im_x - 200
			&& y >= 0 && y <= ptr->im_y)
	{
		c_r = x / ptr->para.zoom + ptr->para.x1 / ptr->para.zoom;
		c_i = y / ptr->para.zoom + ptr->para.y1 / ptr->para.zoom;
		ptr->para.zoom = ptr->para.zoom * 2;
		x_r = c_r * ptr->para.zoom - ptr->para.x1;
		y_r = c_i * ptr->para.zoom - ptr->para.y1;
		ptr->para.x1 = ptr->para.x1 - (x - x_r);
		ptr->para.y1 = ptr->para.y1 - (y - y_r);
	}
	else if (button == 5 && x >= 0 && x <= ptr->im_x - 200
			&& y >= 0 && y <= ptr->im_y)
	{
		c_i = y / ptr->para.zoom + ptr->para.y1 / ptr->para.zoom;
		c_r = x / ptr->para.zoom + ptr->para.x1 / ptr->para.zoom;
		ptr->para.zoom = ptr->para.zoom / 2;
		x_r = c_r * ptr->para.zoom - ptr->para.x1;
		y_r = c_i * ptr->para.zoom - ptr->para.y1;
		ptr->para.x1 = ptr->para.x1 - (x - x_r);
		ptr->para.y1 = ptr->para.y1 - (y - y_r);
	}
	mlx_clear_window (ptr->mlx, ptr->win);
	fractol_mandelbrot(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
	return (0);
}

void			ft_mandelbrot(void)
{
	t_ptr	ptr;

	ptr.mlx = mlx_init();
	ptr.im_x = 1280;
	ptr.im_y = 720;
	ptr.win = mlx_new_window(ptr.mlx, ptr.im_x, ptr.im_y, "Fractol");
	ptr.img.img = mlx_new_image(ptr.mlx, ptr.im_x - 200, ptr.im_y);
	ptr.img.p_img = mlx_get_data_addr(ptr.img.img, &ptr.img.bpp,
			&ptr.img.size_l, &ptr.img.endian);
	ptr = init_para(ptr);
	ptr.img.bpp /= 8;
	fractol_mandelbrot(&ptr);
	mlx_key_hook(ptr.win, key_push, &ptr);
	mlx_mouse_hook(ptr.win, mouse_push, &ptr);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img.img, 0, 0);
	mlx_loop(ptr.mlx);
}
