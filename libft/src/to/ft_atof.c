/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 02:21:15 by gbruscan          #+#    #+#             */
/*   Updated: 2024/11/01 02:31:34 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	ft_parse_decimal(const char *str, int *i)
{
	double	result;
	double	fraction;

	result = 0.0;
	fraction = 0.1;
	while (ft_isdigit(str[*i]))
	{
		result += (str[*i] - '0') * fraction;
		fraction *= 0.1;
		(*i)++;
	}
	return (result);
}

static double	ft_parse_number(const char *str, int *i)
{
	double	result;

	result = 0.0;
	while (ft_isdigit(str[*i]))
	{
		result = result * 10.0 + (str[*i] - '0');
		(*i)++;
	}
	if (str[*i] == '.')
	{
		(*i)++;
		result += ft_parse_decimal(str, i);
	}
	return (result);
}

double	ft_atof(const char *str)
{
	double	result;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	result = ft_parse_number(str, &i);
	return (result * sign);
}
