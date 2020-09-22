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

# define WIN_HEIGHT	900
# define WIN_WIDTH	1050

# define BLACK		0x00000000
# define SATURATION	70.0
# define VALUE		70.0

# define THREADS	16
# define EXIT_TIME	150

typedef struct {
	bool			hold;
	bool			hold_rmb;
	int				x;
	int				y;
	// int				prev_x;
	// int				prev_y;
}	t_mouse;

typedef struct		s_complex {
	double			re;
	double			im;
}					t_complex;

typedef enum		s_type {
	MANDELBROT = 0,
	JULIA,
	BURN_SHIP,
	MANDELBAR,
	PHOENIX,
	OCEAN
}					t_type;

typedef struct	s_param {
	double		x_min;
	double		x_max;
	double		y_min;
	double		y_max;
	int			max_iter;
	int			(*func)(t_complex, t_complex, int);
}				t_param;

typedef struct		s_fractal {
	t_mouse			*mouse;
	void			*mlx;
	void			*window;
	void			*image;
	int				*img_ptr;
//	void			*menu;
//	int				*menu_ptr;
	int				bpp;
	int				line_size;
	int				endian;
	t_param			param;
	int				thread_id;
	t_type			name;
}					t_fractal;

void	exit_err(char *err_msg);
void	thread_init(t_fractal *fr);
void	events_control(t_fractal *fr);
int		mandelbrot(t_complex c, t_complex m, int max_iter);
int		julia(t_complex c, t_complex m, int max_iter);
int		burning_ship(t_complex c, t_complex m, int max_iter);
int		mandelbar(t_complex c, t_complex m, int max_iter);
int		phoenix(t_complex c, t_complex m, int max_iter);
int		ocean(t_complex c, t_complex m, int max_iter);

#endif
