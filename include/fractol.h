/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:29:26 by diona             #+#    #+#             */
/*   Updated: 2020/07/30 18:29:26 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <mlx.h>

# include "libft.h"
# include "errors.h"

# define WIN_HEIGHT	960
# define WIN_WIDTH	1280

# define BLACK		0x00000000
# define SATURATION	70.0
# define VALUE		70.0

# define THREADS	16
# define EXIT_TIME	250

typedef struct		s_complex {
	double			re;
	double			im;
}					t_complex;

typedef enum		e_type {
	MANDELBROT = 0,
	JULIA,
	BURN_SHIP,
	MANDELBAR,
	PHOENIX,
	OCEAN
}					t_type;

typedef struct		s_param {
	double			x_min;
	double			x_max;
	double			y_min;
	double			y_max;
	double			dx;
	double			dy;
	int				max_iter;
	bool			fix_julia;
	t_complex		m;
	int				(*func)(t_complex, t_complex, int);
}					t_param;

typedef struct		s_fractal {
	void			*mlx;
	void			*window;
	void			*image;
	int				*img_ptr;
	int				bpp;
	int				line_size;
	int				endian;
	t_param			param;
	int				thread_id;
	t_type			name;
	int				(*color)(double);
}					t_fractal;

t_complex			get_complex(int x, int y, t_param *fr);
void				exit_err(int err_code);

void				thread_init(t_fractal *fr);
void				events_control(t_fractal *fr);

int					mandelbrot(t_complex c, t_complex m, int max_iter);
int					julia(t_complex c, t_complex m, int max_iter);
int					burning_ship(t_complex c, t_complex m, int max_iter);
int					mandelbar(t_complex c, t_complex m, int max_iter);
int					phoenix(t_complex c, t_complex m, int max_iter);
int					ocean(t_complex c, t_complex m, int max_iter);

int					color_bernstein(double t);
int					color_grayscale(double t);
int					color_hsv(double h);

#endif
