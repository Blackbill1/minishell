/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 20:14:33 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/29 21:10:05 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*initialize_command(void)
{
	t_shell	*new_command;

	new_command = malloc(sizeof(t_shell));
	new_command->cmd = NULL;
	new_command->rd_in = NULL;
	new_command->rd_out = NULL;
	new_command->rd_order = malloc(sizeof(int));
	new_command->rd_order[0] = -1;
	new_command->out_flags = NULL;
	new_command->next = NULL;
	return (new_command);
}

t_shell	*parse_tokens(t_token *tokens, int *tmp_nb)
{
	t_shell	*head;
	t_shell	*cur_command;
	t_token	*cur_token;

	cur_command = initialize_command();
	head = cur_command;
	cur_token = tokens;
	while (cur_token != NULL)
	{
		if (cur_token->type == TOKEN_WORD)
			cur_command = add_word(cur_command, cur_token);
		else if (cur_token->type == TOKEN_PIPE)
			cur_command = add_pipe(cur_command);
		else if (cur_token->type == TOKEN_REDIRECT_IN)
			cur_command = add_redirect_in(cur_command, cur_token);
		else if (cur_token->type == TOKEN_HEREDOC)
			cur_command = add_heredoc(cur_command, cur_token, tmp_nb);
		else if (cur_token->type == TOKEN_REDIRECT_OUT)
			cur_command = add_redirect_out(cur_command, cur_token, 0);
		else if (cur_token->type == TOKEN_APPEND)
			cur_command = add_redirect_out(cur_command, cur_token, 1);
		cur_token = cur_token->next;
	}
	return (head);
}

void	update_redirect_order(int **redirect, int order_val)
{
	int	rd_count;
	int	*new_red_order;
	int	i;

	rd_count = 0;
	if (*redirect)
		while ((*redirect)[rd_count] != -1)
			rd_count++;
	new_red_order = malloc(sizeof(int) * (rd_count + 2));
	i = -1;
	while (++i < rd_count)
	{
		new_red_order[i] = (*redirect)[i];
	}
	new_red_order[rd_count] = order_val;
	new_red_order[rd_count + 1] = -1;
	if (*redirect)
		free(*redirect);
	*redirect = new_red_order;
}

void	update_redirect_in(char ***redirect, const char *file_name)
{
	int		rd_count;
	char	**new_redirect;
	int		i;

	rd_count = 0;
	if (*redirect)
		while ((*redirect)[rd_count] != NULL)
			rd_count++;
	new_redirect = malloc(sizeof(char *) * (rd_count + 2));
	i = -1;
	while (++i < rd_count)
	{
		new_redirect[i] = (*redirect)[i];
	}
	new_redirect[rd_count] = ft_strdup((char *)file_name);
	new_redirect[rd_count + 1] = NULL;
	if (*redirect)
		free(*redirect);
	*redirect = new_redirect;
}

void	update_redirect_out(char ***redirect, int **append_flags,
		const char *file_name, int is_append)
{
	int		rd_count;
	char	**new_redirect;
	int		*new_append_flags;
	int		i;

	rd_count = 0;
	if (*redirect)
		while ((*redirect)[rd_count] != NULL)
			rd_count++;
	new_redirect = malloc(sizeof(char *) * (rd_count + 2));
	new_append_flags = malloc(sizeof(int) * (rd_count + 1));
	i = -1;
	while (++i < rd_count)
	{
		new_redirect[i] = (*redirect)[i];
		new_append_flags[i] = (*append_flags)[i];
	}
	new_redirect[rd_count] = (char *)file_name;
	new_redirect[rd_count + 1] = NULL;
	new_append_flags[rd_count] = is_append;
	if (*redirect)
		(free(*redirect), free(*append_flags));
	*redirect = new_redirect;
	*append_flags = new_append_flags;
}
