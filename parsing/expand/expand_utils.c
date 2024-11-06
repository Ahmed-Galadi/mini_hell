/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:39:13 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/06 00:26:27 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Extracts a key from the string after a '$' sign, updating the index
static char	*get_key(char *str, int *i)
{
	int		length;
	char	*output;

	length = 0;
	if (!str)
		return (NULL);
	(*i)++;
	if (ft_isnum(str[*i]))
		return ((*i)++, NULL);
	if (str[*i] == '?')
		return ((*i)++, ft_strdup("?"));
	while (str[*i + length] && !ft_isspace(str[*i + length])
		&& str[*i + length] != '$' && str[*i + length] != '\''
		&& str[*i + length] != '\"' && str[*i + length] != -1
		&& (ft_isalnum(str[*i + length])
			|| str[*i + length] == '_' ))
		length++;
	output = (char *)gc_malloc(length + 1, LOCAL);
	if (!output)
		return (perror("malloc"), NULL);
	ft_strncpy(output, &str[*i], length);
	output[length] = '\0';
	*i += length;
	return (output);
}

char	*spec_char_quoting(char *spec_str)
{
	char	*output;
	int		tracker;
	int		i;
	int		j;

	(1 && (i = 0), (j = 0));
	while (spec_str[i])
	{
		if (spec_str[i] == '<' || spec_str[i] == '>' || spec_str[i] == '|')
		{
			output = gc_malloc(ft_strlen(spec_str) + 3, LOCAL);
			(1 && (tracker = i) && (i = 0));
			while (spec_str[i])
			{
				if (i == tracker)
					output[j++] = '\"';
				output[j++] = spec_str[i++];
			}
			output[j++] = '\"';
			output[j] = '\0';
			return (output);
		}
		i++;
	}
	return (spec_str);
}

// Expands variable keys and returns their values, including '$?'
char	*get_expand_val(char *str, t_env *env, int *i, int exit_status)
{
	char	*key;
	t_env	*current;

	if (!str)
		return (NULL);
	key = get_key(str, i);
	if (!key)
		return (NULL);
	if (key[0] == '?')
		return (ft_itoa(exit_status));
	key = ft_substr(key, 0, first_occurence(key, '?'));
	current = env;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
			return (spec_char_quoting(current->value));
		current = current->next;
	}
	return (NULL);
}

// Manages the state of single and double quotes based on the input character
void	handle_quotes_state(char c, bool *in_single_q, bool *in_double_q)
{
	if (c == '\"' && !(*in_single_q))
		*in_double_q = !(*in_double_q);
	if (c == '\'' && !(*in_double_q))
		*in_single_q = !(*in_single_q);
}

// Calculates the expanded string's size, accounting for quotes and variables
int	calculate_size(char *str, t_env *env, int exit_status)
{
	int		output_size;
	bool	in_dq;
	bool	in_sq;
	char	*to_ex;
	int		i;

	output_size = ft_strlen(str) + 1;
	in_dq = false;
	in_sq = false;
	if (!str)
		return (-1);
	i = 0;
	while (str[i])
	{
		handle_quotes_state(str[i], &in_sq, &in_dq);
		if ((str[i] == '$' && in_dq) || (str[i] == '$' && !in_dq && !in_sq))
		{
			to_ex = get_expand_val(str, env, &i, exit_status);
			if (to_ex)
				output_size += ft_strlen(to_ex);
		}
		else
			i++;
	}
	return (output_size + 1);
}
