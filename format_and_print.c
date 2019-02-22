/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_and_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 16:23:05 by kblack            #+#    #+#             */
/*   Updated: 2019/02/20 16:23:08 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* Merge Sort

	-	the idea of the algorithm is to sort smaller arrays and then combine those arrays together in sorted order
	-	leverages recursion 
	1) sort the left half of the array (assuming n > 1)
	2) sort right half of the array (assuming n > 1)
	3) merge the 2 halves together 	
	O(n log n) time 
 */

static void print_long(t_info *node, t_ls *ls)
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
	ft_putstr(node->ctime);
	ft_putchar(' ');
	(node->sym_link != NULL) ? ft_putstr(node->sym_link) : ft_putstr(node->name);
	ft_putstr("\n");
}

/* listing reverse ascii (-r) */

void poopy_back(t_info *foo, t_ls *ls)
{
	if (foo == NULL)
		return;
	poopy_back(foo->next, ls);
	if ((ls->flags & OPT_a) || foo->name[0] != '.')
	{
		if (ls->flags & OPT_l)
			print_long(foo, ls);
		else
		{
			ft_putstr(foo->name);
			ft_putchar('\n');
		}
	}
}

/* listing by ascii order */

void not_poopy_back(t_info *foo, t_ls *ls)
{
	if (foo == NULL)
		return ;
	if ((ls->flags & OPT_a) || foo->name[0] != '.')
	{
		if (ls->flags & OPT_l)
			print_long(foo, ls);
		else
		{
			ft_putstr(foo->name);
			ft_putchar('\n');
		}
	}
	not_poopy_back(foo->next, ls);
}

void ls_print_and_format(t_ls *ls)
{
	t_info *cur;

	cur = ls->dir_info;
	get_format(ls);
	if (ls->flags & OPT_l && !ls->is_a_file)
	{
		get_total_bytes(ls);
		ft_putstr("total ");
		ft_putnbr(ls->total);
		ft_putchar('\n');
	}
	if (ls->flags & OPT_t)
		sort_by_time(&cur);
	if (ls->flags & OPT_r)
		poopy_back(cur, ls);
	else
		not_poopy_back(cur, ls);
}