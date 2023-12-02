/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_task.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:04:42 by dmoliner          #+#    #+#             */
/*   Updated: 2023/12/02 23:59:15 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

int	ft_close_task(void *param)
{
	t_data	*fol;

	fol = (t_data *)param;
	mlx_destroy_window(fol->mlx, fol->win);
	mlx_destroy_image(fol->mlx, fol->txr.img);
	free(fol->mlx);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
