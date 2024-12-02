/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dalebran <dalebran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:44:11 by dalebran          #+#    #+#             */
/*   Updated: 2024/11/23 19:44:23 by dalebran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(char c)
{
	return (c == '|');
}

int	is_redirect_out(const char *input, int i)
{
	return (input[i] == '>' && input[i + 1] != '>');
}

int	is_append(const char *input, int i)
{
	return (input[i] == '>' && input[i + 1] == '>');
}

int	is_redirect_in(const char *input, int i)
{
	return (input[i] == '<' && input[i + 1] != '<');
}

int	is_heredoc(const char *input, int i)
{
	return (input[i] == '<' && input[i + 1] == '<');
}
