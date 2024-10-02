/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:51:35 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/18 02:23:03 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Add token to list function
static t_token	*add_token_to_list(t_token *head, t_token *new_token)
{
	t_token	*last;

	last = head;
	if (!head)
		return (new_token);
	while (last->next)
		last = last->next;
	last->next = new_token;
	return (head);
}

// Handle redirection function
static char	*handle_redirection(char **splited_input, int *i)
{
	if (splited_input[*i + 1] && !cstm_strcmp(splited_input[*i + 1], "|"))
	{
		(*i) += 2;
		return (ft_strdup(splited_input[*i - 1]));
	}
	else
	{
		(*i)++;
		return (NULL);
	}
}

// Get token type function
static e_tokenType	get_token_type(char *str)
{
	if (cstm_strcmp(str, "|"))
		return (PIPE);
	if (cstm_strcmp(str, "<"))
		return (RED_IN);
	if (cstm_strcmp(str, ">"))
		return (RED_OUT);
	if (cstm_strcmp(str, ">>"))
		return (APPEND);
	if (cstm_strcmp(str, "<<"))
		return (HERE_DOC_EXP);
	return (COMMAND);
}

// Create token function
static t_token	*create_token(char **splited_input, int *i)
{
	t_token		*new_token;
	e_tokenType	type;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	type = get_token_type(splited_input[*i]);
	new_token->type = type;
	if (type == COMMAND || type == PIPE)
		new_token->value = ft_strdup(splited_input[(*i)++]);
	else
		new_token->value = handle_redirection(splited_input, i);
	new_token->next = NULL;
	return (new_token);
}

/*// Format and switch characters function*/
/*static char	*format_and_switch(char *input)*/
/*{*/
/*	char	*formated_input;*/
/**/
/*	formated_input = format(input);*/
/*	switch_char(&formated_input, ' ', -1);*/
/*	switch_char(&formated_input, '\t', -2);*/
/*	return (formated_input);*/
/*}*/

// Split input into tokens

t_token	*tokenizer(char *input, t_env *env, int *exit_status)
{
	t_token	*head;
	char	**splited_input;
	int		i;
	char	*formated_input;
	t_token	*new_token;

	head = NULL;
	i = 0;
	formated_input = format_and_switch(input);
	splited_input = cstm_split(formated_input, " \t");
	while (splited_input[i])
	{
		new_token = create_token(splited_input, &i);
		if (!new_token)
			return (NULL);
		head = add_token_to_list(head, new_token);
	}
	if (!syntax_error(head))
	{
		*exit_status = 258;
		return (NULL);
	}
	heredoc_type_set(&head);
	return (head);
}
