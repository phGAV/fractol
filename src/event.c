/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:19:40 by diona             #+#    #+#             */
/*   Updated: 2020/08/04 18:19:40 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key.h"
#include <stdio.h>

int		close_hook(t_fractal *fr, int keycode)
{
	(void)keycode;
	// mlx_destroy_image(fr->mlx, fr->menu);
	mlx_destroy_image(fr->mlx, fr->image);
	mlx_destroy_window(fr->mlx, fr->window);
	printf("max iter= %d\n", fr->param.max_iter);
	exit(EXIT_SUCCESS);
}

void		move_im(t_fractal *fr, int keycode)
{
	double	step;

	step = (fr->param.y_max - fr->param.y_min)/30.0;
	if (keycode == ARROW_DOWN)
	{
		fr->param.y_max += step;
		fr->param.y_min += step;
	}
	else
	{
		fr->param.y_max -= step;
		fr->param.y_min -= step;
	}
}

void		move_re(t_fractal *fr, int keycode)
{
	double	step;

	step = (fr->param.x_max - fr->param.x_min)/30.0;
	if (keycode == ARROW_LEFT)
	{
		fr->param.x_max += step;
		fr->param.x_min += step;
	}
	else
	{
		fr->param.x_max -= step;
		fr->param.x_min -= step;
	}
}

void		modify_iter(t_fractal *fr, int keycode)
{
	if (keycode == PLUS)
		fr->param.max_iter += 10;
	else if (fr->param.max_iter > 1)
		fr->param.max_iter -= 10;
}

void			fix_julia(t_fractal *fr, int keycode)
{
	(void)keycode;
	fr->param.fix_julia = !fr->param.fix_julia;
}

void			reset(t_fractal *fr, int keycode)
{
	(void)keycode;
	t_param			param[6] = {
		{-2.5, 1.5, -1.5, 1.5, EXIT_TIME, false, {0, 0}, &mandelbrot},
		{-2.0, 2.0, -1.5, 1.5, EXIT_TIME, false, {0, 0}, &julia},
		{-2.5, 1.5, -1.0, 2.0, EXIT_TIME, false, {0, 0}, &burning_ship},
		{-2.2, 1.8, -1.5, 1.5, EXIT_TIME, false, {0, 0}, &mandelbar},
		{-1.33, 1.33, -0.7, 1.3, EXIT_TIME, false, {0, 0}, &phoenix},
		{-2.0, 2.0, -1.5, 1.5, EXIT_TIME, false, {0, 0}, &ocean},
	};

	fr->param = param[fr->name];
}

int		key_hook(int keycode, t_fractal *fr)
{
	static const t_shortcut	g_key[KEYBOARD_MAX] = {
		[ESC] = (t_shortcut)close_hook,
		[ARROW_UP] = move_im,
		[ARROW_DOWN] = move_im,
		[ARROW_LEFT] = move_re,
		[ARROW_RIGHT] = move_re,
		[PLUS] = modify_iter,
		[MINUS] = modify_iter,
		// [C] = change_colors,
		[F] = fix_julia,
		[R] = reset,
	};

	if (keycode <= KEYBOARD_MAX && g_key[keycode])
	{
		(*g_key[keycode])(fr, keycode);
		thread_init(fr);
	}
	return (0);
}

void	events_control(t_fractal *fr)
{
	mlx_hook(fr->window, DESTROY_NOTIFY, 0, close_hook, fr);
	mlx_hook(fr->window, KEY_PRESS, 1, key_hook, fr);
	mlx_hook(fr->window, BUTTON_PRESS, 1L << 2, mouse_pressed, fr);
	mlx_hook(fr->window, BUTTON_RELEASE, 1L << 3, mouse_released, fr);
	mlx_hook(fr->window, MOTION_NOTIFY, 1L << 8, mouse_move, fr);
}
