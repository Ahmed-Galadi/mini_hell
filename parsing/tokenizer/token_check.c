/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:42:54 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 22:17:05 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quote(char *str)
{
	return (cstm_strcmp(str, "\"") || cstm_strcmp(str, "\'"));
}

int	is_rederection(char *str)
{
	return (cstm_strcmp(str, "<<") || cstm_strcmp(str, ">>")
		|| cstm_strcmp(str, ">") || cstm_strcmp(str, "<"));
}

bool	has_quotes(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\"' || str[i] == '\'')
			return (true);
	return (false);
}

void	heredoc_type_set(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		if (current->value)
			if (current->type == HERE_DOC_EXP && has_quotes(current->value))
				current->type = HERE_DOC;
		current = current->next;
	}
}

// Format and switch characters function
char	*format_and_switch(char *input)
{
	char	*formated_input;

	formated_input = format(input);
	switch_char(&formated_input, ' ', -1);
	switch_char(&formated_input, '\t', -2);
	return (formated_input);
}
