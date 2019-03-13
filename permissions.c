/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 23:36:08 by kblack            #+#    #+#             */
/*   Updated: 2019/02/26 20:56:34 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** this creates a string of the file type and permissions for each file/directory
** in the directory stream and returns the string 
*/

void	get_file_type(struct stat file, char *str)
{
	int	i;
	int	x;

	i = 0;
	x = file.st_mode & S_IFMT;
	S_ISREG(x) ? str[i] = '-' : 0;
	S_ISBLK(x) ? str[i] = 'b' : 0;
	S_ISCHR(x) ? str[i] = 'c' : 0;
	S_ISDIR(x) ? str[i] = 'd' : 0;
	S_ISLNK(x) ? str[i] = 'l' : 0;
	S_ISFIFO(x) ? str[i] = 'p' : 0;
	S_ISSOCK(x) ? str[i] = 's' : 0;
}

char	*get_permissions(struct stat file)
{
	char	*str;
	int	i;

	i = 10;
	str = ft_strnew(i);
	get_file_type(file, str);
	i = 1;
	str[i++] = S_IRUSR & file.st_mode ? 'r' : '-';
	str[i++] = S_IWUSR & file.st_mode ? 'w' : '-';
	str[i++] = S_IXUSR & file.st_mode ? 'x' : '-';
	str[i++] = S_IRGRP & file.st_mode ? 'r' : '-';
	str[i++] = S_IWGRP & file.st_mode ? 'w' : '-';
	str[i++] = S_IXGRP & file.st_mode ? 'x' : '-';
	str[i++] = S_IROTH & file.st_mode ? 'r' : '-';
	str[i++] = S_IWOTH & file.st_mode ? 'w' : '-';
	str[i++] = S_IXOTH & file.st_mode ? 'x' : '-';
	str[i] = '\0';
	return (str);
}
