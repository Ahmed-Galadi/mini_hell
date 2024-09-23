/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-yaqi <yel-yaqi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:08:20 by mrezki            #+#    #+#             */
/*   Updated: 2024/08/07 11:25:16 by yel-yaqi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = strlen(src);
	if (dstsize != 0)
	{
		while (src[i] && i < dstsize - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	lendst;
	size_t	lensrc;
	size_t	i;

	if (dst == NULL && dstsize == 0)
		return (0);
	lendst = strlen(dst);
	lensrc = strlen(src);
	if (dstsize <= lendst || dstsize == 0)
		return (lensrc + dstsize);
	else
	{
		i = 0;
		while (src[i] && lendst + 1 + i < dstsize)
		{
			dst[lendst + i] = src[i];
			i++;
		}
		dst[lendst + i] = '\0';
	}
	return (lendst + lensrc);
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		len1;
	int		len2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (!s1 && s2)
		return ((char *)s2);
	len1 = strlen(s1);
	len2 = strlen(s2);
	ptr = malloc(sizeof(char) * len1 + len2 + 1);
	if (!ptr)
		return (NULL);
	ft_strlcpy(ptr, s1, len1 + 1);
	ft_strlcat(ptr, s2, len1 + len2 + 1);
	return (ptr);
}
