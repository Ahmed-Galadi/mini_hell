/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:51:35 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/23 13:21:54 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void 	token_init(char **s_input, t_token	**to_fill)
{
	e_tokenType	type;
	static int	i;

	if (s_input[i] == NULL)
		*to_fill = NULL;
	*to_fill = (t_token *)malloc(sizeof(t_token));
	if (!(*to_fill) || (is_rederection(s_input[i]) && s_input[i + 1] == NULL))
		error();
	(*to_fill)->next = NULL;
	if (ft_strcmp(s_input[i], "|"))
		type = PIPE;
	else if (ft_strcmp(s_input[i], "<"))
		type = RED_IN;
	else if (ft_strcmp(s_input[i], ">"))
		type = RED_OUT;
	else if (ft_strcmp(s_input[i], ">>"))
		type = APPEND;
	else if (ft_strcmp(s_input[i], "<<"))
		type = HERE_DOC;
	else
		type = COMMAND;
	(*to_fill)->type = type;
	if (type == COMMAND || type == PIPE)
	{
		(*to_fill)->value = ft_strdup(s_input[i]);
		i++;	
	}
	else
	{
		(*to_fill)->value = ft_strdup(s_input[i + 1]);
		i += 2;
	}
}

t_token *tokenizer(char *input)
{
	t_token	*output;
	t_token	*tmp;
	char	*formated_input;
	char	**splited_input;

	formated_input = format(input);
	switch_char(&formated_input, ' ', -1);
	splited_input = ft_split(formated_input, ' ');
	if (ft_strcmp(splited_input[0], "|"))
		error();
	token_init(splited_input, &output);
	tmp = output;
	tmp = tmp->next;
	while (1)
	{
		token_init(splited_input, &tmp);
		if (!tmp)
			break;
		tmp = tmp->next;
	}
	return (output);
}