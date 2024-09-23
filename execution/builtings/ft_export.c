/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:28:21 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/21 16:00:25 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


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

int	ft_export_command(t_env **my_export_env, const char *key, const char *value)
{
    t_env	*current;

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
                free(current->value);
                current->value = ft_strdup(value);
                return (0);
            }
            current = current->next;
        }

        // If the variable does not exist, add it
        t_env *new_node = malloc(sizeof(t_env));
        if (!new_node) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
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
	key = ft_substr(str, 0, first_occurence(str, '='));
	if (!key)
		return (NULL);
	
	return (ft_substr(key, 0, first_occurence(key, '+')));
}

char	*extract_value(char *str)
{
	char	*value;

	if (!str)
			return (NULL);
	value = ft_substr(str, first_occurence(str, '=') + 1, ft_strlen(str));
	if (!value)
		return (NULL);
	if (ft_strcmp(value, str) == 0)
		return ("");
	return (value);
}

int	is_var_exist(char *var, t_env *export)
{
	t_env *curr;

	curr = export;
	while (curr)
	{
		if (ft_strcmp(var, curr->key) == 0)
			return (1);
		curr = curr->next;
	}
	return 0;
}

char	*ft_get_var_value(t_env *env ,const char *key)
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

void	export_manager(t_shell *data, char *crud_operation)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	if (ft_strcmp(crud_operation, "getAll") == 0)
		ft_get_vars(data->export);
	if (ft_strcmp(crud_operation, "create") == 0)
	{
		while (data->command->command[i])
		{
			key = extract_key(data->command->command[i]);
			value = extract_value(data->command->command[i]);
			if (!is_var_exist(data->command->command[i], data->export))
			{
				ft_set_vars(&data->export, key, value);
				ft_set_vars(&data->env, key, value);
			}	
			i++;
		}
	}
	if (ft_strcmp(crud_operation, "append") == 0)
	{
		char	*prev_value;
		while (data->command->command[i])
		{
			key = extract_key(data->command->command[i]);
			value = extract_value(data->command->command[i]);
			prev_value = ft_get_var_value(data->export ,key);
			if (*value)
			{

				ft_set_vars(&data->export, key, ft_strjoin(prev_value, value));
				ft_set_vars(&data->env, key, ft_strjoin(prev_value, value));
			}	
			i++;
		}
	}
}

char	*get_operation(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		if (first_occurence(args[i], '=') && args[i][first_occurence(args[i], '=') - 1] == '+')
			return ("append");
		else if (first_occurence(args[i], '=') && args[i][first_occurence(args[i], '=') - 1] != '+')
			return ("create");
		i++;
	}
	return (NULL);
}

int	ft_check_arg(char *arg)
{
	int	i;

	if (!((arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z')
			|| arg[0] == '_'))
			return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			i = i + 2;
		if (arg[i] == '=' && arg[i + 1] == '\0')
			return (1);
		if (arg[i] == '=')
			i++;
		if (!((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A' && arg[i] <= 'Z')
			|| (arg[i] >= '0' && arg[i] <= '9') 
			|| arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}


int	parse_command(char **args)
{
	int		i;
	char	*key;
	char	*value;

	i = 0;
	while (args[i])
	{
		if (!ft_check_arg(args[i]))
		{
			printf("parse syntaxe error\n");
			return (0);
		}
		key = extract_key(args[i]);
		value = extract_value(args[i]);
		i++;
	}
	return (1);
}

int		ft_export(char **args, t_shell *data)
{
 	char	*operation;

	if (!data)
		return (127);
	if (!args)
		return (1);
	if (!(*args))
		export_manager(data, "getAll");
	operation = get_operation(args);
	if (!operation)
		return (1);
	if (parse_command(args))
		export_manager(data, operation);
	return (0);
}

