/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 18:34:09 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/01 04:04:40 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	exec_builtins(t_exec *exec, char **cmd)
{
	if (ft_strcmp(cmd[0], "cd") == 0)
		ft_cd(exec, cmd);
	else if (ft_strcmp(cmd[0], "echo") == 0)
		ft_echo(cmd);
	else if (ft_strcmp(cmd[0], "env") == 0)
		ft_env(exec->envp);
	else if (ft_strcmp(cmd[0], "exit") == 0)
		ft_exit(cmd, exec);
	else if (ft_strcmp(cmd[0], "export") == 0)
		ft_export(cmd, &exec->envp, exec);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		ft_pwd(exec->envp);
	else if (ft_strcmp(cmd[0], "unset") == 0)
		ft_unset(cmd, &exec->envp);
}

void	child_process(t_exec *exec, char **cmd, int cmd_index)
{
	char		*cmd_path;
	static int	i = 0;

	while (i < cmd_index)
	{
		exec->shell = exec->shell->next;
		i++;
	}
	setup_pipes(exec, cmd_index);
	if (is_ours(cmd[0]))
	{
		exec_builtins(exec, cmd);
		if (cmd_index < exec->cmd_count - 1)
			close(exec->pipe_fd[2 * cmd_index + 1]);
		free_all(exec);
		exit(0);
	}
	else
	{
		cmd_path = find_command_path(cmd[0], exec->envp);
		handle_exec_error(cmd_path, cmd[0], exec);
		execve(cmd_path, cmd, exec->envp);
		(free(cmd_path), free_all(exec));
		exit(0);
	}
}
