/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 18:59:33 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/23 03:09:01 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	select_ft(va_list args, char c)
{
	static int	(*ft[256])(va_list args) = {
	['c'] = ft_putchar,
	['s'] = ft_putstr,
	['p'] = ft_printhex,
	['d'] = ft_putnbr_scam,
	['i'] = ft_putnbr_scam,
	['u'] = ft_putnbru_scam,
	['x'] = ft_lower_printhex,
	['X'] = ft_upper_printhex,
	['%'] = ft_percent,
	};

	if (ft[(unsigned char)c] == NULL)
		return (0);
	return (ft[(unsigned char)c](args));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		res;

	res = 0;
	if (format == NULL)
		return (0);
	va_start(args, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			res += select_ft(args, *format);
		}
		else if (*format == '%' && !*(format + 1))
			break ;
		else
			res += write(1, format, 1);
		format++;
	}
	va_end(args);
	return (res);
}
