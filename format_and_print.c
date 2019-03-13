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
** listing reverse ascii (-r)
*/

void	poopy_back(t_info **list, t_ls *ls, int flags)
{
	t_info	*foo;

	foo = *list;
	if (foo == NULL)
		return ;
	poopy_back(&foo->next, ls, flags);
	if ((flags & OPT_a) || foo->name[0] != '.')
	{
		if (flags & OPT_l)
			print_long(foo, ls, flags);
		else
		{
			if (foo->permission[0] == 'd' ||
				foo->permission[0] == 'l' || foo->permission[3] == 'x')
				check_color(foo);
			else
				ft_putstr(foo->name);
			ft_putchar('\n');
		}
	}
}

/*
** listing by ascii order
*/

void	not_poopy_back(t_info **list, t_ls *ls, int flags)
{
	t_info	*foo;

	foo = *list;
	if (foo == NULL)
		return ;
	if ((flags & OPT_a) || foo->name[0] != '.')
	{
		if (flags & OPT_l)
			print_long(foo, ls, flags);
		else
		{
			if (foo->permission[0] == 'd' ||
				foo->permission[0] == 'l' || foo->permission[3] == 'x')
				check_color(foo);
			else
				ft_putstr(foo->name);
			ft_putchar('\n');
		}
	}
	not_poopy_back(&foo->next, ls, flags);
}

void	print(t_info **cur, t_ls *ls, int flags)
{
	if ((flags & OPT_r) == 8)
		poopy_back(cur, ls, flags);
	else
		not_poopy_back(cur, ls, flags);
}

/*
** handle option -d 
*/

void	print_flag_d(t_info **cur, t_ls *ls, int flags)
{
	t_info	*foo;

	foo = *cur;
	if (foo == NULL)
		return ;
	while (foo != NULL)
	{
		if (ft_strcmp(foo->name, ".") == 0)
		{
			if (flags & OPT_l)
				print_long(foo, ls, flags);
			else
			{
				check_color(foo);
				ft_putchar('\n');
			}
		}
		foo = foo->next;
	}
}

void	ls_print_and_format(t_ls *ls, int flags)
{
	t_info	*cur;

	cur = ls->dir_info;
	get_format(ls);
	if (flags & OPT_d)
	{
		print_flag_d(&cur, ls, flags);
		return ;
	}
	else if (flags & OPT_l && (flags & ls_DIR) != 0)
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
