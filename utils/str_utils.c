/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 06:46:44 by agaladi           #+#    #+#             */
/*   Updated: 2024/09/02 19:25:37 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../main.h"

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

int	ft_strlen(char *str)
{
	int		count;

	count = 0;
	while (str[count])
		count++;
	return (count);
}

int	cstm_strcmp(char *str1, char *str2)
{
	int		i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strdup(char *str)
{
	char	*output;
	int		size;
	int		i;

	size = ft_strlen(str) + 1;
	output = (char *)malloc(size);
	if (!output)
		error();
	i = 0;
	while (str[i])
	{
		output[i] = str[i];
		i++;
	}
	output[i] = '\0';
	return (output);
}



char	*ft_strjoin(char *str1, char *str2)
{
	char	*output;
	int		size;
	int		i;
	int		j;

	if (!str1)
		return (ft_strdup(str2));
	size = ft_strlen(str1) + ft_strlen(str1) + 1;
	output = (char *)malloc(size);
	if (!output)
		error();
	i = 0;
	j = 0;
	while (str1[i])
		output[j++] = str1[i++];
	i = 0;
	while (str2[i])
		output[j++] = str2[i++];
	output[j] = '\0';
	return (output);
}
