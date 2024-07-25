/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:51:35 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/25 22:11:58 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_token	*token_init(char **s_input)
{
	t_token	*to_fill;
	e_tokenType	type;
	static int	i;

	if (!s_input[i])
		to_fill = NULL;
	to_fill = (t_token *)malloc(sizeof(t_token));
	if (!to_fill || (is_rederection(s_input[i]) && s_input[i + 1] == NULL))
		error();
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
	to_fill->type = type;
	if (type == COMMAND || type == PIPE)
	{
		to_fill->value = ft_strdup(s_input[i]);
		i++;	
	}
	else
	{
		to_fill->value = ft_strdup(s_input[i + 1]);
		i += 2;
	}
	to_fill->next = NULL;
	return (to_fill);
}

// t_token *tokenizer(char *input)
// {
// 	t_token	**output;
// 	t_token	*tmp;
// 	char	*formated_input;
// 	char	**splited_input;
// 	e_tokenType	type;
// 	int		i;

// 	formated_input = format(input);
// 	switch_char(&formated_input, ' ', -1);
// 	splited_input = ft_split(formated_input, ' ');
// 	if (ft_strcmp(splited_input[0], "|"))
// 		error();
// 	i = 0;
// 	output = NULL;
// 	*output = NULL;
// 	tmp = *output;
// 	while (splited_input[i])
// 	{
// 		tmp = (t_token *)malloc(sizeof(t_token));
// 		if (!tmp || (is_rederection(splited_input[i]) && splited_input[i + 1] == NULL))
// 			error();
// 		if (ft_strcmp(splited_input[i], "|"))
// 			type = PIPE;
// 		else if (ft_strcmp(splited_input[i], "<"))
// 			type = RED_IN;
// 		else if (ft_strcmp(splited_input[i], ">"))
// 			type = RED_OUT;
// 		else if (ft_strcmp(splited_input[i], ">>"))
// 			type = APPEND;
// 		else if (ft_strcmp(splited_input[i], "<<"))
// 			type = HERE_DOC;
// 		else
// 			type = COMMAND;
// 		tmp->type = type;
// 		if (type == COMMAND || type == PIPE)
// 		{
// 			tmp->value = ft_strdup(splited_input[i]);
// 			i++;	
// 		}
// 		else
// 		{
// 			tmp->value = ft_strdup(splited_input[i + 1]);
// 			i += 2;
// 		}
// 		tmp = tmp->next;
// 	}
// 	printf("%d \n", (*output)->type);
// 	return (*output);
// }

t_token *tokenizer(char *input)
{
    t_token *output = NULL;
    t_token *tmp = NULL;
    t_token *current = NULL;
    char *formated_input;
    char **splited_input;
    e_tokenType type;
    int i = 0;

    formated_input = format(input);
    switch_char(&formated_input, ' ', -1);
    splited_input = ft_split(formated_input, ' ');

    if (ft_strcmp(splited_input[0], "|"))
        error();

    while (splited_input[i])
    {
        tmp = (t_token *)malloc(sizeof(t_token));
        if (!tmp || (is_rederection(splited_input[i]) && splited_input[i + 1] == NULL))
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

        tmp->type = type;
        if (type == COMMAND || type == PIPE)
        {
            tmp->value = ft_strdup(splited_input[i]);
            i++;
        }
        else
        {
            tmp->value = ft_strdup(splited_input[i + 1]);
            i += 2;
        }
        tmp->next = NULL;
        if (output == NULL)
            output = tmp;
        else
            current->next = tmp;
        current = tmp;
    }
    return (output);
}
