/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:17:26 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/16 14:27:03 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	unset_var(t_env **env, char *var_to_unset)
{
	t_env	*curr_env;
	t_env	*node_to_delete;

	curr_env = *env;
	if (curr_env && (ft_strcmp(var_to_unset, curr_env->key) == 0))
	{
		*env = curr_env->next;
		free(curr_env->key);
		free(curr_env->value);
		free(curr_env);
		return (0);
	}
	while (curr_env)
	{
		if (curr_env->next && (ft_strcmp(var_to_unset,
					curr_env->next->key) == 0))
		{
			node_to_delete = curr_env->next;
			curr_env->next = node_to_delete->next;
			free(node_to_delete->key);
			free(node_to_delete->value);
			free(node_to_delete);
			return (0);
		}
		curr_env = curr_env->next;
	}
	return (1);
}

int	ft_unset(char **args, t_shell *data)
{
	char	**tmp_var;

	tmp_var = args;
	if (!(*args) || !(data->export))
		return (1);
	while (*tmp_var)
	{
		unset_var(&data->export, *tmp_var);
		unset_var(&data->env, *tmp_var);
		tmp_var++;
	}
	return (0);
}
