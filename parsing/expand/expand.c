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

// Helper function to skip spaces after redirection
int	skip_spaces(char *str, int i)
{
	while (str[i] && ft_isspace(str[i]))
		i++;
	return (i);
}

// Function to check for redirection operators and ambiguous redirection
static bool	check_redirection(char *str, int *i, bool *redirect_detected)
{
	if (str[*i] == '>' || str[*i] == '<')
	{
		(*i)++;
		if (str[*i] == '>' || str[*i] == '<')
			(*i)++;
		*redirect_detected = true;
		return (true);
	}
	return (false);
}

// Function to detect ambiguous redirection in the expanded string
bool	is_ambiguous_redirection(char *str)
{
	bool	redirect_detected;
	int		i;

	redirect_detected = false;
	i = 0;
	while (str[i])
	{
		if (check_redirection(str, &i, &redirect_detected))
		{
			i = skip_spaces(str, i);
			if (!str[i] || str[i] == '>' || str[i] == '<'
				|| ft_isspace(str[i]))
				return (true);
		}
		else if (redirect_detected && ft_isspace(str[i]))
			return (true);
		i++;
	}
	return (false);
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

// Function to check if string contains spaces
bool	contains_spaces(const char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			return (true);
		str++;
	}
	return (false);
}

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
bool	is_valid_for_expansion(char c)
{
	return (ft_isalnum(c) || c == '_' || c == '?');
}

// Handles the expansion of environment variables
void	handle_variable_expansion(t_expand_data *exp_data, char *output, int *i)
{
	char	*to_ex;
	char	temp_str[1024];

	to_ex = get_expand_val(*(exp_data->token_val),
			exp_data->env, i, exp_data->exit_status);
	if (to_ex)
	{
		if (contains_spaces(to_ex))
		{
			ft_strcpy(temp_str, to_ex);
			copy_expanded_value(&to_ex, output, &exp_data->j);
		}
		else
			copy_expanded_value(&to_ex, output, &exp_data->j);
	}
}

// Handles copying normal characters into the output
void	handle_regular_characters(t_expand_data *exp_data, char *output, int *i)
{
	if ((*(exp_data->token_val))[*i] == '\0')
		return ;
	output[exp_data->j++] = (*(exp_data->token_val))[*i];
	(*i)++;
}

// Main expansion loop
void	handle_expansion_loop(t_expand_data *exp_data, char *output)
{
	int	here_doc;
	int	i;

	i = 0;
	here_doc = 0;
	while ((*(exp_data->token_val))[i])
	{
		handle_quotes_state((*(exp_data->token_val))[i],
			&exp_data->in_single_q, &exp_data->in_double_q);
		if ((*(exp_data->token_val))[i] == '<' && (*(exp_data->token_val))[i + 1] == '<')
			here_doc = 1;
		if (((*(exp_data->token_val))[i] == '$' && (exp_data->in_double_q
			|| (!exp_data->in_double_q && !exp_data->in_single_q))) && !here_doc)
		{
			if (!(*(exp_data->token_val))[i + 1]
				|| !is_valid_for_expansion((*(exp_data->token_val))[i + 1]))
			{
				output[exp_data->j++] = '$';
				i++;
			}
			else
				handle_variable_expansion(exp_data, output, &i);
			here_doc = 0;
		}
		else
			handle_regular_characters(exp_data, output, &i);
	}
	output[exp_data->j] = '\0';
}

// Main expand function
void	expand(char **token_val, t_env *env, int *exit_status)
{
	t_expand_data	*exp_data;
	char			*output;
	int				size;

	exp_data = (t_expand_data *)malloc(sizeof(t_expand_data));
	if (!exp_data)
		return ;
	exp_data->token_val = token_val;
	exp_data->env = env;
	size = initialize_expansion(exp_data);
	if (size < 0)
		return ;
	output = (char *)gc_malloc(size, LOCAL);
	if (!output)
		return ;
	handle_expansion_loop(exp_data, output);

    // After expanding, check if the expanded string has ambiguous redirections
	if (is_ambiguous_redirection(output))
	{
		printf(RED BOLD"Error:"RESET PINK" ambiguous redirect\n"RESET);
		*token_val = "";
		*exit_status = 1;
	}
	else
		*token_val = output;
}

