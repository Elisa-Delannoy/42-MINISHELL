#include "../../minishell.h"

void	ft_free_exec(t_exec *exec)
{
	t_exec	*temp;

	if (exec == NULL)
		return ;
	while (exec)
	{
		temp = exec->next;
		if (exec->cmd)
		{
			free_split(exec->cmd);
			exec->cmd = NULL;
		}
		if (exec->path != NULL)
			free(exec->path);
		free(exec);
		exec = NULL;
		exec = temp;
	}
}

void	ft_free_all(t_var *var)
{
	ft_free_exec(var->exec);
	if (var->parse != NULL)
		ft_lstclear(&(var->parse), free);
	if (var->data != NULL)
		free_split(var->data);
	if (var->env != NULL)
		ft_lstclear(&(var->env), free);
	if (var->pwd != NULL)
		free (var->pwd);
	if (var->oldpwd != NULL)
		free (var->oldpwd);
	if (var->home != NULL)
		free (var->home);
	var->parse = NULL;
	var->data = NULL;
	var->env = NULL;
	var->pwd = NULL;
	var->oldpwd = NULL;
	var->home = NULL;
	free(var);
	rl_clear_history();
}

void	error_message_exit_two_arg(t_var *var, char **tab, char *str)
{
	ft_putstr_fd(tab[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(tab[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("numeric argument required\n", 2);
	var->status = 2;
	ft_free_all(var);
	free (str);
	exit(2);
}

void	ft_exit(t_var *var, char **tab)
{
	long int	str_i;
	char		*str;

	printf("exit\n");
	if (tab[1])
	{
		str_i = ft_atol(tab[1]);
		str = ft_litoa(str_i);
	}
	if (tab[1] && ft_strcmp(str, tab[1]) != 0)
		error_message_exit_two_arg(var, tab, str);
	else if (tab[1] && tab[2])
		return (ft_putstr_fd(tab[0], 2), ft_putstr_fd(": ", 2), ft_putstr_fd("t"
				"oo many arguments\n", 2), var->status = 127, free(str));
	else
	{
		if (tab && tab[1])
			return (ft_free_all(var), free(str), exit(str_i % 256));
		else
			return (ft_free_all(var), exit(EXIT_SUCCESS));
	}
}
