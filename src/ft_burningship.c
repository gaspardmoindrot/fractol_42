/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_burningship.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 11:27:04 by gmoindro          #+#    #+#             */
/*   Updated: 2019/11/16 14:23:34 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			fractol_burningship(t_ptr *ptr)
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
				tmp = z_r * z_r - z_i * z_i + c_r;
				z_r = fabs(2 * z_r * z_i) + c_i;
				z_i = tmp;
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

void			click_menu_burning(t_ptr *ptr, int x, int y)
{
	if (y > (2 * ptr->im_y / 3) && x > (ptr->im_x - 100))
	{
		mlx_destroy_image(ptr->mlx, ptr->img.img);
        mlx_destroy_window(ptr->mlx, ptr->win);
		ft_mandelbrot(ptr->im_x, ptr->im_y);
	}
	else if (y > (2 * ptr->im_y / 3))
	{
		mlx_destroy_image(ptr->mlx, ptr->img.img);
        mlx_destroy_window(ptr->mlx, ptr->win);
		ft_julia(ptr->im_x, ptr->im_y);
	}
	else if (y > ptr->im_y / 3 && x > (ptr->im_x - 100) && ptr->im_x > 300
			&& ptr->im_y > 200)
	{
		mlx_destroy_image(ptr->mlx, ptr->img.img);
		mlx_destroy_window(ptr->mlx, ptr->win);
		ft_burningship(ptr->im_x - 60, ptr->im_y - 40);
	}
	else if (y > ptr->im_y / 3 && x <= (ptr->im_x - 100))
	{
		mlx_destroy_image(ptr->mlx, ptr->img.img);
		mlx_destroy_window(ptr->mlx, ptr->win);
		ft_burningship(ptr->im_x + 60, ptr->im_y + 40);
	}
}

int				mouse_push_burning(int button, int x, int y, t_ptr *ptr)
{
	double	c_r;
	double	x_r;
	double	c_i;
	double	y_r;

	if (button == 1 && x > (ptr->im_x - 200) && x < ptr->im_x)
		click_menu_burning(ptr, x, y);
	else if (button != 4 && button != 5)
		return (0);
	else if (button == 4 && x >= 0 && x <= ptr->im_x - 200
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
	mlx_clear_window(ptr->mlx, ptr->win);
	init_menu_burningship(*ptr);
	fractol_burningship(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
	return (0);
}

void			init_menu_burningship(t_ptr ptr)
{
	int		x;
	int		y;

	y = 0;
	while (y < ptr.im_y)
	{
		x = ptr.im_x - 200;
		while (x < ptr.im_x)
		{
			if (x - (ptr.im_x - 200) < 4 || x - (ptr.im_x - 200) > 196
					|| y < 4 || y > (ptr.im_y - 4) || y == ptr.im_y / 3
					|| y == (ptr.im_y * 2) / 3
					|| (x == ptr.im_x - 100 && y > ptr.im_y / 3))
				mlx_pixel_put(ptr.mlx, ptr.win, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 160, 40, 0xFFFFFF,
			"Commandes :");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, 80, 0xFFFFFF,
			"T : + iteration");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, 100, 0xFFFFFF,
			"Y : - iteration");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, 120, 0xFFFFFF,
			"Fleches : deplac.");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, 140, 0xFFFFFF,
			"Molette : zoom");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, 160, 0xFFFFFF,
			"Clic sur le menu !");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, ptr.im_y / 3 + 50,
			0xFFFFFF, "Agrandir");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 155, ptr.im_y / 3 + 70,
			0xFFFFFF, "la");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, ptr.im_y / 3 + 90,
			0xFFFFFF, "fenetre!");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 85, ptr.im_y / 3 + 50,
			0xFFFFFF, "Diminuer");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 55, ptr.im_y / 3 + 70,
			0xFFFFFF, "la");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 85, ptr.im_y / 3 + 90,
			0xFFFFFF, "fenetre!");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, 2 * ptr.im_y / 3 + 70,
			0xFFFFFF, "Julia !");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 85, 2 * ptr.im_y / 3 + 70,
			0xFFFFFF, "Mandel!");
}

void			ft_burningship(int im_x, int im_y)
{
	t_ptr	ptr;

	ptr.mlx = mlx_init();
	ptr.an_x = 10000;
    ptr.an_y = 10000;
	ptr.im_x = im_x;
	ptr.im_y = im_y;
	ptr.win = mlx_new_window(ptr.mlx, ptr.im_x, ptr.im_y, "Fractol");
	init_menu_burningship(ptr);
	ptr.img.img = mlx_new_image(ptr.mlx, ptr.im_x - 200, ptr.im_y);
	ptr.img.p_img = mlx_get_data_addr(ptr.img.img, &ptr.img.bpp,
			&ptr.img.size_l, &ptr.img.endian);
	ptr = init_para(ptr);
	ptr.img.bpp /= 8;
	fractol_burningship(&ptr);
	mlx_key_hook(ptr.win, key_push_burning, &ptr);
	mlx_mouse_hook(ptr.win, mouse_push_burning, &ptr);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img.img, 0, 0);
	mlx_loop(ptr.mlx);
}
