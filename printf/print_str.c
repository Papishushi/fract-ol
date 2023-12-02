/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:55:45 by dmoliner          #+#    #+#             */
/*   Updated: 2023/09/11 17:19:39 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../libft/libft.h"

int	print_str(char *s)
{
	if (s == NULL)
		return (write(1, "(null)", 6));
	return (write(1, s, ft_strlen(s)));
}
