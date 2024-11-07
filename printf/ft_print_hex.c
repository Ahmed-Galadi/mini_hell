/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 06:07:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/06/23 16:18:16 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(unsigned int nbr, char const *format, int fd)
{
	int	size;

	size = 0;
	if (nbr == 0)
		size++;
	if (*format == 'x')
		ft_putnbr_base(nbr, 16, "0123456789abcdef", fd);
	if (*format == 'X')
		ft_putnbr_base(nbr, 16, "0123456789ABCDEF", fd);
	while (nbr != 0)
	{
		nbr = nbr / 16;
		size++;
	}
	return (size);
}
