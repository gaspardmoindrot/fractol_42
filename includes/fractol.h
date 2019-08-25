/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 15:16:10 by gmoindro          #+#    #+#             */
/*   Updated: 2019/08/25 17:23:51 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>

typedef struct		s_img
{
	void			*img;
	char			*p_img;
	int				bpp;
	int				size_l;
	int				endian;
}					t_img;

typedef struct		s_para
{
	double			zoom;
	int				int_max;
	double			x1;
	double			y1;
	int				color[10];
	int				nb_col;
}					t_para;

typedef struct		s_ptr
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_para			para;
	int				im_x;
	int				im_y;
}					t_ptr;

void				ft_mandelbrot(int im_x, int im_y);
void				fractol_mandelbrot(t_ptr *ptr);
t_ptr				init_para(t_ptr ptr);
int					key_push(int key, t_ptr *ptr);
void				color_key(int key, t_ptr *ptr);
void				int_key(int key, t_ptr *ptr);
void				arrow_key(int key, t_ptr *ptr);
int					mouse_push(int button, int x, int y, t_ptr *ptr);
void				init_menu_mandelbrot(t_ptr ptr);
void				click_menu(t_ptr *ptr, int x, int y);

#endif
