/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 06:06:30 by bzinedda          #+#    #+#             */
/*   Updated: 2024/06/23 16:21:28 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(unsigned long p, int fd)
{
	int	size;

	size = 0;
	ft_putstr("0x", fd);
	ft_putnbr_base(p, 16, "0123456789abcdef", fd);
	size += ft_ptr_len(p);
	return (size + 2);
}
