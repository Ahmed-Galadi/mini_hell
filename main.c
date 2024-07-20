/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 00:31:36 by agaladi           #+#    #+#             */
/*   Updated: 2024/07/20 09:20:58 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"


int main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;
	char *input;
	while (1)
	{
		input = readline("\n$> ");
		if (ft_strcmp(input, "exit"))
			exit(0);
		if (ft_strcmp(input, ""))
			write(1, "", 0);
		if (input)
			ft_putstr(format(input));
	}
	return (0);
}