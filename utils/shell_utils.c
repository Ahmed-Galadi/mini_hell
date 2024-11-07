/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:43:28 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/01 11:19:32 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token(t_token *token)
{
	t_token	*current;

	if (!token)
	{
		printf("empty token!\n");
		return ;
	}
	current = token;
	while (current)
	{
		printf("Type: %d", current->type);
		if (current->value)
			printf("| Value: %s", current->value);
		printf("\n****************************\n");
		current = current->next;
	}
}

void	print_opp(t_opp *opera)
{
	t_opp	*current;

	if (!opera)
		printf("\tempty operations!\n");
	else
	{
		current = opera;
		while (current)
		{
			printf("\tRedirection Type: %d", current->operator);
			if (current->arg)
				printf("\t | File: %s", current->arg);
			printf("\n\t--------------------------\n");
			current = current->next;
		}
	}
}

void	print_command(t_com *command)
{
	t_com	*current;
	int		i;

	if (!command)
	{
		printf("No Command!\n");
		return ;
	}
	current = command;
	while (current)
	{
		i = 0;
		printf("args:");
		while ((current->command)[i])
			printf(" %s", (current->command)[i++]);
		printf("\n");
		print_opp(current->operator);
		current = current->next;
	}
}

void	ft_set_mini_env_config(t_env **path, t_env **pwd,
		t_env **shlvl, t_env **last_command)
{
	char	cwd[1024];

	if (!path || !pwd || !shlvl || !last_command)
		return ;
	(*path)->key = ft_strdup("PATH");
	(*path)->value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	(*path)->next = *pwd;
	(*pwd)->key = ft_strdup("PWD");
	(*pwd)->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	(*pwd)->next = *shlvl;
	(*shlvl)->key = ft_strdup("SHLVL");
	(*shlvl)->value = ft_strdup("1");
	(*shlvl)->next = *last_command;
	(*last_command)->key = ft_strdup("_");
	(*last_command)->value = ft_strdup("/usr/bin/env");
	(*last_command)->next = NULL;
}

t_env	*create_mini_env(void)
{
	t_env	*path;
	t_env	*pwd;
	t_env	*shlvl;
	t_env	*last_command;

	path = gc_malloc(sizeof(t_env), GLOBAL);
	if (!path)
		return (NULL);
	pwd = gc_malloc(sizeof(t_env), GLOBAL);
	if (!pwd)
		return (NULL);
	shlvl = gc_malloc(sizeof(t_env), GLOBAL);
	if (!shlvl)
		return (NULL);
	last_command = gc_malloc(sizeof(t_env), GLOBAL);
	if (!last_command)
		return (NULL);
	ft_set_mini_env_config(&path, &pwd, &shlvl, &last_command);
	return (path);
}
