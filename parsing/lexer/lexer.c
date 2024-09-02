/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 15:17:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 21:47:51 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	args_size(t_token *token)
{
	(void)token;
	return (1);
}

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
	return (NULL);
}