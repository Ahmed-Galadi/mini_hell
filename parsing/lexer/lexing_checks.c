/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:28 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/02 04:43:36 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int		ft_isalpha(char c)
{
	return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

e_tokenType red_type(t_token *token)
{
	bool	is_dq;
	int		i;

	is_dq = false;
	i = 0;
	while ((token->value)[i])
	{
		if ((token->value)[i] == '\"')
			is_dq = !is_dq;
		if (is_dq && ((token->value)[i] == '$' && ft_isalpha((token->value)[i + 1])))
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
	return (token->type);
}

void	trim_quotes(t_token **token)
{
	t_token	*current;
	char	*ptr_holder;
	
	current = *token;
	while (current)
	{
		if ((current->value)[0] == '\"')
		{
			if (!is_red(current->type))
				current->type = D_QUOTE;
			switch_char(&(current->value), -1, ' ');
			ptr_holder = current->value;
			current->value = handle_quotes(ptr_holder);
			free(ptr_holder);
		}
		else if ((current->value)[0] == '\'')
		{
			if (!is_red(current->type))
				current->type = S_QUOTE;
			switch_char(&(current->value), -1, ' ');
			ptr_holder = current->value;
			current->value = handle_quotes(ptr_holder);
			free(ptr_holder);
		}
		else
		{
			switch_char(&(current->value), -1, ' ');
			ptr_holder = current->value;
			current->value = handle_quotes(ptr_holder);
			free(ptr_holder);
		}
		current = current->next;
	}
}

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



int	is_expand(char *str)
{
	int		i;
	
	i = 0;
	while (str[i])
	{		
		if (str[i] == '$' && ft_isalpha(str[i + 1]))
			return (1);
		i++;
	}
	return (0);
}

void	set_expand(t_token **token)
{
	t_token *current;
	
	current = *token;
	while (current)
	{
		if ((current->type != S_QUOTE && !is_red(current->type)))
		{
			if (is_expand(current->value))
				current->type = EXPAND;
		}
		current = current->next;
	}
}

// t_opp *new_op(t_token **token)
// {
//     t_token *current;
//     t_opp   *output;
//     t_opp   *out_head = NULL;
//     t_opp   *out_tail = NULL;

//     if (!*token)
//         return (NULL);
//     current = *token;
//     while (current && (current->type != PIPE))
//     {
//         if (is_red(current->type))
//         {
//             output = (t_opp *)malloc(sizeof(t_opp));
//             if (!output)
//                 return (NULL);
//             output->operator = current->type;
//             output->arg = current->value;
//             output->next = NULL;

//             if (!out_head)
//                 out_head = output;
//             else
//                 out_tail->next = output;
//             out_tail = output;
//         }
//         current = current->next;
//     }
//     return (out_head);
// }

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
	while (current)
	{
		if (is_red(current->type))
		{
			tmp = (t_opp *)malloc(sizeof(t_opp));
			if (!tmp)
                return (NULL);
			tmp->operator = current->type;
            tmp->arg = current->value;
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
