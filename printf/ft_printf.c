/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 22:19:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/06/28 00:41:01 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_handle_formats(char const *format, va_list args, int fd)
{
	int	size;

	size = 0;
	if (*format == 's')
		size += ft_print_str(va_arg(args, char *), fd);
	else if (*format == 'c')
		size += ft_print_chr(va_arg(args, int), fd);
	else if ((*format == 'i') || (*format == 'd'))
		size += ft_print_nbr(va_arg(args, int), fd);
	else if ((*format == 'x') || (*format == 'X'))
		size += ft_print_hex(va_arg(args, unsigned int), format, fd);
	else if (*format == 'p')
		size += ft_print_ptr(va_arg(args, unsigned long), fd);
	else if (*format == 'u')
		size += ft_print_un_nbr(va_arg(args, unsigned int), fd);
	else if (*format == '%')
		size += ft_print_percentage(fd);
	else
		size += ft_print_chr(*format, fd);
	return (size);
}

int	ft_printf(int fd, char const *format, ...)
{
	va_list	args;
	int		size;

	size = 0;
	if (!format || write (1, NULL, 0) == -1)
		return (-1);
	va_start(args, format);
	while (*format != '\0')
	{
		if (*format == '%' && is_space(*(format + 1)))
			break ;
		if (*format == '%' && *(format + 1) == 0)
			break ;
		if (*format == '%')
		{
			size += ft_handle_formats(format + 1, args, fd);
			format++;
		}
		else
			size += ft_print_chr(*format, fd);
		format++;
	}
	va_end(args);
	return (size);
}
