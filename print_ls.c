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

char get_file_type(int file_type, char *str)
{
	int i;

	i = 0;
	if (!file_type || !str)
		return ('\0');
	S_IFREG == file_type ? str[i] = '-' : 0;
	S_IFBLK == file_type ? str[i] = 'b' : 0;
	S_IFCHR == file_type ? str[i] = 'c' : 0;
	S_IFDIR == file_type ? str[i] = 'd' : 0;
	S_IFLNK == file_type ? str[i] = 'l' : 0;
	S_IFIFO == file_type ? str[i] = 'p' : 0;
	S_IFSOCK == file_type ? str[i] = 's' : 0;

	return (str[i]);
}

char *get_permisions(int file_type, int file_mode)
{
	char *str;
	int i;

	i = 10;
	if (!(str = ft_strnew(i)))
		return (NULL);
	else
	{
		get_file_type(file_type, str);
		i = 1;
		str[i++] = S_IRUSR & file_mode ? 'r' : '-';
		str[i++] = S_IWUSR & file_mode ? 'w' : '-';
		str[i++] = S_IXUSR & file_mode ? 'x' : '-';
		str[i++] = S_IRGRP & file_mode ? 'r' : '-';
		str[i++] = S_IWGRP & file_mode ? 'w' : '-';
		str[i++] = S_IXGRP & file_mode ? 'x' : '-';
		str[i++] = S_IROTH & file_mode ? 'r' : '-';
		str[i++] = S_IWOTH & file_mode ? 'w' : '-';
		str[i++] = S_IXOTH & file_mode ? 'x' : '-';
	}
	str[i] = '\0';
	return (str);
}

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
	struct stat file;
	struct dirent *dp;
	struct group *gp;
	struct passwd *pwd;
	t_ls *new_list;
	t_ls *cur;
	t_ls *trail;
	t_ls *node;
	int i;
	int x;

	new_list = NULL;
	cur = NULL;
	trail = NULL;
	node = NULL;
	i = 0;
	while ((dp = readdir(dirp)) != NULL)
	{
		lstat(dp->d_name, &file);
		node = new_node(dp->d_name);
		if ((x = file.st_mode & S_IFMT))
		{
			// printf("%-20s\t%s\n", dp->d_name, get_permisions(x, file.st_mode));
			node->permission = get_permisions(x, file.st_mode);
			// node->ino = file.st_ino; /* inode nummber */

			node->links = file.st_nlink; /* number of links */

			pwd = getpwuid(file.st_uid); /* owner name */
			node->o_name = pwd->pw_name;

			gp = getgrgid(file.st_gid); /* group name */
			node->gp_name = gp->gr_name;

			node->bytes = file.st_size;/* number of bytes */

			node->tbytes += file.st_blocks; /* size of file in 512-byte blocks */

			node->time = ft_strsub(ft_strdup(ctime(&file.st_ctime)), 4, 12); /* strsub string start = 4, end = 12*/
		}
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