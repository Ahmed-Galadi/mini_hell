/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 16:49:02 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/07 19:21:07 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_get_env_var(t_env *env, const char *var_key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, var_key, ft_strlen(var_key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void	change_directory(const char *path, t_data *data, int *ret_val)
{
    char cwd[1024];

    if (chdir(path) != 0) {
        *ret_val = -1;
        printf("cd: %s: No such file or directory\n", path);
    }
	else
	{
        if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
            data->pwd = ft_strdup(cwd);
            if (data->pwd == NULL)
                *ret_val = -1;
			else
				*ret_val = 0;
        }
		else
            *ret_val = -1;
    }
}
	
int		ft_cd(char **args, t_data *data, int *ret_val)
{
	args++;
	if (!(*args))
	{
		data->pwd = ft_get_env_var(data->env, "HOME");
	}
	else
	{
		change_directory(args[0], data, ret_val);
	}
	return (0);
}
