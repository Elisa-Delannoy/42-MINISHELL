/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:44:20 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 15:58:53 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	gest_quote(char *str, int i, int j, t_list **line)
{
	char	quote;
	char	*temp;

	quote = str[i];
	i++;
	while (str[i] != quote && str[i])
		i++;
	if (str[i] == 0)
		return (ft_putstr_fd("Need to close quote.\n", 1), -1);
	while (str[i + 1] && ft_isspace(str[i + 1]) == 0
		&& ft_strchr("<>|", str[i + 1]) == NULL)
		i++;
	temp = ft_substr(str, j, i - j + 1);
	ft_lstadd_back(line, ft_lstnew(temp));
	i++;
	return (i);
}

int	gest_token(char *str, int i, int j, t_list **line)
{
	char	*temp;

	if (i > 0 && (ft_isspace(str[i - 1]) == 0) && str[i - 1] != str[i]
		&& ft_strchr("\"\'", str[i - 1]) == NULL)
	{
		temp = ft_substr(str, j, i - j);
		ft_lstadd_back(line, ft_lstnew(temp));
		j = i;
	}
	if (ft_strchr("<>", str[i + 1]) && ft_strchr("<>", str[i]))
		i++;
	temp = ft_substr(str, j, i - j + 1);
	ft_lstadd_back(line, ft_lstnew(temp));
	i++;
	return (i);
}

void	parse_useless(char *str, int *i, int *j)
{
	while (*i < (int)ft_strlen(str) && ft_isspace(str[*i]) && str[*i])
		(*i)++;
	*j = *i;
	while (*i < (int)ft_strlen(str) && str[*i]
		&& ft_strchr("<>|\'\" 	", str[*i]) == NULL)
		(*i)++;
}

t_list	*parsing_line(char *str)
{
	int		i;
	int		j;
	t_list	*line;
	char	*temp;

	i = 0;
	line = NULL;
	while (i < (int)ft_strlen(str) && str[i])
	{
		j = i;
		parse_useless(str, &i, &j);
		if (ft_isspace(str[i]) || (str[i] == 0 && ft_isspace(str[i - 1]) == 0))
		{
			temp = ft_substr(str, j, i - j);
			ft_lstadd_back(&line, ft_lstnew(temp));
			i++;
		}
		else if (str[i] && ft_strchr("\'\"", str[i]))
			i = gest_quote(str, i, j, &line);
		else if (str[i] && ft_strchr("<|>", str[i]))
			i = gest_token(str, i, j, &line);
		if (i == -1)
			return (ft_lstclear(&line, free), NULL);
	}
	return (line);
}
