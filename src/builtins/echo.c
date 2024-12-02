/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:30:47 by gbruscan          #+#    #+#             */
/*   Updated: 2024/11/30 17:43:39 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_n(const char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (0);
	while (s[i])
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	ft_echo(char **av)
{
	int	nl;
	int	i;
	int	args;

	nl = 0;
	args = 0;
	i = 1;
	while (av[args])
		args++;
	while (i < args && check_n(av[i]))
	{
		i++;
		nl = 1;
	}
	while (i < args)
	{
		write(1, av[i], ft_strlen(av[i]));
		if (i < args - 1)
			write(1, " ", 1);
		i++;
	}
	if (!nl)
		write(1, "\n", 1);
}
