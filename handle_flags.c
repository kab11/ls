/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_flags.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 18:40:09 by kblack            #+#    #+#             */
/*   Updated: 2019/02/08 18:40:16 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int flag_handler(char *av)
{
	int i;
	int flags;

	i = 1;
	flags = 0;
	while (av[i])
	{
		av[i] == 'a' ? BIT_ON(flags, OPT_a) : 0;
		av[i] == 'l' ? BIT_ON(flags, OPT_l) : 0;
		av[i] == 'R' ? BIT_ON(flags, OPT_R) : 0;
		av[i] == 'r' ? BIT_ON(flags, OPT_r) : 0;
		av[i] == 't' ? BIT_ON(flags, OPT_t) : 0;
		av[i] == 'g' ? BIT_ON(flags, OPT_g) : 0;	
		i++;
	}
	return (flags);
}

int check_file(char *name)
{
	struct stat		file_stats;

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

t_info *copy_node(t_info *master)
{
	t_info *copy;

	copy = new_node();
	copy->name = master->name;
	copy->permission = ft_strdup(master->permission);
	copy->sym_link = (master->sym_link != NULL) ? ft_strdup(master->sym_link) : 0;
	copy->links = master->links;
	copy->o_name = 	master->o_name;	
	copy->gp_name = master->gp_name;	
	copy->bytes = master->bytes;
	copy->mtime = ft_strdup(master->mtime);
	copy->int_mtime = master->int_mtime;

	return (copy);
}

t_info *file_handler(char *av, t_ls *fs)
{
	t_info *files;

	get_file_info(".", fs);
	files = fs->dir_info;
	while (files)
	{
		if (strcmp(files->name, av) == 0)
			return (copy_node(files));
		files = files->next;
	}
	return (NULL);
}

void print_file_error(char **av)
{
	int i;

	i = 0;
	while (av[i] != NULL)
	{
		if (check_file(av[i]) != 0 && check_dir(av[i]) != 0)
		{
			ft_putstr("ls: ");
			perror(av[i]);
		}
		i++;
	}
}

int print_file_info(char **av, t_info *links, t_info *list, t_ls *fs, int flags)
{
	int i;
	int file;

	i = 0;
	file = 0;
	while (av[i] != NULL)
	{
		if (check_file(av[i]) == 0 && check_dir(av[i]) != 0)
		{
			file = 1;
			list = file_handler(av[i], fs);
			links = alpha_insert_sort(list, links);
			list = list->next;
		}
		i++;
	}
	if (file == 0)
		return (0);
	fs->dir_info = links;
	ls_print_and_format(fs, flags);
	return (file);
}

void print_dir_info(char **av, int file, int flags)
{
	int i;

	i = 0;
	if (file)
			ft_putchar('\n');
	while (av[i] != NULL)
	{
		if (check_dir(av[i]) == 0)
		{
			ft_putstr(av[i]);
			ft_putstr(":\n");
			main_handler(av[i], flags);
		}
		i++;
	}
}

void parse_flags(char **av, int flags)
{
	int file;
	t_ls fs;
	t_info *list;
	t_info *links;

	ft_bzero(&fs, sizeof(fs));
	links = NULL;
	list = fs.dir_info;
	print_file_error(av);
	file = print_file_info(av, links, list, &fs, flags);
	print_dir_info(av, file, flags);
}
