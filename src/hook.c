/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 17:35:53 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/19 17:35:55 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	scaling(t_mlx *mlx, int x, int y)
{
	double mouse_re;
	double mouse_im;

	mouse_re = ((double)x + (double)mlx->x) / \
	(SCR_WID / (mlx->re_max - mlx->re_min)) + mlx->re_min;
	mouse_im = ((double)y + (double)mlx->y) / \
	(SCR_HEI / (mlx->im_min - mlx->im_max)) + mlx->im_max;
	mlx->re_min = mouse_re + ((mlx->re_min - mouse_re) / mlx->scale);
	mlx->im_min = mouse_im + ((mlx->im_min - mouse_im) / mlx->scale);
	mlx->im_max = mouse_im + ((mlx->im_max - mouse_im) / mlx->scale);
	mlx->re_max = SCR_WID * ((mlx->im_max - mlx->im_min) \
		/ SCR_HEI) + mlx->re_min;
}

void	ft_exit(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx_ptr, mlx->img_ptr);
	exit(0);
}

int		hook_keydown(int key, void *mlx)
{
	t_mlx *ptr;

	ptr = (t_mlx *)mlx;
	if (key == 53)
		ft_exit(ptr);
	if (key == 69 || key == 78)
		deep(key, ptr, 0);
	if (key == 84 || key == 86 || key == 88 || key == 91)
		moving(key, ptr);
	if (key == 67 || key == 75)
		get_tolerance(key, ptr);
	if (key == 76)
	{
		ptr->scale = SC_FACTOR;
		ptr->automode = !(ptr->automode);
	}
	if (key == 81)
		ptr->frozen = !(ptr->frozen);
	if (key == 82)
		reset(ptr);
	if (key == 123 || key == 124)
		change_pal(key, ptr);
	put_to_window(ptr);
	return (0);
}

int		mouse_hook(int button, int x, int y, void *mlx)
{
	t_mlx *ptr;

	ptr = (t_mlx *)mlx;
	if (button == 1 || button == 2)
		deep(button, ptr, 1);
	if (button == 4 || button == 5)
	{
		if (button == 4)
			ptr->scale = 1.0 / SC_FACTOR;
		if (button == 5)
			ptr->scale = SC_FACTOR;
		scaling(ptr, x, y);
	}
	put_to_window(ptr);
	return (0);
}

int		mouse_scan(int x, int y, void *mlx)
{
	t_mlx *ptr;

	ptr = (t_mlx *)mlx;
	if (!(x >= 0 && x < SCR_WID && y >= 0 && y < SCR_HEI))
		return (0);
	ptr->x_coord = x;
	ptr->y_coord = y;
	if (!ptr->frozen)
	{
		ptr->x_c = ptr->x_coord;
		ptr->y_c = ptr->y_coord;
	}
	mlx_clear_window(ptr->mlx_ptr, ptr->win_ptr);
	if ((ptr->fractol == draw_julia || \
		ptr->fractol == draw_julia_sin) && !ptr->frozen)
	{
		put_to_window(ptr);
		return (0);
	}
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img_ptr, 0, 0);
	print_legend(ptr);
	return (0);
}
