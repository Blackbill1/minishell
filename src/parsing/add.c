/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:49:19 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/26 14:29:53 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*add_word(t_shell *cur_cmd, t_token *token)
{
	int		arg_count;
	char	**new_cmd;
	int		i;

	arg_count = 0;
	if (cur_cmd->cmd)
		while (cur_cmd->cmd[arg_count] != NULL)
			arg_count++;
	new_cmd = malloc(sizeof(char *) * (arg_count + 2));
	i = -1;
	while (++i < arg_count)
		new_cmd[i] = cur_cmd->cmd[i];
	new_cmd[arg_count] = ft_strdup(token->value);
	new_cmd[arg_count + 1] = NULL;
	if (cur_cmd->cmd)
		free(cur_cmd->cmd);
	cur_cmd->cmd = new_cmd;
	return (cur_cmd);
}

t_shell	*add_simple_quote(t_shell *cur_cmd, t_token *token)
{
	int		arg_count;
	char	**new_cmd;
	int		i;

	arg_count = 0;
	if (cur_cmd->cmd)
		while (cur_cmd->cmd[arg_count] != NULL)
			arg_count++;
	new_cmd = malloc(sizeof(char *) * (arg_count + 2));
	i = -1;
	while (++i < arg_count)
		new_cmd[i] = cur_cmd->cmd[i];
	new_cmd[arg_count] = ft_strdup(token->value);
	new_cmd[arg_count + 1] = NULL;
	if (cur_cmd->cmd)
		free(cur_cmd->cmd);
	cur_cmd->cmd = new_cmd;
	return (cur_cmd);
}

t_shell	*add_double_quote(t_shell *cur_cmd, t_token *token)
{
	int		arg_count;
	char	**new_cmd;
	int		i;

	arg_count = 0;
	if (cur_cmd->cmd)
		while (cur_cmd->cmd[arg_count] != NULL)
			arg_count++;
	new_cmd = malloc(sizeof(char *) * (arg_count + 2));
	i = -1;
	while (++i < arg_count)
		new_cmd[i] = cur_cmd->cmd[i];
	new_cmd[arg_count] = ft_strdup(token->value);
	new_cmd[arg_count + 1] = NULL;
	if (cur_cmd->cmd)
		free(cur_cmd->cmd);
	cur_cmd->cmd = new_cmd;
	return (cur_cmd);
}
