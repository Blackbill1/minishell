/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:42:53 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/14 21:15:47 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_size(long nb)
{
	size_t	size;

	size = 0;
	if (nb < 0)
	{
		nb = -nb;
		size = 1;
	}
	if (nb == 0)
		size = 1;
	else
	{
		while (nb)
		{
			nb = nb / 10;
			size++;
		}
	}
	return (size);
}

char	*ft_itoa(int n)
{
	size_t	size;
	size_t	neg;
	long	nb;
	char	*str;

	size = count_size((long)n);
	str = (char *)malloc(size + 1);
	if (str == NULL)
		return (NULL);
	nb = (long)n;
	neg = 0;
	if (nb < 0)
	{
		nb = -nb;
		str[0] = '-';
		neg = 1;
	}
	str[size] = '\0';
	while (size > neg)
	{
		str[size - 1] = nb % 10 + '0';
		nb = nb / 10;
		size--;
	}
	return (str);
}
