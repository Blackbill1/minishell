/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:45:24 by gbruscan          #+#    #+#             */
/*   Updated: 2024/10/14 20:09:50 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	words;
	int	i;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

static void	free_tab(char **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i])
			free(tab[i]);
		i++;
	}
	free(tab);
}

static void	fill_tab(char *new, char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
}

static int	tab_init(char **tab, char const *s, char c)
{
	int	count;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		count = 0;
		while (s[i + count] && s[i + count] != c)
			count++;
		if (count > 0)
		{
			tab[j] = malloc(sizeof(char) * (count + 1));
			if (!tab[j])
				return (free_tab(tab, j), 0);
			fill_tab(tab[j], (s + i), c);
			j++;
			i = i + count;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	int		words;
	char	**tab;

	words = count_words(s, c);
	tab = malloc(sizeof(char *) * (words + 1));
	if (!tab)
		return (NULL);
	if (!tab_init(tab, s, c))
		return (NULL);
	return (tab);
}
