/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   permissions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 23:36:08 by kblack            #+#    #+#             */
/*   Updated: 2019/02/13 23:36:19 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char get_file_type(int file_type, char *str)
{
	int i;
	int sym;

	i = 0;
	sym = 0;
	if (!file_type || !str)
		return ('\0');
	S_IFREG == file_type ? str[i] = '-' : 0;
	S_IFBLK == file_type ? str[i] = 'b' : 0;
	S_IFCHR == file_type ? str[i] = 'c' : 0;
	S_IFDIR == file_type ? str[i] = 'd' : 0;
	S_IFLNK == file_type ? str[i] = 'l' : 0;
	S_IFIFO == file_type ? str[i] = 'p' : 0;
	S_IFSOCK == file_type ? str[i] = 's' : 0;

	// if (str[i] == 'l')
	// 	BIT_ON(sym, PER_l);

	return (str[i]);
}

char *get_permissions(int file_type, int file_mode)
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
