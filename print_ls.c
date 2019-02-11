/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:48:37 by kblack            #+#    #+#             */
/*   Updated: 2019/02/08 14:48:49 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Need to create a linked list of structures that can each store infomation about
 * each file in the current directory:
 * 1) name 							7) file mode 	
 * 2) number of links 				8) owner name
 * 3) group name 					9) # of bytes 	
 * 4) abbreviated month 			10) DoM file was last modified
 * 5) hour file was las modified 	11) minute last modified 	
 * 6) pathname
*/

t_ls *new_node(char *name)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
	ft_bzero(new_node, sizeof(t_ls));
	new_node->name = name;
	return(new_node);
}

/* this functions like ls -a */
t_ls *store_file_info(DIR *dirp)
{
	struct stat sb;
	struct dirent *dp;
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
	while ((dp = readdir(dirp)) != NULL)
	{
		node = new_node(dp->d_name);
		lstat(node->name, &sb);
		printf("%s\t %lld\n", node->name, sb.st_size);
		if (new_list == NULL)
			new_list = node;
		else if (ft_strcmp(node->name, new_list->name) <= 0)
		{
			node->next = new_list;
			new_list = node;
		}
		else
		{
			cur = new_list;
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
	}
	return (new_list);
}


int printf_curr_dir(char *path)
{
	DIR *dirp;
	t_ls *file_list;

	dirp = opendir(path); /* opens present directory */
	if (!dirp)
		return (-1);

	file_list = store_file_info(dirp);
	while (file_list != NULL)
	{
		printf("%s\n", file_list->name);
		file_list = file_list->next;
	}
	closedir(dirp);
	return (0);
}