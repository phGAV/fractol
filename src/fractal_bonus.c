/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 18:04:38 by diona             #+#    #+#             */
/*   Updated: 2020/10/01 18:04:38 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		if (((z_next.im * z_next.im) + (z_next.re * z_next.re)) > 32)
			return (n);
		z_next.im = z.re * z.re - z.im * z.im + c.re - 0.5 * z_prev.re;
		z_next.re = 2 * z.re * z.im + c.im - 0.5 * z_prev.im;
		z_prev = z;
		z = z_next;
		n++;
	}
	return (n);
}
