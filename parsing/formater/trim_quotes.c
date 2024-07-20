/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:50:35 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/10 06:57:34 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

static int		quotes_count(char *str)
{
	int		count;
	int		i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"')
			count++;
		i++;
	}
	return (count);

}

static void	skip_quotes(char *str ,int *i)
{
	while (str[*i] == '\"')
		*i += 1;
}

char	*trim_quotes(char *str)
{
	char	*output;
	int		i;
	int		j;

	if ((quotes_count(str) % 2) != 0)
		error();
	output = malloc(ft_strlen(str) + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\"')
		{
			output[j] = '\"';
			skip_quotes(str, &i);
			j++;
		}
		else
			output[j++] = str[i++];
	}
	output[j] = '\0';
	return (output);
}
