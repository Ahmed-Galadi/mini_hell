/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:44:48 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/19 21:46:37 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_check_key(const char *arg)
{
	int	i;

	if (!((arg[0] >= 'a' && arg[0] <= 'z') || (arg[0] >= 'A' && arg[0] <= 'Z')
			|| arg[0] == '_'))
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (2);
		if (arg[i] == '+' && arg[i + 1] == '\0')
			return (0);
		if (!((arg[i] >= 'a' && arg[i] <= 'z') || (arg[i] >= 'A'
					&& arg[i] <= 'Z') || (arg[i] >= '0' && arg[i] <= '9')
				|| arg[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

char	*ft_get_var_value(t_env *env, const char *key)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0 && curr->value)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

char	*get_operation(char *arg)
{
	char	*key;

	key = extract_key(arg);
	if (key && !ft_check_key(key))
	{
		printf(BOLD RED "Error: " RESET PINK "export:"\
			RESET " \'%s\': not a valid identifier\n",
			arg);
		return ("Invalid");
	}
	if (ft_check_key(arg) == 1)
		return ("create");
	else if (ft_check_key(arg) == 2)
		return ("append");
	else if (first_occurence(arg, '=')
		&& arg[first_occurence(arg, '=') - 1] == '+')
		return ("append");
	else if (first_occurence(arg, '=')
		&& arg[first_occurence(arg, '=') - 1] != '+')
		return ("create");
	return (NULL);
}
