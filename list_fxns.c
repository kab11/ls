/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_fxns.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 17:02:02 by kblack            #+#    #+#             */
/*   Updated: 2019/02/09 19:32:34 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

	/* handle if you need to insert node at the head of the list*/
		//if new_node->name is < head->name 
		//new_node points to head
		//head points to new_node
		// printf("new_node: %s\n", new_node(av[i])->name);
	/* handle if you ned to insert node after the head */
		//if new_node needs to be inserted after head
		//traverse the linked list keeping track with 2 additional pointers
		//update trail 1st to point to cur and then update cur to next node in the list
		//when the insert location is found; new_node points to cur and trail points to the new_node

typedef struct s_ls
{
	char *name;
	int num;
	struct s_ls *next;
} t_ls;	

t_ls *new_node(char *name);

void add_info(t_ls *node)
{
	node->num = (rand() % (10 - 0 + 1) + 0);
}

t_ls *ls_init(int ac, char **av)
{
	t_ls *new_list;
	t_ls *cur;
	t_ls *trail;
	t_ls *node;
	int i;

	new_list = NULL;
	cur = NULL;
	trail = NULL;
	node = NULL;
	i = 0;
	/* handles if the list is empty*/
	while (++i < ac)
	{
		node = new_node(av[i]);

		add_info(node);
		if (new_list == NULL)
			new_list = node;
		else if (strcmp(node->name, new_list->name) <= 0)
		{
			node->next = new_list;
			new_list = node;
		}
		else
		{
			cur = new_list;
			while (cur->next != NULL && strcmp(node->name, cur->name) > 0)
			{
				trail = cur;
				cur = cur->next;
			}
			if (strcmp(node->name, cur->name) > 0)
				cur->next = node;
			else
			{
				trail->next = node;
				node->next = cur;
			}
		}
	}	
	return (new_list);
}

t_ls *new_node(char *name)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
	bzero(new_node, sizeof(t_ls));
	new_node->name = name;
	return (new_node);
}

void split_list(struct s_ls *source, struct s_ls **front, struct s_ls **back)
{
	struct s_ls *fast;
	struct s_ls *slow;

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

struct s_ls *sorted_merge(struct s_ls *a, struct s_ls *b)
{
	struct s_ls *result = NULL;

	if (a == NULL)
		return (b);
	else if (b == NULL)
		return (a);
	if (a->num <= b->num)
	{
		result = a;
		result->next = sorted_merge(a->next, b);
	}
	else 
	{
		result = b;
		result->next = sorted_merge(a, b->next);
	}
	return (result);
}

void printList(struct s_ls *node) 
{ 
	while(node!=NULL) 
	{ 
		printf("%s\t%d\n", node->name, node->num); 
		node = node->next; 
	} 
}

void merge_sort(struct s_ls **headRef)
{
	struct s_ls *head = *headRef;
	struct s_ls *a;
	struct s_ls *b;

	if ((head == NULL) || (head->next == NULL))
		return;
	split_list(head, &a, &b);

	merge_sort(&a);
	merge_sort(&b);

	*headRef = sorted_merge(a, b);
}

int main (int argc, char *argv[])
{
	struct s_ls *list;
	
	list = ls_init(argc, argv);
	printf("insert\n");
	merge_sort(&list);
	printf("merge\n");
	printList(list);
	return (0);
}
