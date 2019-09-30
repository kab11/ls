/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:40:09 by kblack            #+#    #+#             */
/*   Updated: 2019/03/05 22:35:23 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** these functions handle command line files and directories that the user writes 
*/

/*
** check_file_and_directory_exist checks to see of the file/directory specificed by the
** user exists and if not prints and error
*/

void	check_file_and_directory_exist(char **av)
{
	int	i;

	i = -1;
	while (av[++i] != NULL)
	{
		if (check_file(av[i]) != 0 && check_dir(av[i]) != 0)
		{
			ft_putstr("ls: ");
			perror(av[i]);
		}
	}
}

/*
** meat_and_potatoes: creates the path for the directory stream
**
**		Calls functions that:
** 			1. populate the struture with file/directory info
** 			2. sorts each node using insert sort
** 			3. format printing based off of the option(s) specified
*/

int	meat_and_potatoes(char **av, t_ls *fs, int flags)
{
	t_info	*node;
	char	*path;
	int	i;

	i = -1;
	while (av[++i] != NULL)
	{
		if (check_file(av[i]) == 0 && check_dir(av[i]) != 0)
		{
			path = ft_strjoin("./", av[i]);
			node = new_node();
			node->name = ft_strdup(av[i]);
			node->pwd = path;
			save_file_info(node, fs);
			fs->dir_info = alpha_insert_sort(node, fs->dir_info);
		}
	}
	ls_print_and_format(fs, flags);
	return (flags);
}

/*
** Prints directory name and then 
*/

void	print_dir_info(char **av, int flags)
{
	int	i;

	i = -1;
	while (av[++i] != NULL)
	{
		BIT_ON(flags, ls_DIR);
		if (check_dir(av[i]) == 0)
		{
			ft_putchar('\n');
			ft_putstr(av[i]);
			ft_putstr(":\n");
			execute_ls(av[i], flags);
		}
	}
}

/* 
** Handles when the user specifies a file or driectory 
*/

void	handle_file_dir(char **av, int flags)
{
	t_ls	fs;
	int	new_flags;

	ft_bzero(&fs, sizeof(fs));
	check_file_and_directory_exist(av);
	new_flags = meat_and_potatoes(av, &fs, flags);
	print_dir_info(av, new_flags);
	free_all_files(fs.dir_info);
}
