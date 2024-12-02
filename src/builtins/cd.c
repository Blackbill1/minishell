/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 19:53:13 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 05:35:00 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	no_arg(t_exec *exec, char *oldpwd)
{
	char	*path;

	path = getenv("HOME");
	if (path == NULL)
	{
		write(2, "golemShell: cd: HOME not set\n", 29);
		return ;
	}
	if (chdir(path) == -1)
		return ;
	update_pwd(exec, oldpwd);
}

int	two_args(char **args, char *cwd, t_exec *exec)
{
	int	dir;

	dir = chdir(args[1]);
	if (dir == 0)
		update_pwd(exec, cwd);
	if (dir == -1)
	{
		write(2, "golemShell: cd: ", 16);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": No such file or directory\n", 28);
		free(cwd);
		exec->exit = 1;
		return (0);
	}
	return (1);
}

int	ft_cd(t_exec *exec, char **args)
{
	int		count;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_getpwd(exec->envp);
	count = count_args(args);
	if (count == 1)
		no_arg(exec, cwd);
	if (count == 2)
		if (!two_args(args, cwd, exec))
			return (0);
	if (count > 2)
	{
		write(2, "cd: too many arguments\n", 23);
		free(cwd);
		exec->exit = 1;
		return (0);
	}
	free(cwd);
	return (1);
}
