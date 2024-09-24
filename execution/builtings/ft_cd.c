/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:49:02 by bzinedda          #+#    #+#             */
/*   Updated: 2024/09/16 14:27:03 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_env_var(t_env *env, const char *var_key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, var_key, ft_strlen(var_key) + 1) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

int	change_directory(const char *path, t_shell *data)
{
    char cwd[1024];

    if (chdir(path) != 0)
	{
        printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		data->pwd = ft_strdup(cwd);
		if (data->pwd)
			return (0);
	}
	return (1);
}
	
int		ft_cd(char **args, t_shell *data)
{
	args++;
	if (!(*args))
	{
		data->pwd = ft_get_env_var(data->env, "HOME");
		if (!data->pwd)
			return (printf("Error: cd: HOME not set\n"), 1);
	}
	return (change_directory(args[0], data));
}
