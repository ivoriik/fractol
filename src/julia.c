/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:30:13 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 15:30:17 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	calc_julia(t_fractal *f, int mode)
{
	f->z_im2 = f->z_im * f->z_im;
	f->z_re2 = f->z_re * f->z_re;
	if ((f->z_im2 + f->z_re2) > 16)
	{
		f->color = get_color(f->iter, f->z_re2, f->z_im2, mode);
		return (f->color);
	}
	f->z_im = (2.0 * f->z_re * f->z_im) + f->c_im;
	f->z_re = f->z_re2 - f->z_im2 + f->c_re;
	return (0);
}

double		nb_to_range(double nb, int min, int max, int range)
{
	if (range == 0)
		ft_error("impossible to convert to 0 range");
	if (min > max)
		ft_swap(&min, &max, sizeof(min));
	if (++nb < range / 2.0)
		return ((nb * 2.0 / (double)range) - 1);
	if (nb == range / 2.0)
		return (0);
	return ((nb - range / 2) * 2.0 / (double)range);
}

void		draw_julia(t_mlx *m, int x0, int y0)
{
	int			x_ofset;
	t_fractal	f;
	double		tmp;

	f.c_im = nb_to_range((double)m->y_c, 1, -1, SCR_HEI);
	f.c_re = nb_to_range((double)m->x_c, 1, -1, SCR_WID);
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
				if (calc_julia(&f, m->col))
					break ;
			img_pixel_put(m, x0, y0, f.color);
		}
		x0++;
	}
}
