/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 18:07:06 by kblack            #+#    #+#             */
/*   Updated: 2019/03/05 22:22:16 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** OBJECTIVE: recreate ls; ls is used to list the contents of directories
**
**	FLAGS:	-l: long listing format	-a: include entries which start with "."
**			-R: recurse				-t: sort by mtime (time last modified)
**			-r: reverse sort order	-u: sort by atime (time last accesssed)
**	1) get all files in the directory
**	2) print the "ls" output
**	3) go throgh all the files in the directory
**	4) check if the current file being lookd at is a directory
**	5) if so, recursively list that directory
*/

/*
** Handles -R flag; recursively lists subdirectories
*/

void	print_recursive(char *path, t_ls *ls, int flags)
{
	t_info	*cur;
	char	*file_path;
	char	*tmp;

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
			execute_ls(file_path, flags);
			free(file_path);
		}
		cur = cur->next;
	}
}

/*
** execute_ls takes care of getting file information, sorting time,
** printing, recursion, and freeing memory at the end of the program
*/

void	execute_ls(char *path, int flags)
{
	t_ls	ls;

	ft_bzero(&ls, sizeof(ls));
	get_file_info(path, &ls);
	if (flags & OPT_t)
		sort_by_time(&ls.dir_info, flags);
	ls_print_and_format(&ls, flags);
	if (flags & OPT_R)
		print_recursive(path, &ls, flags);
	free_all_files(ls.dir_info);
}

/*
** Reads from stdin. Determines whether or not the user has selected
** options and dircts to the appropriate next step. 
*/

int	main(int argc, char **argv)
{
	int	flags;
	int	i;

	i = 0;
	flags = 0;
	if (argc == 1)
		execute_ls(".", flags);
	else if (argc > 1)
	{
		while (++i < argc && argv[i][0] == '-')
			flags |= flag_handler(argv[i]);
		(i == argc) ? execute_ls(".", flags) : handle_file_dir(argv + i, flags);
	}
	return (0);
}
