/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:01:02 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/27 19:04:28 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static bool check_quote_syntax(char *input)
{
    bool single_quote_open = false;
    bool double_quote_open = false;
	int i = 0;

    while (input[i])
	{
        if (input[i] == '\'' && !double_quote_open)
            single_quote_open = !single_quote_open;
		else if (input[i] == '\"' && !single_quote_open)
            double_quote_open = !double_quote_open;
		i++;
    }
    return (!single_quote_open && !double_quote_open);
}


static int get_close_quote(char *input, int index_quote)
{
	char quote;

	quote = input[index_quote];
	index_quote++;
	while (input[index_quote])
	{
		if (input[index_quote] == quote)
			return (index_quote);
		index_quote++;
	}
	return (-1);
}

char	*handle_quotes(char *str)
{
	char	*output;
	int		i;
	int		j;
	int		cq_index;

	output = (char *)malloc(ft_strlen(str) + 1);
	if (!output || !check_quote_syntax(str))
		error();
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			cq_index = get_close_quote(str, i);
			i++;
			while (i < cq_index)
				output[j++] = str[i++];
			if (str[i] && str[i + 1])
				i++;
		}
		else 
			output[j++] = str[i];
		i++;
	}
	output[j] = '\0';
	return (output);
}