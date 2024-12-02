/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:52:41 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 06:22:09 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe(t_exec *exec, int cmd_index)
{
	int	i;
	int	total_pipes;

	i = 0;
	total_pipes = (exec->cmd_count - 1) * 2;
	while (i < total_pipes)
	{
		if (cmd_index == 0 && i == 1)
			continue ;
		if (cmd_index == exec->cmd_count - 1 && i == 2 * (cmd_index - 1))
			continue ;
		if (cmd_index > 0 && cmd_index < exec->cmd_count - 1)
		{
			if (i == 2 * (cmd_index - 1) || i == 2 * cmd_index + 1)
				continue ;
		}
		close(exec->pipe_fd[i]);
		i++;
	}
}

void	setup_pipes(t_exec *exec, int cmd_index)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 1;
	if (exec->cmd_count >= 2)
	{
		handle_exec_redirections(exec, &fd_in, &fd_out);
		duplicate_fds(exec, cmd_index, fd_in, fd_out);
		close_all_pipes(exec);
	}
	else
	{
		handle_exec_redirections(exec, &fd_in, &fd_out);
		duplicate_single_command_fds(exec, fd_in, fd_out);
	}
}

void	handle_exec_redirections(t_exec *exec, int *fd_in, int *fd_out)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = 0;
	if (exec->shell->rd_order[0] == 1 || exec->shell->rd_order[0] == 0)
	{
		while (exec->shell->rd_order[++i] != -1)
		{
			if (exec->shell->rd_order[i] == 0)
			{
				*fd_in = get_infile(exec->shell->rd_in[j], exec);
				j++;
			}
			else
			{
				*fd_out = get_outfile(exec->shell->rd_out[k], exec, k);
				k++;
			}
		}
	}
	else
		elsefd(fd_in, fd_out, exec);
}

void	close_all_pipes(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < (exec->cmd_count - 1) * 2)
	{
		close(exec->pipe_fd[i]);
		i++;
	}
}
