/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:46:44 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 22:08:20 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

// Check if a char is "|" or "<" or ">"  
int	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	cstm_strcmp(char *str1, char *str2)
{
	int		i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}
