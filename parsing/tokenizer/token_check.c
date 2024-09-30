/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:42:54 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 22:17:05 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quote(char *str)
{
	return (cstm_strcmp(str, "\"") || cstm_strcmp(str, "\'"));
}

int	is_rederection(char *str)
{
	return (cstm_strcmp(str, "<<") || cstm_strcmp(str, ">>")
		|| cstm_strcmp(str, ">") || cstm_strcmp(str, "<"));
}

/*bool	has_quotes(char *str)*/
/*{*/
/*	int	i;*/
/**/
/*	i = -1;*/
/*	while (str[++i])*/
/*		if (str[i] == '\"' || str[i] == '\'')*/
/*			return (true);*/
/*	return (false);*/
/*}*/
/**/
/*// Get token type function*/
/*e_tokenType	get_token_type(char *str)*/
/*{*/
/*	if (cstm_strcmp(str, "|"))*/
/*		return (PIPE);*/
/*	if (cstm_strcmp(str, "<"))*/
/*		return (RED_IN);*/
/*	if (cstm_strcmp(str, ">"))*/
/*		return (RED_OUT);*/
/*	if (cstm_strcmp(str, ">>"))*/
/*		return (APPEND);*/
/*	if (cstm_strcmp(str, "<<"))*/
/*		return (HERE_DOC_EXP);*/
/*	return (COMMAND);*/
/*}*/

