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

void p_token(t_token *token)
{
	t_token *current;

	if (!token)
	{
		printf("empty token!\n");
		return ;
	}
	current = token;
	while (current)
	{
		printf("Type: %d", current->type);
		if (current->value)
			printf("| Value: %s", current->value);
		printf("\n****************************\n");
		current = current->next;
	}
}

t_token *tokenizer(char *input, t_env *env)
{
    t_token *head = NULL;
    char *formated_input;
    char **splited_input;
    e_tokenType type;
    int i = 0;

    formated_input = format(input);
    switch_char(&formated_input, ' ', -1);
	switch_char(&formated_input, '\t', -2);
	splited_input = cstm_split(formated_input, " \t");

    while (splited_input[i])
    {
        t_token *new_token = (t_token *)malloc(sizeof(t_token));
        if (!new_token)
            return (NULL);
        if (cstm_strcmp(splited_input[i], "|"))
			type = PIPE;
		else if (cstm_strcmp(splited_input[i], "<"))
			type = RED_IN;
        else if (cstm_strcmp(splited_input[i], ">"))
			type = RED_OUT;
        else if (cstm_strcmp(splited_input[i], ">>"))
            type = APPEND;
        else if (cstm_strcmp(splited_input[i], "<<"))
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
            if (splited_input[i + 1] && !cstm_strcmp(splited_input[i + 1],"|"))
			{
                new_token->value = ft_strdup(splited_input[i + 1]);
				i += 2;
			}
            else
			{
                new_token->value = NULL;
				i++;
			}
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
	/*print_token(head);*/
	if (!syntax_error(head))
		return (NULL);
	
    return (head);
}
