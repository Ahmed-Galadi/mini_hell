/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:42:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/20 18:59:34 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	switch_char(char **str, char to_find, char character)
 {
	int		in_quote;
	int		i;

	in_quote = 0;
	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\"' && !in_quote)
			in_quote = 1;
		else if ((*str)[i] == '\"' && in_quote)
			in_quote = 0;
		if (in_quote && (*str)[i] == to_find)
			(*str)[i] = character;
		i++;
	}
 }

int		has_char(char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

void	quotes_handling(char **str)
{
	char	**splited_str;
	int		i;
	
	switch_char(str, ' ', -1);
	splited_str = ft_split(*str, ' ');
	i = 0;
	while (splited_str[i])
	{
		if (has_char(splited_str[i], '\"'))
			trim_quotes(&splited_str[i]);
		i++;
	}
	i = 0;
	*(str) = ft_strjoin(splited_str);
}

char	**format(char *str)
{
	char	*formated_input;
	char	**output;
	int		i;

	formated_input = ft_strdup(str);
	switch_char(&formated_input, '|', -1);
	formated_input = add_spaces(formated_input);
	output = ft_split(formated_input, '|');
	i = 0;
	while (output[i])
	{
		switch_char(&output[i], -1, '|');
		if (has_char(output[i], '\"'))
			quotes_handling(&output[i]);
		i++;
	}
	return (output);
}