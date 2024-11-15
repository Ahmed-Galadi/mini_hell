/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formater.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:42:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/14 22:57:10 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
