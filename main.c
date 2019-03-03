/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 18:07:06 by kblack            #+#    #+#             */
/*   Updated: 2019/02/26 21:39:45 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** OBJECTIVE: recreate ls; ls is used to list the contents of directories
**
**	FLAGS:	-l: long listing format	-a: include entries which start with "."
**			-R: recurse				-t: sort by mtime
**			-r: reverse sort order
**	1) get all files in the directory
**	2) print the "ls" output
**	3) go throgh all the files in the directory
**	4) check if the current file being lookd at is a directory
**	5) if so, recursively list that directory
*/

void		free_file(t_info *file)
{
	(file->name != NULL) ? free(file->name) : 0;
	(file->pwd != NULL) ? free(file->pwd) : 0;
	(file->permission != NULL) ? free(file->permission) : 0;
	(file->sym_link != NULL) ? free(file->sym_link) : 0;
	(file->mtime != NULL) ? free(file->mtime) : 0;
	free(file);
	file = NULL;
}

void		free_all_files(t_info *files)
{
	t_info		*temp;

	while (files != NULL)
	{
		temp = files->next;
		free_file(files);
		files = temp;
	}
}

void print_recursive(char *path, t_ls *ls, int flags)
{
	t_info *cur;
	char *file_path;
	char *tmp;

	cur = ls->dir_info;
	while (cur != NULL)
	{
		if (ft_strcmp(cur->name, ".") == 0 || ft_strcmp(cur->name, "..") == 0)
			;
		else if (cur->name[0] == '.' && (flags & OPT_a) != 1)
			;
		else if (cur->permission[0] == 'd')
		{
			tmp = ft_strjoin(path, "/");
			file_path = ft_strjoin(tmp, cur->name);
			free(tmp);
			ft_putchar('\n');
			ft_putstr(file_path);
			ft_putstr(":\n");
			main_handler(file_path, flags);
		}
		cur = cur->next;
	}
}

void main_handler(char *path, int flags)
{
	t_ls ls;

	ft_bzero(&ls, sizeof(ls));
	get_file_info(path, &ls);
	ls_print_and_format(&ls, flags);

	if (flags & OPT_R)
		print_recursive(path, &ls, flags);
	free_all_files(ls.dir_info);
}

int main(int argc, char **argv)
{
	int flags;
	int i;

	i = 1;
	flags = 0;
	if (argc == 1)
		main_handler(".", flags);
	else if (argc > 1)
	{
		while (i < argc && argv[i][0] == '-')
		{
			flags |= flag_handler(argv[i]);
			i++;
		}
		if (i == argc)
			main_handler(".", flags);
		else
			parse_flags(argv + i, flags);
	}
	return (0);
}
