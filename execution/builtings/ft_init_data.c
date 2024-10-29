/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 05:26:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/28 03:59:16 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

t_env	*create_mini_env(void)
{
	char	cwd[1024];
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
	path->key = ft_strdup("PATH");
	path->value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	path->next = pwd;
	pwd->key = ft_strdup("PWD");
	pwd->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	pwd->next = shlvl;
	shlvl->key = ft_strdup("SHLVL");
	shlvl->value = ft_strdup("1");
	shlvl->next = last_command;
	last_command->key = ft_strdup("_");
	last_command->value = ft_strdup("/usr/bin/env");
	last_command->next = NULL;
	return (path);
}

void	increment_shlvl(t_shell *data)
{
	int		shell_lvl;
	char	*shlvl;

	if (data && data->env)
	{
		shlvl = ft_get_var_value(data->env, "SHLVL");
		if (!shlvl)
			(1 && (ft_set_vars(&data->env, "SHLVL", "")),
				(ft_set_vars(&data->export, "SHLVL", "")));
		else
		{
			if (*shlvl == '\0')
				(1 && (ft_set_vars(&data->env, "SHLVL", "1")),
					(ft_set_vars(&data->export, "SHLVL", "1")));
			else if (ft_atoi(shlvl) == 999)
				(1 && (ft_set_vars(&data->env, "SHLVL", "")),
					(ft_set_vars(&data->env, "SHLVL", "")));
			else
			{
				shell_lvl = ft_atoi(shlvl) + 1;
				(1 && (ft_set_vars(&data->env, "SHLVL", ft_itoa(shell_lvl))),
					(ft_set_vars(&data->export, "SHLVL",
						ft_itoa(shell_lvl))));
			}
		}
	}
}
int	init_shell_data_config(t_shell *data, char **envp)
{
	char	cwd[1024];

	data->exit_status = 0;
	data->heredoc_count = 0;
	data->heredoc_index = 0;
	data->command = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		data->pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	else
		perror("getcwd failed");
	if ((!*envp))
		(1 && (data->env = create_mini_env()),
			(data->export = create_mini_env()));
	else
	{
		data->env = init_env(envp, "env");
		if (!data->env)
			return (1);
		data->export = init_env(envp, "export");
		if (!data->export)
			return (1);
		increment_shlvl(data);
	}
	return (1);
}
