/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:28:21 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/09 11:40:25 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <readline/readline.h>
#include <stdio.h>

void	ft_get_vars(t_env *export)
{
	t_env	*tmp;

	if (!export)
		return ;
	tmp = export;
	while (tmp)
	{
		if (!tmp->value)
			printf("declare -x %s\n", tmp->key);
		else if (tmp->key)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

int	ft_set_vars(t_env **my_export_env, const char *key, const char *value)
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

int	ft_export_command(t_env **my_export_env, const char *key, const char *value)
{
	t_env	*current;
	t_env	*new_node;

	if (key == NULL)
	{
		ft_get_vars(*my_export_env);
		return (0);
	}
	else
	{
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
	}
	return (0);
}

int	first_occurence(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_key(char *str)
{
	char	*key;

	if (!str)
		return (NULL);
	if (first_occurence(str, '=') < 0)
		return (str);
	key = ft_substr(str, 0, first_occurence(str, '='));
	if (!key)
		return (NULL);
	return (ft_substr(key, 0, first_occurence(key, '+')));
}

char	*extract_value(char *str)
{
	char	*value;

	if (first_occurence(str, '=') < 0)
		return (NULL);
	if (first_occurence(str, '=') > 0 && !str[first_occurence(str, '=') + 1])
		return ("");
	value = ft_substr(str, first_occurence(str, '=') + 1, ft_strlen(str));
	if (!value)
		return (NULL);
	return (value);
}

int	is_var_exist(char *var, t_env *export)
{
	t_env	*curr;

	curr = export;
	while (curr)
	{
		if (ft_strcmp(var, curr->key) == 0)
			return (1);
		curr = curr->next;
	}
	return (0);
}

char	*ft_get_var_value(t_env *env, const char *key)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

void	export_manager(char *str, t_shell *data, char *crud_operation)
{
	int		i;
	char	*key;
	char	*value;
	char	*prev_value;

	i = 1;
	if (!str || !crud_operation)
		return ;
	if (!ft_strcmp(crud_operation, "Invalid"))
		return ;
	if (ft_strcmp(crud_operation, "create") == 0)
	{
		key = extract_key(str);
		value = extract_value(str);
		if (!is_var_exist(str, data->export))
		{
			if (!value)
			{
				ft_set_vars(&data->export, key, value);
				ft_set_vars(&data->env, key, value);
			}
			else
			{
				ft_set_vars(&data->export, key, value);
				ft_set_vars(&data->env, key, value);
			}
		}
	}
	if (ft_strcmp(crud_operation, "append") == 0)
	{
		key = extract_key(str);
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
}

int	ft_check_key(const char *arg)
{
	int	i;

	if (!((arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z')
			|| arg[0] == '_'))
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		if (arg[i] == '+' && arg[i + 1] == '\0')
			return (0);
		if (!((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A'
					&& arg[i] <= 'Z') || (arg[i] >= '0' && arg[i] <= '9')
				|| arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*get_operation(char *arg)
{
	char	*key;

	key = extract_key(arg);
	if (key && !ft_check_key(key))
	{
		printf(BOLD RED "Error: " RESET PINK "export:" RESET " \'%s\': not a valid identifier\n",
			arg);
		return ("Invalid");
	}
	if (first_occurence(arg, '=') && arg[first_occurence(arg, '=') - 1] == '+')
	{
		return ("append");
	}
	else if (first_occurence(arg, '=') && arg[first_occurence(arg, '=')
		- 1] != '+')
	{
		return ("create");
	}
	return (NULL);
}

int	ft_export(char **args, t_shell *data)
{
	char	*operation;

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
		export_manager(*args, data, operation);
		args++;
	}
	return (0);
}
