/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_apollonian.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:00:58 by dmoliner          #+#    #+#             */
/*   Updated: 2023/12/02 22:00:52 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/fractol.h"

int32_t	ft_check_apollonian(t_complex z)
{
	int		i;
	double	temp;

	i = 0;
	while (i++ < MAX_ITER)
	{
		temp = z.real;
		z.real = z.real * z.real - z.imag * z.imag + 0.3;
		z.imag = 2 * temp * z.imag;
		if (z.real * z.real + z.imag * z.imag > THRESHOLD)
			return (i);
	}
	return (MAX_ITER);
}
