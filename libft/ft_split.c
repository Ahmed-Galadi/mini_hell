/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 06:54:41 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/07 18:36:26 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	count_words(char const *s, char c)
{
	size_t	counter;
	size_t	is_counter_triggred;

	counter = 0;
	is_counter_triggred = 0;
	while (*s != '\0')
	{
		if (*s != c && (is_counter_triggred == 0))
		{
			is_counter_triggred = 1;
			counter++;
		}
		else if (*s == c)
			is_counter_triggred = 0;
		s++;
	}
	return (counter);
}

static	void	fill_word(char *currentWord, char const *s,
							size_t s_index, size_t word_size)
{
	int	i;

	i = 0;
	while (word_size > 0)
	{
		currentWord[i] = s[s_index - word_size];
		i++;
		word_size--;
	}
	currentWord[i] = '\0';
}
