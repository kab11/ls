/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 13:24:49 by kblack            #+#    #+#             */
/*   Updated: 2019/03/05 22:55:41 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** check_file and check_dir use lstat and opendir to determine whether the 
** the parameter is a vaild file or valid directory
*/

int	check_file(char *name)
{
	struct stat	file_stats;

	if (lstat(name, &file_stats) == -1)
		return (-1);
	return (0);
}

int	check_dir(char *name)
{
	DIR			*d_stream;

	d_stream = opendir(name);
	if (d_stream == NULL)
		return (-1);
	closedir(d_stream);
	d_stream = NULL;
	return (0);
}

/*
** check_color checks if the file passed is a symolic link, executable file, or
** a directory and prints the name with the corresponding color 
**
** To create a symlink:
**	[ln -s <file make symlink> <symlink name>]
*/

void print_symlink(char *str)
{
	int i;

	i = -1;
	while(str[++i] != '>')
	{
		ft_putstr(ANSI_COLOR_MAGENTA);
		ft_putchar(str[i]);
	}
	ft_putchar(str[i]);
	ft_putstr(ANSI_COLOR_RESET);
	while (str[++i])
		ft_putchar(str[i]);
}

void	check_color(t_info *file)
{
	if (file->permission[0] == 'l')
		print_symlink(file->sym_link);
	else if (file->permission[0] == 'd')
	{
		(file->permission[9] == 't') ? ft_putstr(GREEN_HIGHLIGHT)
			: ft_putstr(BOLDCYAN);
		ft_putstr(file->name);
	}
	else if (file->permission[9] == 't' || file->permission[3] == 'x')
	{
		file->permission[9] == 't' ? ft_putstr(GREEN_HIGHLIGHT)
			: ft_putstr(ANSI_COLOR_RED);
		ft_putstr(file->name);
	}
	ft_putstr(ANSI_COLOR_RESET);
}

/*
** this is where the long form; when -l is specified, is printed
*/

void	print_long(t_info *node, t_ls *ls)
{
	ft_putstr(node->permission);
	ft_putchar(' ');
	link_padding(ft_numlen(node->links), ls);
	ft_putnbr(node->links);
	ft_putchar(' ');
	ft_putstr(node->o_name);
	ft_putstr("  ");
	ft_putstr(node->gp_name);
	ft_putstr("  ");
	byte_padding(ft_numlen(node->bytes), ls);
	ft_putnbr(node->bytes);
	ft_putchar(' ');
	ft_putstr(node->mtime);
	ft_putchar(' ');
	if (node->permission[0] == 'd' ||
		node->permission[0] == 'l' || node->permission[3] == 'x'
			|| node->permission[9] == 't')
		check_color(node);
	else
		ft_putstr(node->name);
	ft_putstr("\n");
}
