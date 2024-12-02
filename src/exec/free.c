/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:12:05 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 05:58:24 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_exec(t_exec *exec)
{
	free(exec->pipe_fd);
	free(exec->pids);
	free(exec);
}

void	free_envp(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
		free(envp[i]);
	free(envp);
}

void	free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		free(token->value);
		tmp = token;
		token = token->next;
		free(tmp);
	}
	free(token);
}

void	free_cmd_rdin(t_shell *shell)
{
	int	i;

	i = -1;
	if (shell->cmd)
	{
		while (shell->cmd[++i])
			free(shell->cmd[i]);
		free(shell->cmd);
	}
	i = 0;
	if (shell->rd_in)
	{
		while (shell->rd_in[i])
		{
			free(shell->rd_in[i]);
			i++;
		}
		free(shell->rd_in);
	}
}

void	free_shell(t_shell *shell)
{
	t_shell	*tmp;

	while (shell)
	{
		free_cmd_rdin(shell);
		if (shell->rd_out)
			free(shell->rd_out);
		if (shell->out_flags)
			free(shell->out_flags);
		tmp = shell;
		free(shell->rd_order);
		shell = shell->next;
		free(tmp);
	}
	free(shell);
}
