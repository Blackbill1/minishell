/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 22:46:07 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/01 05:56:12 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_both(char **key_val)
{
	int	i;

	i = 0;
	while (key_val[i])
	{
		free(key_val[i]);
		i++;
	}
	free(key_val);
}

char	*create_var(char *key, char *val)
{
	char	*var;

	if (!val)
		return (NULL);
	var = ft_strjoin(key, "=");
	if (!val)
	{
		free(var);
		return (NULL);
	}
	if (!var)
		return (NULL);
	var = clean_join(var, val);
	return (var);
}

char	**cpy_envp(char ***envp, int i)
{
	char	**new_envp;
	int		j;

	j = 0;
	new_envp = malloc((i + 2) * sizeof(char *));
	while ((*envp)[j])
	{
		new_envp[j] = (*envp)[j];
		j++;
	}
	return (new_envp);
}

int	check_identifier(char *id)
{
	int	i;

	if (!id || !(ft_isalpha(id[0]) || id[0] == '_'))
		return (0);
	i = 1;
	while (id[i])
	{
		if (!(ft_isalnum(id[i]) || id[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

void	add_to_env(char **new_envp, char ***envp, int *status, t_exec *exec)
{
	if (*status == 0)
	{
		exec->tmp = exec->envp;
		*envp = new_envp;
		(*status)++;
	}
	else
	{
		free(*envp);
		*envp = new_envp;
	}
}
