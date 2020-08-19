/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:29:06 by diona             #+#    #+#             */
/*   Updated: 2020/08/05 23:29:06 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

static void		put_pixel(t_fractal *fr, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		fr->img_ptr[y * WIN_WIDTH + x] = color;
}

int		count_mandelbrot(t_complex c)
{
	int			n;
	t_complex	z;
	float		temp;

	n = 0;
	z.re = 0;
	z.im = 0;
	while (n < EXIT_TIME)
	{
		if (((z.im*z.im) + (z.re*z.re)) > 4)
			return (n);
		temp = z.re*z.re - z.im*z.im + c.re;
		z.im = 2*z.re*z.im + c.im;
		z.re = temp;
		n++;
	}
	return (n);
}

t_complex	get_complex(int x, int y, t_param *fr)
{
	t_complex	z;
	float dx;
	float dy;

	dx = (fr->x_max - fr->x_min) / WIN_WIDTH;
	dy = (fr->y_max - fr->y_min) / WIN_HEIGHT;
	z.re = fr->x_min + x * dx;
	z.im = fr->y_max - y * dy;
	return (z);
}

void	draw(t_fractal *fr)
{
	int	x;
	int	y;
	int	n;

	y = 0;
	n = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if ((n = fr->param.func(get_complex(x, y, &fr->param))) == EXIT_TIME)
				// put_pixel(fr, x, y, WHITE);
				put_pixel(fr, x, y, BLACK);
			else
				// put_pixel(fr, x, y, (n % EXIT_TIME)*n);
				put_pixel(fr, x, y, log(EXIT_TIME / n)*n);
				// put_pixel(fr, x, y, BLACK);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fr->mlx, fr->window, fr->image, 0, 0);
}

// void	julia(t_fractal *fr)
// {
// 	(void*)fr;
// 	return;
// }
