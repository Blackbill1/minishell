/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 06:00:47 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/23 03:09:07 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_printhex(va_list args)
{
	static char		tab[17] = {"0123456789abcdef"};
	static char		buff[16] = {""};
	unsigned long	ptr;
	int				i;
	int				count;

	i = 0;
	count = 0;
	ptr = (unsigned long)va_arg(args, unsigned long);
	if (ptr == 0)
		return (write(1, "(nil)", 5));
	while (ptr > 0)
	{
		buff[i] = tab[ptr % 16];
		ptr /= 16;
		i++;
	}
	write(1, "0x", 2);
	while (i--)
	{
		write(1, &buff[i], 1);
		count++;
	}
	return (count + 2);
}

int	ft_lower_printhex(va_list args)
{
	static char		tab[17] = {"0123456789abcdef"};
	static char		buff[16] = {""};
	unsigned int	ptr;
	int				i;
	int				count;

	i = 0;
	count = 0;
	ptr = (unsigned int)va_arg(args, unsigned int);
	if (ptr == 0)
		return (write(1, "0", 1));
	while (ptr > 0)
	{
		buff[i] = tab[ptr % 16];
		ptr /= 16;
		i++;
	}
	while (i--)
	{
		write(1, &buff[i], 1);
		count++;
	}
	return (count);
}

int	ft_upper_printhex(va_list args)
{
	static char		tab[17] = {"0123456789ABCDEF"};
	static char		buff[16] = {""};
	unsigned int	ptr;
	int				i;
	int				count;

	i = 0;
	count = 0;
	ptr = (unsigned int)va_arg(args, unsigned int);
	if (ptr == 0)
		return (write(1, "0", 1));
	while (ptr > 0)
	{
		buff[i] = tab[ptr % 16];
		ptr /= 16;
		i++;
	}
	while (i--)
	{
		write(1, &buff[i], 1);
		count++;
	}
	return (count);
}
