/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 01:14:55 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/19 04:04:36 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_signal_received;

void	init_prompt_msgs(t_msgs *prompt_data)
{
	prompt_data->prompt_msg1 = ft_strdup("\001"F_COLOR"\002 \001"RESET"\002" \
"\001"YELLOW"\002 ┄─━࿅༻  \001"RESET ORANGE BOLD"\002");
	prompt_data->prompt_msg2 = ft_strdup("\001"RESET"\002" \
"\001"YELLOW"\002༺  ࿅━─┄\n\001"RESET"\002");
	prompt_data->valid_arrow = ft_strdup("\001"GREEN_FG"\002❱ \001"RESET"\002");
	prompt_data->unvalid_arrow = ft_strdup("\001"RED"\002❱ \001"RESET"\002");
}

char	*simple_pwd(char *pwd, char *home)
{
	char	*rest_path;
	char	*simplified;
	int		len;

	if (!home)
		return (pwd);
	len = ft_strlen(home);
	if (ft_strncmp(pwd, home, ft_strlen(home)))
		return (pwd);
	rest_path = ft_substr(pwd, len, ft_strlen(pwd) - len);
	simplified = ft_strjoin("~", rest_path, GLOBAL);
	return (simplified);
}

char	*prompt(t_shell *data)
{
	t_msgs	*prompt_data;
	char	*cwd;
	char	*output;
	t_env	*tmp;

	prompt_data = (t_msgs *)gc_malloc(sizeof(t_msgs), LOCAL);
	if (!prompt_data)
		return (NULL);
	init_prompt_msgs(prompt_data);
	output = NULL;
	output = ft_strjoin(output, prompt_data->prompt_msg1, GLOBAL);
	(1 && (tmp = data->env), (cwd = data->pwd));
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "HOME"))
			cwd = simple_pwd(cwd, tmp->value);
		tmp = tmp->next;
	}
	output = ft_strjoin(output, cwd, GLOBAL);
	output = ft_strjoin(output, prompt_data->prompt_msg2, GLOBAL);
	if (data->exit_status != 0)
		output = ft_strjoin(output, prompt_data->unvalid_arrow, GLOBAL);
	else
		output = ft_strjoin(output, prompt_data->valid_arrow, GLOBAL);
	return (output);
}
