/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 00:55:40 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/06 07:46:34 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

t_env	*create_env_node(char *env_str)
{
	t_env	*node;
	int		start;

	if (!env_str)
		return (NULL);
	node = (t_env *)gc_malloc(sizeof(t_env), GLOBAL);
	if (!node)
		return (NULL);
	start = -1;
	while (env_str[++start])
		if (env_str[start] == '=')
			break ;
	node->key = ft_substr(env_str, 0, start);
	if (ft_strcmp("OLDPWD", node->key) == 0)
		node->value = NULL;
	else
		node->value = ft_substr(env_str, start + 1, ft_strlen(env_str));
	node->next = NULL;
	return (node);
}

t_env	*convert_env_to_list(char **envp)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;

	head = NULL;
	i = 0;
	while (envp[i])
	{
		new_node = create_env_node(envp[i]);
		if (!new_node)
			continue ;
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
		if (*(tmp->key) == '_')
			printf("%s=%s\n", "_", "/usr/bin/env");
		else if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

t_env	*init_env(char **envp)
{
	t_env	*envs;

	if (!envp)
		return (NULL);
	envs = convert_env_to_list(envp);
	return (envs);
}

int	is_builtin(const char *cmd)
{
	int		i;
	char	*builtins[8];

	if (!cmd)
		return (0);
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
