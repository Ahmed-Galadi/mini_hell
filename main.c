/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/27 19:05:01 by agaladi          ###   ########.fr       */
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
		printf("Type: %d | Value: %s\n", current->type, current->value);
		current = current->next;
	}
}



int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char *input;
	while (1)
	{
		input = readline("\n$> ");
		if (ft_strcmp(input, "exit"))
			exit(0);
		else if (ft_strcmp(input, ""))
			write(1, "", 0);
		else
		{
			t_token *token;
			token = tokenizer(input);
			print_token(token);
			printf("\n%s\n", handle_quotes(token->value));
		}
		add_history(input);
	}
	return (0);
}