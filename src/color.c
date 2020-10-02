/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 18:22:21 by diona             #+#    #+#             */
/*   Updated: 2020/10/01 18:22:21 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				color_bernstein(double t)
{
	int		r;
	int		g;
	int		b;

	r = (int)(9.0 * (1 - t) * t * t * t * 255.0);
	g = (int)(15.0 * (1 - t) * (1 - t) * t * t * 255.0);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255.0);
	return ((r << 0x10) | (g << 0x8) | b);
}

int				color_grayscale(double t)
{
	int		r;
	int		g;
	int		b;

	r = (int)((1 - t) * 0.0 + t * 255.0);
	g = (int)((1 - t) * 0.0 + t * 255.0);
	b = (int)((1 - t) * 0.0 + t * 255.0);
	return ((r << 0x10) | (g << 0x8) | b);
}

int				color_hsv(double h)
{
	int			i;
	double		vm;
	double		vi;
	double		vd;

	h *= 360.0;
	i = ((int)h / 60) % 6;
	vm = ((100 - SATURATION) * VALUE) / 100;
	vi = vm + (VALUE - vm) * (fmod(h, 60) / 60);
	vd = VALUE - (VALUE - vm) * (fmod(h, 60) / 60);
	vm *= 2.55;
	vi *= 2.55;
	vd *= 2.55;
	if (i < 1)
		return (((int)(VALUE * 2.55) << 0x10) | ((int)vi << 0x8) | (int)vm);
	if (i < 2)
		return (((int)vd << 0x10) | ((int)(VALUE * 2.55) << 0x8) | (int)vm);
	if (i < 3)
		return (((int)vm << 0x10) | ((int)(VALUE * 2.55) << 0x8) | (int)vi);
	if (i < 4)
		return (((int)vm << 0x10) | ((int)vd << 0x8) | (int)(VALUE * 2.55));
	if (i < 5)
		return (((int)vi << 0x10) | ((int)vm << 0x8) | (int)(VALUE * 2.55));
	return (((int)(VALUE * 2.55) << 0x10) | ((int)vm << 0x8) | (int)vd);
}
