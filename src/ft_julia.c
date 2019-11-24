/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:27:29 by gmoindro          #+#    #+#             */
/*   Updated: 2019/11/24 12:33:49 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			fractol_julia(t_ptr *ptr)
{
	ptr->x = 0;
	while (ptr->x < (ptr->im_x - 200))
	{
		ptr->y = 0;
		while (ptr->y < ptr->im_y)
		{
			ptr->c_r = 0.285 + ptr->change_x / 1000;
			ptr->c_i = 0.01 + ptr->change_y / 1000;
			ptr->z_r = ptr->x / ptr->para.zoom + ptr->para.x1 / ptr->para.zoom;
			ptr->z_i = ptr->y / ptr->para.zoom + ptr->para.y1 / ptr->para.zoom;
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

void			color_key_julia(int key, t_ptr *ptr)
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
	fractol_julia(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
}

void			arrow_key_julia(int key, t_ptr *ptr)
{
	if (key == 123)
		ptr->para.x1 = ptr->para.x1 - 100;
	else if (key == 124)
		ptr->para.x1 = ptr->para.x1 + 100;
	else if (key == 125)
		ptr->para.y1 = ptr->para.y1 + 100;
	else if (key == 126)
		ptr->para.y1 = ptr->para.y1 - 100;
	fractol_julia(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
}

void			int_key_julia(int key, t_ptr *ptr)
{
	if (key == 16 && ptr->para.int_max > 10)
		ptr->para.int_max = ptr->para.int_max - 10;
	else if (key == 17)
		ptr->para.int_max = ptr->para.int_max + 10;
	fractol_julia(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
}

int				key_push_julia(int key, t_ptr *ptr)
{
	if ((key > 17 && key < 30) && key != 24 && key != 27)
		color_key_julia(key, ptr);
	else if (key > 122 && key < 127)
		arrow_key_julia(key, ptr);
	else if (key == 16 || key == 17)
		int_key_julia(key, ptr);
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

void			click_menu_julia(t_ptr *ptr, int x, int y)
{
	if (y > (2 * ptr->im_y / 3) && x > (ptr->im_x - 100))
	{
		mlx_destroy_image(ptr->mlx, ptr->img.img);
		mlx_destroy_window(ptr->mlx, ptr->win);
		ft_burningship(ptr->im_x, ptr->im_y);
	}
	else if (y > (2 * ptr->im_y / 3))
	{
		mlx_destroy_image(ptr->mlx, ptr->img.img);
		mlx_destroy_window(ptr->mlx, ptr->win);
		ft_mandelbrot(ptr->im_x, ptr->im_y);
	}
	else if (y > ptr->im_y / 3 && x > (ptr->im_x - 100) && ptr->im_x > 300
			&& ptr->im_y > 200)
	{
		mlx_destroy_image(ptr->mlx, ptr->img.img);
		mlx_destroy_window(ptr->mlx, ptr->win);
		ft_julia(ptr->im_x - 60, ptr->im_y - 40);
	}
	else if (y > ptr->im_y / 3 && x <= (ptr->im_x - 100))
	{
		mlx_destroy_image(ptr->mlx, ptr->img.img);
		mlx_destroy_window(ptr->mlx, ptr->win);
		ft_julia(ptr->im_x + 60, ptr->im_y + 40);
	}
}

int				mouse_push_julia(int button, int x, int y, t_ptr *ptr)
{
	if (button == 1 && x > (ptr->im_x - 200) && x < ptr->im_x)
		click_menu_julia(ptr, x, y);
	else if (button != 4 && button != 5)
		return (0);
	else if (button == 4 && x >= 0 && x <= ptr->im_x - 200
			&& y >= 0 && y <= ptr->im_y)
		mouse_push_2(button, x, y, ptr);
	else if (button == 5 && x >= 0 && x <= ptr->im_x - 200
			&& y >= 0 && y <= ptr->im_y)
		mouse_push_2(button, x, y, ptr);
	mlx_clear_window(ptr->mlx, ptr->win);
	init_menu_julia(*ptr);
	fractol_julia(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
	return (0);
}

void			init_menu_julia(t_ptr ptr)
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
	init_menu_mandelbrot_2(ptr);
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, 180, 0xFFFFFF,
			"s pour figer");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 185, 2 * ptr.im_y / 3 + 70,
			0xFFFFFF, "Mandel!");
	mlx_string_put(ptr.mlx, ptr.win, ptr.im_x - 85, 2 * ptr.im_y / 3 + 70,
			0xFFFFFF, "Burning!");
}

int				mouse_hook_julia(int x, int y, t_ptr *ptr)
{
	if (ptr->move == 1)
		return (0);
	if (ptr->an_x > 9999 || ptr->an_y > 9999)
	{
		ptr->an_x = x;
		ptr->an_y = y;
		return (0);
	}
	ptr->change_x = x - ptr->an_x;
	ptr->change_y = y - ptr->an_y;
	fractol_julia(ptr);
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img.img, 0, 0);
	return (0);
}

void			ft_julia(int im_x, int im_y)
{
	t_ptr	ptr;

	ptr.mlx = mlx_init();
	ptr.im_x = im_x;
	ptr.im_y = im_y;
	ptr.an_x = 10000;
	ptr.an_y = 10000;
	ptr.change_x = 0;
	ptr.change_y = 0;
	ptr.move = 0;
	ptr.win = mlx_new_window(ptr.mlx, ptr.im_x, ptr.im_y, "Fractol");
	init_menu_julia(ptr);
	ptr.img.img = mlx_new_image(ptr.mlx, ptr.im_x - 200, ptr.im_y);
	ptr.img.p_img = mlx_get_data_addr(ptr.img.img, &ptr.img.bpp,
			&ptr.img.size_l, &ptr.img.endian);
	ptr = init_para(ptr);
	ptr.img.bpp /= 8;
	fractol_julia(&ptr);
	mlx_key_hook(ptr.win, key_push_julia, &ptr);
	mlx_mouse_hook(ptr.win, mouse_push_julia, &ptr);
	mlx_hook(ptr.win, 6, 0, mouse_hook_julia, &ptr);
	mlx_put_image_to_window(ptr.mlx, ptr.win, ptr.img.img, 0, 0);
	mlx_loop(ptr.mlx);
}
