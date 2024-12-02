/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:55:41 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/01 19:25:25 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isnumeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

void	handle_numeric_arg(char *tmp, t_exec *exec)
{
	if (!isnumeric(tmp))
	{
		write(STDERR_FILENO, "exit: ", 6);
		write(STDERR_FILENO, tmp, ft_strlen(tmp));
		write(STDERR_FILENO, ": numeric argument required\n", 28);
		free_all(exec);
		free(tmp);
		exit(2);
	}
}

int	ft_exit(char **args, t_exec *exec)
{
	int		exit_code;
	char	*tmp;

	if (args[1] == NULL)
		(free_all(exec), exit(0));
	tmp = ft_strtrim(args[1], " ");
	handle_numeric_arg(tmp, exec);
	if (args[2] != NULL)
	{
		if (exec->cmd_count < 2)
			write(STDERR_FILENO, "exit\n", 5);
		write(STDERR_FILENO, "exit: too many arguments\n", 25);
		exec->exit = 1;
		free(tmp);
		return (1);
	}
	exit_code = ft_atoi(args[1]);
	if (exit_code < 0)
		exit_code += 256;
	exit_code %= 256;
	free_all(exec);
	free(tmp);
	exit(exit_code);
}
