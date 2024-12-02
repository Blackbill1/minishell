/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 18:00:55 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 04:50:21 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **envp)
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
	printf("%s\n", cwd);
	if (cwd)
		free(cwd);
}
