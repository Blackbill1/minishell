/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tle-dref <tle-dref@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:48:29 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 04:37:09 by tle-dref         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ours(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0 || ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "pwd") == 0 || ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "echo") == 0 || ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

void	exec_cmd(t_exec *exec, char **cmd, int cmd_index)
{
	pid_t	pid;

	if (exec->cmd_count == 1 && ((ft_strcmp(cmd[0], "unset") == 0
				|| ft_strcmp(cmd[0], "cd") == 0) || ft_strcmp(cmd[0],
				"export") == 0 || ft_strcmp(cmd[0], "exit") == 0))
		exec_builtins(exec, cmd);
	else if (cmd_index == exec->cmd_count - 1)
	{
		pid = fork();
		if (pid == 0)
			child_process(exec, cmd, cmd_index);
		exec->pids[cmd_index] = pid;
	}
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("Fork error"));
		if (pid == 0)
			child_process(exec, cmd, cmd_index);
		exec->pids[cmd_index] = pid;
	}
}

void	cmdloop(t_exec *exec)
{
	int		i;
	t_shell	*current;

	i = 0;
	current = exec->shell;
	while (current)
	{
		if (current->cmd)
		{
			exec_cmd(exec, current->cmd, i);
		}
		current = current->next;
		i++;
	}
}

void	execute_commands(t_exec *exec)
{
	int	i;

	i = 0;
	while (i < exec->cmd_count - 1)
	{
		if (pipe(exec->pipe_fd + 2 * i) == -1)
		{
			perror("Pipe creation failed");
			return ;
		}
		i++;
	}
	cmdloop(exec);
	i = -1;
	while (++i < (exec->cmd_count - 1) * 2)
		close(exec->pipe_fd[i]);
	if (exec->pids[0] != -1)
		wait_process(exec);
}

void	wait_process(t_exec *exec)
{
	int	i;
	int	wait;
	int	status;

	i = -1;
	status = 0;
	while (++i < exec->cmd_count)
		waitpid(exec->pids[i], &wait, 0);
	if WIFEXITED (wait)
		status = WEXITSTATUS(wait);
	exec->exit = status;
}
