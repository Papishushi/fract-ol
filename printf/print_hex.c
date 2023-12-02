/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:55:06 by dmoliner          #+#    #+#             */
/*   Updated: 2023/09/11 17:18:55 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

int	print_hex(unsigned int n, bool uppercase)
{
	int				ret;
	unsigned int	pow;
	char			c;

	ret = 0;
	pow = 1;
	while (n / pow / 16)
		pow *= 16;
	while (pow)
	{
		c = n / pow + '0';
		if (!(c >= '0' && c <= '9'))
		{
			c += 7;
			if (!uppercase)
				c += 32;
		}
		ret += write(1, &c, 1);
		n %= pow;
		pow /= 16;
	}
	return (ret);
}
