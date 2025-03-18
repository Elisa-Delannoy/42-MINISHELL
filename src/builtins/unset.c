#include "../../minishell.h"

size_t	var_name_length(char *tab)
{
	size_t	j;

	j = 0;
	while (tab && tab[j + 1] != '='
		&& (ft_isalnum(tab[j]) == 1 || tab[j] == '_'))
		j++;
	return (j);
}

int	unset_first(t_var *var, char *tab, t_list *temp, int len)
{
	if (var->env && ft_strncmp(ft_strjoin(tab, "="),
			(char *)var->env->content, len) == 0)
	{
		temp = var->env->next;
		free (var->env->content);
		free (var->env);
		var->env = temp;
		return (0);
	}
	return (1);
}

void	check_var_env_unset(t_var *var, char *tab)
{
	if (strncmp(tab, "HOME", ft_strlen(tab)) == 0)
	{
		free (var->home);
		var->home = NULL;
	}
	else if (strncmp(tab, "OLDPWD", ft_strlen(tab)) == 0)
	{
		free (var->oldpwd);
		var->oldpwd = NULL;
	}
	return ;
}

int	unset_second_or_more(t_var *var, char *tab, t_list *temp, int len)
{
	t_list	*temp2;

	if (var->env->next && ft_strncmp(ft_strjoin(tab, "="),
			(char *)var->env->next->content, len) == 0)
	{
		check_var_env_unset(var, tab);
		if (var->env->next->next)
			temp2 = var->env->next->next;
		else
			temp2 = NULL;
		free (var->env->next->content);
		free (var->env->next);
		var->env->next = temp2;
		var->env = temp;
		return (0);
	}
	return (1);
}

void	ft_unset(t_var *var, char **tab)
{
	t_list	*temp;
	int		len;
	int		i;

	i = 1;
	while (tab[i])
	{
		len = var_name_length(tab[i]) + 1;
		temp = var->env;
		if (var_name_length(tab[i]) != ft_strlen(tab[i]))
			return ;
		if (unset_first(var, tab[i], temp, len) == 1)
		{
			while (var->env && var->env->next)
			{
				if (unset_second_or_more(var, tab[i], temp, len) == 0)
					break ;
				else
					var->env = var->env->next;
			}
		}
		var->env = temp;
		i++;
	}
	var->env = temp;
}
