/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/01 23:38:52 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

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

int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char *input;
	while (1)
	{
		input = readline("\n$> ");
		if (!input)
			break ;
		add_history(input);
		if (ft_strcmp(input, "exit"))
			exit(0);
		else if (ft_strcmp(input, ""))
			write(1, "", 0);
		else
		{
			t_token *token = tokenizer(input);
			t_com	*com = create_cmds(token);
			print_command(com);
		}
	}
	return (0);
}