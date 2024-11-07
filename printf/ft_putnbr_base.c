/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 04:50:59 by bzinedda          #+#    #+#             */
/*   Updated: 2024/06/28 02:14:42 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_base(unsigned long nbr,
						int base_value, char *base_rep, int fd)
{
	if ((nbr / base_value) != 0)
	{
		ft_putnbr_base(nbr / base_value, base_value, base_rep, fd);
		ft_putchar(base_rep[nbr % base_value], fd);
	}
	else
		ft_putchar(base_rep[nbr % base_value], fd);
}
