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

// static	char	**free_arr(char **tmp, int i)
// {
// 	while (i > 0)
// 	{
// 		i--;
// 		free(tmp[i]);
// 	}
// 	free(tmp);
// 	return (NULL);
// }

// static	char	**allocate_strings(char const *s, char delimeter,
// 									size_t nbr_of_words, char **splited_strings)
// {
// 	size_t	s_index;
// 	size_t	current_word_index;
// 	size_t	word_size;

// 	current_word_index = 0;
// 	word_size = 0;
// 	s_index = 0;
// 	while (current_word_index < nbr_of_words)
// 	{
// 		while (s[s_index] && s[s_index] == delimeter)
// 			s_index++;
// 		while (s[s_index] && s[s_index] != delimeter)
// 		{
// 			word_size++;
// 			s_index++;
// 		}
// 		splited_strings[current_word_index] = (char *)gc_malloc(word_size + 1, );
// 		if (!splited_strings[current_word_index])
// 			return (gc_free_all(), NULL);
// 			// return (free_arr(splited_strings, current_word_index));
// 		fill_word(splited_strings[current_word_index], s, s_index, word_size);
// 		word_size = 0;
// 		current_word_index++;
// 	}
// 	splited_strings[current_word_index] = NULL;
// 	return (splited_strings);
// }

// char	**ft_split(char const *s, char c)
// {
// 	char	**splited_strings;
// 	size_t	nbr_of_words;

// 	if (!s)
// 		return (NULL);
// 	nbr_of_words = count_words(s, c);
// 	splited_strings = (char **)gc_malloc(sizeof(char *) * (nbr_of_words + 1));
// 	if (!splited_strings)
// 		return (NULL);
// 	splited_strings = allocate_strings(s, c, nbr_of_words, splited_strings);
// 	return (splited_strings);
// }
