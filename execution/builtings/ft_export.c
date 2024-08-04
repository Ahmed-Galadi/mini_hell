/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 04:28:21 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/04 07:52:41 by bzinedda         ###   ########.fr       */
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
			printf("%s\n", tmp->key);
		else if (tmp->key)
			printf("%s=%s\n", tmp->key, tmp->value);
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

int		ft_export(char **args, t_data *data)
{
	char	*env_key;
	char	*env_value;
	if (!data)
		return (127);

	env_key = args[0];
	env_value = args[1];
	if (env_key)
		ft_export_command(&data->export, env_key, env_value);
	else
		export_print(data->export);	
	return (0);
}