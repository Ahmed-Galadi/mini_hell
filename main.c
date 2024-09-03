/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/03 15:17:33 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int main(int argc, char *argv[], char **envp)
{
	char	*cmd_line_args;
   	char	**args;
	t_data	data;
	int		return_value;

	(void)argv;
	(void)argc;
    if (!init_data(&data, envp))
	{
        fprintf(stderr, "Failed to initialize data\n");
        return (1);
    }
	while (1)
	{
		cmd_line_args = readline(BASH_PROMPT_NAME);
		if (!cmd_line_args)
			break ;
		add_history(cmd_line_args);
		args = ft_split(cmd_line_args, ' ');
		t_token *token = tokenizer(cmd_line_args);
		t_com	*com = create_cmds(token);
		// printf("***** start ******\n");
		// print_command(com);
		// printf("***** end ******\n");
		if (com->command)
			ft_execute_command(args, &return_value, &data);
	}
	return (0);
}

// int main(int argc, char *argv[], char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// 	char *input;
// 	while (1)
// 	{
// 		input = readline("\n$> ");
// 		if (!input)
// 			break ;
// 		add_history(input);
// 		if (cstm_strcmp(input, "exit"))
// 			exit(0);
// 		else if (cstm_strcmp(input, ""))
// 			write(1, "", 0);
// 		else
// 		{
// 			t_token *token = tokenizer(input);
// 			t_com	*com = create_cmds(token);
// 			print_command(com);
// 		}
// 	}
// 	return (0);
// }