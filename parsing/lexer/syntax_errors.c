/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:03:40 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/28 20:39:52 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipes(t_token *token)
{
	t_token	*current;

	if (!token)
		return (-1);
	current = token;
	if (current->type == PIPE || last_token(token)->type == PIPE)
		return (0);
	while (current)
	{
		if (current->type == PIPE && current->next->type == PIPE)
			return (0);
		current = current->next;
	}
	return (1);
}

int	check_redirection(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (is_red(current->type) && is_rederection(current->value))
			return (0);
		if (!current->value && is_red(current->type))
			return (0);
		current = current->next;
	}
	return (1);
}

bool	check_quote_syntax(char *input)
{
	bool	single_quote_open;
	bool	double_quote_open;
	int		i;

	single_quote_open = false;
	double_quote_open = false;
	i = 0;
	if (!input)
		return (-1);
	while (input[i])
	{
		if (input[i] == '\'' && !double_quote_open)
			single_quote_open = !single_quote_open;
		else if (input[i] == '\"' && !single_quote_open)
			double_quote_open = !double_quote_open;
		i++;
	}
	return (!single_quote_open && !double_quote_open);
}

int	syntax_error(t_token *token)
{
	t_token	*current;
	int		output;

	output = 1;
	if (!token)
		return (1);
	if (!check_pipes(token) || !check_redirection(token))
	{
		if (!check_pipes(token))
			printf(RED BOLD"Syntax Error:"RESET PINK" invalid pipes!\n"RESET);
		if (!check_redirection(token))
			printf(RED BOLD"Syntax Error:"RESET PINK" invalid file!\n"RESET);
		return (0);
	}
	current = token;
	while (current)
	{
		if (!check_quote_syntax(current->value))
		{
			printf(RED BOLD"Syntax Error:"RESET PINK" invalid quotes !\n"RESET);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
