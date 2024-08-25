/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 20:50:40 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/25 22:50:41 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int ft_execute_command(char **args, int *return_value, t_data *data)
{
    int builtin_status;

    if (*args == NULL)
        return (1);
    builtin_status = ft_execute_builtin(args, return_value, data);
    if (builtin_status != -1)
    {
        //printf("execute builtin called\n");
        return (builtin_status);
    }
    else
    {
        //printf("execute external called\n");
        return (ft_execute_external(args, return_value, data));
    }
}