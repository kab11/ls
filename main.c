/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 18:07:06 by kblack            #+#    #+#             */
/*   Updated: 2019/02/02 18:07:09 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* OBJECTIVE: recreate ls; ls is used to list the contents of directories */

/* 
 *	FLAGS:	-l: long listing format	-a: include entries which satrt with .
 *			-R: recurse				-t: sort by mtime
 *			-r: reverse sort order
*/

/* displays the list of files inside a directory and information about a file 
 * 1 file per line is okay
 * - manage all types of files (e.g. symbolic links, ...) i
 * - need to manage user errors (e.g. premission denied and directory/file doesn't exist)
 * - include major and minor device numbers 
 * - hanlde 'b' and 'c' that are specific to certain devices and in \dev 
 * - (-lG) manage colors */

/* opendir(): opens the current directory (indicated by ".") and rturn a pointer to the 
 * 			  directory stream 
 * readdir(): returns a pointer to the next directory entry (dirent structure); returns NULL
 * 			  once it reaches the end of the directory stream or if an error occurred 
 * closedir(): closes directory stream associated with dirp; alos closes the fd associated with dirp*/

/*	struct dirent {
	 	ino_t          d_ino;        -->inode number 
	   	off_t          d_off;        -->offset to the next dirent 
    	unsigned short d_reclen;     -->length of this record 
    	unsigned char  d_type;       -->type of file; not supported
    	                                by all file system types 
    	char           d_name[256];  -->filename 
	}; 
	~inode: a datastructure that stores all info about a file except its name and its actual data
*/

/* struct stat {
		  dev_t		st_dev;	     -->device 
		  ino_t		st_ino;	     -->inode 
		  mode_t	st_mode;     -->protection 
		  nlink_t	st_nlink;    -->number of hard links 
		  uid_t		st_uid;	     -->user ID of owner 
		  gid_t		st_gid;	     -->group ID of owner 
		  dev_t		st_rdev;     -->device type (if inode device) 
		  off_t		st_size;     -->total size, in bytes; th size of symlink is len of pathname it wontains w/o trailing NULL
		  blksize_t	st_blksize;  -->blocksize for filesystem I/O 
		  blkcnt_t	st_blocks;   -->size of file in 512-byte blocks 
		  time_t	st_atime;    -->time of last access 
		  time_t	st_mtime;    -->time of last modification 
		  time_t	st_ctime;    -->time of last change 
	};
	**lstat is identical to stat except in the case of a symbolic link, where the link itself is stat-ed,
	not the file that it refers to
*/

/* ls omits hidden dotfiles (the option '-a' forces ls to show them) */


#include "ft_ls.h"

int main(int argc, char **argv)
{
	t_ls ls;

	ft_bzero(&ls, sizeof(ls));
	if (argc == 1)
	{
		//handle only ls
		printf_curr_dir(".");
	}
	else if (argc > 1)
	{
		// check for flags
		parse_flags(argc, argv, &ls);
		printf_curr_dir(argv[1]);
	}

	return (0);
}