/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:48:37 by kblack            #+#    #+#             */
/*   Updated: 2019/02/26 20:54:31 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** Created a linked list of structures that can each
** store infomation about each file in the current directory:
** 1) name 							7) file mode
** 2) number of links 				8) owner name
** 3) group name 					9) # of bytes
** 4) abbreviated month 			10) DoM file was last modified
** 5) hour file was las modified 	11) minute last modified
** 6) pathname
*/

void	symlink_handler(t_info *node, t_ls *ls)
{
	size_t	bufsize;
	ssize_t	len;
	char	*buf;
	char	*str;
	char	*tmp;

	bufsize = ls->stat.st_size + 1;
	buf = (char *)malloc(bufsize);
	len = readlink(node->name, buf, bufsize);
	buf[len] = '\0';
	str = ft_strjoin(node->name, " -> ");
	tmp = ft_strjoin(str, buf);
	node->sym_link = ft_strdup(tmp);
	free(buf);
	free(str);
	free(tmp);
}

/*
** Populates the t_info sturcture with all info for each file/directory
*/

void	save_file_info(t_info *node, t_ls *ls)
{
	struct group *gp;
	struct passwd *pwd;

	lstat(node->pwd, &ls->stat);
	node->permission = get_permissions(ls->stat);
	if ((ft_strchr(node->permission, 'l')))
		symlink_handler(node, ls);
	node->links = ls->stat.st_nlink;
	pwd = getpwuid(ls->stat.st_uid);
	node->o_name = pwd->pw_name;
	gp = getgrgid(ls->stat.st_gid);
	node->gp_name = gp->gr_name;
	node->bytes = ls->stat.st_size;
	node->total_bytes += ls->stat.st_blocks;
	node->int_mtime = ls->stat.st_mtime;
	node->mtime = ft_strsub(ctime(&ls->stat.st_mtime), 4, 12);
	node->int_atime = ls->stat.st_atime;
	node->atime = ft_strsub(ctime(&ls->stat.st_atime), 4, 12);
}

/*
** Opens and reads from a directory stream corressponding to path provided
** and stores the information into a linked list 
*/

void	get_file_info(char *path, t_ls *ls)
{
	DIR	*dirp;
	struct dirent	*dp;
	t_info	*node;
	char	*tmp;

	dirp = opendir(path);
	if (dirp == NULL)
	{
		perror(path);
		exit(-1);
	}
	while ((dp = readdir(dirp)) != NULL)
	{
		node = new_node();
		node->name = ft_strdup(dp->d_name);
		tmp = ft_strjoin(path, "/");
		node->pwd = ft_strjoin(tmp, node->name);
		free(tmp);
		save_file_info(node, ls);
		ft_bzero(&ls->stat, sizeof(ls->stat));
		ls->dir_info = alpha_insert_sort(node, ls->dir_info);
	}
	closedir(dirp);
}
