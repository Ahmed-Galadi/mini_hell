/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:49:02 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/16 14:27:03 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	ft_set_var(t_env **my_export_env, const char *key, const char *value)
{

    t_env	*current;

	current = *my_export_env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
    }
	// If the variable does not exist, add it
	t_env *new_node = malloc(sizeof(t_env));
	if (!new_node)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *my_export_env;
	*my_export_env = new_node;
	return (0);
}

char	*ft_get_env_var(t_env *env, const char *var_key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, var_key, ft_strlen(var_key) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	change_directory(const char *path, t_shell *data)
{
    char cwd[1024];
	ft_set_var(&data->env, "OLDPWD", data->pwd);
	ft_set_var(&data->export, "OLDPWD", data->pwd);
    if (chdir(path) != 0)
	{
        printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		data->pwd = ft_strdup(cwd);
		if (data->pwd)
		{
			ft_set_var(&data->env, "PWD", data->pwd);
			ft_set_var(&data->export, "PWD", data->pwd);
			return (0);
		}
	}
	return (1);
}
	
int		ft_cd(char **args, t_shell *data)
{
	char	*home;
	args++;

	if (!(*args))
	{
		home = ft_get_env_var(data->env, "HOME");
		if (!home)
			return (printf("Error: cd: HOME not set\n"), 1);
		change_directory(home, data);
		return (0);
	}
	return (change_directory(args[0], data));
}
