/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:03:38 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/01 19:26:12 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_env_var(char ***envp, int index)
{
	free((*envp)[index]);
	while ((*envp)[index])
	{
		(*envp)[index] = (*envp)[index + 1];
		index++;
	}
}

static int	compare_env_key(char *env_var, char *key, int lenkey)
{
	return (ft_strncmp(env_var, key, lenkey) == 0 && env_var[lenkey] == '=');
}

static void	process_arg(char *arg, char ***envp)
{
	char	*key;
	int		lenkey;
	int		j;

	key = arg;
	lenkey = ft_strlen(key);
	j = 0;
	while ((*envp)[j])
	{
		if (compare_env_key((*envp)[j], key, lenkey))
		{
			remove_env_var(envp, j);
			break ;
		}
		j++;
	}
}

void	ft_unset(char **args, char ***envp)
{
	int	i;

	i = 1;
	while (args[i])
	{
		process_arg(args[i], envp);
		i++;
	}
}

// void	print_env(char **envp)
// {
// 	int	i;

// 	i = 0;
// 	while (envp[i])
// 	{
// 		printf("%s\n", envp[i]);
// 		i++;
// 	}
// }

// int	main(void)
// {
// 	char	*args[] = {"USER=", "PATH=", NULL};
// 	int		i;

// 	char **envp = malloc(sizeof(char *) * 4);
// 	envp[0] = strdup("USER=John");
// 	envp[1] = strdup("HOME=/home/john");
// 	envp[2] = strdup("PATH=/usr/bin:/bin:/usr/sbin:/sbin");
// 	envp[3] = NULL;
// 	printf("Environnement avant unset:\n");
// 	print_env(envp);
// 	unset(args, &envp);
// 	printf("\nEnvironnement après unset:\n");
// 	print_env(envp);
// 	i = 0;
// 	while (envp && envp[i])
// 	{
// 		free(envp[i]);
// 		i++;
// 	}
// 	free(envp);
// 	return (0);
// }
