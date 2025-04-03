/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrontard <nrontard@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 13:43:04 by nrontard          #+#    #+#             */
/*   Updated: 2025/04/02 16:19:39 by nrontard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_echo(t_var *var, char **tab, int i, int j)
{
	if (tab[i][j] == '~')
		ft_putstr_fd(var->home +5, 1);
	else if (tab[i] && tab[i][j])
	{
		printf("%s", tab[i]);
		if (tab[i + 1])
			printf(" ");
	}
}

int	check_n(char **tab, int *i)
{
	int	check;
	int	j;

	check = 0;
	while (tab[*i])
	{
		if (tab[*i][0] == '-' && tab[*i][1] == 'n')
		{
			j = 1;
			while (tab[*i][j] && tab[*i][j] == 'n')
				j++;
			if (tab[*i][j] == 0)
				check = 1;
			else
				break ;
		}
		else
			break ;
		*i = *i + 1;
	}
	return (check);
}

void	ft_echo(t_var *var, char **tab)
{
	int	i;
	int	j;
	int	check;

	(void) var;
	i = 1;
	j = 0;
	check = check_n(tab, &i);
	while (tab[i])
	{
		print_echo(var, tab, i, j);
		j = 0;
		i++;
	}
	if (check != 1)
		printf("\n");
	var->status = 0;
}
