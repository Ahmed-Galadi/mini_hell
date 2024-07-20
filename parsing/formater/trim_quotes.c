/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:50:35 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/20 16:44:52 by agaladi          ###   ########.fr       */
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
void	trim_quotes(char **str)
{
	char *dup_str;
	int  i;
	int  j;

	dup_str = ft_strdup(*str);
	i = 0;
	j = 0;
	
	if (dup_str[i] != '\"' || (quotes_count(dup_str) % 2))
		error();
	(*str)[j++] = '\"';
	while (dup_str[i])
	{
		if (dup_str[i] != '\"')
			(*str)[j++] = dup_str[i];
		i++;
	}
	(*str)[j++] = '\"';
	(*str)[j] = '\0';
}