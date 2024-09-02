/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 06:57:01 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/02 20:16:43 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;
	char			converted_c;

	if (!s)
		return (NULL);
	converted_c = (char) c;
	i = 0;
	while (s[i])
	{
		if (s[i] == converted_c)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == converted_c)
		return ((char *) &s[i]);
	return (NULL);
}
