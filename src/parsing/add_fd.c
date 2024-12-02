/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:29:38 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/30 21:15:13 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*add_pipe(t_shell *cur_command)
{
	t_shell	*new_command;

	new_command = malloc(sizeof(t_shell));
	new_command->cmd = NULL;
	new_command->rd_in = NULL;
	new_command->rd_out = NULL;
	new_command->out_flags = NULL;
	new_command->rd_order = malloc(sizeof(int));
	new_command->rd_order[0] = -1;
	new_command->next = NULL;
	cur_command->next = new_command;
	cur_command = new_command;
	return (cur_command);
}

t_shell	*add_redirect_in(t_shell *cur_command, t_token *token)
{
	update_redirect_in(&(cur_command->rd_in), token->next->value);
	update_redirect_order(&(cur_command->rd_order), 0);
	token->next->type = TOKEN_FILE_NAME;
	return (cur_command);
}

t_shell	*add_redirect_out(t_shell *cur_comm, t_token *token, int is_append)
{
	update_redirect_out(&(cur_comm->rd_out), &(cur_comm->out_flags),
		token->next->value, is_append);
	update_redirect_order(&(cur_comm->rd_order), 1);
	token->next->type = TOKEN_FILE_NAME;
	return (cur_comm);
}

t_shell	*add_heredoc(t_shell *cur_comm, t_token *token, int *tmp_nb)
{
	int		tmp;
	char	*file_name;
	char	*id;

	id = ft_itoa((*tmp_nb));
	file_name = ft_strjoin(".tmp", id);
	free(id);
	(*tmp_nb)++;
	tmp = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (tmp < 0)
	{
		ft_error("GolemShell: can't open the folder.\n");
		free(file_name);
		exit(EXIT_FAILURE);
	}
	gnl_heredoc(token, tmp);
	update_redirect_in(&(cur_comm->rd_in), file_name);
	update_redirect_order(&(cur_comm->rd_order), 0);
	token->next->type = TOKEN_FILE_NAME;
	free(file_name);
	return (cur_comm);
}
