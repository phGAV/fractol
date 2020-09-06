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

double interpolate(double start, double end, double interpolation)
{
    return start + ((end - start) * interpolation);
}

void	zoom(t_param *param, double x, double y, double factor)
{
	t_complex	m;
	double		dx;
	double		dy;
	double		interpolation;

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
		zoom(&fr->param, (double)x, (double)y, 1.05);
		thread_init(fr);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		zoom(&fr->param, (double)x, (double)y, 0.95);
		thread_init(fr);
	}
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
	// fr->mouse->prev_x = fr->mouse->x;
	// fr->mouse->prev_y = fr->mouse->y;
	if (fr->name == JULIA)
	{
		fr->mouse->x = x;
		fr->mouse->y = y;
		thread_init(fr);
	}
	return (0);
}
