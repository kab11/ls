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

//https://aljensencprogramming.wordpress.com/tag/st_mode/

/* Need to create a linked list of structures that can each store infomation about
 * each file in the current directory:
 * 1) name 							7) file mode 	
 * 2) number of links 				8) owner name
 * 3) group name 					9) # of bytes 	
 * 4) abbreviated month 			10) DoM file was last modified
 * 5) hour file was las modified 	11) minute last modified 	
 * 6) pathname
*/

/* lstat(): declare a struct stat
 *			call lstat() passing as the firs parameter the file we want metadata of
 *			and as the second arument the address of the struct stat variable we declared)
 */

t_ls *new_node(char *name)
{
	t_ls *new_node;

	new_node = malloc(sizeof(t_ls));
	ft_bzero(new_node, sizeof(t_ls));
	new_node->name = name;
	return(new_node);
}

void populate_struct(t_ls *node, struct stat file, int x)
{
	struct group *gp;
	struct passwd *pwd;

	node->permission = get_permissions(x, file.st_mode);
	node->links = file.st_nlink; /* number of links */

	pwd = getpwuid(file.st_uid); /* owner name */
	node->o_name = pwd->pw_name;
			
	gp = getgrgid(file.st_gid);  /* group name */
	node->gp_name = gp->gr_name;
			
	node->bytes = file.st_size;/* number of bytes */
	node->tbytes += file.st_blocks; /* size of file in 512-byte blocks */
	node->time = ft_strsub(ft_strdup(ctime(&file.st_ctime)), 4, 12); /* strsub string start = 4, end = 12*/
}

void traverse_list(t_ls *new_list, t_ls *node)
{
	t_ls *cur;
	t_ls *trail;

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

/* this functions like ls -a */
t_ls *store_file_info(DIR *dirp)
{
	struct stat file;
	struct dirent *dp;
	t_ls *node;
	t_ls *new_list;
	int i;
	int x;

	i = 0;
	while ((dp = readdir(dirp)) != NULL)
	{
		lstat(dp->d_name, &file);
		node = new_node(dp->d_name);
		if ((x = file.st_mode & S_IFMT))
			populate_struct(node, file, x);
		if (new_list == NULL)
			new_list = node; 
		else if (ft_strcmp(node->name, new_list->name) <= 0)
		{
			node->next = new_list;
			new_list = node;
		}
		else
			traverse_list(new_list, node);
	}
	return (new_list);
}


int get_file_info(char *path)
{
	DIR *dirp;
	t_ls *file_list;
	int total_bytes;

	total_bytes = 0;
	dirp = opendir(path); /* opens present directory */
	if (!dirp)
		return (-1);

	file_list = store_file_info(dirp);
	while (file_list != NULL)
	{
		total_bytes += file_list->tbytes;
		printf("%-10s\t%d\t%s\t%s\t%d\t%s\t%s\n", file_list->permission, file_list->links, file_list->o_name, file_list->gp_name, file_list->bytes, file_list->time, file_list->name);
		file_list = file_list->next;
	}
	printf("total: %d\n", total_bytes);
	closedir(dirp);
	return (0);
}