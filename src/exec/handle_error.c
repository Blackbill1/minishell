/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:01:14 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/01 06:06:51 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exec_error(char *cmd_path, char *cmd_name, t_exec *exec)
{
	if (!cmd_name)
		handle_no_cmd_name(exec, cmd_path);
	else if (!cmd_path)
		handle_no_cmd_path(exec, cmd_name);
	else if (is_directory(cmd_path))
		handle_is_directory(exec, cmd_path, cmd_name);
	else if (access(cmd_path, X_OK) == -1)
		handle_no_exec_permission(exec, cmd_path, cmd_name);
}

void	handle_no_cmd_name(t_exec *exec, char *cmd_path)
{
	write(2, "Permission denied : \n", 21);
	free(cmd_path);
	close_all_pipes(exec);
	free_all(exec);
	exit(1);
}

void	handle_no_cmd_path(t_exec *exec, char *cmd_name)
{
	char	*error;

	error = clean_join(ft_strjoin(cmd_name, ": command not found"), "\n");
	write(2, error, ft_strlen(error));
	free(error);
	close_all_pipes(exec);
	free_all(exec);
	exit(127);
}

void	handle_is_directory(t_exec *exec, char *cmd_path, char *cmd_name)
{
	char	*error;

	error = clean_join(ft_strjoin(cmd_name, ": Is a directory"), "\n");
	write(2, error, ft_strlen(error));
	free(cmd_path);
	free(error);
	close_all_pipes(exec);
	free_all(exec);
	exit(126);
}

void	handle_no_exec_permission(t_exec *exec, char *cmd_path, char *cmd_name)
{
	struct stat	file_stat;
	char		*error;

	if (access(cmd_path, F_OK) == -1)
	{
		error = clean_join(ft_strjoin(cmd_name, ": command not found"), "\n");
		write(2, error, ft_strlen(error));
		free_path(cmd_path, error, exec);
		exit(127);
	}
	if (stat(cmd_path, &file_stat) == 0 && S_ISREG(file_stat.st_mode))
	{
		error = clean_join(ft_strjoin(cmd_name, ": Permission denied"), "\n");
		write(2, error, ft_strlen(error));
		free_path(cmd_path, error, exec);
		exit(126);
	}
	else
	{
		error = clean_join(ft_strjoin(cmd_name, ": Permission denied"), "\n");
		write(2, error, ft_strlen(error));
		free_path(cmd_path, error, exec);
		exit(1);
	}
}
