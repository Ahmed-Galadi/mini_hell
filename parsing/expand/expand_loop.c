/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 19:05:21 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/27 21:58:41 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	track_redirect(t_expand_data *exp_data,
	int *tmp_index, int *is_redirect, int *i)
{
	handle_quotes_state((*(exp_data->token_val))[*i],
		&exp_data->in_single_q, &exp_data->in_double_q);
	if (((*(exp_data->token_val))[*i] == '<'
		|| (*(exp_data->token_val))[*i] == '>')
		&& (!exp_data->in_double_q && !exp_data->in_single_q))
	{
		*is_redirect = 1;
		*tmp_index = *i + 1;
		if ((*(exp_data->token_val))[*tmp_index] == '<'
			|| (*(exp_data->token_val))[*tmp_index] == '>')
			(*tmp_index)++;
		while (ft_isspace((*(exp_data->token_val))[*tmp_index]))
			(*tmp_index)++;
		if ((*(exp_data->token_val))[*tmp_index] == '$' &&
			(exp_data->in_double_q || (!exp_data->in_double_q
			&& !exp_data->in_single_q)))
			*is_redirect = 1;
		else
			*is_redirect = 0;
	}
}

void	handle_var_expansion(t_expand_data *exp_data, char *output, int *i)
{
	if ((*(exp_data->token_val))[*i + 1] == '$')
		*i = *i + 2;
	else if (!(*(exp_data->token_val))[*i + 1]
		|| !is_valid_for_expansion((*(exp_data->token_val))[*i + 1]))
	{
		output[exp_data->j++] = '$';
		(*i)++;
	}
	else
		handle_variable_expansion(exp_data, output, i);
}

int	check_quts_after_dlr(t_expand_data *exp_data, int i)
{
	return ((*(exp_data->token_val))[i] == '$'
			&& ((*(exp_data->token_val))[i + 1] == '\"'
			|| (*(exp_data->token_val))[i + 1] == '\'')
			&& (!exp_data->in_double_q && !exp_data->in_single_q));
}

int	expand_check(t_expand_data *exp_data,
	int is_redirect, int i, bool is_heredoc)
{
	return ((*(exp_data->token_val))[i] == '$' &&
			(exp_data->in_double_q
			|| (!exp_data->in_double_q && !exp_data->in_single_q) || is_heredoc)
			&& !is_redirect);
}

void	handle_expansion_loop(t_expand_data *exp_data,
	char *output, bool is_herdoc)
{
	int	i;
	int	is_redirect;
	int	tmp_index;

	(1 && (i = 0), (is_redirect = 0));
	while ((*(exp_data->token_val))[i])
	{
		track_redirect(exp_data, &tmp_index, &is_redirect, &i);
		if (check_quts_after_dlr(exp_data, i))
			i++;
		else if (expand_check(exp_data, is_redirect, i, is_herdoc))
			handle_var_expansion(exp_data, output, &i);
		else
		{
			if (is_redirect && (*(exp_data->token_val))[i] == '$')
			{
				copy_non_space(exp_data, output, &i);
				is_redirect = 0;
				continue ;
			}
			handle_regular_characters(exp_data, output, &i);
		}
	}
	output[exp_data->j] = '\0';
}
