/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:22:59 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/02 20:56:10 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_n_flag(char *flag)
{
	char *tmp;

	tmp = flag;
	if (*tmp == '-')
		tmp++;
	else
		return (0);
	while (*tmp)
	{
		if (*tmp == 'n')
			tmp++;
		else
			break ;
	}
	if (*tmp == '\0')
		return (1);
	return (0);
}

int ft_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (args[i])
	{
		if (args[i] && (ft_check_n_flag(args[i]) == 1))
		{
			newline = 0;
			i++;
		}
		if (ft_check_n_flag(args[i]) != 1)
			printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
