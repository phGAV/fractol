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

void	zoom(t_param *p, int x, int y, double factor)
{
	t_complex	m;
	double		dx;
	double		dy;
	double		px;
	double		py;

	m = get_complex(x, y, p);
	dx = p->dx * (1 - 1 / factor);
	dy = p->dy * (1 - 1 / factor);
	px = (m.re - p->x_min) / p->dx;
	py = (m.im - p->y_min) / p->dy;
	p->x_min += dx * px;
	p->y_min += dy * py;
	p->dx -= dx;
	p->dy -= dy;
	p->x_max = p->dx + p->x_min;
	p->y_max = p->dy + p->y_min;
	if (factor > 1)
		p->max_iter++;
}

int		mouse_pressed(int button, int x, int y, t_fractal *fr)
{
	(void)x;
	(void)y;
	if (button == MOUSE_SCROLL_UP)
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

int		mouse_move(int x, int y, t_fractal *fr)
{
	if (fr->name == JULIA && fr->param.fix_julia == false)
	{
		fr->param.m = get_complex(x, y, &fr->param);
		thread_init(fr);
	}
	return (0);
}
