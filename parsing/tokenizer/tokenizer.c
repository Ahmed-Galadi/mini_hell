/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:51:35 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/22 15:13:41 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_token	*token_init(char **s_input)
{
	t_token		*output;
	e_tokenType	type;

	output = (t_token *)malloc(sizeof(t_token));
	if (!output)
		error();
	if (ft_strcmp(s_input[0], "|"))
		error();
	output->next = NULL;
	if (ft_strcmp(s_input[0], "<"))
		type = RED_IN;
	else if (ft_strcmp(s_input[0], ">"))
		type = RED_OUT;
	else if (ft_strcmp(s_input[0], ">>"))
		type = APPEND;
	else if (ft_strcmp(s_input[0], "<<"))
		type = HERE_DOC;
	else
		type = COMMAND;
	output->type = type;
	output->value = ft_strdup(s_input[0]);
	return (output);
}

t_token *tokenizer(char *input)
{
	t_token	*output;
	char	*formated_input;
	char	**splited_input;
	int		i;

	formated_input = format(input);
	switch_char(&formated_input, ' ', -1);
	splited_input = ft_split(formated_input, ' ');
	output = token_init(splited_input);
	i = 1;
	while (splited_input[i]) 
	{
		// tokenize everything
	}
	return (output);
}