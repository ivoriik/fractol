/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:02:11 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 17:02:14 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <pthread.h>
# include <sys/time.h>

# define SCR_WID	800
# define SCR_HEI	800
# define RE_MAX		2
# define RE_MIN		-2
# define IM_MAX		2
# define IM_MIN		-2
# define MAX_ITER	50
# define NB_THREADS	10
# define SC_FACTOR	1.01
# define TOLERANCE	0.00000001
# define MANDELBROT "mandelbrot"
# define JULIA "julia"
# define NEWTON "newton"
# define JULIAS_SIN "julias_sin"

typedef	struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*data_add;
	int				bpp;
	int				s_line;
	int				endian;
	float			deep;
	int				x_coord;
	int				y_coord;
	int				x_c;
	int				y_c;
	pthread_mutex_t a_lock;
	double			re_min;
	double			re_max;
	double			im_min;
	double			im_max;
	double			scale;
	double			tolerance;
	int				x;
	int				y;
	int				automode;
	int				frozen;
	int				col;
	void			(*fractol)();
}					t_mlx;

typedef	struct		s_fractal
{
	double			z_im;
	double			z_re;
	unsigned int	iter;
	unsigned int	color;
	double			c_im;
	double			c_re;
	double			z_im2;
	double			z_re2;
}					t_fractal;

typedef	struct		s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

void				change_pal(int key, t_mlx *mlx);
void				configuration(void);
void				deep(int key, t_mlx *mlx, int mouse);
void				draw_julia(t_mlx *mlx, int x0, int y0);
void				draw_julia_sin(t_mlx *mlx, int x0, int y0);
void				draw_mandelbrot(t_mlx *mlx, int x0, int y0);
void				draw_newton(t_mlx *mlx, int x0, int y0);
void				ft_error(char *message);
int					ft_perror(char *message);
int					hook_keydown(int key, void *mlx);
unsigned int		hsv_to_rgb(double h, double s, double v);
unsigned int		get_color(unsigned int iter, \
	double re, double im, int mode);
unsigned int		get_rgb(unsigned int red, \
	unsigned int green, unsigned int blue);
void				get_tolerance(int key, t_mlx *mlx);
void				img_pixel_put(t_mlx *mlx, int x, int y, unsigned int color);
int					loop_hook(void *param);
int					mouse_hook(int button, int x, int y, void *mlx);
int					mouse_scan(int x, int y, void *mlx);
void				moving(int key, t_mlx *mlx);
int					mult_threads(t_mlx *mlx);
double				nb_to_range(double nb, int min, int max, int range);
void				print_legend(t_mlx *mlx);
void				put_to_window(t_mlx *ptr);
void				reset(t_mlx *mlx);
void				scaling(t_mlx *mlx, int x, int y);

#endif
