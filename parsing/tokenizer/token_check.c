/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:42:54 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 18:50:23 by agaladi          ###   ########.fr       */
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
