/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:49:02 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/07 18:41:56 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_set_var(t_env **my_export_env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;

	current = *my_export_env;
	while (current)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			// free(current->value);
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	// If the variable does not exist, add it
	new_node = gc_malloc(sizeof(t_env), GLOBAL);
	if (!new_node)
		return (perror("gc_malloc"), 1);
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
	char	cwd[1024];
		char *oldpwd_with_2_points;

	if (!path)
		return (1);
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
	else
	{
		printf("cd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		oldpwd_with_2_points = ft_strjoin(ft_get_env_var(data->env, "OLDPWD"),
				"/..", GLOBAL);
		data->pwd = oldpwd_with_2_points;
	}
	return (1);
}

int	ft_cd(char **args, t_shell *data)
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
	// else if (!ft_strcmp(*args, "-"))
	// 	return (change_directory(ft_get_env_var(data->env, "OLDPWD"), data));
	return (change_directory(args[0], data));
}
