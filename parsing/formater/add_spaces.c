/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_spaces.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:52:32 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/07 18:37:17 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Toggle quote states (single and double quotes)
static void	toggle_quotes(char c, bool *open_s_quote, bool *open_d_quote)
{
	if (c == '\'')
		*open_s_quote = !(*open_s_quote);
	if (c == '\"')
		*open_d_quote = !(*open_d_quote);
}

// Add space around double operators like ">>" or "<<"
static int	handle_double_operator(char *str, char *output, int *i, int *j)
{
	if ((str[*i] == '>' && str[*i + 1] == '>')
		|| (str[*i] == '<' && str[*i + 1] == '<'))
	{
		output[(*j)++] = ' ';
		output[(*j)++] = str[(*i)++];
		output[(*j)++] = str[(*i)++];
		output[(*j)++] = ' ';
		return (1);
	}
	return (0);
}

// Add spaces around single operators like "|" or "<" or ">"
static void	handle_single_operator(char *str, char *output, int *i, int *j)
{
	if (*j > 0 && output[*j - 1] != ' ')
		output[(*j)++] = ' ';
	output[(*j)++] = str[(*i)++];
	if (str[*i] && str[*i] != ' ')
		output[(*j)++] = ' ';
}

/* Process each character,
 * add spaces around operators while respecting quotes */
static void	process_characters(char *str, char *output,
								bool *open_s_quote, bool *open_d_quote)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		toggle_quotes(str[i], open_s_quote, open_d_quote);
		if (!(*open_d_quote || *open_s_quote)
			&& handle_double_operator(str, output, &i, &j))
			continue ;
		else if (is_op(str[i]) && !(*open_d_quote || *open_s_quote))
			handle_single_operator(str, output, &i, &j);
		else
			output[j++] = str[i++];
	}
	output[j] = '\0';
}

// Add spaces around operators and handle quotes (main function)
char	*add_spaces(char *str)
{
	char	*output;
	bool	open_d_quote;
	bool	open_s_quote;

	open_d_quote = false;
	open_s_quote = false;
	output = gc_malloc(ft_strlen(str) * 2 + 1, LOCAL);
	if (!output)
		return (NULL);
	process_characters(str, output, &open_s_quote, &open_d_quote);
	return (output);
}
