/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:51:04 by diona             #+#    #+#             */
/*   Updated: 2020/10/01 17:51:04 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key.h"

int		close_hook(t_fractal *fr, int keycode)
{
	(void)keycode;
	mlx_destroy_image(fr->mlx, fr->image);
	mlx_destroy_window(fr->mlx, fr->window);
	exit(EXIT_SUCCESS);
}

void	reset(t_fractal *fr, int keycode)
{
	static t_param			param[6] = {
	{-2.5, 1.5, -1.5, 1.5, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &mandelbrot},
	{-2.0, 2.0, -1.5, 1.5, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &julia},
	{-2.5, 1.5, -1.0, 2.0, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &burning_ship},
	{-2.2, 1.8, -1.5, 1.5, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &mandelbar},
	{-1.33, 1.33, -0.7, 1.3, 2.66, 2.0, EXIT_TIME, false, {0, 0}, &phoenix},
	{-2.0, 2.0, -1.5, 1.5, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &ocean},
	};

	(void)keycode;
	fr->param = param[fr->name];
}

void	change_fractal(t_fractal *fr, int keycode)
{
	(void)keycode;
	fr->name = fr->name < OCEAN ? fr->name + 1 : 0;
	reset(fr, keycode);
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
		[C] = change_colors,
		[F] = fix_julia,
		[R] = reset,
		[RETURN] = change_fractal,
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
	mlx_hook(fr->window, MOTION_NOTIFY, 1L << 8, mouse_move, fr);
}
