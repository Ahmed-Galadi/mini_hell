/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/03 00:49:42 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>

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
	{
		printf("empty operations!\n");
		return ;
	}
	current = opera;
	while (current)
	{
		printf("Redirection Type: %d", current->operator);
		if (current->arg)
			printf(" | File: %s", current->arg);
		printf("\n");
		current = current->next;
	}
}

int main(int argc, char *argv[], char **envp)
{
	char *cmd;
    char *args[argc];
    int i;
	t_data data;

    if (argc < 2)
    {
        printf("Usage: ./minishell \"command\"\n");
        return (1);
    }
    cmd = argv[1];
	i = 1;
	while (i < argc)
	{
        args[i - 1] = argv[i];
		i++;
	}
	data.env = init_env(envp);
    args[argc - 1] = NULL;
    if (ft_strcmp(cmd, "echo") == 0)
        return ft_echo(args);
    if (ft_strcmp(cmd, "env") == 0)
        return ft_env(data.env);
    else
        printf("Unknown command: %s\n", cmd);

    if (!init_data(&data, envp)) {
        fprintf(stderr, "Failed to initialize data\n");
        return (1);
    }
	
	return (0);
}