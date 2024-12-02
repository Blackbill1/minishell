/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 14:57:09 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/30 02:08:01 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction générique pour créer un token
t_token	*create_token(t_token_Type type, const char *value, int *i,
		int increment)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	new_token->type = type;
	new_token->value = ft_strdup(value);
	(*i) += increment;
	new_token->next = NULL;
	return (new_token);
}

t_token	*add_token_to_list(t_token *head, t_token *new_token)
{
	t_token	*current;

	if (head == NULL)
		return (new_token);
	current = head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_token;
	return (head);
}

t_token	*tokenize(const char *input, char **envp, int *exit_value)
{
	t_token		*head;
	t_token		*new_token;
	t_envp_exit	envp_exit;
	int			i;

	head = NULL;
	new_token = NULL;
	i = 0;
	envp_exit.envp = envp;
	envp_exit.exit_value = exit_value;
	while (input[i])
	{
		if (is_space(input[i]))
		{
			i++;
			continue ;
		}
		new_token = handle_token_creation(input, &i, envp_exit);
		if (new_token)
			head = add_token_to_list(head, new_token);
	}
	return (head);
}

t_token	*handle_token_creation(const char *input, int *i, t_envp_exit envp_exit)
{
	t_token	*new_token;

	new_token = NULL;
	if (is_pipe(input[*i]))
		new_token = create_token(TOKEN_PIPE, "|", i, 1);
	else if (is_append(input, *i))
		new_token = create_token(TOKEN_APPEND, ">>", i, 2);
	else if (is_redirect_out(input, *i))
		new_token = create_token(TOKEN_REDIRECT_OUT, ">", i, 1);
	else if (is_heredoc(input, *i))
		new_token = create_token(TOKEN_HEREDOC, "<<", i, 2);
	else if (is_redirect_in(input, *i))
		new_token = create_token(TOKEN_REDIRECT_IN, "<", i, 1);
	else
		new_token = create_word_token(input, i, envp_exit);
	return (new_token);
}

t_token	*create_word_token(const char *input, int *i, t_envp_exit envp_exit)
{
	char	*result_word;
	t_token	*new_token;

	result_word = ft_strdup("");
	while (input[*i] && !ft_strchr(" |><", input[*i]))
	{
		if (is_simple_quote(input[*i]))
			handle_simple_quote(input, i, &result_word);
		else if (is_double_quote(input[*i]))
			handle_double_quote(input, i, &result_word, envp_exit);
		else if (is_dollar_interrogation(input, *i))
			handle_dollar_interrogation(i, &result_word, envp_exit.exit_value);
		else
			handle_unquoted_word(input, i, &result_word, envp_exit);
	}
	if (ft_strlen(result_word) == 0)
	{
		free(result_word);
		return (NULL);
	}
	new_token = create_token(TOKEN_WORD, result_word, i, 0);
	return (free(result_word), new_token);
}
