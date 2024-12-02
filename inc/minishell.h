/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 22:23:24 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/01 02:04:43 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "builtins.h"
#include "exec.h"
#include "libft.h"
#include "parsing.h"
#include <ctype.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

typedef struct s_shell			t_shell;

typedef struct s_token			t_token;

extern volatile sig_atomic_t	g_signal_received;

typedef struct s_shell
{
	char						**rd_in;
	char						**rd_out;
	int							*out_flags;
	int							*rd_order;
	char						**cmd;
	struct s_shell				*next;
}								t_shell;
typedef struct s_exec
{
	t_shell						*shell;
	char						**envp;
	int							*pipe_fd;
	pid_t						*pids;
	int							infile;
	int							outfile;
	int							cmd_count;
	t_token						*tokens;
	int							exit;
	char						**tmp;
	char						**tmp2;
}								t_exec;
