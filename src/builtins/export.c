/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 16:45:52 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/01 19:36:53 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_or_modify(char *key, char *val, char ***envp, t_exec *exec)
{
	int			i;
	size_t		lkey;
	char		*var;
	char		**new_envp;
	static int	status = 0;

	i = 0;
	lkey = ft_strlen(key);
	var = create_var(key, val);
	if (!var)
		return ;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, lkey) == 0 && (*envp)[i][lkey] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = var;
			return ;
		}
		i++;
	}
	new_envp = cpy_envp(envp, i);
	new_envp[i] = var;
	new_envp[i + 1] = NULL;
	add_to_env(new_envp, envp, &status, exec);
}

int	extract_key_val(char *arg, char ***key_val, char **key, char **val)
{
	*key_val = ft_split(arg, '=');
	if (!*key_val || !(*key_val)[0])
	{
		free_both(*key_val);
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		return (0);
	}
	*key = ft_strdup((*key_val)[0]);
	if (!(*key_val)[1])
		*val = NULL;
	else
		*val = ft_strdup((*key_val)[1]);
	return (1);
}

int	handle_invalid_identifier(char *key, char *val, char *arg)
{
	if (!key || !check_identifier(key))
	{
		write(STDERR_FILENO, "export: `", 9);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, "': not a valid identifier\n", 26);
		free(key);
		free(val);
		return (1);
	}
	return (0);
}

void	process_export_arg(char *arg, char ***envp, t_exec *exec)
{
	char	**key_val;
	char	*key;
	char	*val;

	key_val = NULL;
	key = NULL;
	val = NULL;
	if (!extract_key_val(arg, &key_val, &key, &val))
	{
		exec->exit = 1;
		return ;
	}
	free_both(key_val);
	if (handle_invalid_identifier(key, val, arg))
	{
		exec->exit = 1;
		return ;
	}
	add_or_modify(key, val, envp, exec);
	free(key);
	free(val);
}

void	ft_export(char **args, char ***envp, t_exec *exec)
{
	int	i;

	i = 1;
	while (args[i])
	{
		process_export_arg(args[i], envp, exec);
		i++;
	}
}
