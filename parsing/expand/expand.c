/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:52:15 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/04 22:26:44 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	copy_non_space(t_expand_data *exp_data, char *output, int *i)
{
	while ((*(exp_data->token_val))[*i]
		&& !ft_isspace((*(exp_data->token_val))[*i]))
		output[exp_data->j++] = (*(exp_data->token_val))[(*i)++];
}

// Function to initialize variables and calculate size
int	initialize_expansion(t_expand_data *exp_data)
{
	int	size;

	size = calculate_size(*(exp_data->token_val),
			exp_data->env, exp_data->exit_status);
	if (size < 0)
		return (-1);
	exp_data->j = 0;
	exp_data->in_double_q = false;
	exp_data->in_single_q = false;
	return (size);
}

// Main expand function
void	expand(char **token_val, t_env *env, int *exit_status, bool is_herdoc)
{
	t_expand_data	*exp_data;
	char			*output;
	int				size;

	exp_data = (t_expand_data *)gc_malloc(sizeof(t_expand_data), LOCAL);
	if (!exp_data)
		return ;
	exp_data->token_val = token_val;
	exp_data->exit_status = *exit_status;
	exp_data->env = env;
	size = initialize_expansion(exp_data);
	if (size < 0)
		return ;
	output = (char *)gc_malloc(size * 2, LOCAL);
	if (!output)
		return ;
	handle_expansion_loop(exp_data, output, is_herdoc);
	*token_val = output;
}

void	expand_tokens(t_token *token, t_env *env, int *exit_status)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type != HERE_DOC && current->type != HERE_DOC_EXP)
			expand(&(current->value), env, exit_status, false);
		current = current->next;
	}
}
