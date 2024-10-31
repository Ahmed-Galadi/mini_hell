/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 05:23:12 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/31 15:41:19 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_pwd(t_shell *data)
{
	char	buffer[1024];

	if (!data)
		return (127);
	if (getcwd(buffer, sizeof(buffer)))
		printf("%s\n", buffer);
	else
		return (perror("getcwd"), 1);
	return (0);
}
