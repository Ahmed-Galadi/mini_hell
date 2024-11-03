/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:40:16 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/03 21:51:41 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_exit_status = 0;

t_com	*set_command(t_shell *data_config, char *cmd_line_args)
{
	t_token	*token;
	t_com	*com;

	expand(&cmd_line_args, data_config->env, &data_config->exit_status, false);
	token = tokenizer(cmd_line_args,
			data_config->env, &(data_config->exit_status));
	if (!token)
		return (NULL);
	com = create_cmds(token);
	if (!data_config || !cmd_line_args)
		return (NULL);
	data_config->command = com;
	return (com);
}

int	is_spaces(char *str)
{
	int	i;

	if (!*str)
		return (1);
	i = 0;
	while (str[i])
	{
		if (str[i] != ' '
			&& str[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

void	disable_echo(struct termios term)
{
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
	{
		perror("tcgetattr");
		gc_free_all(LOCAL);
		gc_free_all(GLOBAL);
		exit(EXIT_FAILURE);
	}
}

static void	handle_sig(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_status = 1;
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	signals_init(t_shell *data, struct termios term)
{
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
	if (g_exit_status == 1)
	{
		data->trap_sigint = 1;
		data->exit_status = 1;
	}
	g_exit_status = 0;
}
