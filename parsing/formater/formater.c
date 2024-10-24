/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:42:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/28 20:39:34 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*void	switch_char(char **str, char to_find, char character)*/
/*{*/
/*	int		in_quote;*/
/*	int		i;*/
/**/
/*	in_quote = 0;*/
/*	i = 0;*/
/*	while ((*str)[i])*/
/*	{*/
/*		if ((*str)[i] == '\"' && !in_quote)*/
/*			in_quote = !in_quote;*/
/*		else if ((*str)[i] == '\"' && in_quote)*/
/*			in_quote = !in_quote;*/
/*		if (in_quote && (*str)[i] == to_find)*/
/*			(*str)[i] = character;*/
/*		i++;*/
/*	}*/
/*}*/

void	switch_char(char **str, char to_find, char character)
{
	bool	in_s_quote;
	bool	in_d_quote;
	int		i;

	in_d_quote = false;
	in_s_quote = false;
	i = 0;
	while ((*str)[i])
	{
		handle_quotes_state((*str)[i], &in_s_quote, &in_d_quote);
		if ((*str)[i] == to_find && (in_s_quote || in_d_quote))
			(*str)[i] = character;
		i++;
	}
}

char	*format(char *str)
{
	char	*formated_input;

	formated_input = ft_strdup(str);
	switch_char(&formated_input, '|', -1);
	formated_input = add_spaces(formated_input);
	switch_char(&formated_input, -1, '|');
	return (formated_input);
}
