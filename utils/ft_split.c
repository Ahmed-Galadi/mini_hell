/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 01:55:15 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/11 02:15:33 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

static int	count_words(const char *str, char d)
{
	int		i;
	int		count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (i == 0 && str[i] != d)
			count++;
		if (str[i] == d && str[i + 1] != d && str[i + 1])
			count++;
	}
	return (count);
}

static int	del_str_len(const char *str, char d)
{
	int		i;

	i = 0;
	while (str[i] != d && str[i])
		i++;
	return (i);
}

static char	*alloc_strs(const char **s, char **ret_arr, char c)
{
	int		i;
	int		str_len;

	str_len = del_str_len(*s, c);
	i = 0;
	*ret_arr = malloc(str_len + 1);
	if (!(*ret_arr))
		return (NULL);
	while (i < str_len)
	{
		(*ret_arr)[i] = **s;
		i++;
		(*s)++;
	}
	(*ret_arr)[i] = '\0';
	return (*ret_arr);
}

static void	free_arrs(char **arr, int index)
{
	int		i;

	i = 0;
	while (i < index)
	{
		free(arr[i]);
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**ret_arr;
	int		words_count;
	int		i;

	if (!s)
		return (NULL);
	words_count = count_words(s, c);
	i = 0;
	ret_arr = (char **)malloc((words_count + 1) * sizeof(char *));
	if (!ret_arr)
		error();
	while (i < words_count)
	{
		while (*s == c)
			s++;
		if (alloc_strs(&s, &ret_arr[i], c) == NULL)
		{
			free_arrs(ret_arr, i);
			free(ret_arr);
			error();
		}
		i++;
	}
	ret_arr[i] = 0;
	return (ret_arr);
}
