/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:27:24 by bzinedda          #+#    #+#             */
/*   Updated: 2024/08/04 05:32:20 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


// NOTE 
// export
// var=value, if value is null do not print in env. do not update value.
// var+=value, joins value with the previous one.
// value. alpha num only and '_' and in one case (var+=value).

int ft_env(t_env *env)
{
	ft_printf_envs(env);
	return (0);
}
