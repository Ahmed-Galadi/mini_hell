/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 04:49:26 by bzinedda          #+#    #+#             */
/*   Updated: 2024/06/23 16:15:21 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int nbr, int fd)
{
	long	n;

	n = nbr;
	if (n < 0)
	{
		n = -n;
		ft_putchar('-', fd);
	}
	if (n < 10)
		ft_putchar(n + 48, fd);
	else
	{
		ft_putnbr(n / 10, fd);
		ft_putnbr(n % 10, fd);
	}
}
