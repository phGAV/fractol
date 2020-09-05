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
#include <pthread.h>

static void		put_pixel(t_fractal *fr, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		fr->img_ptr[y * WIN_WIDTH + x] = color;
}

int		count_mandelbrot(t_complex c, int max_iter)
{
	int			n;
	t_complex	z;
	float		temp;

	n = 0;
	z.re = 0;
	z.im = 0;
	while (n < max_iter)
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

int		color_bernstein(int iter, t_param *fr)
{
	float	t;
	int		r;
	int		g;
	int		b;

	t = (float)iter/(float)fr->max_iter;
	r = (int)(9.0 * (1 - t) * t * t * t * 255.0);
	g = (int)(15.0 * (1 - t) * (1 - t) * t * t * 255.0);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255.0);
	return ((r << 0x10) | (g << 0x8) | b);
}

void	draw_thread(void *fractal)
{
	int	x;
	int	y;
	int	y_last;
	int	n;
	t_fractal	*fr;

	fr = (t_fractal*)fractal;
	y = (WIN_HEIGHT / THREADS) * fr->thread_id;
	y_last = (WIN_HEIGHT / THREADS) * (fr->thread_id + 1);
	n = 0;
	while (y < y_last)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if ((n = fr->param.func(get_complex(x, y, &fr->param), fr->param.max_iter))
					== fr->param.max_iter)
				put_pixel(fr, x, y, BLACK);
			else
				put_pixel(fr, x, y, color_bernstein(n, &fr->param));
			x++;
		}
		y++;
	}
}

void	thread_init(t_fractal *fr)
{
	pthread_t	threads[THREADS];
	t_fractal	fractal[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		fractal[i] = *fr;
		fractal[i].thread_id = i;
		if (pthread_create(&threads[i], NULL,
			(void *(*)(void *))draw_thread, (void *)&fractal[i]))
			exit_err(ERR_THREADS);
		i++;
	}
	while (i-- > 0)
		if (pthread_join(threads[i], NULL))
			exit_err(ERR_THREADS);
	mlx_put_image_to_window(fr->mlx, fr->window, fr->image, 0, 0);
}
