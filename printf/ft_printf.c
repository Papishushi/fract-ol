/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:54:54 by dmoliner          #+#    #+#             */
/*   Updated: 2023/09/11 17:17:22 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../header/ft_printf.h"

int	handle_flag(va_list *args, const char c)
{
	if (c == 'c')
		return (print_char(va_arg(*args, int)));
	else if (c == 's')
		return (print_str(va_arg(*args, char *)));
	else if (c == 'd')
		return (print_int(va_arg(*args, int)));
	else if (c == 'i')
		return (print_int(va_arg(*args, int)));
	else if (c == 'u')
		return (print_uint(va_arg(*args, unsigned int)));
	else if (c == 'x')
		return (print_hex(va_arg(*args, unsigned int), false));
	else if (c == 'X')
		return (print_hex(va_arg(*args, unsigned int), true));
	else if (c == 'p')
		return (print_ptr(va_arg(*args, unsigned long)));
	else if (c == '%')
		return (write(1, "%", 1));
	return (0);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = -1;
	count = 0;
	va_start(args, format);
	while (format[++i] != '\0')
	{
		if (format[i] == '%' && format[i + 1] != '\0')
			count += handle_flag(&args, format[i++ + 1]);
		else if (format[i] != '%')
			count += write(1, &format[i], 1);
	}
	return (va_end(args), count);
}
