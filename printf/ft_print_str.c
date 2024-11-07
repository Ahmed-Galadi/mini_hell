/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 06:08:34 by bzinedda          #+#    #+#             */
/*   Updated: 2024/06/23 16:09:44 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_str(char *s, int fd)
{
	char	*null;

	null = "(null)";
	if (!s)
	{
		ft_putstr(null, fd);
		return (ft_strlen(null));
	}
	ft_putstr(s, fd);
	return (ft_strlen(s));
}
