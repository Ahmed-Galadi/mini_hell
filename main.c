/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/05 15:43:51 by bzinedda         ###   ########.fr       */
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
	char *cmd_line_args;
    char **args;
	t_data data;

	(void)argv;
	(void)argc;
    if (!init_data(&data, envp))
	{
        fprintf(stderr, "Failed to initialize data\n");
        return (1);
    }
	while (1)
	{
		cmd_line_args = readline("$> ");
		if (!cmd_line_args || !ft_strcmp(cmd_line_args, "exit"))
			return (0);
		add_history(cmd_line_args);
		args = ft_split(cmd_line_args, ' ');
    	if (ft_strcmp(args[0], "echo") == 0)
        	ft_echo(&args[1]);
		else if (ft_strcmp(args[0], "env") == 0)
			ft_env(data.env);
		else if (ft_strcmp(args[0], "export") == 0)
			ft_export(&args[1], &data);
		else if (ft_strcmp(args[0], "pwd") == 0)
			ft_pwd(&data);
		else
			printf("Unknown command: %s\n", args[0]);	
	}
	return (0);
}