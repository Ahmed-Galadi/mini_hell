/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:28 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/16 14:42:05 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

int	is_red(e_tokenType type)
{
	return (type == RED_IN || type == RED_OUT
		|| type == APPEND || type == HERE_DOC);
}

void	add_opp(t_opp **opp, t_opp *to_add)
{
	t_opp	*current;

	if (!*opp)
		*opp = to_add;
	else
	{
		current = *opp;
		while (current->next)
			current = current->next;
		current->next = to_add;
	}
}

t_opp	*new_op(t_token **token)
{
	t_opp	*output;
	t_token	*current;
	t_opp	*tmp;

	output = NULL;
	current = *token;
	while (current && current->type != PIPE)
	{
		if (is_red(current->type))
		{
			tmp = (t_opp *)malloc(sizeof(t_opp));
			if (!tmp)
				return (NULL);
			tmp->operator = current->type;
			tmp->arg = ft_strdup(current->value);
			tmp->next = NULL;
			if (!output)
				output = tmp;
			else
				add_opp(&output, tmp);
		}
		current = current->next;
	}
	return (output);
}
