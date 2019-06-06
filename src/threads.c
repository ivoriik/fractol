/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 17:52:26 by vbespalk          #+#    #+#             */
/*   Updated: 2018/08/02 17:52:28 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*thread_funct(void *mlx)
{
	static int x_coord;

	pthread_mutex_lock(&((t_mlx *)mlx)->a_lock);
	if (x_coord == 800)
		x_coord = 0;
	x_coord += 80;
	pthread_mutex_unlock(&((t_mlx *)mlx)->a_lock);
	(((t_mlx *)mlx)->fractol)(((t_mlx *)mlx), x_coord - 80, 0);
	return (NULL);
}

int		mult_threads(t_mlx *mlx)
{
	int			count;
	pthread_t	threads_id[NB_THREADS];

	count = -1;
	while (++count < NB_THREADS)
		if (pthread_create((&(threads_id[count])), NULL, thread_funct, mlx))
			ft_error("error creating thread\n");
	count = -1;
	while (++count < NB_THREADS)
		if (pthread_join(threads_id[count], NULL))
			ft_error("error joining thread\n");
	return (0);
}
