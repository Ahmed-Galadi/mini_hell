/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 01:51:35 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/22 10:38:08 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_token	*token_init(char **s_input, int *index)
{
	
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
	i = 0;
	while (splited_input[i])
		
}