/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 20:22:59 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/16 13:28:58 by bzinedda         ###   ########.fr       */
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

int	ft_check_quotes(const char *arg)
{
	if (*arg == '\"' && *(arg + (ft_strlen(arg) - 1)) == '\"')
		return (1);
	return (0);
}
int	count_quotes(char *str)
{
	int	count;
	int	i;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			count++;
		i++;
	}
	return (count);
}

char	*ft_rm_quotes(const char *arg)
{
	char	*without_qtes;
	char	*head;

	if (!arg)
		return (NULL);
	without_qtes = malloc(ft_strlen(arg) + 1);
	if (!without_qtes)
		return (NULL);
	head = without_qtes;
	while (*arg)
	{
		if (*arg == '\"')
			arg++;
		else
		{
			*without_qtes = *arg;
			without_qtes++;
			arg++;	
		}
	}
	*without_qtes = '\0';
	return (head);
}

int ft_echo(char **args, int *ret_val)
{
	int		i;
	int		newline;

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

		if (ft_strcmp("$?", args[i]) == 0)
		{
			//*ret_val = 0;
			printf("%d", *ret_val);
		}
		else
		{	if (count_quotes(args[i]) == 0)
				printf("%s",  args[i]);	
			else if ((count_quotes(args[i]) % 2) == 0)
				printf("%s", ft_rm_quotes(args[i]));
			else
				while (1)
 					readline("> ");
		}
		if (args[i + 1])
			printf(" ");
		i++;
	}
	if (newline)
		printf("\n");
	return (*ret_val);
}
