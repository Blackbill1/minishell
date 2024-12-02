/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 05:55:24 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 06:03:26 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_exec *exec)
{
	if (exec->tmp)
		free(exec->tmp);
	if (exec->tokens)
		free_token(exec->tokens);
	if (exec->shell)
		free_shell(exec->shell);
	if (exec->envp)
		free_envp(exec->envp);
	if (exec)
		clear_exec(exec);
}

void	free_path(char *cmd_path, char *error, t_exec *exec)
{
	free(cmd_path);
	free(error);
	close_all_pipes(exec);
	free_all(exec);
}
