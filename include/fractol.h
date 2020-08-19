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

# define WHITE		0x00FFFFFF
# define BLACK		0x00000000

# define EXIT_TIME	1500

typedef struct {
	bool			hold;
	bool			hold_rmb;
	int				x;
	int				y;
	int				prev_x;
	int				prev_y;
}	t_mouse;

typedef struct		s_complex {
	float			re;
	float			im;
}					t_complex;

typedef enum		s_type {
	MANDELBROT,
	JULIA
}					t_type;

typedef struct	s_param {
	float		x_min;
	float		x_max;
	float		y_min;
	float		y_max;
	int		(*func)(t_complex);
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
	t_type			name;
}					t_fractal;

void	exit_err(char *err_msg);
void	draw(t_fractal *fr);
void	events_control(t_fractal *fr);
int		count_mandelbrot(t_complex c);

#endif
