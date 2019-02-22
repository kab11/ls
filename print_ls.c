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

/* ERROR HANDLING:
 * 		-> opendir: if unsuccessful opendir returns a NULL pointer; EACCES (read permission 
 * 		denied for the directory names by dirname), EMFILE (process has too many files open),
 * 		ENFILE (system cannot support any additional open files atm), ENOMEM (not enough memory available)
 *
 *
 * 		-> readdir: if there re no more entries in the directory or an error is detected readdir returns
 * 					a NULL pointer; to distinguish between EOD or an error 'errno' must be set to zero
 * 					before calling readdir
 *		**readdir points to a buffer within the DIR object; each call to readdir causes the data in
 *			the buffer to be overwritten; d_name (or whatever) needs to be copied if its needed later 
*/

/* -R:
 *		- opendir checks to see if the directory exists
 *		- printdir makes a call to chdr to the directory specified
 *		- while entries returned by readdir exist, the program checks whether the entry is a directory
 *		- if it isnt, it prints an intended file entry
 *		- if it is a directory the printdir function calls itself (recursion) with the subdirectory name
 *		- recursion ends when there are no more subdirectories to process
 *		- then the current directory is closed via closedir
*/

t_info *new_node()
{
	t_info *new_node;

	new_node = (t_info*)malloc(sizeof(t_info));
	ft_bzero(new_node, sizeof(t_info));
	return(new_node);
}

t_info *sort_file_info(t_info *node, t_info *list)
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

void symlink_handler(t_info *node, t_ls *ls)
{
	size_t bufsize;
	ssize_t len;
	char *buf;
	char *tmp;

	bufsize = ls->stat.st_size + 1;
	buf = (char *)malloc(bufsize);
	len = readlink(node->name, buf, bufsize);
	buf[len] = '\0';
	tmp = ft_strjoin(node->name, " -> ");
	tmp = ft_strjoin(tmp, buf);
	node->sym_link = ft_strdup(tmp);
	free(tmp);
}

void read_file_info(t_info *node, t_ls *ls)
{
	lstat(node->pwd, &ls->stat);
	struct group *gp;
	struct passwd *pwd;

	node->permission = get_permissions(ls->stat);
	if ((ft_strchr(node->permission, 'l')))
		symlink_handler(node, ls);
	node->links = ls->stat.st_nlink; /* number of links */
	pwd = getpwuid(ls->stat.st_uid); /* owner name */
	node->o_name = pwd->pw_name;		
	gp = getgrgid(ls->stat.st_gid);  /* group name */
	node->gp_name = gp->gr_name;		
	node->bytes = ls->stat.st_size;/* number of bytes */
	node->total_bytes += ls->stat.st_blocks; /* size of file in 512-byte blocks */
	node->ctime = ft_strsub(ft_strdup(ctime(&ls->stat.st_ctime)), 4, 12); /* strsub string start = 4, end = 12*/
	node->int_mtime = ls->stat.st_mtime;
	node->mtime_str = ft_strsub(ft_strdup(ctime(&ls->stat.st_mtime)), 4, 12);
}


void get_file_info(char *path, t_ls *ls)
{
	DIR *dirp;
	struct dirent *dp;
	t_info *node;

	dirp = opendir(path); /* opens present directory */
	if (dirp == NULL)
	{
		perror("opendir");
		exit(-1);
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		node = new_node();
		node->name = ft_strdup(dp->d_name);
		node->pwd = ft_strjoin(path, "/");
		node->pwd = ft_strjoin(node->pwd, node->name);
		read_file_info(node, ls);
		ls->total += ls->stat.st_blocks;
		ft_bzero(&ls->stat, sizeof(ls->stat));
		ls->dir_info = sort_file_info(node, ls->dir_info);
	}
	closedir(dirp);
}
