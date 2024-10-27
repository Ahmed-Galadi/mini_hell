/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 20:40:24 by agaladi           #+#    #+#             */
/*   Updated: 2024/10/08 17:21:27 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nbr_len(int nbr)
{
	int		count;

	count = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		count++;
	while (nbr)
	{
		count++;
		nbr /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*nbr_str;
	int		len_nbr;
	long	nbr;

	nbr = n;
	len_nbr = nbr_len(nbr);
	nbr_str = gc_malloc(len_nbr + 1, LOCAL);
	nbr_str[len_nbr] = '\0';
	if (nbr < 0)
	{
		nbr_str[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
	{
		nbr_str[0] = '0';
		return (nbr_str);
	}
	while (nbr)
	{
		nbr_str[--len_nbr] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (nbr_str);
}
