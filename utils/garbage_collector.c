/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bzinedda <bzinedda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 16:08:22 by bzinedda          #+#    #+#             */
/*   Updated: 2024/10/31 16:08:24 by bzinedda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_init_memos(t_memory_list **local_mem, t_memory_list **global_mem)
{
	if (!local_mem || !global_mem)
		return (NULL);
	if (!(*local_mem))
	{
		(*local_mem) = malloc(sizeof(t_memory_list));
		if (!(*local_mem))
			return (perror("malloc"), NULL);
		(*local_mem)->head = NULL;
		(*local_mem)->tail = NULL;
	}
	if (!(*global_mem))
	{
		(*global_mem) = malloc(sizeof(t_memory_list));
		if (!(*global_mem))
			return (perror("malloc"), NULL);
		(*global_mem)->head = NULL;
		(*global_mem)->tail = NULL;
	}
	return ("Success");
}

static t_memory_list	*get_memory_list(t_type type, int flag)
{
	static t_memory_list	*local_mem;
	static t_memory_list	*global_mem;
	t_memory_list			*tmp;

	if (!ft_init_memos(&local_mem, &global_mem))
		return (NULL);
	if (type == LOCAL)
	{
		tmp = local_mem;
		if (flag)
			local_mem = NULL;
		return (tmp);
	}
	else
	{
		tmp = global_mem;
		if (flag)
			global_mem = NULL;
		return (tmp);
	}
}

void	add_memory(void *ptr, t_type type)
{
	t_node			*new_node;
	t_memory_list	*memory_list;

	memory_list = get_memory_list(type, 0);
	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node || !memory_list)
		return (perror("malloc"));
	new_node->ptr = ptr;
	new_node->next = NULL;
	if (memory_list->tail)
		memory_list->tail->next = new_node;
	else
		memory_list->head = new_node;
	memory_list->tail = new_node;
}

void	*gc_malloc(size_t size, t_type type)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (perror("malloc"), NULL);
	add_memory(ptr, type);
	return (ptr);
}

void	gc_free_all(t_type type)
{
	t_node			*current;
	t_node			*tmp;
	t_memory_list	*memory_list;

	memory_list = get_memory_list(type, 1);
	current = memory_list->head;
	while (current)
	{
		if (current->ptr)
		{
			free(current->ptr);
			current->ptr = NULL;
		}
		tmp = current;
		current = current->next;
		free(tmp);
	}
	free(memory_list);
}
