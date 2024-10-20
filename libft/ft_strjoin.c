/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 06:55:10 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/07 18:34:46 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <libc.h>

char	*ft_strjoin(char const *s1, char const *s2, t_type type)
{
	size_t	i;
	size_t	j;
	char	*strjoin;
	size_t	leng_s1;
	size_t	leng_s2;

	if (!s1 && !s2)
		return (NULL);
	leng_s1 = ft_strlen(s1);
	leng_s2 = ft_strlen(s2);
	strjoin = (char *)gc_malloc(leng_s1 + leng_s2 + 1, type);
	if (!strjoin)
		return (NULL);
	i = 0;
	j = 0;
	while (i < leng_s1)
		strjoin[j++] = s1[i++];
	i = 0;
	while (i < leng_s2)
		strjoin[j++] = s2[i++];
	strjoin[j] = '\0';
	return (strjoin);
}
