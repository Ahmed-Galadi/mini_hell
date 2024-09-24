/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:28 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 22:17:05 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

e_tokenType red_type(t_token *token)
{
	bool	dq_fl;
	bool	is_dq;
	int		i;

	is_dq = false;
	dq_fl = false;
	i = 0;
	while ((token->value)[i])
	{
		if ((token->value)[i] == '\"')
		{
			dq_fl = true;
			break;
		}
		i++;
	}
	if (!dq_fl)
	{
		i = 0;
		while ((token->value)[i])
		{
			if ((token->value)[i] == '$' && ft_isalpha((token->value)[i + 1]))
			{
				if (token->type == RED_IN)
					return (RED_IN_EXP);
				else if (token->type == RED_OUT)
					return (RED_OUT_EXP);
				else if (token->type == APPEND)
					return (APPEND_EXP);
				else if (token->type == HERE_DOC)
					return (HERE_DOC_EXP);
			}
			i++;
		}
	}
	else
	{
		i = 0;
		while ((token->value)[i])
		{
			if ((token->value)[i] == '\"')
				is_dq = !is_dq;
			if ((is_dq && ((token->value)[i] == '$' && ft_isalpha((token->value)[i + 1]))))
			{
				if (token->type == RED_IN)
					return (RED_IN_EXP);
				else if (token->type == RED_OUT)
					return (RED_OUT_EXP);
				else if (token->type == APPEND)
					return (APPEND_EXP);
				else if (token->type == HERE_DOC)
					return (HERE_DOC_EXP);
			}
			i++;
		}
	}
	return (token->type);
}

void	trim_quotes(t_token **token)
{
	t_token	*current;
	char	*ptr_holder;
	
	current = *token;
	while (current)
	{
		if (current->value != NULL)
		{
			if ((current->value)[0] == '\"')
			{
				switch_char(&(current->value), -1, ' ');
				switch_char(&(current->value), -2, '\t');
				ptr_holder = current->value;
				current->value = handle_quotes(ptr_holder);
				free(ptr_holder);
			}
			else if ((current->value)[0] == '\'')
			{
				switch_char(&(current->value), -1, ' ');
				switch_char(&(current->value), -2, '\t');
				ptr_holder = current->value;
				current->value = handle_quotes(ptr_holder);
				free(ptr_holder);
			}
			else
			{
				switch_char(&(current->value), -1, ' ');
				switch_char(&(current->value), -2, '\t');
				ptr_holder = current->value;
				current->value = handle_quotes(ptr_holder);
				free(ptr_holder);
			}
		}
		current = current->next;
	}
}



int	is_red(e_tokenType type)
{
	return (type == RED_IN || type == RED_OUT || type == APPEND || type == HERE_DOC
		|| type == RED_IN_EXP || type == RED_OUT_EXP || type == APPEND_EXP || type == HERE_DOC_EXP);
}

int	check_red(t_token *token)
{
	t_token	*current;

	current = token;
	while(current)
	{
		if (is_red(current->type) && current->value == NULL)
			return (0);
		current = current->next;
	}
	return (1);
}

void	add_opp(t_opp **opp, t_opp *to_add)
{
	t_opp	*current;

	if (!*opp)
		*opp = to_add;
	else
	{
		current = *opp;
		while (current->next)
			current = current->next;
		current->next = to_add;
	}
}

t_opp *new_op(t_token **token)
{
	t_opp	*output;
	t_token	*current;
	t_opp	*tmp;

	output = NULL;
	current = *token;
	while (current && current->type != PIPE)
	{
		if (is_red(current->type))
		{
			tmp = (t_opp *)malloc(sizeof(t_opp));
			if (!tmp)
                return (NULL);
			tmp->operator = current->type;
            tmp->arg = ft_strdup(current->value);
            tmp->next = NULL;
			if (!output)
				output = tmp;
			else
				add_opp(&output, tmp);
		}
		current = current->next;
	}
	return (output);
}
