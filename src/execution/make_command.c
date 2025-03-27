#include "../../minishell.h"

char	*find_path(char **path, char *cmd)
{
	char	*temp;
	int		i;

	i = 0;
	while (path[i] != NULL)
	{
		temp = ft_strnjoin(2, (char *[]){path[i], cmd}, "/");
		if (access(temp, F_OK) == 0)
			return (temp);
		free(temp);
		i++;
	}
	return (NULL);
}

char	*check_path(char **env, char *cmd)
{
	int		i;
	char	**path;
	char	*temp;

	if (cmd == NULL || env == NULL)
		return (NULL);
	if (ft_strchr(cmd, '/') != NULL)
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		else
			return ("not found");
	}
	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (!env[i])
		return ("not found");
	path = ft_split(env[i] + 5, ':');
	temp = find_path(path, cmd);
	return (free_split(path), temp);
}

int	count_command(char **tab)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tab[i])
	{
		if (ft_strcmp(tab[i], "|") == 0 && ft_strcmp(tab[i - 1], "|") != 0)
			count++;
		if (ft_strcmp(tab[i], "|") == 0 && tab[i + 1] == NULL)
			return (count);
		i++;
	}
	return (count + 1);
}

int	count_element(char **tab, int i)
{
	int	count;

	count = 0;
	while (tab[i] && ft_strcmp(tab[i], "|") != 0)
	{
		if (ft_strcmp(tab[i], "<") == 0 || ft_strcmp(tab[i], ">") == 0
			|| ft_strcmp(tab[i], ">>") == 0 || ft_strcmp(tab[i], "<<") == 0)
			i += 2;
		else if (tab[i] && ft_strcmp(tab[i], "|") != 0)
		{
			count++;
			i++;
		}
	}
	return (count);
}

char	**check_command(char **tab, t_var *var, t_exec *exec)
{
	char	**cmd;
	int		i;

	i = 0;
	exec->input = check_input(var, tab, var->cmd_count);
	exec->output = check_output(tab, var->cmd_count);
	cmd = malloc(sizeof(char *) * (count_element(tab, var->cmd_count) + 1));
	while (tab[var->cmd_count] && ft_strcmp(tab[var->cmd_count], "|") != 0)
	{
		if (ft_strcmp(tab[var->cmd_count], "<") == 0
			|| ft_strcmp(tab[var->cmd_count], ">") == 0
			|| ft_strcmp(tab[var->cmd_count], ">>") == 0
			|| ft_strcmp(tab[var->cmd_count], "<<") == 0)
			var->cmd_count += 2;
		else if (tab[var->cmd_count]
			&& ft_strcmp(tab[var->cmd_count], "|") != 0)
		{
			cmd[i++] = ft_strdup(tab[var->cmd_count]);
			var->cmd_count++;
		}
	}
	cmd[i] = NULL;
	var->cmd_count++;
	return (cmd);
}
