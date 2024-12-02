/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:47:24 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/14 22:13:34 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *src, unsigned int start, size_t size)
{
	char	*result;
	size_t	len_src;

	len_src = ft_strlen(src);
	if (!len_src || len_src < start)
		return (ft_strdup(""));
	if (len_src - start < size)
		size = len_src - start;
	result = malloc(sizeof(char) * (size + 1));
	if (!result)
		return (NULL);
	ft_strlcpy(result, src + start, size + 1);
	return (result);
}
