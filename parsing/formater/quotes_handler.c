/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 19:01:02 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/07 18:37:25 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Finds the index of the matching closing quote in the input string.
static int	get_close_quote(char *input, int index_quote)
{
	char	quote;

	quote = input[index_quote];
	index_quote++;
	while (input[index_quote])
	{
		if (input[index_quote] == quote)
			return (index_quote);
		index_quote++;
	}
	return (-1);
}

// Copies characters from input to output, excluding quoted sections.
static int	copy_without_quotes(char *str, char *output)
{
	int	i;
	int	j;
	int	cq_index;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			cq_index = get_close_quote(str, i);
			if (cq_index == -1)
				return (-1);
			i++;
			while (i < cq_index)
				output[j++] = str[i++];
			i++;
		}
		else
			output[j++] = str[i++];
	}
	output[j] = '\0';
	return (j);
}

// Processes input string to remove quoted sections and returns a new string.
static char	*handle_quotes(char *str)
{
	char	*output;

	if (!check_quote_syntax(str))
		return (error(), NULL);
	output = (char *)gc_malloc(ft_strlen(str) + 1, LOCAL);
	if (!output)
		return (error(), NULL);
	if (copy_without_quotes(str, output) == -1)
		return (error(), NULL);
	return (output);
}

// Switch characters before trimming quotes then handle quotes
static void	process_token_value(char **value)
{
	char	*ptr_holder;

	if (*value != NULL)
	{
		switch_char(value, -1, ' ');
		switch_char(value, -2, '\t');
		ptr_holder = *value;
		*value = handle_quotes(ptr_holder);
	}
}

// Main function to process each token in the list
void	trim_quotes(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		process_token_value(&(current->value));
		if (!current->value)
			break ;
		current = current->next;
	}
}
