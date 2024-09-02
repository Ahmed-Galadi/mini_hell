/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/02 19:02:58 by bzinedda         ###   ########.fr       */
=======
/*   Updated: 2024/08/02 04:44:34 by agaladi          ###   ########.fr       */
>>>>>>> 9cefbccd785f0aaca6bd182350f3cd896b39d52a
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int main(int argc, char *argv[], char **envp)
{
	// char	*cmd_line_args;
    // char	**args;
	// t_data	data;
	// int		return_value;

<<<<<<< HEAD
	// (void)argv;
	// (void)argc;
    // if (!init_data(&data, envp))
	// {
    //     fprintf(stderr, "Failed to initialize data\n");
    //     return (1);
    // }
	// while (1)
	// {
	// 	cmd_line_args = readline(BASH_PROMPT_NAME);
	// 	if (!cmd_line_args)
	// 		return (0);
	// 	add_history(cmd_line_args);
	// 	args = ft_split(cmd_line_args, ' ');
	// 	ft_execute_command(args, &return_value, &data);
	// }
=======
	if (!opera)
	{
		printf("empty operations!\n");
		return ;
	}
	current = opera;
	printf("\n/////////////////////////////\n");
	while (current)
	{
		printf("Redirection Type: %d", current->operator);
		if (current->arg)
			printf(" | File: %s", current->arg);
		printf("\n--------------------------\n");
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
			t_opp	*opp = new_op(&token);
			print_opp(opp);
			print_token(token);
		}
	}
>>>>>>> 9cefbccd785f0aaca6bd182350f3cd896b39d52a
	return (0);
}