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
#include <stdio.h>

int		check_name(char *name)
{
	if (!ft_strcmp("Mandelbrot", name))
		return (1);
	else if (!ft_strcmp("Julia", name))
		return (2);
	else
		return (0);
}

void	fractal_init(char *name, t_fractal *fractal)
{
	fractal->line_size = WIN_WIDTH;
	fractal->mlx = mlx_init();
	fractal->window = mlx_new_window(fractal->mlx, WIN_WIDTH, WIN_HEIGHT, name);
	fractal->image = mlx_new_image(fractal->mlx, WIN_WIDTH, WIN_HEIGHT);
	fractal->img_ptr = (int*)mlx_get_data_addr(fractal->image, &fractal->bpp,
			&fractal->line_size, &fractal->endian);
}

static void		put_pixel(t_fractal *fr, int x, int y, int color)
{
	// if (x >= 0 && x < WIN_WIDTH && y >= 0 && y < WIN_HEIGHT)
		fr->img_ptr[y * WIN_WIDTH + x] = color;
}

int		count_mandelbrot(t_complex c)
{
	int			n;
	t_complex	z;
	float		temp;

	n = 0;
	z.re = 0;
	z.im = 0;
	while (n < EXIT_TIME)
	{
		if (((z.im*z.im) + (z.re*z.re)) > 4)
			return (0);
		temp = z.re*z.re - z.im*z.im + c.re;
		z.im = 2*z.re*z.im + c.im;
		z.re = temp;
		n++;
	}
	return (1);
}

t_complex	get_complex(int x, int y)
{
	t_complex	z;
	float		k;

	k = (float)2/WIN_HEIGHT;
	z.re = k * (float)x;
	z.im = k * (float)y;
	return (z);
}

void	mandelbrot(t_fractal *fr)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (count_mandelbrot(get_complex(x - 2*WIN_WIDTH/3, y - WIN_HEIGHT/2)))
				put_pixel(fr, x, y, BLACK);
			else
				put_pixel(fr, x, y, WHITE);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fr->mlx, fr->window, fr->image, 0, 0);
}

// void	julia(t_fractal *fr)
// {
// 	(void*)fr;
// 	return;
// }

int		main(int argc, char **argv)
{
	t_fractal	fractal;
	int			fr_num;

	fr_num = 0;
	if (argc != 2 || !(fr_num = check_name(argv[1])))
		exit_err(USAGE);
	ft_memset(&fractal, 0, sizeof(t_fractal));
	fractal_init(argv[1], &fractal);
	if (fr_num == 1)
		mandelbrot(&fractal);
	// else if (fr_num == 2)
	// 	julia(&fractal);
	// events_control(&fractal);
	mlx_loop(fractal.mlx);
	return (EXIT_SUCCESS);
}
