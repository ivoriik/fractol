/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:26:37 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 17:26:39 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	moving(int key, t_mlx *mlx)
{
	if (key == 84)
		mlx->y += 5;
	if (key == 86)
		mlx->x -= 5;
	if (key == 88)
		mlx->x += 5;
	if (key == 91)
		mlx->y -= 5;
}

void	deep(int key, t_mlx *mlx, int mouse)
{
	if (key == 69 || (mouse && key == 1))
		mlx->deep += 5;
	if (key == 78 || (mouse && key == 2))
	{
		mlx->deep += -5;
		if (mlx->deep < 0)
			mlx->deep = 0;
	}
}

void	get_tolerance(int key, t_mlx *mlx)
{
	if (key == 67)
	{
		if (mlx->tolerance < 0.00000000000001)
			return ;
		mlx->tolerance /= 2;
	}
	if (key == 75)
		mlx->tolerance *= 2;
}

void	change_pal(int key, t_mlx *mlx)
{
	if (key == 124 && mlx->col < 4)
		(mlx->col)++;
	if (key == 123 && mlx->col > 0)
		(mlx->col)--;
}

void	reset(t_mlx *mlx)
{
	mlx->deep = MAX_ITER;
	mlx->re_min = RE_MIN;
	mlx->re_max = RE_MAX;
	mlx->im_min = IM_MIN;
	mlx->im_max = IM_MAX;
	mlx->tolerance = TOLERANCE;
	mlx->x_c = 0;
	mlx->y_c = 0;
	mlx->x = 0;
	mlx->y = 0;
	mlx->frozen = 0;
	mlx->automode = 0;
	mlx->col = 0;
}
