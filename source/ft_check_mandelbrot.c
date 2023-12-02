/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_mandelbrot.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:59:59 by dmoliner          #+#    #+#             */
/*   Updated: 2023/12/02 22:00:58 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

int32_t	ft_check_mandelbrot(t_complex c)
{
	t_complex	z;
	int			i;
	double		temp;

	z.real = 0.0;
	z.imag = 0.0;
	i = 0;
	while (i++ < MAX_ITER)
	{
		temp = z.real;
		z.real = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * temp * z.imag + c.imag;
		if (z.real * z.real + z.imag * z.imag > THRESHOLD)
			return (i);
	}
	return (MAX_ITER);
}
