/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 01:19:26 by kblack            #+#    #+#             */
/*   Updated: 2019/02/26 21:59:34 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_info		*new_node(void)
{
	t_info	*new_node;

	new_node = (t_info*)malloc(sizeof(t_info));
	ft_bzero(new_node, sizeof(t_info));
	return (new_node);
}

void		link_padding(int num, t_ls *ls)
{
	while (num++ < ls->link_len)
		ft_putchar(' ');
}

void		byte_padding(int num, t_ls *ls)
{
	num == 0 ? num++ : 0;
	while (num++ < ls->byte_len)
		ft_putchar(' ');
}

void		get_format(t_ls *ls)
{
	t_info	*file;

	file = ls->dir_info;
	while (file)
	{
		if (file->links > ls->gt_link)
			ls->gt_link = file->links;
		if (file->bytes > ls->gt_byte)
			ls->gt_byte = file->bytes;
		file = file->next;
	}
	ls->link_len = ft_numlen(ls->gt_link);
	ls->byte_len = ft_numlen(ls->gt_byte);
}

void		get_total_bytes(t_ls *ls, int flags)
{
	t_info	*node;
	int		tmp;

	tmp = 0;
	node = ls->dir_info;
	while (node)
	{
		if (!(flags & OPT_a) && (ft_strncmp(node->name, ".", 1) == 0))
			node = node->next;
		else
			tmp += node->total_bytes;
		node = node->next;
	}
	ls->total = tmp;
}
