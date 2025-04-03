/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:44:10 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 17:35:19 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_simple_quote(char *str, int *i)
{
	char	quote;

	while (str[*i])
	{
		if (str[*i] == '\'')
		{
			quote = str[*i];
			(*i)++;
			while (str[*i] != quote && str[*i])
				(*i)++;
		}
		else if (str[*i] == '$')
			return ;
		(*i)++;
	}
}

char	*parse_all_str_for_dollar(t_var *var, char *str, int i, int y)
{
	char	*temp;
	char	*temp2;
	char	*newstr;
	int		prev_i;

	temp = NULL;
	temp2 = NULL;
	newstr = NULL;
	prev_i = 0;
	while ((size_t)i < ft_strlen(str))
	{
		y = prev_i;
		temp = check_dollars_parsing(var, str, &i, y);
		if (temp2 != NULL)
			newstr = ft_strjoin(temp2, temp);
		if (temp2 != NULL)
			free(temp2);
		else
			newstr = ft_strdup(temp);
		temp2 = newstr;
		prev_i = i + 1;
		free(temp);
		i++;
	}
	return (newstr);
}

char	*check_quote(char *str, int i, int y)
{
	char	quote;
	char	*cpy;

	if (str == NULL)
		return (NULL);
	if (ft_strcmp(str, "\"\"") == 0 || ft_strcmp(str, "\'\'") == 0)
		return (ft_strdup(str));
	cpy = malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (i < (int)ft_strlen(str) && str[i])
	{
		if (ft_strchr("\'\"", str[i]) != NULL && str[i])
		{
			quote = str[i];
			i++;
			while (i < (int)ft_strlen(str) && str[i] != quote && str[i])
				cpy[y++] = str[i++];
			i++;
		}
		else
			cpy[y++] = str[i++];
	}
	cpy[y] = 0;
	if (cpy[0] == 0)
		return (free(cpy), NULL);
	return (cpy);
}

char	*check_exit(char *temp2, char *temp3)
{
	free(temp2);
	if (temp3 == NULL)
		return (ft_strdup(""));
	return (temp3);
}

char	**convert_parse(t_var *var, t_list *lst)
{
	char	*temp;
	char	*temp2;
	char	*temp3;
	char	**exit;
	int		i;

	i = 0;
	exit = malloc(sizeof(char *) * (ft_lstsize(lst) + 1));
	while (lst)
	{
		temp = lst->content;
		temp2 = parse_all_str_for_dollar(var, temp, 0, 0);
		temp3 = check_quote(temp2, 0, 0);
		exit[i] = check_exit(temp2, temp3);
		i++;
		if (temp3 && ft_strcmp(temp3, "<<") == 0 && lst->next)
		{
			exit[i] = ft_strdup((char *)lst->next->content);
			i++;
			lst = lst->next;
		}
		lst = lst->next;
	}
	exit[i] = 0;
	return (exit);
}
