/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:02:41 by dmoliner          #+#    #+#             */
/*   Updated: 2023/12/02 23:59:15 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

void	calculate_chunk(int start_x, int end_x, int start_y, int end_y, t_data *fol)
{
	int32_t		x;
	int32_t		y;
	t_complex	c;

	c.real = -0.7;
	c.imag = 0.27015;
	x = start_x;
	while (x < end_x)
	{
		y = start_y;
		while (y < end_y)
		{
			chunk_inner_loop(x, y++, c, fol);
		}
		x++;
	}
}

int	ft_render(void *param)
{
	t_data	*fol;

	fol = (t_data *)param;
	render_loop(fol);
	if (mlx_put_image_to_window(fol->mlx, fol->win, fol->txr.img, 0, 0) \
	== -1)
	{
		mlx_destroy_window(fol->mlx, fol->win);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
