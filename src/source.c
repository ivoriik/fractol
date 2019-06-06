/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   source.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbespalk <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/31 10:03:28 by vbespalk          #+#    #+#             */
/*   Updated: 2018/06/31 15:03:32 by vbespalk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(-1);
}

int		ft_perror(char *message)
{
	ft_putstr_fd("Error: ", 2);
	if (message)
		ft_putstr_fd(message, 2);
	else
		perror(NULL);
	return (-1);
}

void	configuration(void)
{
	write(1, "---------------------------------\n", 34);
	write(1, "MOVE       : 8 2 4 6 (numeric)   \n", 34);
	write(1, "DEEP       : + - (numeric)       \n", 34);
	write(1, "ZOOM       : wheel               \n", 34);
	write(1, "COLOR MODE : left right          \n", 34);
	write(1, "AUTO MODE  : enter (numeric)     \n", 34);
	write(1, "FREEZE     : = (numeric)         \n", 34);
	write(1, "RESET      : 0 (numeric)         \n", 34);
	write(1, "---------------------------------\n", 34);
}
