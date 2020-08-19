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

int		close_hook(t_fractal *fr, int keycode)
{
	(void)keycode;
	// mlx_destroy_image(fr->mlx, fr->menu);
	mlx_destroy_image(fr->mlx, fr->image);
	mlx_destroy_window(fr->mlx, fr->window);
	exit(EXIT_SUCCESS);
}

int		key_hook(int keycode, t_fractal *fr)
{
	static const t_shortcut	g_key[KEYBOARD_MAX] = {
		[ESC] = (t_shortcut)close_hook,
		// [ARROW_UP] = move_up,
		// [ARROW_DOWN] = move_up,
		// [ARROW_LEFT] = move_side,
		// [ARROW_RIGHT] = move_side,
		// [PLUS] = flatten,
		// [MINUS] = flatten,
		// [KEY_1] = change_angle_x,
		// [KEY_2] = change_angle_x,
		// [KEY_3] = change_angle_y,
		// [KEY_4] = change_angle_y,
		// [KEY_5] = change_angle_z,
		// [KEY_6] = change_angle_z,
		// [C] = change_colors,
		// [M] = change_blur,
		// [I] = change_projection,
		// [P] = change_projection
	};

	if (keycode <= KEYBOARD_MAX && g_key[keycode])
		(*g_key[keycode])(fr, keycode);
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
