/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 06:19:34 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 06:22:11 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duplicate_single_command_fds(t_exec *exec, int fd_in, int fd_out)
{
	if (fd_in != -1)
	{
		if (exec->shell->rd_in)
			dup2(fd_in, STDIN_FILENO);
		else
			dup2(fd_in, STDIN_FILENO);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
	}
	if (fd_out != -1)
	{
		if (exec->shell->rd_out)
			dup2(fd_out, STDOUT_FILENO);
		else
			dup2(fd_out, STDOUT_FILENO);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
	}
}

void	duplicate_fds(t_exec *exec, int cmd_index, int fd_in, int fd_out)
{
	if (fd_in != -1)
	{
		if (exec->shell->rd_in)
			dup2(fd_in, STDIN_FILENO);
		else if (cmd_index == 0)
			dup2(exec->pipe_fd[0], STDIN_FILENO);
		else
			dup2(exec->pipe_fd[2 * (cmd_index - 1)], STDIN_FILENO);
		if (fd_in != STDIN_FILENO)
			close(fd_in);
	}
	if (fd_out != -1)
	{
		if (exec->shell->rd_out)
			dup2(fd_out, STDOUT_FILENO);
		else if (cmd_index == exec->cmd_count - 1)
			dup2(fd_out, STDOUT_FILENO);
		else
			dup2(exec->pipe_fd[2 * cmd_index + 1], STDOUT_FILENO);
		if (fd_out != STDOUT_FILENO)
			close(fd_out);
	}
}

void	elsefd(int *fd_in, int *fd_out, t_exec *exec)
{
	*fd_in = get_infile(NULL, exec);
	*fd_out = get_outfile(NULL, exec, 0);
}
