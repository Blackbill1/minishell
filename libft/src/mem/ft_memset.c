/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:44:00 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/22 23:33:48 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*p, int value, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		*(unsigned char *)(p + i++) = (unsigned char)value;
	return (p);
}
