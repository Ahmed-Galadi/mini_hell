/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 02:42:54 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/26 17:48:17 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../main.h"

int	is_quote(char *str)
{
	return (ft_strcmp(str, "\"") || ft_strcmp(str, "\'"));
}

int	is_rederection(char *str)
{
	return (ft_strcmp(str, "<<") || ft_strcmp(str, ">>")
	|| ft_strcmp(str, ">") || ft_strcmp(str, "<"));
}
