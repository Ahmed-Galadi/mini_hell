/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:40:34 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 22:17:05 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error(void)
{
	ft_putstr("*ERROR!*\n");
}

void	*error_handler(t_token *head, int *exit_status)
{
	if (!syntax_error(head))
	{
		*exit_status = 258;
		return (NULL);
	}
	if (syntax_error(head) == -1)
	{
		*exit_status = 1;
		printf(RED BOLD"Error:"RESET PINK" ambiguous redirect\n"RESET);
		return (NULL);
	}
	return ("WORKING");
}
