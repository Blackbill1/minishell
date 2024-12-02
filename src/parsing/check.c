/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:26:39 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/30 18:23:03 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(const char *input, int i)
{
	if (input[i] == '|')
	{
		i++;
		while (input[i] == ' ')
			i++;
		if (input[i] == '|' || !input[i])
		{
			ft_error("golemShell: syntax error near unexpected token `|'\n");
			return (0);
		}
	}
	return (1);
}

int	check_single_quotes_closed(const char *input, int *i)
{
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == '\'')
		{
			return (1);
		}
		(*i)++;
	}
	ft_error("golemShell: syntax error: expected closing single quote\n");
	return (0);
}

int	check_double_quotes_closed(const char *input, int *i)
{
	(*i)++;
	while (input[*i])
	{
		if (input[*i] == '"')
		{
			return (1);
		}
		(*i)++;
	}
	ft_error("golemShell: syntax error: expected closing double quote\n");
	return (0);
}

int	check_quotes(const char *input, int *i)
{
	if (input[*i] == '\'')
	{
		if (!check_single_quotes_closed(input, i))
			return (0);
	}
	else if (input[*i] == '"')
	{
		if (!check_double_quotes_closed(input, i))
			return (0);
	}
	return (1);
}

int	check_syntax_errors(const char *input)
{
	int	i;

	i = 0;
	while (is_space(input[i]))
		i++;
	if (input[i] == '|')
	{
		ft_error("golemShell: syntax error near unexpected token `|'\n");
		return (0);
	}
	while (input[i])
	{
		if (!check_redirections(input, &i))
			return (0);
		if (!check_quotes(input, &i))
			return (0);
		if (!check_pipe(input, i))
			return (0);
		i++;
	}
	return (1);
}
