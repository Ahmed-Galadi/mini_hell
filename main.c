/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/25 22:46:02 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>


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
			return (0);
		add_history(cmd_line_args);
		args = ft_split(cmd_line_args, ' ');
		// remember to change envp with actual environment (t_env *env)
		return (ft_execute_command(args, &return_value, &data));
	}
	return (0);
}