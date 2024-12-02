/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:13:51 by dalebran          #+#    #+#             */
/*   Updated: 2024/12/01 06:28:56 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "minishell.h"

typedef struct s_exec	t_exec;
typedef struct s_shell	t_shell;
typedef struct s_token	t_token;

// cmd.c
int						is_ours(char *cmd);
void					execute_commands(t_exec *exec);
void					exec_cmd(t_exec *exec, char **cmd, int cmd_index);
void					wait_process(t_exec *exec);

// exec.c
void					exec_builtins(t_exec *exec, char **cmd);
void					child_process(t_exec *exec, char **cmd, int cmd_index);

// init.c
int						cmd_count(t_shell *shell);
t_exec					*exec_init(t_shell *shell, char **envp,
							t_token *tokens);

// path.c
char					*search_in_paths(char **paths, char *cmd);
char					*find_command_path(char *cmd, char **envp);
char					**get_envp(char **envp);

// pipes.c
void					close_pipe(t_exec *exec, int cmd_index);
void					setup_pipes(t_exec *exec, int cmd_index);
void					close_all_pipes(t_exec *exec);
void					duplicate_single_command_fds(t_exec *exec, int fd_in,
							int fd_out);
void					duplicate_fds(t_exec *exec, int cmd_index, int fd_in,
							int fd_out);
void					handle_exec_redirections(t_exec *exec, int *fd_in,
							int *fd_out);
void					elsefd(int *fd_in, int *fd_out, t_exec *exec);

// free.c
void					free_envp(char **envp);
void					clear_exec(t_exec *exec);
void					free_shell(t_shell *shell);
void					free_token(t_token *token);
void					free_all(t_exec *exec);
void					free_cmd_rdin(t_shell *shell);
void					free_path(char *cmd_path, char *error, t_exec *exec);

// handle_error
void					handle_no_cmd_name(t_exec *exec, char *cmd_path);
void					handle_no_cmd_path(t_exec *exec, char *cmd_name);
int						is_directory(char *path);
void					handle_is_directory(t_exec *exec, char *cmd_path,
							char *cmd_name);
void					handle_no_exec_permission(t_exec *exec, char *cmd_path,
							char *cmd_name);
void					handle_exec_error(char *cmd_path, char *cmd_name,
							t_exec *exec);

// fds
int						ft_open(t_shell *shell, char *rd, int b, int i);
int						get_outfile(char *rd_out, t_exec *exec, int index);
int						get_infile(char *rd_in, t_exec *exec);
void					fd_errorout(char *rd_out);
void					fd_errorin(char *rd_in);

// fds_manager
void					elsefd(int *fd_in, int *fd_out, t_exec *exec);
void					duplicate_fds(t_exec *exec, int cmd_index, int fd_in,
							int fd_out);
void					duplicate_single_command_fds(t_exec *exec, int fd_in,
							int fd_out);

// loop.c
void					minishell_loop(char **envp);
void					minishell_iteration(char ***cur_envp, t_exec **exec,
							int *exit_value);
int						handle_execution(char ***cur_envp, t_exec **exec,
							int *exit_value, char *input);
void					execute_and_cleanup(t_exec **exec, t_token *tokens,
							t_shell *parsed_commands, char ***cur_envp);
void					ctrl_d(t_exec *exec, char **cur_envp, int *exit_value);