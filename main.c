/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/26 22:00:26 by agaladi          ###   ########.fr       */
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

bool check_quote_syntax(char *input)
{
    bool single_quote_open = false;
    bool double_quote_open = false;
	int i = 0;

    while (input[i])
	{
        if (input[i] == '\'' && !double_quote_open)
            single_quote_open = !single_quote_open;
		else if (input[i] == '\"' && !single_quote_open)
            double_quote_open = !double_quote_open;
		i++;
    }
    return (!single_quote_open && !double_quote_open);
}


int get_close_quote(char *input, char quote)
{
	
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
			printf("\n%d\n", check_quote_syntax(token->value));
		}
		add_history(input);
	}
	return (0);
}