/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:30:57 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 17:30:59 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	automode(t_mlx *mlx)
{
	scaling(mlx, mlx->x_coord, mlx->y_coord);
	if (mlx->scale > 1)
		mlx->deep += 0.5;
	else
	{
		mlx->deep -= 0.5;
		if (mlx->deep < 0)
			mlx->deep = 0;
	}
	put_to_window(mlx);
}

int		loop_hook(void *param)
{
	t_mlx *mlx;

	mlx = (t_mlx *)param;
	if (mlx->automode)
		automode(mlx);
	return (1);
}
