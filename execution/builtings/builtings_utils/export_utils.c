/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:45:04 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/03 22:16:40 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

void	ft_get_vars(t_env *exp)
{
	t_env	*tmp;

	if (!exp)
		return ;
	tmp = exp;
	while (tmp)
	{
		if (!tmp->value && ft_strcmp(tmp->key, "_"))
			printf("declare -x %s\n", tmp->key);
		else if (tmp->key && ft_strcmp(tmp->key, "_"))
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
			current->value = ft_strdup(value);
			return (0);
		}
		current = current->next;
	}
	new_node = gc_malloc(sizeof(t_env), GLOBAL);
	if (!new_node)
		return (perror("gc_malloc"), 1);
	new_node->key = ft_strdup(key);
	new_node->value = ft_strdup(value);
	new_node->next = *my_export_env;
	*my_export_env = new_node;
	return (0);
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
	return (key);
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

int	is_var_exist(char *var, t_env *expo)
{
	t_env	*curr;

	curr = expo;
	while (curr)
	{
		if (ft_strcmp(var, curr->key) == 0)
			return (1);
		curr = curr->next;
	}
	return (0);
}
