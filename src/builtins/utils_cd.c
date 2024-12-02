/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 05:19:18 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 05:22:04 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_args(char **args)
{
	int	count;

	count = 0;
	while (args[count])
		count++;
	return (count);
}

char	*ft_getpwd(char **envp)
{
	char	*cwd;
	int		i;

	i = 0;
	cwd = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PWD=", 4) == 0)
		{
			cwd = ft_strdup(envp[i] + 4);
			break ;
		}
		i++;
	}
	return (cwd);
}

void	update_oldpwd(t_exec *exec, char *pwd_value)
{
	char	*new_oldpwd[3];

	new_oldpwd[0] = ft_strdup("krauter");
	new_oldpwd[1] = ft_strjoin("OLDPWD=", pwd_value);
	new_oldpwd[2] = NULL;
	ft_export(new_oldpwd, &exec->envp, exec);
	free(new_oldpwd[0]);
	free(new_oldpwd[1]);
}

void	update_pwd(t_exec *exec, char *oldpwd)
{
	char	*cwd;
	char	*pwd[3];

	cwd = getcwd(NULL, 0);
	if (!cwd)
		cwd = ft_getpwd(exec->envp);
	update_oldpwd(exec, oldpwd);
	pwd[0] = ft_strdup("caca");
	pwd[1] = ft_strjoin("PWD=", cwd);
	pwd[2] = NULL;
	ft_export(pwd, &exec->envp, exec);
	free(cwd);
	free(pwd[0]);
	free(pwd[1]);
}
