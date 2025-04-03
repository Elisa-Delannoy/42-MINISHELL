/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edelanno <edelanno@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:43:23 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/03 13:48:14 by edelanno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_var_env_unset(t_var *var, char *tab)
{
	if (strncmp(tab, "HOME", ft_strlen(tab)) == 0)
	{
		if (var->home)
			free (var->home);
		var->home = NULL;
	}
	else if (strncmp(tab, "OLDPWD", ft_strlen(tab)) == 0)
	{
		if (var->oldpwd != NULL)
			free (var->oldpwd);
		var->oldpwd = NULL;
	}
	return ;
}

int	unset_first(t_var *var, char *tab, t_list *temp, int len)
{
	int	len_env;

	len_env = var_name_len((char *)var->env->content);
	if (var->env && len_env == len && ft_strncmp(tab,
			(char *)var->env->content, len) == 0)
	{
		check_var_env_unset(var, tab);
		temp = var->env->next;
		free (var->env->content);
		free (var->env);
		var->env = temp;
		return (0);
	}
	return (1);
}

int	unset_between(t_var *var, char *tab, t_list *temp, int len)
{
	t_list	*temp2;
	int		len_env;

	len_env = var_name_len((char *)var->env->next->content);
	check_var_env_unset(var, tab);
	if (var->env->next && len_env == len && ft_strncmp(tab,
			(char *)var->env->next->content, len) == 0)
	{
		if (var->env->next->next)
		{
			temp2 = var->env->next->next;
			free (var->env->next->content);
		}
		else
			temp2 = NULL;
		free (var->env->next);
		var->env->next = temp2;
		var->env = temp;
		return (0);
	}
	return (1);
}

void	unset_next(t_var *var, char *tab, t_list *temp)
{
	while (var->env && var->env->next)
	{
		if (unset_between(var, tab, temp, var_name_len(tab)) == 0)
			break ;
		else
			var->env = var->env->next;
	}
	var->env = temp;
}

void	ft_unset(t_var *var, char **tab)
{
	t_list	*temp;
	int		i;

	i = 1;
	temp = var->env;
	while (tab[i])
	{
		if (var_name_len(tab[i]) != ft_strlen(tab[i]))
			return ;
		if (unset_first(var, tab[i], temp, var_name_len(tab[i])) == 0)
			temp = var->env;
		else
			unset_next(var, tab[i], temp);
		i++;
	}
	var->env = temp;
	var->status = 0;
}
