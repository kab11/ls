/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_and_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:23:05 by kblack            #+#    #+#             */
/*   Updated: 2019/03/05 22:51:57 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This is where ft_ls prints information based off options chosen by the user */

#include "ft_ls.h"

/*
** listing reverse ascii (-r); print linked list content from right to left
*/

void	print_reverse(t_info **list, t_ls *ls, int flags)
{
	t_info	*foo;

	foo = *list;
	if (foo == NULL)
		return ;
	print_reverse(&foo->next, ls, flags);
	if ((flags & OPT_a) || foo->name[0] != '.')
	{
		if (flags & OPT_l)
			print_long(foo, ls);
		else
		{
			if (foo->permission[0] == 'd' ||
				foo->permission[0] == 'l' || foo->permission[3] == 'x'
					|| foo->permission[9] == 't')
					check_color(foo);
			else
				ft_putstr(foo->name);
			ft_putchar('\n');
		}
	}
}

/*
** listing by ascii order; recursively print linked list
** content from left to right
*/

void	print_standard(t_info **list, t_ls *ls, int flags)
{
	t_info	*foo;

	foo = *list;
	if (foo == NULL)
		return ;
	if ((flags & OPT_a) || foo->name[0] != '.')
	{
		if (flags & OPT_l)
			print_long(foo, ls);
		else
		{
			if (foo->permission[0] == 'd' ||
				foo->permission[0] == 'l' || foo->permission[3] == 'x'
					|| foo->permission[9] == 't')
					check_color(foo);
			else
				ft_putstr(foo->name);
			ft_putchar('\n');
		}
	}
	print_standard(&foo->next, ls, flags);
}

/*
** Determines what end of the linked lists to start printing data
*/

void	print(t_info **cur, t_ls *ls, int flags)
{
	if ((flags & OPT_r) == 8)
		print_reverse(cur, ls, flags);
	else
		print_standard(cur, ls, flags);
}

/*
** Gets the printing format based off of the option(s) specified by the user
*/

void	ls_print_and_format(t_ls *ls, int flags)
{
	t_info	*cur;

	cur = ls->dir_info;
	get_format(ls);
	if (flags & OPT_l && (flags & ls_DIR) != 0)
	{
		get_total_bytes(ls, flags);
		if (ls->total > 0)
		{
			ft_putstr("total ");
			ft_putnbr(ls->total);
			ft_putchar('\n');
		}
	}
	print(&cur, ls, flags);
}
