/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 01:14:59 by kblack            #+#    #+#             */
/*   Updated: 2019/02/26 21:53:26 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
**	Merge sort function used when '-t' (sort by time modified) option it used
*/


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

// void swap(t_info **prev, t_info **n1, t_info **n2, t_info **head)
// {
// 	if (*prev != NULL)
// 	{
// 		(*prev)->next = (*n2);
// 		(*n1)->next = (*n2)->next;
// 		(*n2)->next = (*n1);
// 	}
// 	else
// 	{
// 		(*n1)->next = (*n2)->next;
// 		(*n2)->next = (*n1);
// 		(*n1) = (*n2);
// 		*head = *n2;
// 	}
// }

// void sort_by_time(t_info **list)
// {
// 	int i;
// 	t_info *cur;
// 	t_info *trail;
// 	t_info *next;

// 	i = 1;
// 	cur = *list;
// 	next = cur->next;
// 	trail = NULL;
// 	if (list == NULL)
// 		return ; 
// 	while (cur->next != NULL)
// 	{
// 		if (cur->int_mtime > cur->next->int_mtime)
// 		{
// 			swap(&trail, &cur, &next, list);
// 			cur = *list;
// 			next = cur->next;
// 			trail = NULL;
// 			continue;
// 		}
// 		trail =cur;
// 		cur = cur->next;
// 		if (cur != NULL)
// 			next = cur->next;
// 	}
// }


t_info *alpha_insert_sort(t_info *node, t_info *list)
{
	t_info *cur;
	t_info *trail;

	cur = list;
	if (list == NULL)
		list = node; 
	else if (ft_strcmp(node->name, list->name) <= 0)
	{
		node->next = list;
		list = node;
	}
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
