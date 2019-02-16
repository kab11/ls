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

int flag_handler(int i, char **av, t_ls *ls)
{
	int k;

	while (av[i] && av[i][0] == '-')
	{
		k = 1;
		while (av[i][k])
		{
			av[i][k] == 'a' ? BIT_ON(ls->flags, OPT_a) : 0;
			av[i][k] == 'l' ? BIT_ON(ls->flags, OPT_l) : 0;
			av[i][k] == 'R' ? BIT_ON(ls->flags, OPT_R) : 0;
			av[i][k] == 'r' ? BIT_ON(ls->flags, OPT_r) : 0;
			av[i][k] == 't' ? BIT_ON(ls->flags, OPT_t) : 0;	
			k++;
		}
		i++;
	}
	return (i);
}

int file_handler(int i, char **av, t_ls *ls)
{
	while (av[i])
	{
		extern int errno;
		FILE *file;
		file = fopen(av[i], "r");
		if (file == NULL)
			printf("%s: %s: %s\n", av[0], av[i], strerror(errno));
		else
		{
			struct stat path;
			lstat(av[i], &path);
			if (S_ISREG(path.st_mode) && ls->flags == 0)
				printf("%s\n", av[i]);
			else
				get_file_info(av[i]);
		}
		i++;
	}
	return (i);
}

void parse_flags(int ac, char **av, t_ls *ls)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' && av[i])
			i = flag_handler(i, av, ls);
		if (av[i] && av[i][0] && av[i][0] != '-')
			i = file_handler(i, av, ls);
		break;
	}
	if (ls->flags > 0)
		get_file_info(".");
}
