/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 17:59:27 by tle-dref          #+#    #+#             */
/*   Updated: 2024/12/01 05:52:59 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "minishell.h"

typedef struct s_exec	t_exec;

// env
void					ft_env(char **envp);

// exit
int						ft_exit(char **args, t_exec *exec);

// export
void					ft_export(char **args, char ***envp, t_exec *exec);
void					process_export_arg(char *arg, char ***envp,
							t_exec *exec);
int						handle_invalid_identifier(char *key, char *val,
							char *arg);
int						extract_key_val(char *arg, char ***key_val, char **key,
							char **val);
void					add_or_modify(char *key, char *val, char ***envp,
							t_exec *exec);
int						check_identifier(char *id);
char					**cpy_envp(char ***envp, int i);
char					*create_var(char *key, char *val);
void					free_both(char **key_val);
void					add_to_env(char **new_envp, char ***envp, int *status,
							t_exec *exec);

// unset
void					ft_unset(char **args, char ***envp);

// cd
int						ft_cd(t_exec *exec, char **args);
char					*ft_getpwd(char **envp);
void					update_oldpwd(t_exec *exec, char *pwd_value);
void					update_pwd(t_exec *exec, char *oldpwd);
int						count_args(char **args);
void					no_arg(t_exec *exec, char *oldpwd);
int						two_args(char **args, char *cwd, t_exec *exec);

// echo
void					ft_echo(char **av);

// pwd
void					ft_pwd(char **envp);
