/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 04:13:06 by dalebran          #+#    #+#             */
/*   Updated: 2024/12/01 19:34:53 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(const char *message)
{
	if (message)
		write(2, message, ft_strlen(message));
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	len = ft_strnlen(s, n);
	dup = malloc(len + 1);
	if (!dup)
	{
		return (NULL);
	}
	ft_strncpy(dup, s, len);
	dup[len] = '\0';
	return (dup);
}

void	gnl_heredoc(t_token *token, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(0);
		if (!line)
		{
			if (g_signal_received)
				ft_error("golemShell: here-doc terminated by signal\n");
			else
				ft_error("golemShell: warning: here-doc needs its delimiter\n");
			close(fd);
			return ;
		}
		if (ft_strncmp(token->next->value, line, ft_strlen(line) - 1) == 0
			&& (ft_strlen(line) - 1 == ft_strlen(token->next->value)))
			break ;
		ft_putstr_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
}

void	unlink_tmps(int tmp_nb)
{
	int		i;
	char	*tmp;
	char	*id;

	i = 1;
	while (i < tmp_nb)
	{
		id = ft_itoa(i);
		tmp = ft_strjoin(".tmp", id);
		unlink(tmp);
		free(id);
		free(tmp);
		i++;
	}
}
