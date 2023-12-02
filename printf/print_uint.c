/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_uint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:55:48 by dmoliner          #+#    #+#             */
/*   Updated: 2023/09/11 17:19:24 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	print_uint(unsigned int n)
{
	int				ret;
	unsigned int	pow_ten;
	char			c;

	ret = 0;
	pow_ten = 1;
	while (n / pow_ten / 10)
		pow_ten *= 10;
	while (pow_ten)
	{
		c = n / pow_ten + '0';
		ret += write(1, &c, 1);
		n %= pow_ten;
		pow_ten /= 10;
	}
	return (ret);
}
