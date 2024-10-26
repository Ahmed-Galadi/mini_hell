


#include "../../minishell.h"

// Helper function to copy expanded value into output
void	copy_expanded_value(char **to_ex, char *output, int *j)
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

void	handle_expansion_loop(t_expand_data *exp_data, char *output)
{
	int	i;
	int	is_redirect;  // Track if we're in a redirection context
	int	tmp_index;

	i = 0;
	is_redirect = 0;
	while ((*(exp_data->token_val))[i])
	{
		handle_quotes_state((*(exp_data->token_val))[i], &exp_data->in_single_q, &exp_data->in_double_q);
		if ((*(exp_data->token_val))[i] == '<' || (*(exp_data->token_val))[i] == '>')
		{
			is_redirect = 1;  // Redirection found
			tmp_index = i + 1;
			if ((*(exp_data->token_val))[tmp_index] == '<' || (*(exp_data->token_val))[tmp_index] == '>')
				tmp_index++;
			while (ft_isspace((*(exp_data->token_val))[tmp_index]))
				tmp_index++;
			if ((*(exp_data->token_val))[tmp_index] == '$' && 
				(exp_data->in_double_q || (!exp_data->in_double_q && !exp_data->in_single_q)))
				is_redirect = 1;  // Variable after redirection, do not expand
			else
				is_redirect = 0;  // No variable, reset the redirection flag
		}
		if ((*(exp_data->token_val))[i] == '$'
			&& ((*(exp_data->token_val))[i + 1] == '\"' || (*(exp_data->token_val))[i + 1] == '\'')
			&& (!exp_data->in_double_q && !exp_data->in_single_q))
			i++;
		else if ((*(exp_data->token_val))[i] == '$' && 
			(exp_data->in_double_q || (!exp_data->in_double_q && !exp_data->in_single_q)) && !is_redirect)
		{
			if ((*(exp_data->token_val))[i + 1] == '$')
				i = i + 2;
			else if (!(*(exp_data->token_val))[i + 1] || !is_valid_for_expansion((*(exp_data->token_val))[i + 1]))
			{
				output[exp_data->j++] = '$';
				i++;
			}
			else
				handle_variable_expansion(exp_data, output, &i);
		}
		else
		{
			if (is_redirect)
			{
				if ((*(exp_data->token_val))[i] == '$')
				{
					while ((*(exp_data->token_val))[i] && !ft_isspace((*(exp_data->token_val))[i]))
						output[exp_data->j++] = (*(exp_data->token_val))[i++];
					is_redirect = 0;  // Reset after processing redirection target
					continue;
				}
			}
			handle_regular_characters(exp_data, output, &i);
		}
	}
	output[exp_data->j] = '\0'; // Null-terminate the output string
}

