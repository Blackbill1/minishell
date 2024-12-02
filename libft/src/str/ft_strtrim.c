/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:46:51 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/14 11:46:52 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(str) - 1;
	while (ft_strchr((char *)set, str[start]))
		start++;
	while (ft_strchr((char *)set, str[end]))
		end--;
	return (ft_substr(str, start, (end - start) + 1));
}
