/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 19:08:52 by vbespalk          #+#    #+#             */
/*   Updated: 2018/07/17 19:08:56 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			init_mlx(t_mlx *mlx, char *set)
{
	ft_bzero(mlx, sizeof(t_mlx));
	if (!(mlx->mlx_ptr = mlx_init()))
		return (ft_perror("connection to the X server failed\n"));
	if (!(mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCR_WID, SCR_HEI, set)))
		return (ft_perror("impossible to create new window\n"));
	if (!(mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, SCR_WID, SCR_HEI)))
		return (ft_perror("impossible to set up image\n"));
	mlx->data_add = mlx_get_data_addr(mlx->img_ptr, \
		&mlx->bpp, &mlx->s_line, &mlx->endian);
	ft_bzero(mlx->data_add, SCR_HEI * SCR_WID);
	mlx->deep = MAX_ITER;
	mlx->a_lock = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
	mlx->scale = 1;
	mlx->re_min = RE_MIN;
	mlx->re_max = RE_MAX;
	mlx->im_min = IM_MIN;
	mlx->im_max = IM_MAX;
	mlx->tolerance = 0.1;
	configuration();
	return (0);
}

int			main(int argc, char **argv)
{
	t_mlx	mlx;

	if (argc < 2 || (!ft_strequ(argv[1], MANDELBROT) && \
		!ft_strequ(argv[1], JULIA) && !ft_strequ(argv[1], NEWTON) \
		&& !ft_strequ(argv[1], JULIAS_SIN)))
		ft_error("usage: fractol mandelbrot/julia/newton/julias_sin\n");
	if (init_mlx(&mlx, argv[1]))
		exit(-1);
	if (ft_strequ(argv[1], MANDELBROT))
		mlx.fractol = draw_mandelbrot;
	if (ft_strequ(argv[1], JULIA))
		mlx.fractol = draw_julia;
	if (ft_strequ(argv[1], NEWTON))
		mlx.fractol = draw_newton;
	if (ft_strequ(argv[1], JULIAS_SIN))
		mlx.fractol = draw_julia_sin;
	put_to_window(&mlx);
	mlx_loop_hook(mlx.mlx_ptr, loop_hook, (void *)&mlx);
	mlx_hook(mlx.win_ptr, 2, 0, hook_keydown, (void *)&mlx);
	mlx_hook(mlx.win_ptr, 4, 1L << 6, mouse_hook, (void *)&mlx);
	if (!mlx.frozen)
		mlx_hook(mlx.win_ptr, 6, 1L << 6, mouse_scan, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
