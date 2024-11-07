/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/08 16:54:37 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	args_count(t_token *token)
{
	t_token	*current;
	int		count;

	count = 0;
	current = token;
	while (current && current->type != PIPE)
	{
		if (!is_red(current->type))
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

	output = (t_com *)gc_malloc(sizeof(t_com), LOCAL);
	if (!output)
		return (NULL);
	out_args = (char **)gc_malloc(
			sizeof(char *) * (args_count(token) + 1), LOCAL);
	if (!out_args)
		return (NULL);
	i = 0;
	out_opp = new_op(&token);
	while (token && token->type != PIPE)
	{
		if (!is_red(token->type))
			out_args[i++] = ft_strdup(token->value);
		token = token->next;
	}
	out_args[i] = NULL;
	output->command = out_args;
	output->operator = out_opp;
	output->next = NULL;
	return (output);
}

void	add_com(t_com **command, t_com *to_add)
{
	t_com	*current;

	if (!*command)
		*command = to_add;
	else
	{
		current = *command;
		while (current->next)
			current = current->next;
		current->next = to_add;
	}
}

t_com	*create_cmds(t_token *token)
{
	t_com	*output;
	t_token	*current;

	output = NULL;
	current = token;
	while (current)
	{
		add_com(&output, new_com(current));
		while (current && current->type != PIPE)
			current = current->next;
		if (current)
			current = current->next;
	}
	return (output);
}
