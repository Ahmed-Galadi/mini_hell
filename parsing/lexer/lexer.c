/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/02 06:59:10 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

t_com	*new_com(t_token *token)
{
	char	**out_args;
	t_opp	*out_opp;
	int		i;
	
	out_args = (char **)malloc(args_size(token));
	if (!out_args)
		return (NULL);
	i = 0;
	out_opp = NULL;
	while (token)
	{
		if (token->type == COMMAND || token->type == EXPAND)
		{
			// TO DO
		}
		token = token->next;
	}
}