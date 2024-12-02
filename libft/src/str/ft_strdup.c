/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:45:35 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/14 11:45:35 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str, ft_strlen(str) + 1);
	return (dup);
}
