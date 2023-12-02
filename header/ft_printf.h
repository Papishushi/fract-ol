/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmoliner <dmoliner@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 16:56:14 by dmoliner          #+#    #+#             */
/*   Updated: 2023/09/11 16:58:59 by dmoliner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdbool.h>

int	ft_printf(const char *format, ...);
int	print_char(int c);
int	print_str(char *s);
int	print_int(int n);
int	print_uint(unsigned int n);
int	print_ptr(unsigned long n);
int	print_hex(unsigned long n, bool flag);

#endif
