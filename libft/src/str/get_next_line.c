/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 00:38:34 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/23 03:08:49 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	len_char(const char *str, char c)
{
	size_t	i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

static char	*ft_strjoin_line(char *line, char *buffer)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join = (char *)malloc(len_char(line, '\0') + len_char(buffer, '\n') + 2);
	if (!join)
		return (NULL);
	while (line && line[j])
		join[i++] = line[j++];
	j = 0;
	while (buffer && buffer[j] && buffer[j] != '\n')
		join[i++] = buffer[j++];
	join[i] = '\n';
	if (buffer[j] == '\n')
		i++;
	join[i] = '\0';
	if (line)
		free(line);
	return (join);
}

static void	set_buf(char *buffer)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	while (buffer[i + j])
	{
		buffer[j] = buffer[i + j];
		j++;
	}
	buffer[j] = '\0';
}

static char	*read_file(int fd, char *buffer)
{
	char	*line;
	ssize_t	bytes_read;

	bytes_read = 1;
	line = NULL;
	if (buffer && buffer[0])
	{
		line = ft_strjoin_line(line, buffer);
		if (len_char(buffer, '\n') != len_char(buffer, '\0'))
			return (line);
	}
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (NULL);
		buffer[bytes_read] = '\0';
		line = ft_strjoin_line(line, buffer);
		if (len_char(buffer, '\n') != len_char(buffer, '\0'))
			break ;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buffer[1024][BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, buffer[fd]);
	if (line == NULL)
		return (NULL);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	set_buf(buffer[fd]);
	return (line);
}
