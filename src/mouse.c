/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 23:12:19 by diona             #+#    #+#             */
/*   Updated: 2020/07/20 21:55:44 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key.h"

float interpolate(float start, float end, float interpolation)
{
    return start + ((end - start) * interpolation);
}

void	zoom_in(t_param *param, float x, float y)
{
	float factor = 1.05;
	t_complex	m;
	float dx;
	float dy;
	float interpolation;

	dx = (param->x_max - param->x_min) / WIN_WIDTH;
	dy = (param->y_max - param->y_min) / WIN_HEIGHT;
	m.re = param->x_min + x * dx;
	m.im = param->y_max - y * dy;

	interpolation = 1.0 / factor;
	param->x_min = interpolate(m.re, param->x_min, interpolation);
	param->x_max = interpolate(m.re, param->x_max, interpolation);
	param->y_min = interpolate(m.im, param->y_min, interpolation);
	param->y_max = interpolate(m.im, param->y_max, interpolation);
}

int		mouse_pressed(int button, int x, int y, t_fractal *fr)
{
	(void)x;
	(void)y;
	if (button == MOUSE_LEFT_BUTTON)
		fr->mouse->hold = true;
	else if (button == MOUSE_RIGHT_BUTTON)
		fr->mouse->hold_rmb = true;
	else if (button == MOUSE_SCROLL_UP)
	{
		zoom_in(&fr->param, (float)x, (float)y);
		thread_init(fr);
		// draw(fr);
	}
	// else if (button == MOUSE_SCROLL_DOWN)
	// 	fr->camera->zoom > MIN_ZOOM ? fr->camera->zoom-- : MIN_ZOOM;
	return (0);
}

int		mouse_released(int button, int x, int y, t_fractal *fr)
{
	(void)button;
	(void)x;
	(void)y;
	fr->mouse->hold = false;
	fr->mouse->hold_rmb = false;
	return (0);
}

int		mouse_move(int x, int y, t_fractal *fr)
{
	fr->mouse->prev_x = fr->mouse->x;
	fr->mouse->prev_y = fr->mouse->y;
	fr->mouse->x = x;
	fr->mouse->y = y;
	if (fr->mouse->hold_rmb)
	{
		// fr->camera->angle_x -= (y - fdf->mouse->prev_y) * ANGLE_STEP;
		// fr->camera->angle_z -= (x - fdf->mouse->prev_x) * ANGLE_STEP;
	}
	else if (fr->mouse->hold)
	{
		// fdf->camera->offset_y -= fdf->mouse->prev_y - y;
		// fdf->camera->offset_x -= fdf->mouse->prev_x - x;
	}
	return (0);
}
