/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:04:52 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 17:04:54 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

unsigned int	get_rgb(unsigned int red, unsigned int green, unsigned int blue)
{
	unsigned int color;

	color = red;
	color = (color << 8) + green;
	color = (color << 8) + blue;
	return (color);
}

unsigned int	hsv_to_rgb(double h, double s, double v)
{
	t_color	rgb;
	int		i;
	double	hh;

	h = h == 360 ? 0 : h / 60.0;
	i = (int)trunc(h);
	hh = h - i;
	rgb.r = v * (1.0 - s);
	rgb.g = v * (1.0 - s * hh);
	rgb.b = v * (1.0 - s * (1.0 - hh));
	if (i == 0)
		return (get_rgb(v * 255, rgb.b * 255, rgb.r * 255));
	if (i == 1)
		return (get_rgb(rgb.g * 255, v * 255, rgb.r * 255));
	if (i == 2)
		return (get_rgb(rgb.r * 255, v * 255, rgb.b * 255));
	if (i == 3)
		return (get_rgb(rgb.r * 255, rgb.g * 255, v * 255));
	if (i == 4)
		return (get_rgb(rgb.b * 255, rgb.r * 255, v * 255));
	else
		return (get_rgb(v * 255, rgb.r * 255, rgb.g * 255));
}

unsigned int	get_color(unsigned int iter, double re, double im, int mode)
{
	double smooth;

	smooth = iter + 1 - log(log(fabs(re + im))) / log(2.0);
	if (mode == 4)
		return (hsv_to_rgb(0.0f + 5 * smooth, 0.6f, 0.9f));
	if (mode == 3)
		return (hsv_to_rgb(160.0f + 5 * smooth, 0.8f, 0.7f));
	if (mode == 2)
		return (hsv_to_rgb(220.0f + 5 * smooth, 0.7f, 0.6f));
	if (mode == 1)
		return (get_rgb(0, (unsigned int)(2 * smooth), \
			(unsigned int)(8 * smooth)));
		return (get_rgb((unsigned int)(5 + 5 * smooth), \
		(unsigned int)(5 + 5 * smooth), (unsigned int)(5 + 5 * smooth)));
}
