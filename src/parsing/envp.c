/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:15:03 by dalebran          #+#    #+#             */
/*   Updated: 2024/12/01 04:50:53 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(const char *var_name, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var_name);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var_name, len) == 0 && envp[i][len] == '=')
		{
			return (&envp[i][len + 1]);
		}
		i++;
	}
	return (NULL);
}

char	*process_dollar(const char *value, char *result)
{
	char	*old_result;

	old_result = result;
	if (value)
	{
		result = ft_strjoin(result, value);
		free(old_result);
	}
	return (result);
}

char	*process_char(char c, char *result)
{
	char	temp_str[2];

	temp_str[0] = c;
	temp_str[1] = '\0';
	result = clean_join(result, temp_str);
	return (result);
}

char	*handle_dollar(const char *input, int *i, char *result, char **envp)
{
	char	*var_name;
	char	*value;
	int		start;

	(*i)++;
	start = *i;
	if (!input[*i] || is_space(input[*i]))
	{
		result = clean_join(result, "$");
		if (input[*i])
			(*i)++;
		return (process_char(input[*i], result));
	}
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_')
		&& input[*i] != '$')
		(*i)++;
	var_name = ft_strndup(&input[start], *i - start);
	value = get_env_value(var_name, envp);
	free(var_name);
	return (process_dollar(value, result));
}

char	*calc_dollar_envp(const char *input, char **envp, int *exit_value)
{
	char	*result;
	int		i;
	char	*exit_code;

	result = ft_strdup("");
	i = 0;
	while (input[i])
	{
		if (is_dollar_interrogation(input, i))
		{
			i += 2;
			exit_code = ft_itoa(*exit_value);
			result = clean_join(result, exit_code);
			free(exit_code);
		}
		if (input[i] == '$')
			result = handle_dollar(input, &i, result, envp);
		else
		{
			result = process_char(input[i], result);
			i++;
		}
	}
	return (result);
}
