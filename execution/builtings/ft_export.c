/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:28:21 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/16 20:05:47 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_export_command(t_env **my_export_env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;

	if (key == NULL)
		return (ft_get_vars(*my_export_env), 0);
	else
	{
		current = *my_export_env;
		while (current)
		{
			if (ft_strcmp(current->key, key) == 0)
				return (current->value = ft_strdup(value), 0);
			current = current->next;
		}
		new_node = gc_malloc(sizeof(t_env), GLOBAL);
		if (!new_node)
			return (perror("gc_malloc"), 1);
		new_node->key = ft_strdup(key);
		new_node->value = ft_strdup(value);
		new_node->next = *my_export_env;
		*my_export_env = new_node;
	}
	return (0);
}

static void	handle_create_operation(t_shell *data, char *key,
	char *value, char *str)
{
	key = extract_key(str);
	value = extract_value(str);
	if (!is_var_exist(str, data->export))
	{
		ft_set_vars(&data->export, key, value);
		ft_set_vars(&data->env, key, value);
	}
}

static void	handle_append_operation(t_shell *data, char *key,
	char *value, char *str)
{
	char	*prev_value;

	key = extract_key(str);
	key = ft_substr(key, 0, ft_strlen(key) - 1);
	value = extract_value(str);
	prev_value = ft_get_var_value(data->export, key);
	if (prev_value)
	{
		ft_set_vars(&data->export, key, ft_strjoin(prev_value, value,
				GLOBAL));
		ft_set_vars(&data->env, key, ft_strjoin(prev_value, value, GLOBAL));
	}
	else
	{
		ft_set_vars(&data->export, key, value);
		ft_set_vars(&data->env, key, value);
	}
}

int	export_manager(char *str, t_shell *data, char *crud_operation)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	if (!str || !crud_operation)
		return (1);
	if (!ft_strcmp(crud_operation, "Invalid"))
		return (1);
	if (ft_strcmp(crud_operation, "create") == 0)
		handle_create_operation(data, key, value, str);
	if (ft_strcmp(crud_operation, "append") == 0)
		handle_append_operation(data, key, value, str);
	return (0);
}

int	ft_export(char **args, t_shell *data)
{
	int		err;
	char	*operation;

	err = 0;
	if (!data)
		return (127);
	if (!args)
		return (1);
	if (!(*args))
		ft_get_vars(data->export);
	while (*args)
	{
		operation = get_operation(*args);
		if (!operation)
			return (1);
		if (export_manager(*args, data, operation))
			err = 1;
		args++;
	}
	if (err)
		return (1);
	return (0);
}
