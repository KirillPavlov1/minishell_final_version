/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchalmer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 22:44:16 by rchalmer          #+#    #+#             */
/*   Updated: 2021/07/28 22:44:18 by rchalmer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <term.h>
# include <string.h>
# include <curses.h>
# include <termcap.h>
# include <stdlib.h>
# include <errno.h>
# include "libft/libft.h"
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "readline/readline.h"
# include <readline/history.h>
# define TMP_FD ".tmp_fd"
# define TMP_FILE ".heredoc"

int	g_status;

typedef struct s_fd
{
	int					std_input;
	int					std_output;
}						t_fd;

typedef struct s_redirect{
	int					redirect;
	char				*argv;
	struct s_redirect	*next;
}						t_redirect;

typedef struct s_cmd
{
	char				*way;
	char				**argv;
	int					count;
	t_redirect			*dir;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_all
{
	char				*dollar;
	char				*path;
	char				**my_env;
	t_cmd				*cmd;
	int					f;
	char				*old;
	char				*to_red;
	int					exit_code;
	t_fd				fd;
}						t_all;

char					*ft_realloc(char *ptr, size_t size);
char					*str_add_to_end(char *str, char c);
size_t					ft_strlen2(const char *s);
void					make_null(char ***argv, int n);
void					ft_listadd_back(t_cmd **lst, t_cmd *new);
t_cmd					*ft_listnew(void);
t_cmd					*ft_listlast(t_cmd *lst);
void					parse_line(char *line, t_all **all);
char					*try_find(char *path, char **env);
void					output_all(t_all *all);
char					*find_binary(char *cmnd, char *paths);
void					find_path(t_all **all);
void					redirect_back(t_redirect **lst, t_redirect *new);
t_redirect				*new_redirect(void);
t_redirect				*redirect_last(t_redirect *lst);
void					redirect2(char *line, int *i, t_all **all);
void					redirect3(char *line, int *i, t_all **all);
void					redirect4(char *line, int *i, t_all **all);
void					free_all(t_all **all);
int						is_equal(char *path, char *env);
int						is_minishell(char *line);
int						ft_strcmp(char *s1, char *s2);
void					signal_handler(int sig_num);
void					redirect3_12(char *line, int *i, t_all **all);
int						count_argv(char *line, int i);
void					parse_line3(char *line, int *i, int *m, t_all **all);
void					parse_line4(char *line, int *i, int *m, t_all **all);
void					parse_line5(char *line, int *i, int *m, t_all **all);
char					**copy_env(char **env);
int						is_number(char *value);
int						my_echo(char **argv);
int						my_cd(char **argument, char ***envp_cp);
int						my_pwd(void);
int						my_export(char **argv, char ***envp_cp);
void					print_arr_2x(char **array);
char					*get_value(char **envp_cp, char *key);
char					*check_arg(char **envp_cp, char **key);
void					sort_array_2x(char **array);
int						count_envp(char **envp_cp);
void					executor(t_all **all);
void					execute_binary(char *binary_path, \
							char **argv, char ***envp_cp, int *exit_code);
int						builtins(t_cmd *tmp, char ***envp, int *exit_code);
int						fail(char *str, int res);
int						count_arguments(char **argv);
int						my_unset(char ***envp_cp, char **argument);
int						my_env(char **envp_cp, char **argv);
void					my_exit(char **argv, int *exit_code);
char					**copy_arrays_2x(char **src_arr);
void					clear_arr_2x(char **a);
char					**check_key(char **envs, char *key);
int						set_value_arr_2x(char *str, char ***arr);
int						check_var_validity(char *argument);
int						add_to_envp(char ***envp_cp, char *argument);
int						replace_var(char *key, char **envp_cp, char *argument);
int						my_heredoc(char *delimiter, t_all *all);
int						exec_heredoc(char *delimeter, t_all *all);
int						is_builtin(t_cmd *tmp);
char					*parse_dollar(char *line, t_all **all);
char					*get_absolute_path(char **envp_cp, char *relative_path);
int						ft_free(char **ptr, int res);
int						call_exec_simple(t_all **all, \
											t_cmd *tmp, int backup_fd[2]);
void					init_child(t_all **all, int excode, \
							t_cmd *tmp, int fd_pipe[2]);
void					recover_fd(int backup_fd[2], t_fd *fd);
void					tmp_fd(int input_fd, int exit_code);
int						do_redirection(int redirect, char *argv, t_fd *std_fd);
int						perror_and_return(char *argv);
void					call_exec_complex(t_all **all, \
								t_cmd *tmp, int backup_fd[2]);
int						scan_redirects(t_redirect *dir, \
							t_fd *std_fd, t_all *all);
char					*increase_sh_level(char *value);
char					**add_default_variables(char ***envp);
#endif
