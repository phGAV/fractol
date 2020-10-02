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

t_complex		get_complex(int x, int y, t_param *fr)
{
	t_complex	z;
	double		dx;
	double		dy;

	dx = fr->dx / WIN_WIDTH;
	dy = fr->dy / WIN_HEIGHT;
	z.re = fr->x_min + x * dx;
	z.im = fr->y_max - y * dy;
	return (z);
}

void			draw_thread(void *fractal)
{
	int			x;
	int			y;
	int			y_last;
	int			n;
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
			if ((n = fr->param.func(get_complex(x, y, &fr->param), fr->param.m,
						fr->param.max_iter)) == fr->param.max_iter)
				put_pixel(fr, x, y, BLACK);
			else
				put_pixel(fr, x, y,
						fr->color((double)n / (double)fr->param.max_iter));
			x++;
		}
		y++;
	}
}

void			thread_init(t_fractal *fr)
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
