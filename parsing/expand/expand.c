/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 00:52:15 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/07 18:37:10 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Function to initialize variables and calculate size
int initialize_expansion(t_expand_data *exp_data)
{
    int size = calculate_size(*(exp_data->token_val), exp_data->env, exp_data->exit_status);
    if (size < 0)
        return (-1);
    exp_data->j = 0;
    exp_data->in_double_q = false;
    exp_data->in_single_q = false;
    return (size);
}

// Helper function to copy expanded value into output
void copy_expanded_value(char **to_ex, char *output, int *j)
{
    while (**to_ex)
    {
        output[(*j)++] = **to_ex;
        (*to_ex)++;
    }
}

// Check if the next character after "$" is valid for expansion
int is_valid_for_expansion(char c)
{
    return (ft_isalnum(c) || c == '_' || c == '?');
}

// Handles the expansion of environment variables
void handle_variable_expansion(t_expand_data *exp_data, char *output, int *i)
{
    char *to_ex = get_expand_val(*(exp_data->token_val), exp_data->env, i, exp_data->exit_status);
    if (to_ex)
        copy_expanded_value(&to_ex, output, &exp_data->j);
}

// Handles copying normal characters into the output
void handle_regular_characters(t_expand_data *exp_data, char *output, int *i)
{
    if ((*(exp_data->token_val))[*i] != '\0')
    {
        output[exp_data->j++] = (*(exp_data->token_val))[*i];
        (*i)++;
    }
}

void handle_expansion_loop(t_expand_data *exp_data, char *output)
{
    int i = 0;
    int is_redirect = 0;  // Track if we're in a redirection context
    int tmp_index;

    while ((*(exp_data->token_val))[i])
    {
        // Update quote states
        handle_quotes_state((*(exp_data->token_val))[i], &exp_data->in_single_q, &exp_data->in_double_q);

        // Check for redirection operator and set redirection flag
        if ((*(exp_data->token_val))[i] == '<' || (*(exp_data->token_val))[i] == '>')
        {
            is_redirect = 1;  // Redirection found
            tmp_index = i + 1;

            // Handle cases like '>>' or '<<'
            if ((*(exp_data->token_val))[tmp_index] == '<' || (*(exp_data->token_val))[tmp_index] == '>')
                tmp_index++;

            // Skip spaces after the redirection operator
            while (ft_isspace((*(exp_data->token_val))[tmp_index]))
                tmp_index++;

            // If a variable follows the redirection, prevent expansion
            if ((*(exp_data->token_val))[tmp_index] == '$' && 
                (exp_data->in_double_q || (!exp_data->in_double_q && !exp_data->in_single_q)))
            {
                is_redirect = 1;  // Variable after redirection, do not expand
            }
            else
            {
                is_redirect = 0;  // No variable, reset the redirection flag
            }
        }
		// handle $
		if ((*(exp_data->token_val))[i] == '$'
			&& ((*(exp_data->token_val))[i + 1] == '\"' || (*(exp_data->token_val))[i + 1] == '\'')
			&& (!exp_data->in_double_q && !exp_data->in_single_q))
			i++;
        // Handle variable expansion if not in a redirection context
		else if ((*(exp_data->token_val))[i] == '$' && 
            (exp_data->in_double_q || (!exp_data->in_double_q && !exp_data->in_single_q)) && !is_redirect)
        {
            if (!(*(exp_data->token_val))[i + 1] || !is_valid_for_expansion((*(exp_data->token_val))[i + 1]))
            {
                output[exp_data->j++] = '$';
                i++;
            }
            else
            {
                // Handle the actual variable expansion
                handle_variable_expansion(exp_data, output, &i);
            }
        }
        else
        {
            // If we're processing a redirection target, skip expansion
            if (is_redirect)
            {
                // Skip the variable after redirection without expanding
                if ((*(exp_data->token_val))[i] == '$')
                {
                    while ((*(exp_data->token_val))[i] && !ft_isspace((*(exp_data->token_val))[i]))
                        output[exp_data->j++] = (*(exp_data->token_val))[i++];
                    is_redirect = 0;  // Reset after processing redirection target
                    continue;
                }
            }

            // Handle regular characters
            handle_regular_characters(exp_data, output, &i);
        }
    }
    output[exp_data->j] = '\0'; // Null-terminate the output string
}


// Main expand function
void expand(char **token_val, t_env *env, int *exit_status)
{
    t_expand_data *exp_data = (t_expand_data *)malloc(sizeof(t_expand_data));
    if (!exp_data)
        return;
    
    exp_data->token_val = token_val;
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

