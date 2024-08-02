/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:42:54 by agaladi           #+#    #+#             */
/*   Updated: 2024/08/02 03:21:00 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_quote(char *str)
{
	return (ft_strcmp(str, "\"") || ft_strcmp(str, "\'"));
}

int	is_rederection(char *str)
{
	return (ft_strcmp(str, "<<") || ft_strcmp(str, ">>")
	|| ft_strcmp(str, ">") || ft_strcmp(str, "<"));
}
