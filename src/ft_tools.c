/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 13:13:13 by gmoindro          #+#    #+#             */
/*   Updated: 2019/11/24 13:14:47 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void			fractol_mandelbrot_color(t_ptr *ptr)
{
	if (ptr->i == ptr->para.int_max)
		*(int *)(ptr->img.p_img + (((int)ptr->y * (ptr->im_x - 200) +
						(int)ptr->x) * ptr->img.bpp)) = 0;
	else
		*(int *)(ptr->img.p_img + (((int)ptr->y * (ptr->im_x - 200) +
						(int)ptr->x) * ptr->img.bpp)) =
			ptr->para.color[ptr->para.nb_col] * ptr->i / 8;
}

void			mouse_push_2(int button, int x, int y, t_ptr *ptr)
{
	ptr->c_r = x / ptr->para.zoom + ptr->para.x1 / ptr->para.zoom;
	ptr->c_i = y / ptr->para.zoom + ptr->para.y1 / ptr->para.zoom;
	if (button == 4)
		ptr->para.zoom = ptr->para.zoom * 2;
	else
		ptr->para.zoom = ptr->para.zoom / 2;
	ptr->x = ptr->c_r * ptr->para.zoom - ptr->para.x1;
	ptr->y = ptr->c_i * ptr->para.zoom - ptr->para.y1;
	ptr->para.x1 = ptr->para.x1 - (x - ptr->x);
	ptr->para.y1 = ptr->para.y1 - (y - ptr->y);
}

void			init_menu_mandelbrot_2(t_ptr ptr)
{
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
}
