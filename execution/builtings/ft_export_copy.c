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


void	export_print(t_env *export)
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

int	ft_export_command(t_env **my_export_env, const char *key, const char *value)
{
    t_env	*current;

	if (key == NULL)
	{
		export_print(*my_export_env);
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

int	is_valid(char *str, int *join_string);
/*
	- First character is either alpha or '_'
	- Rest is alpha or numeric or '_'
	- Join_string is valid only if "export key+=new_value"
*/
/*
void	add_to_export(char *str, t_shell *data);
		env_key = ft_substr(*args, 0, first_occurence(*args, '='));
		env_value = ft_substr(*args, first_occurence(*args, '=') + 1, ft_strlen(*args));
*/

int		ft_export(char **args, t_shell *data)
{
	char	*env_key;
	char	*env_value;
	int		join_string; // export a+=dsa

	join_string = 0;
	if (!data)
		return (127);
	if (!args || !(*args))
		return (export_print(data->export), 0);
	while (*args)
	{
		if (!is_valid(*args, &join_string))
		{
			print_error_export(*args);
			args++;
			continue;
		}
		else if (!ft_strchr(*args, '='))
			empty_value(*args, data);
		else
			add_to_export(*args, data);
		args++;
	}
	if (env_key)
		ft_export_command(&data->export, env_key, env_value);
		ft_export_command(&data->env, env_key, env_value);
	return (0);
}