/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:52:15 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/18 00:57:10 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

char *get_key(char *str, int *i)
{
    int length;
    char *output;
    int j;

    if (!str)
        return (NULL);
    // Move past the initial '$'
    (*i)++;
    length = 0;
    j = 0;
    // Parse until a delimiter (space, quote, etc.) is found
    while (str[*i + length])
    {
        if (ft_isspace(str[*i + length]) || str[*i + length] == '$' || str[*i + length] == -1
            || str[*i + length] == '\'' || str[*i + length] == '\"')
            break;
        length++;
    }
    // Allocate memory for the extracted key
    output = (char *)malloc(length + 1);
    if (!output)
        exit(EXIT_FAILURE);
    j = 0;
	// extract key
    while (j < length)
    {
        output[j] = str[*i + j];
        j++;
    }
    output[j] = '\0';
    // Update the index to the end of the key
    *i += length;
    return (output);
}

char	*get_expand_val(char *str, t_env *env, int *i, int exit_status)
{
	char	*holder;
	t_env	*current;
	
	if (!str)
		return (NULL);
	holder = get_key(str, i);
	if (!holder)
		return (NULL);
	if (!ft_strcmp(holder, "?"))
		return (ft_itoa(exit_status));
	current = env;
	// loop through env struct
	while (current)
	{
		// if the holder (holds the key str) and the current key in env matshed we return it
		if (ft_strcmp(holder, current->key) == 0)	
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int		calculate_size(char *str, t_env *env, int exit_status)
{
	int		output_size;
	bool	in_dq;
	bool	in_sq;
	char	*to_ex;
	int		i;
	
	if (!str)
		return (-1);
	in_dq = false;
	in_sq = false;
	output_size = ft_strlen(str) + 1;
	i = 0;
	while (str[i])
	{
		// Handle double and single quotes
		if (str[i] == '\"' && !in_sq)
			in_dq = !in_dq;
		if (str[i] == '\'' && !in_dq)
			in_sq = !in_sq;
		// Handle variable expansion
		if ((str[i] == '$' && in_dq) || (str[i] == '$' && !in_dq && !in_sq))
		{
			to_ex = get_expand_val(str, env, &i, exit_status);
			if (to_ex)
				output_size += ft_strlen(to_ex);
		}
		else 
			i++;
	}
	return (output_size);
}

void	expand(char **str, t_env *env, int exit_status)
{
	char *output;
	char *to_ex;
	bool in_double_q = false;
	bool in_single_q = false;
	int	i = 0;
	int j = 0;

	// Allocate memory for the output string
	if (calculate_size(*str, env, exit_status) < 0)
	{
		printf("Syntax error\n");
		return ;
	}
	output = (char *)malloc(calculate_size(*str, env, exit_status));
	if (!output)
		return (perror("malloc"));
	if (!*str)
		return ;
	while ((*str)[i])
	{
		// Handle double and single quotes
		if ((*str)[i] == '\"' && !in_single_q)
			in_double_q = !in_double_q;
		if ((*str)[i] == '\'' && !in_double_q)
			in_single_q = !in_single_q;

		// Handle variable expansion
		if ((*str)[i] == '$' && (ft_isspace((*str)[i + 1]) || (*str)[i + 1] == '\0'))
		{
			if((*str)[i + 1] == '\"' || (*str)[i + 1] == '\'')
				i++;
			else
				output[j++] = (*str)[i++];
		}
		else if (((*str)[i] == '$' && in_double_q) || ((*str)[i] == '$' && !in_double_q && !in_single_q))
		{
			// Expand the environment variable
			to_ex = get_expand_val(*str, env, &i, exit_status); // `i` is updated inside get_expand_val()
			// If a valid expansion is found
			if (to_ex)
				// Copy the expanded value into output
				while (*to_ex)
					output[j++] = *to_ex++;
			else
				// If the expansion failed (i.e., NULL), skip the dollar sign
				if ((*str)[i] != '$')
					output[j++] = (*str)[i++];
		}
		else
			// Copy current character from the original string
			output[j++] = (*str)[i++];
	}
	output[j] = '\0';  // Null-terminate the output string
	*str = output;
}

void	expand_str(t_token **token, t_env *env, int exit_status)
{
	t_token *current_token;

	current_token = *token;
	if (!env)
		return ;
	while (current_token)
	{
		expand(&(current_token->value), env, exit_status);
		current_token = current_token->next;
	}
}

