/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:29:59 by diona             #+#    #+#             */
/*   Updated: 2020/07/30 18:29:59 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		choose_type(char *name, t_fractal *fractal)
{
	if (!ft_strcmp("Mandelbrot", name))
		fractal->name = MANDELBROT;
	else if (!ft_strcmp("Julia", name))
		fractal->name = JULIA;
	else
		exit_err(USAGE);
}

void			fractal_init(char *name, t_fractal *fractal)
{
	/* x_min x_max y_min y_max max_iter */
	t_param			param[3] = {
		{-2.5, 1.0, -1.5, 1.5, EXIT_TIME, &count_mandelbrot},
		{-2.5, 1.5, -2.0, 2.0, EXIT_TIME, &count_mandelbrot},
		{-2.5, 1.5, -2.0, 2.0, EXIT_TIME, &count_mandelbrot},
	};

	fractal->line_size = WIN_WIDTH;
	fractal->mlx = mlx_init();
	fractal->window = mlx_new_window(fractal->mlx, WIN_WIDTH, WIN_HEIGHT, name);
	fractal->image = mlx_new_image(fractal->mlx, WIN_WIDTH, WIN_HEIGHT);
	fractal->img_ptr = (int*)mlx_get_data_addr(fractal->image, &fractal->bpp,
			&fractal->line_size, &fractal->endian);
	fractal->param = param[fractal->name];
}

int				main(int argc, char **argv)
{
	t_fractal	fractal;
	t_mouse		mouse;

	ft_memset(&fractal, 0, sizeof(t_fractal));
	fractal.mouse = ft_memset(&mouse, 0, sizeof(t_mouse));
	if (argc != 2)
		exit_err(USAGE);
	choose_type(argv[1], &fractal);
	fractal_init(argv[1], &fractal);
	// if (fractal.name == MANDELBROT)
	draw(&fractal);
	events_control(&fractal);
	mlx_loop(fractal.mlx);
	return (EXIT_SUCCESS);
}
