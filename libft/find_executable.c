/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_executable.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 00:08:16 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/07 18:52:22 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_to_array(t_env *env)
{
    int count = 0;
    t_env *temp = env;
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    char **env_array = gc_malloc(sizeof(char*) * (count + 1), LOCAL);
    if (!env_array)
        return NULL;

    int i = 0;
    while (env)
    {
        env_array[i] = gc_malloc(ft_strlen(env->key) + ft_strlen(env->value) + 2, LOCAL);
        if (!env_array[i])
        {
            return (gc_free_all(LOCAL), NULL);
        }
        sprintf(env_array[i], "%s=%s", env->key, env->value);
        env = env->next;
        i++;
    }
    env_array[i] = NULL;
    return env_array;
}


char	*join_path(char *path, char *cmd)
{
	char	*with_back_slash;
	char	*full_path;

	if (!path || !cmd)
		return (NULL);
	with_back_slash = "/";
	with_back_slash = ft_strjoin(path, with_back_slash, LOCAL);
	full_path = ft_strjoin(with_back_slash, cmd, LOCAL);
	return (full_path);
}

char	*ft_getenv(char **p_env)
{
	if (!p_env)
		return (NULL);
	while (*p_env)
	{
		if (ft_strncmp(*p_env, "PATH", 4) == 0)
			return (*p_env);
		p_env++;
	}
	return (NULL);
}

static char	*ft_check_for_unset_path(char *cmd, char **p_env)
{
	char	*path_env;
	char	*full_path;

	path_env = ft_getenv(p_env);
	if (!path_env)
	{
		full_path = ft_strchr(cmd, '/');
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
	}
	return (path_env);
}

char	*find_command(char *cmd, char **p_env)
{
	char	**tokens;
	char	*path_env;
	char	*path_copy;
	char	*full_path;

	path_env = ft_check_for_unset_path(cmd, p_env);
	path_copy = ft_strdup(path_env);
	if (!path_copy)
		return (NULL);
	tokens = cstm_split(path_copy, ":");
	while (*tokens)
	{
		if (ft_strchr(cmd, '/') == NULL)
			full_path = join_path(*tokens, cmd);
		else
			full_path = ft_strdup(cmd);
		if (!full_path)
			return (NULL);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		tokens++;
	}
	return (NULL);
}