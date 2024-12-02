/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_red.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:42:21 by gbruscan          #+#    #+#             */
/*   Updated: 2024/11/28 16:05:55 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_red_in(const char *input, int *i)
{
	(*i)++;
	if (input[*i] == '<')
	{
		(*i)++;
		while (is_space(input[*i]))
			(*i)++;
		if (!input[*i] || ft_strchr("|><", input[*i]))
		{
			ft_error("golemShell: syntax error near unexpected token `<<'\n");
			return (0);
		}
	}
	else
	{
		while (is_space(input[*i]))
			(*i)++;
		if (!input[*i] || ft_strchr("|><", input[*i]))
		{
			ft_error("golemShell: syntax error near unexpected token `<'\n");
			return (0);
		}
	}
	return (1);
}

int	check_red_out(const char *input, int *i)
{
	(*i)++;
	if (input[*i] == '>')
	{
		(*i)++;
		while (is_space(input[*i]))
			(*i)++;
		if (!input[*i] || ft_strchr("|><", input[*i]))
		{
			ft_error("golemShell: syntax error near unexpected token `>>'\n");
			return (0);
		}
	}
	else
	{
		while (is_space(input[*i]))
			(*i)++;
		if (!input[*i] || ft_strchr("|><", input[*i]))
		{
			ft_error("golemShell: syntax error near unexpected token `>'\n");
			return (0);
		}
	}
	return (1);
}

int	check_redirections(const char *input, int *i)
{
	if (input[*i] == '<')
	{
		if (!check_red_in(input, i))
			return (0);
	}
	else if (input[*i] == '>')
	{
		if (!check_red_out(input, i))
			return (0);
	}
	return (1);
}
