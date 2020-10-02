/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diona <diona@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 18:05:46 by diona             #+#    #+#             */
/*   Updated: 2020/07/25 18:41:01 by diona            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_H
# define KEY_H

# include "fractol.h"

# define KEYBOARD_MAX		127

# define ESC				0x35

# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# define ARROW_UP			126
# define ARROW_DOWN			125
# define ARROW_LEFT			123
# define ARROW_RIGHT		124

# define C					8
# define R					15
# define F					3
# define RETURN				36

# define PLUS				24
# define MINUS				27

# define KEY_PRESS			02
# define KEY_RELEASE		03
# define BUTTON_PRESS		04
# define BUTTON_RELEASE		05
# define MOTION_NOTIFY		06
# define DESTROY_NOTIFY		17

typedef void	(*t_shortcut)(t_fractal *, int);
typedef int		(*t_colormap)(double);

int				mouse_pressed(int button, int x, int y, t_fractal *fr);
int				mouse_move(int x, int y, t_fractal *fr);

int				close_hook(t_fractal *fr, int keycode);
void			move_im(t_fractal *fr, int keycode);
void			move_re(t_fractal *fr, int keycode);
void			modify_iter(t_fractal *fr, int keycode);
void			fix_julia(t_fractal *fr, int keycode);
void			change_colors(t_fractal *fr, int keycode);

#endif
