/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:34:28 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/27 21:59:00 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
// Helper function to copy expanded value into output
static void	copy_expanded_value(char **to_ex, char *output, int *j)
{
	while (**to_ex)
	{
		output[(*j)++] = **to_ex;
		(*to_ex)++;
	}
}

// Check if the next character after "$" is valid for expansion
int	is_valid_for_expansion(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

// Handles the expansion of environment variables
void	handle_variable_expansion(t_expand_data *exp_data, char *output, int *i)
{
	char	*to_ex;

	to_ex = get_expand_val(*(exp_data->token_val),
			exp_data->env, i, exp_data->exit_status);
	if (to_ex)
		copy_expanded_value(&to_ex, output, &exp_data->j);
}

// Handles copying normal characters into the output
void	handle_regular_characters(t_expand_data *exp_data, char *output, int *i)
{
	if ((*(exp_data->token_val))[*i] != '\0')
	{
		output[exp_data->j++] = (*(exp_data->token_val))[*i];
		(*i)++;
	}
}
