/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/05 22:48:57 by diona             #+#    #+#             */
/*   Updated: 2020/09/05 22:48:57 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mandelbrot(t_complex c, t_complex m, int max_iter)
{
	int			n;
	t_complex	z;
	double		temp;

	(void)m;
	n = 0;
	z.re = 0;
	z.im = 0;
	while (n < max_iter)
	{
		if (((z.im*z.im) + (z.re*z.re)) > 32)
			return (n);
		temp = z.re*z.re - z.im*z.im + c.re;
		z.im = 2*z.re*z.im + c.im;
		z.re = temp;
		n++;
	}
	return (n);
}

int		julia(t_complex c, t_complex m, int max_iter)
{
	int			n;
	t_complex	z;
	double		temp;

	n = 0;
	z.re = c.re;
	z.im = c.im;
	while (n < max_iter)
	{
		if (((z.im*z.im) + (z.re*z.re)) > 32)
			return (n);
		temp = z.re*z.re - z.im*z.im + m.re;
		z.im = 2*z.re*z.im + m.im;
		z.re = temp;
		n++;
	}
	return (n);
}

int		burning_ship(t_complex c, t_complex m, int max_iter)
{
	int			n;
	t_complex	z;
	double		temp;

	(void)m;
	n = 0;
	z.re = 0;
	z.im = 0;
	while (n < max_iter)
	{
		if (((z.im*z.im) + (z.re*z.re)) > 32)
			return (n);
		temp = z.re*z.re - z.im*z.im + c.re;
		z.im = -fabs(2*z.re*z.im) + c.im;
		z.re = temp;
		n++;
	}
	return (n);
}

int		mandelbar(t_complex c, t_complex m, int max_iter)
{
	int			n;
	t_complex	z;
	double		temp;

	(void)m;
	n = 0;
	z.re = 0;
	z.im = 0;
	while (n < max_iter)
	{
		if (((z.im*z.im) + (z.re*z.re)) > 32)
			return (n);
		temp = z.re*z.re - z.im*z.im + c.re;
		z.im = -2*z.re*z.im + c.im;
		z.re = temp;
		n++;
	}
	return (n);
}

int		phoenix(t_complex c, t_complex m, int max_iter)
{
	int			n;
	t_complex	z;
	t_complex	z_next;
	t_complex	z_prev;

	m.re = 0.5667;
	m.im = 0.0;
	n = 0;
	z.re = c.im;
	z.im = c.re;
	z_next.re = z.re*z.re - z.im*z.im + m.re - 0.5*z.re;
	z_next.im = 2*z.re*z.im + m.im - 0.5*z.im;
	z_prev = z;
	z = z_next;
	while (n < max_iter)
	{
		if (((z_next.im*z_next.im) + (z_next.re*z_next.re)) > 32)
			return (n);
		z_next.re = z.re*z.re - z.im*z.im + m.re - 0.5*z_prev.re;
		z_next.im = 2*z.re*z.im + m.im - 0.5*z_prev.im;
		z_prev = z;
		z = z_next;
		n++;
	}
	return (n);
}

int		ocean(t_complex c, t_complex m, int max_iter)
{
	int			n;
	t_complex	z;
	t_complex	z_next;
	t_complex	z_prev;

	(void)m;
	n = 0;
	z_prev.re = 0;
	z_prev.im = 0;
	z.re = z_prev.im;
	z.im = z_prev.re;
	while (n < max_iter)
	{
		if (((z_next.im*z_next.im) + (z_next.re*z_next.re)) > 32)
			return (n);
		z_next.im = z.re*z.re - z.im*z.im + c.re - 0.5*z_prev.re;
		z_next.re = 2*z.re*z.im + c.im - 0.5*z_prev.im;
		z_prev = z;
		z = z_next;
		n++;
	}
	return (n);
}
