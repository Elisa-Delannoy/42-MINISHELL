/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:44:45 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 17:35:54 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <sys/wait.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <termios.h>
# include "libft/libft.h"

extern int	g_sig;

typedef struct s_exec
{
	char			**cmd;
	char			*path;
	int				input;
	int				output;
	int				unset_path;
	struct s_exec	*next;
}	t_exec;

typedef struct s_heredoc
{
	char	*line;
	char	*line2;
	int		fd;
	char	*file;
	char	*n_eof;
	int		i;
}	t_heredoc;

typedef struct s_var
{
	t_list		*env;
	t_list		*export;
	t_list		*parse;
	t_exec		*exec;
	t_heredoc	hd;
	char		**data;
	char		*pwd;
	char		*oldpwd;
	char		*home;
	int			cmd_count;
	int			nbcmd;
	int			status;
	int			count_line;
	int			save_fd;
}	t_var;

char		**convert_parse(t_var *var, t_list *lst);
t_list		*parsing_line(char *str);
int			check_error_parsed(t_list *check);
char		*check_dollars_parsing(t_var *var, char *str, int *i, int y);
t_var		*init_struct(t_var *var, char **env);
void		ft_env(t_var *var, char **tab);
void		ft_export(t_var *var, char **tab);
void		increase_shlvl(t_var *var);
void		add_var_env(t_var *var, char **tab);
void		ft_unset(t_var *var, char **tab);
void		(*ft_cmd(char **cmd))(t_var *var, char **tab);
void		ft_exe(t_var *var, char **tab);
void		exec_pid(t_var *var, char **tab);
char		**convert_env(t_list *env);
void		execution(t_var *var, t_exec *exec);
int			gest_heredoc(t_var *var, char *eof, int i);
void		ft_error_path_cmd(t_var *var, t_exec *exec, char **env);
void		setup_dup2_and_close(t_exec *exec, int *fd);
void		wait_all_pid(t_var *var, pid_t *pids);
void		select_input(t_exec *exec, int i, int *prevfd);
void		select_output(int *fd, t_exec *exec, int i, t_var *var);
void		setup_exec(t_var *var, t_exec *exec);
void		exec_all(t_var *var, t_exec *exec, char **env);
void		close_fd(int *fd, int prevfd, int i, t_exec *exec);
void		do_pids(t_exec *exec, pid_t *pids, int *fd, t_var *var);
int			count_command(char **tab);
char		*check_path(char **env, char *cmd);
char		**check_command(char **tab, t_var *var, t_exec *exec);
t_exec		*init_exec(t_var *var, char **tab);
void		exec_add_back(t_exec **exec, t_exec *new);
t_exec		*exec_last(t_exec *exec);
t_exec		*ft_execnew(void);
int			check_input(t_var *var, char **cmd, int i);
int			check_output(char **cmd, int i);
void		ft_lstadd_next(t_list **lst, t_list *new);
long int	ft_atol(char *str);
size_t		ft_strlenlongint(long n);
char		*ft_litoa(long int nb);
char		*ft_strncpy(char *str, int size);
void		ft_echo(t_var *var, char **tab);
void		ft_pwd(t_var *var, char **tab);
void		ft_cd(t_var *var, char **tab);
void		ft_dollar(t_var *var, char **tab);
size_t		var_name_len(char *tab);
void		ft_exit(t_var *var, char **tab);
void		ft_free_all(t_var *var);
void		ft_free_exec(t_exec *exec);
int			check_shlv(t_var *var);
void		update_env_pwd_and_old_(t_var *var);
char		*check_export(t_var *var, char *str, int size);
void		ft_ctrl_c(int sig);
int			ft_ctrl_c_heredoc(int sig, char *line, int fd);
void		ft_ctrl_slash(int sig);
void		manage_signal(void);
int			ft_check_ctrl_c_heredoc(void);
void		ft_ctrl_d_heredoc(t_var *var, char *eof);
char		*check_quote(char *str, int i, int y);
void		all_dollar(char *str, int *i);
char		*parse_dollar(t_var *var, char *str, int *i, int y);
char		*return_str(char *str, char *cpy, int i, int y);
char		*parse_all_str_for_dollar(t_var *var, char *str, int i, int y);
char		*parse_dollar(t_var *var, char *str, int *i, int y);
char		*check_return_value(t_var *var, char *temp);
char		*check_dollars_heredoc(t_var *var, char *str, int *i, int y);
char		*check_dollars_parsing(t_var *var, char *str, int *i, int y);
void		check_simple_quote(char *str, int *i);
void		err_brioshell(char *tab);

#endif
