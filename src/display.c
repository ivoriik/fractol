/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:19:29 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 17:19:31 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	put_to_window(t_mlx *ptr)
{
	ft_bzero(ptr->data_add, (size_t)(SCR_HEI * ptr->s_line));
	mult_threads(ptr);
	mlx_clear_window(ptr->mlx_ptr, ptr->win_ptr);
	mlx_put_image_to_window(ptr->mlx_ptr, ptr->win_ptr, ptr->img_ptr, 0, 0);
	print_legend(ptr);
}

void	img_pixel_put(t_mlx *mlx, int x, int y, unsigned int color)
{
	char *data;

	color = mlx_get_color_value(mlx->mlx_ptr, color);
	if (!(x >= 0 && x < SCR_WID && y >= 0 && y < SCR_HEI))
		return ;
	data = mlx->data_add;
	data += y * mlx->s_line + mlx->bpp / 8 * x;
	ft_memcpy(data, &color, sizeof(color));
}

void	print_legend(t_mlx *mlx)
{
	char *tmp;

	tmp = ft_itoa(mlx->deep);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 5, 0, 16774638, \
		"DEEP: ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 0, 16774638, \
		tmp);
	free(tmp);
	tmp = ft_itoa(mlx->x_coord);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 5, 20, 16774638, \
		"X:    ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 20, 16774638, \
		tmp);
	free(tmp);
	tmp = ft_itoa(mlx->y_coord);
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 5, 40, 16774638, \
		"Y:    ");
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 60, 40, 16774638, \
		tmp);
	free(tmp);
}
