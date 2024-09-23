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

int custom_atoi(const char *str, int *valid)
{
    long int result = 0;
    int sign = 1;
    *valid = 1;  // Assume valid until proven otherwise

    // Check for empty string
    if (str == NULL || *str == '\0')
    {
        *valid = 0;
        return 0;
    }
    // Check for optional sign
    if (*str == '-')
    {
        sign = -1;
        str++;
    }
    else if (*str == '+')
        str++;

    // Convert characters to integer
    while (*str) {
        if (!(*str >= '0' && *str <= '9'))
        {
            *valid = 0;
            fprintf(stderr, "exit: %s: numeric argument required\n", str);
            return 0;
        }
        result = result * 10 + (*str - '0');
        str++;
    }

    result *= sign;

    // Check for overflow
    if (result < INT_MIN || result > INT_MAX)
    {
        *valid = 0;
        fprintf(stderr, "Error: Argument out of range\n");
        return 0;
    }
    return ((int)result);
}


void	ft_exit(char **args, int *ret_val)
{
    // skip exit arg
    args++;
    // there is no arg
    if (!(*args))
    {
        *ret_val = 0;
        exit(*ret_val);
    }
    else
    {
        args++;
        if (*args) 
        {
            fprintf(stderr, "%s: exit: too many arguments\n", RED"ERROR!"RESET);
            *ret_val = 1;
        }
        else
        {
            args--;
            exit (custom_atoi(*args, ret_val));
        }
    }
}
