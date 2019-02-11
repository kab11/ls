/*Insert a node at the beginning*/
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct		node_t
{
	int				content;
	size_t			content_size;
	struct node_t 	*next;
}					t_list;

void *ft_lstadd_begin(t_list **head, int new_data)
{
	t_list *new;

	new = (t_list *)malloc(sizeof(t_list));
	new->content = new_data;
	new->next = NULL;
	if (*head != NULL)
		new->next = *head;
	*head = new;
	return (0);
}

void Print(t_list *head)
{
    t_list *current_node = head;
    printf("List is: \n");
   	while ( current_node != NULL) 
   	{
        printf("%d ", current_node->content);
        current_node = current_node->next;
    }
    printf("\n");
}

int main(int argc, char **argv)
{
	t_list *head;

	head = NULL;
	printf("How many numbers?\n");
	int n, i, x;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		printf("Enter the number\n");
		scanf("%d", &x);
		ft_lstadd_begin(&head, x);
		Print(head);
	}
	return (0);
}