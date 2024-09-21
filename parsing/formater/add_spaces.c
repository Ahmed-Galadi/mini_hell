/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:52:32 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 22:17:05 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_op(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

char	*add_spaces(char *str)
{
	char	*output;
	bool	open_d_quote;
	bool	open_s_quote;
	int		i;
	int		j;

	output = malloc(ft_strlen(str) * 2 + 1);
	open_d_quote = false;
	open_s_quote = false;
	(1 && (i = 0, j = 0));
	while (str[i])
	{
		if (str[i] == '\'')
			open_s_quote = !open_s_quote;
		if (str[i] == '\"')
			open_d_quote = !open_d_quote;
		if (((str[i] == '>' && str[i + 1] =='>')
			|| (str[i] == '<' && str[i + 1] =='<')) && (!open_d_quote && !open_s_quote))
		{
			output[j++] = ' ';
			output[j++] = str[i++];
			output[j++] = str[i++];
			output[j++] = ' ';
		}
		else if ((((!is_op(str[i]) && is_op(str[i + 1])))
			|| (is_op(str[i]) && !is_op(str[i + 1]))
			|| (is_op(str[i]) && is_op(str[i + 1]))) && (!open_d_quote && !open_s_quote))
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
