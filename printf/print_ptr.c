/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:55:36 by dmoliner          #+#    #+#             */
/*   Updated: 2023/09/11 17:19:12 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	print_ptr(unsigned long n)
{
	int				ret;
	unsigned long	pow;
	char			c;

	ret = write(1, "0x", 2);
	pow = 1;
	while (n / pow / 16)
		pow *= 16;
	while (pow)
	{
		c = n / pow;
		if (c >= 0 && c <= 9)
			c += '0';
		else
			c += 'W';
		ret += write(1, &c, 1);
		n %= pow;
		pow /= 16;
	}
	return (ret);
}
