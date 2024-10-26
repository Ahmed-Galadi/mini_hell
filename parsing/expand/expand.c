/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:52:15 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/26 11:50:31 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
void expand(char **token_val, t_env *env, int *exit_status)
{
	t_expand_data *exp_data;

	exp_data = (t_expand_data *)malloc(sizeof(t_expand_data));
	if (!exp_data)
		return;
	exp_data->token_val = token_val;
	exp_data->exit_status = *exit_status;
	exp_data->env = env;
	int size = initialize_expansion(exp_data);
	if (size < 0)
		return;
	char *output = (char *)gc_malloc(size, LOCAL);
	if (!output)
		return;
	handle_expansion_loop(exp_data, output);
	*token_val = output;
	free(exp_data); // Free the allocated memory for exp_data
}

void	expand_tokens(t_token *token, t_env *env, int *exit_status)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (current->type != HERE_DOC && current->type != HERE_DOC_EXP)
			expand(&(current->value), env, exit_status);
		current = current->next;
	}
}
