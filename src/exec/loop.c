/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 06:26:09 by gbruscan          #+#    #+#             */
/*   Updated: 2024/12/01 06:28:59 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_loop(char **envp)
{
	t_exec	*exec;
	char	**cur_envp;
	int		exit_value;

	exec = NULL;
	exit_value = 0;
	cur_envp = get_envp(envp);
	while (1)
	{
		minishell_iteration(&cur_envp, &exec, &exit_value);
	}
}

void	minishell_iteration(char ***cur_envp, t_exec **exec, int *exit_value)
{
	char	*input;
	int		tmp_nb;

	g_signal_received = 0;
	input = readline("$ ");
	if (!input)
	{
		ctrl_d(*exec, *cur_envp, exit_value);
	}
	if (*input)
	{
		add_history(input);
		if (!check_syntax_errors(input))
		{
			*exit_value = 2;
			free(input);
			return ;
		}
		tmp_nb = handle_execution(cur_envp, exec, exit_value, input);
		unlink_tmps(tmp_nb);
	}
	free(input);
}

int	handle_execution(char ***cur_envp, t_exec **exec, int *exit_value,
		char *input)
{
	t_token	*tokens;
	t_shell	*parsed_commands;
	int		tmp_nb;

	if (*exec)
	{
		*exit_value = (*exec)->exit;
		*cur_envp = (*exec)->envp;
		clear_exec(*exec);
	}
	g_signal_received = 2;
	tmp_nb = 1;
	tokens = tokenize(input, *cur_envp, exit_value);
	parsed_commands = parse_tokens(tokens, &tmp_nb);
	execute_and_cleanup(exec, tokens, parsed_commands, cur_envp);
	return (tmp_nb);
}

void	execute_and_cleanup(t_exec **exec, t_token *tokens,
		t_shell *parsed_commands, char ***cur_envp)
{
	*exec = exec_init(parsed_commands, *cur_envp, tokens);
	execute_commands(*exec);
	close_all_pipes(*exec);
	free_token(tokens);
	free_shell(parsed_commands);
	if ((*exec)->tmp)
	{
		free((*exec)->tmp);
		(*exec)->tmp = NULL;
	}
}

void	ctrl_d(t_exec *exec, char **cur_envp, int *exit_value)
{
	if (exec)
	{
		if (exec->tmp)
			free(exec->tmp);
		(*exit_value) = exec->exit;
		if (exec->envp)
			free_envp(exec->envp);
		clear_exec(exec);
	}
	else
		free_envp(cur_envp);
	exit(*exit_value);
}
