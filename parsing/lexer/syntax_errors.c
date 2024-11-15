/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:03:40 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/14 00:03:56 by agaladi          ###   ########.fr       */
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
	int		i;

	current = token;
	while (current)
	{
		if (is_red(current->type) && cstm_strcmp(current->value, ""))
			return (-2);
		if (is_red(current->type) && is_rederection(current->value))
			return (0);
		if (!current->value && is_red(current->type))
			return (0);
		if (is_red(current->type))
		{
			i = -1;
			while ((current->value)[++i])
				if (ft_isspace((current->value)[i]))
					return (-1);
		}
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

int	is_valid_quotes(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (!check_quote_syntax(current->value))
		{
			ft_printf(2, RED BOLD"Syntax Error:"RESET \
				PINK" invalid quotes !\n"RESET);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	syntax_error(t_token *token)
{
	int		output;

	output = 0;
	if (!token)
		return (1);
	if (!check_pipes(token) || !check_redirection(token)
		|| check_redirection(token) == -1)
	{
		if (check_redirection(token) == -1)
			return (-1);
		else if (!check_redirection(token))
			ft_printf(2, RED BOLD"Syntax Error:"RESET \
				PINK" invalid file!\n"RESET);
		else if (!check_pipes(token))
			ft_printf(2, RED BOLD"Syntax Error:"RESET \
				PINK" invalid pipes!\n"RESET);
		return (0);
	}
	if (!is_valid_quotes(token))
		return (0);
	return (1);
}
