/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 17:45:39 by diona             #+#    #+#             */
/*   Updated: 2020/10/01 17:45:39 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "key.h"

void	move_im(t_fractal *fr, int keycode)
{
	double	step;

	step = (fr->param.y_max - fr->param.y_min) / 30.0;
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

void	move_re(t_fractal *fr, int keycode)
{
	double	step;

	step = (fr->param.x_max - fr->param.x_min) / 30.0;
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

void	modify_iter(t_fractal *fr, int keycode)
{
	if (keycode == PLUS)
		fr->param.max_iter += 10;
	else if (fr->param.max_iter > 10)
		fr->param.max_iter -= 10;
}

void	fix_julia(t_fractal *fr, int keycode)
{
	(void)keycode;
	fr->param.fix_julia = !fr->param.fix_julia;
}

void	change_colors(t_fractal *fr, int keycode)
{
	static	int			n;
	static t_colormap	g_colormap[3] = {
		color_bernstein, color_grayscale, color_hsv,
	};

	(void)keycode;
	n = n < 2 ? n + 1 : 0;
	fr->color = g_colormap[n];
}
