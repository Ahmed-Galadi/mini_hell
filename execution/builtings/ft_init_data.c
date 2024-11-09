/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 05:26:20 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/08 11:53:13 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	increment_shlvl(t_shell *sh)
{
	int		shell_lvl;
	char	*shlvl;

	if (sh && sh->env)
	{
		shlvl = ft_get_var_value(sh->env, "SHLVL");
		if (!shlvl)
			(1 && (ft_set_vars(&sh->env, "SHLVL", "")),
				(ft_set_vars(&sh->export, "SHLVL", "")));
		else
		{
			if (*shlvl == '\0')
				(1 && (ft_set_vars(&sh->env, "SHLVL", "1")),
					(ft_set_vars(&sh->export, "SHLVL", "1")));
			else if (ft_atoi(shlvl) == 999)
				(1 && (ft_set_vars(&sh->env, "SHLVL", "")),
					(ft_set_vars(&sh->env, "SHLVL", "")));
			else
			{
				shell_lvl = ft_atoi(shlvl) + 1;
				(1 && (ft_set_vars(&sh->env, "SHLVL", ft_itoa(shell_lvl))),
					(ft_set_vars(&sh->export, "SHLVL", ft_itoa(shell_lvl))));
			}
		}
	}
}

int	init_shell_data_config(t_shell *data, char **envp)
{
	char	cwd[1024];

	data->exit_status = 0;
	data->heredoc_count = 0;
	data->heredoc_index = 0;
	data->command = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		data->pwd = ft_strdup(getcwd(cwd, sizeof(cwd)));
	else
		perror("getcwd failed");
	if ((!*envp))
		(1 && (data->env = create_mini_env()),
			(data->export = create_mini_env()));
	else
	{
		data->env = init_env(envp);
		if (!data->env)
			return (1);
		data->export = init_env(envp);
		if (!data->export)
			return (1);
		increment_shlvl(data);
	}
	return (1);
}
