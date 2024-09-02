/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 20:17:26 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/27 14:52:27 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	unset_var(t_env **env, char *var_to_unset, int *ret_var)
{
	t_env	*curr_env;
	t_env	*head_env;

	curr_env = *env;
	head_env = curr_env;
	if (curr_env && (ft_strcmp(var_to_unset, curr_env->key) == 0))
	{
		*env = curr_env->next;
		*ret_var = 0;
		return ;
	}

	while (curr_env->next)
	{

		if ((ft_strcmp(var_to_unset, curr_env->key) == 0))
		{
				curr_env = curr_env->next;	
		}
		curr_env = curr_env->next;
	}
	*env = head_env;
}

int		ft_unset(char **args, t_data *data, int *ret_val)
{
	char	*var_to_unset;

	args++;
	var_to_unset = *args;
	if (!(*args) || !(data->export))
		*ret_val = 1;
	unset_var(&data->export, var_to_unset, ret_val);
	unset_var(&data->env, var_to_unset, ret_val);
	*ret_val = 0;
	return (*ret_val);
}