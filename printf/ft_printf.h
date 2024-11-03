/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 18:20:49 by bzinedda          #+#    #+#             */
/*   Updated: 2024/06/28 02:13:12 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int		ft_print_un_nbr(unsigned int nbr, int fd);
int		ft_ptr_len(unsigned long ptr);
int		ft_print_ptr(unsigned long p, int fd);
int		ft_print_hex(unsigned int nbr, char const *format, int fd);
int		ft_print_nbr(int nb, int fd);
int		ft_print_str(char *s, int fd);
int		ft_print_chr(char c, int fd);
int		ft_print_percentage(int fd);
int		is_space(char c);
int		ft_printf(int fd, char const *format, ...);
void	ft_putnbr_base(unsigned long nbr, int base_value,
			char *base_rep, int fd);
void	ft_putstr(char *s, int fd);
void	ft_putchar(char c, int fd);
void	ft_putnbr(int nbr, int fd);
size_t	ft_strlen(const char *str);

#endif
