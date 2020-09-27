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

// void	zoom(t_param *p, double x, double y, double factor)
// {
// 	t_complex	m;
// 	double dx = (p->x_max - p->x_min) * (1 - 1 / factor);
// 	double dy = (p->y_max - p->y_min) * (1 - 1 / factor);
// 	double px, py;

// 	m = get_complex(x, y, p);
// 	px = (m.re - p->x_min)/(p->x_max - p->x_min);
// 	py = (m.im - p->y_min)/(p->y_max - p->y_min);
// 	p->x_min += dx*px;
// 	p->x_max -= dx*(1-px);
// 	p->y_min += dy*py;
// 	p->y_max -= dy*(1-py);
// 	if (factor > 1)
// 		p->max_iter += 10;
// }
void	zoom(t_param *p, int x, int y, double factor)
{
	t_complex	m;
	double dx = (p->x_max - p->x_min) * (1 - 1 / factor);
	double dy = (p->y_max - p->y_min) * (1 - 1 / factor);
	double px, py;

	m = get_complex(x, y, p);
	px = (m.re - p->x_min)/(p->x_max - p->x_min);
	py = (m.im - p->y_min)/(p->y_max - p->y_min);
	p->x_min += dx*px;
	p->x_max -= dx*(1-px);
	p->y_min += dy*py;
	p->y_max -= dy*(1-py);
	if (factor > 1)
		p->max_iter++;
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
		zoom(&fr->param, x, y, 1.05);
		thread_init(fr);
	}
	else if (button == MOUSE_SCROLL_DOWN)
	{
		zoom(&fr->param, x, y, 0.95);
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
	if (fr->name == JULIA && fr->param.fix_julia == false)
	{
		fr->param.m = get_complex(x, y, &fr->param);
		thread_init(fr);
	}
	fr->mouse->x = x;
	fr->mouse->y = y;
	return (0);
}
