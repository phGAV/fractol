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
	else if (!ft_strcmp("Burning ship", name))
		fractal->name = BURN_SHIP;
	else if (!ft_strcmp("Mandelbar", name))
		fractal->name = MANDELBAR;
	else if (!ft_strcmp("Phoenix", name))
		fractal->name = PHOENIX;
	else if (!ft_strcmp("Ocean", name))
		fractal->name = OCEAN;
	else
		exit_err(USAGE);
}

void			fractal_init(char *name, t_fractal *fractal)
{
	static t_param			param[6] = {
	{-2.5, 1.5, -1.5, 1.5, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &mandelbrot},
	{-2.0, 2.0, -1.5, 1.5, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &julia},
	{-2.5, 1.5, -1.0, 2.0, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &burning_ship},
	{-2.2, 1.8, -1.5, 1.5, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &mandelbar},
	{-1.33, 1.33, -0.7, 1.3, 2.66, 2.0, EXIT_TIME, false, {0, 0}, &phoenix},
	{-2.0, 2.0, -1.5, 1.5, 4.0, 3.0, EXIT_TIME, false, {0, 0}, &ocean},
	};

	fractal->line_size = WIN_WIDTH;
	fractal->mlx = mlx_init();
	fractal->window = mlx_new_window(fractal->mlx, WIN_WIDTH, WIN_HEIGHT, name);
	fractal->image = mlx_new_image(fractal->mlx, WIN_WIDTH, WIN_HEIGHT);
	fractal->img_ptr = (int*)mlx_get_data_addr(fractal->image, &fractal->bpp,
			&fractal->line_size, &fractal->endian);
	fractal->param = param[fractal->name];
	fractal->color = color_bernstein;
}

int				main(int argc, char **argv)
{
	t_fractal	fractal;

	ft_memset(&fractal, 0, sizeof(t_fractal));
	if (argc != 2)
		exit_err(USAGE);
	choose_type(argv[1], &fractal);
	fractal_init(argv[1], &fractal);
	thread_init(&fractal);
	events_control(&fractal);
	mlx_loop(fractal.mlx);
	return (EXIT_SUCCESS);
}
