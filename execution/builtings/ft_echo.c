/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:22:59 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/16 00:15:30 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_check_n_flag(char *flag)
{
	char	*tmp;

	if (!flag)
		return (0);
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

int	ft_echo(char **args)
{
	int	i;
	int	newline;

	(1 && (i = 0), (newline = 1));
	while (args[i])
	{
		if ((ft_check_n_flag(args[i]) == 1))
		{
			newline = 0;
			i++;
		}
		else
			break ;
	}
	while (args[i])
	{
		ft_printf(1, "%s", args[i]);
		if (args[i + 1])
			ft_printf(1, " ");
		i++;
	}
	if (newline)
		ft_printf(1, "\n");
	return (0);
}
