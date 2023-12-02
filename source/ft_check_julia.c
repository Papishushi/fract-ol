/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_julia.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:00:26 by dmoliner          #+#    #+#             */
/*   Updated: 2023/12/02 20:13:57 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

int32_t	ft_check_julia(t_complex z, t_complex c)
{
	int		i;
	double	temp;

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
