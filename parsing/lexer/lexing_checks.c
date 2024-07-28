/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:28 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/28 02:14:12 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void	trim_quotes(t_token **token)
{
	t_token	*current;
	char	*ptr_holder;
	
	current = *token;
	while (current)
	{
		if ((current->value)[0] == '\"')
		{
			if (!is_red(current->type))
				current->type = D_QUOTE;
			switch_char(&(current->value), -1, ' ');
			ptr_holder = current->value;
			current->value = handle_quotes(ptr_holder);
			free(ptr_holder);
		}
		else if ((current->value)[0] == '\'')
		{
			if (!is_red(current->type))
				current->type = D_QUOTE;
			switch_char(&(current->value), -1, ' ');
			ptr_holder = current->value;
			current->value = handle_quotes(ptr_holder);
			free(ptr_holder);
		}
		else
		{
			switch_char(&(current->value), -1, ' ');
			ptr_holder = current->value;
			current->value = handle_quotes(ptr_holder);
			free(ptr_holder);
		}
		current = current->next;
	}
}

int	check_pipes(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->type == PIPE || last_token(token)->type == PIPE)
		return (0);
	while(current)
	{
		if (current->type == PIPE && current->next->type == PIPE)
			return (0);
		current = current->next;
	}
	return (1);
}

int	is_red(e_tokenType type)
{
	return (type == RED_IN || type == RED_OUT || type == APPEND || type == HERE_DOC);
}

int	check_red(t_token *token)
{
	t_token	*current;

	current = token;
	while(current)
	{
		if (is_red(current->type) && current->value == NULL)
			return (0);
		current = current->next;
	}
	return (1);
}

void	set_expand(t_token *str)
{
	// to do
}