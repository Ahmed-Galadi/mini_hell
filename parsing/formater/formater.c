/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:42:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/20 11:50:52 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	switch_char(char *str, char to_find, char character)
 {
	int		in_quote;
	int		i;

	in_quote = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\"' && !in_quote)
			in_quote = 1;
		else if (str[i] == '\"' && in_quote)
			in_quote = 0;
		if (in_quote && str[i] == to_find)
			str[i] = character;
		i++;
	}
 }



char	*format(char *str)
{
	char	*output;

	output = ft_strdup(str);
	// remove uneeded quotes
	output = trim_quotes(str, output);
	// check for pipes and change them to (char)-1
	switch_char(output, '|', -1);
	// fotmat the input by adding spaces 
	output = add_spaces(output);
	return (output);
}