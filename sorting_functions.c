/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 01:14:59 by kblack            #+#    #+#             */
/*   Updated: 2019/02/22 01:15:06 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* listing by time modified */
/* using merge sort: 
	1) if head is NULL or if there is only 1 element then return
	2) else divide the linked list into 2 halves
	3) sort the 2 halves a and b
	4) merge the sorted a and b andupdate the head pointer using the pointer to head */

void split_list(t_info *source, t_info **front, t_info **back)
{
	t_info *fast;
	t_info *slow;

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

t_info *sort_and_merge(t_info *a, t_info *b)
{
	t_info *result;

	result = NULL;
	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->int_mtime >= b->int_mtime)
	{
		result = a;
		result->next = sort_and_merge(a->next, b);
	}
	else
	{
		result = b;
		result->next = sort_and_merge(a, b->next);
	}
	return (result);
}

void sort_by_time(t_info **headRef)
{
	t_info *head = *headRef;
	t_info *a;
	t_info *b;

	if ((head == NULL) || (head->next == NULL))
		return;
	split_list(head, &a, &b);

	sort_by_time(&a);
	sort_by_time(&b);
	*headRef = sort_and_merge(a, b);
}