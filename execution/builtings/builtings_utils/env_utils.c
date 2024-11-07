/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 15:44:48 by bzinedda          #+#    #+#             */
/*   Updated: 2024/11/06 07:52:08 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

int	ft_check_key(const char *arg, const char *value)
{
	size_t	i;

	if (!(ft_isalpha(arg[0]) || arg[0] == '_'))
		return (0);
	if (!arg[1])
		return (1);
	i = 0;
	while (++i < ft_strlen(arg) - 1)
		if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
			return (0);
	if (arg[i] == '+')
	{
		if (value)
			return (2);
		return (0);
	}
	if (!(ft_isalnum(arg[i]) || arg[i] == '_'))
		return (0);
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
	char	*value;
	int		op;

	key = extract_key(arg);
	value = extract_value(arg);
	op = ft_check_key(key, value);
	if (key && !op)
	{
		ft_printf(2, "Error: " "export:"\
			" \'%s\': not a valid identifier\n",
			arg);
		return ("Invalid");
	}
	if (op == 1)
		return ("create");
	else if (op == 2)
		return ("append");
	return (NULL);
}
