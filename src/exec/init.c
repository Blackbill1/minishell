/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 22:03:37 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 05:10:16 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_count(t_shell *shell)
{
	t_shell	*tmp;
	int		i;

	tmp = shell;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_exec	*exec_init(t_shell *shell, char **envp, t_token *tokens)
{
	t_exec	*exec;

	exec = malloc(sizeof(t_exec));
	exec->shell = shell;
	exec->envp = envp;
	exec->pipe_fd = malloc(sizeof(int) * (cmd_count(shell) - 1) * 2);
	ft_memset(exec->pipe_fd, 0, sizeof(int) * (cmd_count(shell) - 1) * 2);
	exec->pids = malloc(sizeof(pid_t) * cmd_count(shell));
	exec->pids[0] = -1;
	exec->cmd_count = cmd_count(shell);
	exec->tokens = tokens;
	exec->exit = 0;
	exec->tmp = NULL;
	exec->tmp2 = NULL;
	return (exec);
}
