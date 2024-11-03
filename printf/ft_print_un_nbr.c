/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_un_nbr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 04:50:23 by bzinedda          #+#    #+#             */
/*   Updated: 2024/06/23 16:20:44 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_un_nbr(unsigned int n, int fd)
{
	int	size;

	size = 0;
	if (n == 0)
		size = 1;
	if (n < 10)
		ft_putchar(n + 48, fd);
	else
	{
		ft_putnbr(n / 10, fd);
		ft_putnbr(n % 10, fd);
	}
	while (n != 0)
	{
		n /= 10;
		size++;
	}
	return (size);
}
