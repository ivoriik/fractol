/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 19:09:08 by vbespalk          #+#    #+#             */
/*   Updated: 2018/07/17 19:09:11 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calc_mandelbrot(t_fractal *f, int mode)
{
	f->z_im2 = f->z_im * f->z_im;
	f->z_re2 = f->z_re * f->z_re;
	if ((f->z_im2 + f->z_re2) > 4)
	{
		f->color = get_color(f->iter, f->z_re2, f->z_im2, mode);
		return (f->color);
	}
	f->z_im = (2 * f->z_re * f->z_im) + f->c_im;
	f->z_re = f->z_re2 - f->z_im2 + f->c_re;
	return (0);
}

void		draw_mandelbrot(t_mlx *m, int x0, int y0)
{
	t_fractal	f;
	int			x_ofset;

	x_ofset = SCR_WID - x0 - 80;
	while (x0 + x_ofset < SCR_WID)
	{
		f.c_re = (m->x + x0) * (m->re_max - m->re_min) / SCR_WID + m->re_min;
		y0 = -1;
		while (++y0 < SCR_HEI)
		{
			f.color = 0;
			f.c_im = (m->y + y0) * (m->im_min - m->im_max) \
			/ SCR_HEI + m->im_max;
			f.iter = 0;
			f.z_im = 0;
			f.z_re = 0;
			while (++(f.iter) <= (unsigned int)m->deep)
				if (calc_mandelbrot(&f, m->col))
					break ;
			img_pixel_put(m, x0, y0, f.color);
		}
		x0++;
	}
}
