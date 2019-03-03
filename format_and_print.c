/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_and_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:23:05 by kblack            #+#    #+#             */
/*   Updated: 2019/02/26 20:58:44 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"


static void	print_long(t_info *node, t_ls *ls, int flags)
{
	// printf("not opt g = %d\n", (flags & ~OPT_g));
	ft_putstr(node->permission);
	ft_putchar(' ');
	link_padding(ft_numlen(node->links), ls);
	ft_putnbr(node->links);
	ft_putchar(' ');
	if (flags & OPT_g)
		ft_putstr(node->gp_name);
	else
	{
		ft_putstr(node->o_name);
		ft_putstr("  ");
		ft_putstr(node->gp_name);
	}
	ft_putstr("  ");
	byte_padding(ft_numlen(node->bytes), ls);
	ft_putnbr(node->bytes);
	ft_putchar(' ');
	ft_putstr(node->mtime);
	ft_putchar(' ');
	if (node->sym_link != NULL)
		ft_putstr(node->sym_link);
	else
		ft_putstr(node->name);
	ft_putstr("\n");
}

/*
** listing reverse ascii (-r)
*/

void		poopy_back(t_info **list, t_ls *ls, int flags)
{
	t_info *foo;

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
			ft_putstr(foo->name);
			ft_putchar('\n');
		}
	}
}

/*
** listing by ascii order
*/

void		not_poopy_back(t_info **list, t_ls *ls, int flags)
{
	t_info *foo;

	foo = *list;
	if (foo == NULL)
		return ;
	if ((flags & OPT_a) || foo->name[0] != '.')
	{
		if (flags & OPT_l)
			print_long(foo, ls, flags);
		else
		{
			ft_putstr(foo->name);
			ft_putchar('\n');
		}
	}
	not_poopy_back(&foo->next, ls, flags);
}

void print(t_info *cur, t_ls *ls, int flags)
{
	if ((flags & OPT_r) == 8)
		poopy_back(&cur, ls, flags);
	else
		not_poopy_back(&cur, ls, flags);
}

void		ls_print_and_format(t_ls *ls, int flags)
{
	t_info	*cur;

	cur = ls->dir_info;
	get_format(ls);
	if (flags & OPT_l)
	{
		get_total_bytes(ls, flags);
		if (ls->total > 0)
		{
			ft_putstr("total ");
			ft_putnbr(ls->total);
			ft_putchar('\n');
		}
	}
	if (flags & OPT_t)
		sort_by_time(&cur);
	print(cur, ls, flags);
}
