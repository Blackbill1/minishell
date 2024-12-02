/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:46:43 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/22 23:50:57 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *search, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*search == '\0')
		return ((char *)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (search[j] && (i + j) < len && str[i + j] == search[j])
			j++;
		if (search[j] == '\0')
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}
