/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 05:26:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/04 06:38:39 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int init_data(t_data *data, char **envp)
{
    if (!data || !envp)
        return (0);

    // Initialize environment variable linked list
    data->env = init_env(envp);
    if (!data->env)
        return (0);

    // Initialize current working directory
    data->pwd = getcwd(NULL, 0);
    if (!data->pwd)
	{
        // Free allocated resources in case of failure
        t_env *tmp;
        while (data->env) {
            tmp = data->env;
            data->env = data->env->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
        return (0);
    }

	data->export = convert_env_to_list(envp);
    if (!data->export)
        return (0);

    return (1);
}
