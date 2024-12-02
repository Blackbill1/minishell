/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 01:24:08 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/29 17:11:12 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_simple_quote(const char *input, int *i, char **result_word)
{
	int		start;
	char	*current_word;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	current_word = ft_strndup(&input[start], *i - start);
	if (!current_word)
	{
		free(*result_word);
		return (0);
	}
	*result_word = clean_join(*result_word, current_word);
	free(current_word);
	if (input[*i] == '\'')
		(*i)++;
	return (1);
}

int	handle_double_quote(const char *input, int *i, char **result_word,
		t_envp_exit envp_exit)
{
	int		start;
	char	*current_word;
	char	*expanded_word;

	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
		(*i)++;
	current_word = ft_strndup(&input[start], *i - start);
	if (!current_word)
	{
		free(*result_word);
		return (0);
	}
	expanded_word = calc_dollar_envp(current_word, envp_exit.envp,
			envp_exit.exit_value);
	free(current_word);
	*result_word = clean_join(*result_word, expanded_word);
	free(expanded_word);
	if (input[*i] == '"')
		(*i)++;
	return (1);
}

void	handle_dollar_interrogation(int *i, char **result_word, int *exit_value)
{
	char	*expanded_word;

	(*i) += 2;
	expanded_word = ft_itoa(*exit_value);
	*result_word = clean_join(*result_word, expanded_word);
	free(expanded_word);
}

void	handle_unquoted_word(const char *input, int *i, char **result_word,
		t_envp_exit envp_exit)
{
	int		start;
	char	*current_word;
	char	*expanded_word;

	start = *i;
	while (input[*i] && !ft_strchr(" |><'\"", input[*i]))
		(*i)++;
	current_word = ft_strndup(&input[start], *i - start);
	expanded_word = calc_dollar_envp(current_word, envp_exit.envp,
			envp_exit.exit_value);
	free(current_word);
	if (ft_strlen(expanded_word) > 0)
	{
		*result_word = clean_join(*result_word, expanded_word);
	}
	free(expanded_word);
}
