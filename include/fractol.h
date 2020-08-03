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
# define WIN_WIDTH	1400
// # define MENU_WIDTH	250

# define WHITE		0x00FFFFFF
# define BLACK		0x00000000

# define EXIT_TIME	1000
// typedef struct {
// 	bool			hold;
// 	bool			hold_rmb;
// 	int				x;
// 	int				y;
// 	int				prev_x;
// 	int				prev_y;
// }	t_mouse;

// typedef enum {
// 	ISO,
// 	PARALLEL
// }	t_projection;

typedef struct		s_complex {
	float			re;
	float			im;
}					t_complex;

// typedef struct {
// 	t_projection	projection;
// 	double			angle_x;
// 	double			angle_y;
// 	double			angle_z;
// 	int				ratio_z;
// 	int				zoom;
// 	int				offset_x;
// 	int				offset_y;
// }	t_camera;

typedef struct		s_fractal {
//	t_camera		*camera;
//	t_mouse			*mouse;
	void			*mlx;
	void			*window;
	void			*image;
	int				*img_ptr;
//	void			*menu;
//	int				*menu_ptr;
	int				bpp;
	int				line_size;
	int				endian;
}					t_fractal;

void	exit_err(char *err_msg);

#endif
