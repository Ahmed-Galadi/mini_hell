/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:17:26 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/05 05:47:06 by agaladi          ###   ########.fr       */
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
		return (0);
	}
	while (curr_env)
	{
		if (curr_env->next && (ft_strcmp(var_to_unset,
					curr_env->next->key) == 0))
		{
			node_to_delete = curr_env->next;
			curr_env->next = node_to_delete->next;
			return (0);
		}
		curr_env = curr_env->next;
	}
	return (1);
}

int	ft_unset(char **args, t_shell *data)
{
	char	**tmp_var;
	int		err;

	(1 && (err = 0), (tmp_var = args));
	if (!(data->export))
		return (1);
	if (!(*args))
		return (0);
	while (*tmp_var)
	{
		if (ft_check_key(*tmp_var, NULL) == 1)
		{
			unset_var(&data->export, *tmp_var);
			unset_var(&data->env, *tmp_var);
		}
		else
		{
			err = 1;
			ft_printf(2, "Error: " "export:"\
				" \'%s\': not a valid identifier\n",
				*tmp_var);
		}
		tmp_var++;
	}
	return (err);
}
