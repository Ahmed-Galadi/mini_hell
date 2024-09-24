/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 19:49:56 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/07 20:48:55 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <limits.h>

int custom_atoi(const char *str)
{
    long result = 0;
    int sign = 1;

    if (str == NULL || *str == '\0')
        return 0;
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
        str++;

    while (*str)
	{
		if ((result > (LLONG_MAX / 10) || 
            (result == LLONG_MAX / 10 && (*str - '0') > LLONG_MAX % 10))
			|| !(*str >= '0' && *str <= '9'))
        {
            fprintf(stderr, "exit\nexit: %s: numeric argument required\n", str);
			return (-1);
		}
        result = result * 10 + (*str - '0');
        str++;
    }

    result *= sign;
    return (result & 0xFF);
}


int	ft_exit(char **args, int exit_status)
{
	int	exit_tmp;

	args++;
	if (!(*args))
		return (printf("exit\n"), exit(exit_status), 0);
	exit_tmp = custom_atoi(*args);
	if (exit_tmp < 0)
		exit(255);
	args++;
	if (!*args)
		exit (exit_tmp);
	fprintf(stderr, "%s: exit: too many arguments\n", RED"ERROR!"RESET);
	return (1);
}
