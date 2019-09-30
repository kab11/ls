/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 01:14:59 by kblack            #+#    #+#             */
/*   Updated: 2019/03/05 22:37:54 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Merge sort function used when '-t' (sort by time modified) option it used
*/

void	split_list(t_info *source, t_info **front, t_info **back)
{
	t_info	*fast;
	t_info	*slow;

	if (source == NULL || source->next == NULL)
	{
		*front = source;
		*back = NULL;
	}
	else
	{
		slow = source;
		fast = source->next;
		while (fast)
		{
			fast = fast->next;
			if (fast)
			{
				slow = slow->next;
				fast = fast->next;
			}
		}
		*front = source;
		*back = slow->next;
		slow->next = NULL;
	}
}

t_info	*handle_time(t_info **ab, int x, t_info *result, int flags)
{
	t_info	*a;
	t_info	*b;

	a = ab[0];
	b = ab[1];
	if (x == 0)
	{
		result = a;
		result->next = sort_and_merge(a->next, b, flags);
	}
	else
	{
		result = b;
		result->next = sort_and_merge(a, b->next, flags);
	}
	return (result);
}

t_info	*sort_and_merge(t_info *a, t_info *b, int flags)
{
	t_info	*result;
	t_info	*ab[2];

	ab[0] = a;
	ab[1] = b;
	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (flags & OPT_t)
		result = handle_time(ab, ((a->int_mtime >= b->int_mtime) ? 0 : 1), result, flags);
	return (result);
}

void	sort_by_time(t_info **headref, int flags)
{
	t_info	*head;
	t_info	*a;
	t_info	*b;

	head = *headref;
	if ((head == NULL) || (head->next == NULL))
		return ;
	split_list(head, &a, &b);
	sort_by_time(&a, flags);
	sort_by_time(&b, flags);
	*headref = sort_and_merge(a, b, flags);
}

/*
** insert-sort that takes each new node and places it into a linked list
** in lexicographical order 
*/

t_info	*alpha_insert_sort(t_info *node, t_info *list)
{
	t_info	*cur;
	t_info	*trail;

	cur = list;
	if (list == NULL)
		list = node;
	else if (ft_strcmp(node->name, list->name) <= 0 && (node->next = list))
		list = node;
	else
	{
		while (cur->next != NULL && ft_strcmp(node->name, cur->name) > 0)
		{
			trail = cur;
			cur = cur->next;
		}
		if (ft_strcmp(node->name, cur->name) > 0)
			cur->next = node;
		else
		{
			trail->next = node;
			node->next = cur;
		}
	}
	return (list);
}
