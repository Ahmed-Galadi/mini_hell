/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 05:23:12 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/20 02:59:48 by agaladi          ###   ########.fr       */
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
	{
		if (data->pwd)
			return (printf("%s\n", data->pwd), 0);
		return (perror("getcwd"), 1);
	}
	return (0);
}
