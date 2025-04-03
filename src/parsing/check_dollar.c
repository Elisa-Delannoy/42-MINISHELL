/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:44:01 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 17:21:09 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*check_return_value(t_var *var, char *temp)
{
	char	*cpy;
	char	*status_value;

	cpy = NULL;
	status_value = ft_itoa(var->status);
	if (temp != NULL)
		cpy = ft_strjoin(temp, status_value);
	else
		cpy = ft_strdup(status_value);
	free(status_value);
	return (cpy);
}

char	*return_str(char *str, char *cpy, int i, int y)
{
	char	*temp3;
	char	*temp4;

	temp3 = NULL;
	temp4 = NULL;
	temp3 = ft_substr(str, y, i - y);
	temp4 = cpy;
	if (temp4 == NULL)
		temp4 = ft_strdup("");
	cpy = ft_strjoin(temp4, temp3);
	free(temp3);
	free(temp4);
	return (cpy);
}

void	all_dollar(char *str, int *i)
{
	while (str[*i] && str[*i] == '$')
	{
		if (str[*i + 1] != '$')
			break ;
		*i = *i + 1;
	}
	return ;
}

char	*check_dollars_heredoc(t_var *var, char *str, int *i, int y)
{
	char	*cpy;
	char	*temp;
	int		init_i;

	cpy = NULL;
	temp = NULL;
	init_i = *i;
	while (str[*i] && str[*i] != '$' && *i < (int)ft_strlen(str))
		*i = *i + 1;
	if (str[*i] == '$')
	{
		all_dollar(str, i);
		temp = parse_dollar(var, str, i, y);
		y = *i;
		cpy = return_str(str, temp, *i, y);
	}
	else
	{
		cpy = ft_strdup(str + init_i);
	}
	return (cpy);
}

char	*check_dollars_parsing(t_var *var, char *str, int *i, int y)
{
	char	*cpy;
	char	*temp;
	int		init_i;

	cpy = NULL;
	temp = NULL;
	init_i = *i;
	check_simple_quote(str, i);
	while (str[*i] && str[*i] != '$' && *i < (int)ft_strlen(str))
		*i = *i + 1;
	if (str[*i] == 0)
	{
		*i = *i + ft_strlen(str);
		return (ft_strdup(str + init_i));
	}
	if (str[*i] == '$')
	{
		all_dollar(str, i);
		temp = parse_dollar(var, str, i, y);
		y = *i;
		cpy = return_str(str, temp, *i, y);
	}
	else
		cpy = ft_strdup(str + init_i);
	return (cpy);
}
