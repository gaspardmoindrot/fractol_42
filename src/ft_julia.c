/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_julia.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:27:29 by gmoindro          #+#    #+#             */
/*   Updated: 2019/11/24 13:16:47 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

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
