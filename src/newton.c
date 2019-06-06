/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 15:42:10 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 15:42:43 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	z_calc(double *x, double *y, double x2, double y2)
{
	double x4;
	double y4;
	double tmp;
	double denominator;

	tmp = *x;
	x4 = pow(*x, 4);
	y4 = pow(*y, 4);
	denominator = 3.0 * x4 + 6.0 * x2 * y2 + 3.0 * y4;
	*x -= (pow(*x, 5) + 2.0 * y2 * pow(*x, 3) + y4 * tmp + y2 - x2)\
			/ (denominator);
	*y -= (x4 * *y + 2.0 * x2 * pow(*y, 3) + 2.0 * tmp * *y + pow(*y, 5))\
			/ (denominator);
}

static int	check_roots(t_fractal *f, double tolerance, int col_mod)
{
	double	roots_re[3];
	double	roots_im[3];
	int		i;

	roots_re[0] = 1.0;
	roots_re[1] = -0.5;
	roots_re[2] = -0.5;
	roots_im[0] = 0.0;
	roots_im[1] = sqrt(3.0) / 2.0;
	roots_im[2] = -1.0 * sqrt(3.0) / 2.0;
	i = -1;
	while (++i < 3)
		if ((fabs(f->z_re - roots_re[i]) <= tolerance) && \
			(fabs(f->z_im - roots_im[i]) <= tolerance))
			return (f->color = get_color(f->iter, 1, 1, col_mod));
	return (0);
}

void		draw_newton(t_mlx *m, int x0, int y0)
{
	int			x_ofset;
	t_fractal	f;
	double		tmp;

	x_ofset = SCR_WID - x0 - 80;
	while (x0 + x_ofset < SCR_WID)
	{
		tmp = (m->x + x0) * (m->re_max - m->re_min) / SCR_WID + m->re_min;
		y0 = -1;
		while (++y0 < SCR_HEI && (!(f.color = 0)))
		{
			f.z_re = tmp;
			f.z_im = (m->y + y0) * (m->im_min - m->im_max) \
			/ SCR_HEI + m->im_max;
			f.iter = 0;
			while (++(f.iter) <= (unsigned int)m->deep)
			{
				z_calc(&f.z_re, &f.z_im, pow(f.z_re, 2), pow(f.z_im, 2));
				if (check_roots(&f, m->tolerance, m->col))
					break ;
			}
			img_pixel_put(m, x0, y0, f.color);
		}
		x0++;
	}
}
