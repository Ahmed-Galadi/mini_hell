/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 05:26:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/18 18:16:07 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_token(t_token *token)
{
	t_token *current;

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

void print_opp(t_opp *opera)
{
	t_opp *current;

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
	
	if (!command)
	{
		printf("No Command!\n");
		return ;
	}
	current = command;
	while(current)
	{
		int i = 0;
		printf("args:");
		while ((current->command)[i])
			printf(" %s", (current->command)[i++]);
		printf("\n");
		print_opp(current->operator);
		current = current->next;
	}
}

int init_shell_data_config(t_shell *data, char **envp)
{
	char	cwd[1024];

	if (!data || !envp)
		return (0);
	// Initilize command struct
	data->command = NULL;
	// Initialize environment variable linked list
	data->env = init_env(envp);
	if (!data->env)
		return (0);
	// Initialize current working directory
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		data->pwd = ft_strdup(getcwd(cwd, sizeof(cwd))); 
	else
        perror("getcwd failed");
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
