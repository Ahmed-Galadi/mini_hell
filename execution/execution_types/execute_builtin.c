/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:48:47 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/04 17:35:45 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_execute_builtin(char **args, int *return_value, t_data *data, t_com *command)
{
	 (void)command;
	if (ft_strcmp(args[0], "echo") == 0)
		ft_echo(&args[1], return_value);
	else if (ft_strcmp(args[0], "env") == 0)
		ft_env(data->env);
	else if (ft_strcmp(args[0], "export") == 0)
		ft_export(&args[1], data);
	else if (ft_strcmp(args[0], "pwd") == 0)
		ft_pwd(data);
	else if (ft_strcmp(args[0], "cd") == 0)
		ft_cd(args, data, return_value);
	else if (ft_strcmp(args[0], "unset") == 0)
		ft_unset(args, data, return_value);
	else if (ft_strcmp(args[0], "exit") == 0)
		ft_exit(args, return_value);
	else
	{
		// Not a builtin command
		*return_value = -1;
	}
   		return (*return_value);
}