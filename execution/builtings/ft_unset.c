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


void	unset_var(t_env **env, char *var_to_unset, int *ret_var)
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
		*ret_var = 0;
		return;
	}

	while (curr_env)
	{
		if (curr_env->next && (ft_strcmp(var_to_unset, curr_env->next->key) == 0))
		{
			node_to_delete = curr_env->next;
			curr_env->next = node_to_delete->next;
			free(node_to_delete->key);
			free(node_to_delete->value);
			free(node_to_delete);
			*ret_var = 0;
			return;
		}
		curr_env = curr_env->next;
	}
	*ret_var = 1;
}

int		ft_unset(char **args, t_shell *data, int *ret_val)
{
	char	**tmp_var;

	tmp_var = args;
	if (!(*args) || !(data->export))
		*ret_val = 1;
	while (*tmp_var)
	{
		unset_var(&data->export, *tmp_var, ret_val);
		unset_var(&data->env, *tmp_var, ret_val);
		tmp_var++;
	}
	*ret_val = 0;
	return (*ret_val);
}

