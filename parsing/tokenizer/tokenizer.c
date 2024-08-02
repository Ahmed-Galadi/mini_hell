/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:51:35 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/02 01:11:07 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

void    set_expand_opp(t_token **token)
{
	t_token	*current;

	current = *token;
	while (current)
	{
		current->type = red_type(current);
		current = current->next;
	}
}

t_token *tokenizer(char *input)
{
    t_token *head = NULL;
    char *formated_input;
    char **splited_input;
    e_tokenType type;
    int i = 0;

    formated_input = format(input);
    switch_char(&formated_input, ' ', -1);
    splited_input = ft_split(formated_input, ' ');

    while (splited_input[i])
    {
        t_token *new_token = (t_token *)malloc(sizeof(t_token));
        if (!new_token)
            error();
        if (ft_strcmp(splited_input[i], "|"))
			type = PIPE;
		else if (ft_strcmp(splited_input[i], "<"))
			type = RED_IN;
        else if (ft_strcmp(splited_input[i], ">"))
			type = RED_OUT;
        else if (ft_strcmp(splited_input[i], ">>"))
            type = APPEND;
        else if (ft_strcmp(splited_input[i], "<<"))
            type = HERE_DOC;
        else
            type = COMMAND;
        new_token->type = type;
        if (type == COMMAND || type == PIPE)
        {
            new_token->value = ft_strdup(splited_input[i]);
            i++;
        }
        else
        {
            if (splited_input[i + 1])
                new_token->value = ft_strdup(splited_input[i + 1]);
            else
                return (NULL);
            i += 2;
        }

        new_token->next = NULL;

        if (head == NULL)
            head = new_token;
        else
        {
            t_token *last = head;
            while (last->next)
                last = last->next;
            last->next = new_token;
        }
    }
	set_expand_opp(&head);
	trim_quotes(&head);
	set_expand(&head);
    return (head);
}
