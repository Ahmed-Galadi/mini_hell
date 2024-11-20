/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_herdc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:50:54 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/20 02:48:55 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_signal_received;

void	rm_heredoc_files(t_shell *data)
{
	int		file_index;

	file_index = 0;
	while (data->heredoc_files[file_index])
	{
		if (g_signal_received && data->heredoc_files[file_index])
			unlink(data->heredoc_files[file_index]);
		file_index++;
	}
}

void	heredoc_count_check(int count)
{
	if (count > 16)
	{
		printf("Error: maximum here-document count exceeded\n");
		exit(2);
	}
}

void	open_tty(void)
{
	if (open("/dev/tty", O_RDONLY) == -1)
	{
		perror("open");
		exit (1);
	}
}
