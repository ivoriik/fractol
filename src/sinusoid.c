/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sinusoid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:44:34 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 15:44:37 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calc_julia_sin(t_fractal *f, int mode)
{
	double sin_re;
	double sin_im;

	sin_re = sin(f->z_re) * cosh(f->z_im);
	sin_im = cos(f->z_re) * sinh(f->z_im);
	f->z_re = sin_re * f->c_re - sin_im * f->c_im;
	f->z_im = sin_re * f->c_im + sin_im * f->c_re;
	if (fabs(f->z_im) > 50)
		f->color = get_color(f->iter, f->z_re, f->z_im, mode);
	return (f->color);
}

void		draw_julia_sin(t_mlx *m, int x0, int y0)
{
	int			x_ofset;
	t_fractal	f;
	double		tmp;

	f.c_im = 2 * nb_to_range((double)m->y_c, 1, -1, SCR_HEI);
	f.c_re = 1;
	x_ofset = SCR_WID - x0 - 80;
	while (x0 + x_ofset < SCR_WID)
	{
		tmp = (m->x + x0) * (m->re_max - m->re_min) / SCR_WID + m->re_min;
		y0 = -1;
		while (++y0 < SCR_HEI)
		{
			f.color = 0;
			f.z_re = tmp;
			f.z_im = (m->y + y0) * (m->im_min - m->im_max) \
			/ SCR_HEI + m->im_max;
			f.iter = 0;
			while (++(f.iter) <= (unsigned int)m->deep)
				if (calc_julia_sin(&f, m->col))
					break ;
			img_pixel_put(m, x0, y0, f.color);
		}
		x0++;
	}
}
