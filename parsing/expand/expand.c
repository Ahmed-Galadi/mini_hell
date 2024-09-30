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

// Function to initialize variables and calculate size
int	initialize_expansion(t_expand_data *exp_data, int *j,
						bool *in_double_q, bool *in_single_q)
{
	int	size;

	size = calculate_size(*(exp_data->token_val),
					   exp_data->env, exp_data->exit_status);
	if (size < 0)
		return (-1);
	*j = 0;
	*in_double_q = false;
	*in_single_q = false;
	return (size);
}

// Function to handle the main expansion loop
void handle_expansion_loop(t_expand_data *exp_data, char *output, e_tokenType *token_typ) 
{
	bool	in_double_q;
	bool	in_single_q;
	int		i;
	int		j;

	i = 0;
	j = 0;
    in_double_q = false;
	in_single_q = false;
    while ((*(exp_data->token_val))[i]) 
	{
        handle_quotes_state((*(exp_data->token_val))[i],
								&in_single_q, &in_double_q);
        if ((*(exp_data->token_val))[i] == '$'
				&& (in_double_q || (!in_double_q && !in_single_q)))
		{
            char *to_ex = get_expand_val(*(exp_data->token_val),
										 exp_data->env, &i, exp_data->exit_status);
            if (to_ex)
                while (*to_ex)
                    output[j++] = *to_ex++;
        }
		else 
            output[j++] = (*(exp_data->token_val))[i++];
    }
    output[j] = '\0';
}

// Main function to expand environment variables
void expand(char **token_val, e_tokenType *token_typ, t_env *env, int exit_status) {
    int j;
    t_expand_data exp_data = { token_val, env, exit_status };

    int size = initialize_expansion(&exp_data, &j, &(bool){false}, &(bool){false});
    if (size < 0)
		return ;
    char *output = (char *)malloc(size);
    if (!output)
		return ;
    handle_expansion_loop(&exp_data, output, token_typ);
    *token_val = output;
}

// Iterates through a list of tokens and applies variable expansion to each one
void	expand_str(t_token **token, t_env *env, int exit_status)
{
	t_token *current_token;

	current_token = *token;
	if (!env)
		return ;
	while (current_token)
	{
		expand(&(current_token->value), &(current_token->type), env, exit_status);
		current_token = current_token->next;
	}
}

