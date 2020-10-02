/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 16:51:38 by diona             #+#    #+#             */
/*   Updated: 2020/08/03 16:51:38 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <errno.h>

void	exit_err(int err_code)
{
	if (errno != 0)
		strerror(errno);
	else if (err_code == USAGE)
		ft_putendl_fd("usage:\t ./fractol name\n\n"
					"options: Mandelbrot\n\t"
					" Julia\n\t"
					" Burning ship\n\t"
					" Mandelbar\n\t"
					" Phoenix\n\t"
					" Ocean\n\n"
					"controls:[r] – reset,\n\t [c] – color change,\n\t"
					" [+/-] – change iteration number,\n\t"
					" [return] – next fractal,\n\t"
					" [F] – fix Julia parameter,\n\t"
					" move with arrows, zoom with mouse\n", STDERR_FILENO);
	else if (err_code == MEMORY)
		ft_putendl_fd("Memory allocation failed\n", STDERR_FILENO);
	else if (err_code == THREADS)
		ft_putendl_fd("Error creating threads\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}
