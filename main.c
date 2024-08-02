/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/02 00:58:57 by agaladi          ###   ########.fr       */
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

int main(int argc, char *argv[], char **env)
{
	(void)argc;
	(void)argv;
	(void)env;
	char *input;
	while (1)
	{
		input = readline("\n$> ");
		add_history(input);
		if (ft_strcmp(input, "exit"))
			exit(0);
		else if (ft_strcmp(input, ""))
			write(1, "", 0);
		else
		{
			t_token *token;
			token = tokenizer(input);
			// printf("\n%d | %s\n", red_type(token), token->value);
			print_token(token);
		}
	}
	return (0);
}