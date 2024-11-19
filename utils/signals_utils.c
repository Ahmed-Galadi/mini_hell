/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 11:40:16 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/19 04:04:54 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	g_signal_received = 0;

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
	remove_abg_command(&com);
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

void	disable_echoctl(struct termios *term)
{
	if (isatty(STDIN_FILENO) && tcsetattr(STDIN_FILENO, TCSANOW, term) == -1)
	{
		perror("tcsetattr");
		gc_free_all(LOCAL);
		gc_free_all(GLOBAL);
		exit(EXIT_FAILURE);
	}
}

void	handle_sig(int sig)
{
	(void) sig;
	g_signal_received = 1;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	signals_init(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_sig);
	signal(SIGQUIT, SIG_IGN);
}
