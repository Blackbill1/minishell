/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbruscan <gbruscan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 17:33:31 by dalebran          #+#    #+#             */
/*   Updated: 2024/12/01 06:25:24 by gbruscan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "minishell.h"

typedef struct s_shell	t_shell;

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_FILE_NAME,
}						t_token_Type;

typedef struct s_token
{
	t_token_Type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef struct s_envp_exit
{
	char				**envp;
	int					*exit_value;
}						t_envp_exit;

// is.c
int						is_space(char c);
int						is_simple_quote(char c);
int						is_double_quote(char c);
int						is_dollar_interrogation(const char *input, int i);
int						is_directory(char *path);

// in_fd.c
int						is_pipe(char c);
int						is_redirect_out(const char *input, int i);
int						is_append(const char *input, int i);
int						is_redirect_in(const char *input, int i);
int						is_heredoc(const char *input, int i);

// tokens.c
t_token					*create_token(t_token_Type type, const char *value,
							int *i, int increment);
t_token					*add_token_to_list(t_token *head, t_token *new_token);
t_token					*tokenize(const char *input, char **envp,
							int *exit_value);
t_token					*handle_token_creation(const char *input, int *i,
							t_envp_exit envp_exit);
t_token					*create_word_token(const char *input, int *i,
							t_envp_exit envp_exit);

// handle.c
int						handle_simple_quote(const char *input, int *i,
							char **result_word);
int						handle_double_quote(const char *input, int *i,
							char **result_word, t_envp_exit envp_exit);
void					handle_dollar_interrogation(int *i, char **result_word,
							int *exit_value);
void					handle_unquoted_word(const char *input, int *i,
							char **result_word, t_envp_exit envp_exit);

// parser.c
t_shell					*initialize_command(void);
t_shell					*parse_tokens(t_token *tokens, int *tmp_nb);
void					update_redirect_in(char ***redirect,
							const char *file_name);
void					update_redirect_out(char ***redirect,
							int **append_flags, const char *file_name,
							int is_append);
void					update_redirect_order(int **redirect, int order_val);

// add.c
t_shell					*add_word(t_shell *cur_cmd, t_token *token);
t_shell					*add_simple_quote(t_shell *cur_cmd, t_token *token);
t_shell					*add_double_quote(t_shell *cur_cmd, t_token *token);

// add_fd.c
t_shell					*add_pipe(t_shell *current_command);
t_shell					*add_redirect_in(t_shell *cur_command, t_token *token);
t_shell					*add_redirect_out(t_shell *current_command,
							t_token *token, int is_append);
t_shell					*add_heredoc(t_shell *cur_comm, t_token *token,
							int *tmp_nb);

// check.c
int						check_pipe(const char *input, int i);
int						check_single_quotes_closed(const char *input, int *i);
int						check_double_quotes_closed(const char *input, int *i);
int						check_syntax_errors(const char *input);
int						check_quotes(const char *input, int *i);

// check_red.c
int						check_red_in(const char *input, int *i);
int						check_red_out(const char *input, int *i);
int						check_redirections(const char *input, int *i);

// utils.c
void					gnl_heredoc(t_token *token, int fd);
void					ft_error(const char *message);
char					*ft_strndup(const char *s, size_t n);
void					unlink_tmps(int tmp_nb);

// envp.c
char					*calc_dollar_envp(const char *input, char **envp,
							int *exit_value);
char					*get_env_value(const char *var_name, char **envp);
char					*process_dollar(const char *value, char *result);
char					*process_char(char c, char *result);
char					*handle_dollar(const char *input, int *i, char *result,
							char **envp);
