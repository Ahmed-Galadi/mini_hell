/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/09 09:55:18 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	args_count(t_token *token)
{
	t_token	*current;
	int		count;

	count = 0;
	current = token;
	while (current && current->type != PIPE)
	{
		if (!is_red(token->type))
			count++;
		current = current->next;
	}
	return (count);
}

t_com	*new_com(t_token *token)
{
	t_com	*output;
	char	**out_args;
	t_opp	*out_opp;
	int		i;
	
	output = (t_com *)malloc(sizeof(t_com));
	out_args = (char **)malloc(args_count(token));
	if (!out_args || !output)
		return (NULL);
	i = 0;
	out_opp = new_op(&token);
	while (token && token->type != PIPE)
	{
		if (!is_red(token->type))
		{
			out_args[i] = ft_strdup(token->value);
			i++;
		}
		token = token->next;
	}
	output->command = out_args;
	output->operator = out_opp;
	output->next = NULL;
	return (output);
}
