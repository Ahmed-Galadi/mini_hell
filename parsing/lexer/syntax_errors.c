/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 15:03:40 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 18:46:48 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	check_pipes(t_token *token)
{
	t_token	*current;

	current = token;
	if (current->type == PIPE || last_token(token)->type == PIPE)
		return (0);
	while(current)
	{
		if (current->type == PIPE && current->next->type == PIPE)
			return (0);
		current = current->next;
	}
	return (1);
}

int		check_redirection(t_token *token)
{
	t_token	*current;

	current = token;
	while (current)
	{
		if (is_red(current->type) && !ft_strlen(current->value))
			return (0);
		current = current->next;
	}
	return (1);
}
bool check_quote_syntax(char *input)
{
    bool single_quote_open = false;
    bool double_quote_open = false;
	int i = 0;

    while (input[i])
	{
        if (input[i] == '\'' && !double_quote_open)
            single_quote_open = !single_quote_open;
		else if (input[i] == '\"' && !single_quote_open)
            double_quote_open = !double_quote_open;
		i++;
    }
    return (!single_quote_open && !double_quote_open);
}

// int		syntax_error(t_token *token)
// {
	
// }