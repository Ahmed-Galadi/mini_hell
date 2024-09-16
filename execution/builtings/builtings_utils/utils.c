/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 05:30:19 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/16 14:58:32 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

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

int	is_builtin(const char *cmd)
{
	int		i;
	char	*builtins[8];

	if(!cmd)
		return (-1);
	builtins[0] = "echo";
	builtins[1] = "cd";
	builtins[2] = "pwd";
	builtins[3] = "env";
	builtins[4] = "export";
	builtins[5] = "unset";
	builtins[6] = "exit";
	builtins[7] = NULL;

	i = -1;
	while (++i < 8)
		if (ft_strcmp((const char *)builtins[i], cmd) == 0)
			return (1);
	return (0);
}