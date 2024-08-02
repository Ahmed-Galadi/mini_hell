/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:27:24 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/03 00:56:46 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
//#include <string.h>

t_env   *create_env_node(char *env_str) 
{
	t_env   *node;

	node = (t_env *)malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	int start = -1;
	while (env_str[++start])
		if (env_str[start] == '=')
			break ;
	node->key = ft_substr(env_str, 0, start);
	node->value = ft_substr(env_str, start + 1, ft_strlen(env_str));
	node->next = NULL;
	return (node);
}

t_env   *convert_env_to_list(char **envp)
{
	t_env *head = NULL;
	t_env *current;
	t_env *new_node;
	int i;

	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
			continue;
		if (!head)
		{
			head = new_node;
			current = head;
		}
		else
		{
			current->next = new_node;
			current = new_node;
		}
		i++;
	} 
	return (head);
}

int init_data(t_data *data, char **envp)
{
    if (!data || !envp)
        return (0);

    // Initialize environment variable linked list
    data->env = convert_env_to_list(envp);
    if (!data->env)
        return (0);

    // Initialize current working directory
    data->cwd = getcwd(NULL, 0);
    if (!data->cwd)
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
    return (1);
}
void	ft_printf_envs(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
t_env *init_env(char **env)
{
	t_env	*envs;
	
	if (!env)
		return (NULL);
	envs = convert_env_to_list(env);
	return (envs);
}
// NOTE 
// export
// var=value, if value is null do not print in env. do not update value.
// var+=value, joins value with the previous one.
// value. alpha num only and '_' and in one case (var+=value).

int ft_env(t_env *env)
{
	ft_printf_envs(env);
	return (0);
}