/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:50:01 by dalebran          #+#    #+#             */
/*   Updated: 2024/12/01 06:07:17 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || (c >= '\t' && c <= '\r'));
}

int	is_simple_quote(char c)
{
	return (c == '\'');
}

int	is_double_quote(char c)
{
	return (c == '"');
}

int	is_dollar_interrogation(const char *input, int i)
{
	return (input[i + 1] && input[i] == '$' && input[i + 1] == '?');
}

int	is_directory(char *path)
{
	struct stat	file_stat;

	return (stat(path, &file_stat) == 0 && S_ISDIR(file_stat.st_mode));
}
