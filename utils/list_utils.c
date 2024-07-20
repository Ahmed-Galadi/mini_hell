/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 05:39:53 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/16 06:19:23 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	add_lstback(t_opperator *operators, t_opperator *to_add)
{
	t_opperator *current;

	current = operators;
	if (!operators)
		operators = to_add;
	else
	{
		while (current->next)
			current = current->next;
		current->next = to_add;
	}
}
