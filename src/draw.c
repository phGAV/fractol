/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:49:21 by diona             #+#    #+#             */
/*   Updated: 2020/09/05 22:49:21 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <pthread.h>

static void		put_pixel(t_fractal *fr, int x, int y, int color)
{
	if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		fr->img_ptr[y * WIN_WIDTH + x] = color;
}

t_complex	get_complex(int x, int y, t_param *fr)
{
	t_complex	z;
	double		dx;
	double		dy;

	dx = (fr->x_max - fr->x_min) / WIN_WIDTH;
	dy = (fr->y_max - fr->y_min) / WIN_HEIGHT;
	z.re = fr->x_min + x * dx;
	z.im = fr->y_max - y * dy;
	return (z);
}

int		color_bernstein(int iter, t_param *fr)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)iter/(double)fr->max_iter;
	r = (int)(9.0 * (1 - t) * t * t * t * 255.0);
	g = (int)(15.0 * (1 - t) * (1 - t) * t * t * 255.0);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255.0);
	return ((r << 0x10) | (g << 0x8) | b);
}

int		color_grayscale(int iter, t_param *fr)
{
	double	t;
	int		r;
	int		g;
	int		b;

	t = (double)iter/(double)fr->max_iter;
	r = (int)((1 - t)*0.0 + t*255.0);
	g = (int)((1 - t)*0.0 + t*255.0);
	b = (int)((1 - t)*0.0 + t*255.0);
	return ((r << 0x10) | (g << 0x8) | b);
}

int		color_hsv(int iter, t_param *fr)
{
	double		h;
	int		i;
	double		vm, a, vi, vd;

	h = (360.0*(double)iter/(double)fr->max_iter);
	i = ((int)h/60)%6;
	vm = ((100 - SATURATION) * VALUE)/100;
	a = (VALUE - vm) * (fmod(h, 60)/60);
	vi = vm + a;
	vd = VALUE - a;
	if (i < 1)
		return (((int)(VALUE*2.55) << 0x10) | ((int)(vi*2.55) << 0x8) | (int)(vm*2.55));
	if (i < 2)
		return (((int)(vd*2.55) << 0x10) | ((int)(VALUE*2.55) << 0x8) | (int)(vm*2.55));
	if (i < 3)
		return (((int)(vm*2.55) << 0x10) | ((int)(VALUE*2.55) << 0x8) | (int)(vi*2.55));
	if (i < 4)
		return (((int)(vm*2.55) << 0x10) | ((int)(vd*2.55) << 0x8) | (int)(VALUE*2.55));
	if (i < 5)
		return (((int)(vi*2.55) << 0x10) | ((int)(vm*2.55) << 0x8) | (int)(VALUE*2.55));
	return (((int)(VALUE*2.55) << 0x10) | ((int)(vm*2.55) << 0x8) | (int)(vd*2.55));
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
			if ((n = fr->param.func(get_complex(x, y, &fr->param),
							get_complex(fr->mouse->x, fr->mouse->y, &fr->param),
							fr->param.max_iter)) == fr->param.max_iter)
				put_pixel(fr, x, y, BLACK);
			else
				// put_pixel(fr, x, y, color_bernstein(n, &fr->param));
				put_pixel(fr, x, y, color_hsv(n, &fr->param));
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
