/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cstm_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:40:15 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/07 18:38:47 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_delimiter(char c, const char *delims)
{
	while (*delims)
	{
		if (c == *delims)
			return (true);
		delims++;
	}
	return (false);
}

static int	count_words(const char *str, const char *delims)
{
	int		count;
	bool	in_word;

	count = 0;
	in_word = false;
	while (*str)
	{
		if (!is_delimiter(*str, delims) && !in_word)
		{
			in_word = true;
			count++;
		}
		else if (is_delimiter(*str, delims))
			in_word = false;
		str++;
	}
	return (count);
}

static char	*copy_word(const char *start, const char *end)
{
	int		len;
	int		i;
	char	*word;

	len = end - start;
	word = (char *)gc_malloc(len + 1, LOCAL);
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[len] = '\0';
	return (word);
}

char	**split_loop(const char *str, const char *delims, char **result)
{
	int			i;
	const char	*start;

	result = (char **)gc_malloc((
				count_words(str, delims) + 1) * sizeof(char *), LOCAL);
	if (!result)
		return (NULL);
	i = 0;
	while (*str)
	{
		if (!is_delimiter(*str, delims))
		{
			start = str;
			while (*str && !is_delimiter(*str, delims))
				str++;
			result[i] = copy_word(start, str);
			if (!result[i])
				return (NULL);
			i++;
		}
		else
			str++;
	}
	result[i] = NULL;
	return (result);
}

char	**cstm_split(const char *str, const char *delims)
{
	char	**output;

	if (!str || !delims)
		return (NULL);
	output = split_loop(str, delims, output);
	if (!output)
		return (NULL);
	return (output);
}
