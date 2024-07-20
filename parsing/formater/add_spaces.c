/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:52:32 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/11 02:39:01 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*add_spaces(char *str)
{
	char	*output;
	int		i;
	int		j;

	output = malloc(ft_strlen(str) * 2 + 1);
	(1 && (i = 0, j = 0));
	while (str[i])
	{
		if ((str[i] == '>' && str[i + 1] =='>')
			|| (str[i] == '<' && str[i + 1] =='<'))
		{
			output[j++] = ' ';
			output[j++] = str[i++];
			output[j++] = str[i++];
			output[j++] = ' ';
		}
		if (((!is_op(str[i]) && is_op(str[i] + 1)))
			|| (is_op(str[i]) && !is_op(str[i + 1])))
		{
			output[j++] = ' ';
			output[j++] = str[i++];
			output[j++] = ' ';
		}
		else
			output[j++] = str[i++];
	}
	output[j] = '\0';
	free(str);
	return (output);
}
