/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 05:04:46 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 05:07:09 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open(t_shell *shell, char *rd, int b, int i)
{
	int	fd;

	if (b == 0)
		fd = open(rd, O_RDONLY, 0644);
	else
	{
		if (shell->out_flags[i] == 0)
			fd = open(rd, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		else
			fd = open(rd, O_WRONLY | O_APPEND | O_CREAT, 0644);
	}
	return (fd);
}

int	get_outfile(char *rd_out, t_exec *exec, int index)
{
	int	fd;

	if (!rd_out)
		return (open("/dev/stdout", O_WRONLY | O_CREAT | O_TRUNC, 0644));
	fd = ft_open(exec->shell, rd_out, 1, index);
	if (fd == -1)
	{
		close_all_pipes(exec);
		fd_errorout(rd_out);
		free_all(exec);
		exit(1);
	}
	return (fd);
}

int	get_infile(char *rd_in, t_exec *exec)
{
	int	fd;

	if (!rd_in)
		return (open("/dev/stdin", O_RDONLY, 0644));
	fd = ft_open(exec->shell, rd_in, 0, 0);
	if (fd == -1)
	{
		close_all_pipes(exec);
		fd_errorin(rd_in);
		free_all(exec);
		exit(1);
	}
	return (fd);
}

void	fd_errorout(char *rd_out)
{
	if (access(rd_out, F_OK) == -1)
	{
		write(2, rd_out, ft_strlen(rd_out));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, rd_out, ft_strlen(rd_out));
		write(2, ": Permission denied\n", 21);
	}
}

void	fd_errorin(char *rd_in)
{
	if (access(rd_in, F_OK) == -1)
	{
		write(2, rd_in, ft_strlen(rd_in));
		write(2, ": No such file or directory\n", 28);
	}
	else
	{
		write(2, rd_in, ft_strlen(rd_in));
		write(2, ": Permission denied\n", 21);
	}
}
