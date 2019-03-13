/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utilities.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/05 13:24:49 by kblack            #+#    #+#             */
/*   Updated: 2019/03/05 22:30:21 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** flag_handler uses bit masking to signal what flags the user is specifying
** this value is saved in "flags" and passed throughout the program
*/

void	flag_error(char av)
{
	ft_putstr("ls: illegal option -- ");
	ft_putchar(av);
	ft_putchar('\n');
	ft_putstr("usage: ls [-");
	ft_putstr(FLAG);
	ft_putstr("] [file ...]");
	ft_putchar('\n');
	exit(-1);
}

int	flag_handler(char *av)
{
	int	i;
	int	flags;

	i = 1;
	flags = 0;
	while (av[i])
	{
		if (!(ft_strchr(FLAG, av[i])))
			flag_error(av[i]);
		av[i] == 'a' ? BIT_ON(flags, OPT_a) : 0;
		av[i] == 'l' ? BIT_ON(flags, OPT_l) : 0;
		av[i] == 'R' ? BIT_ON(flags, OPT_R) : 0;
		av[i] == 'r' ? BIT_ON(flags, OPT_r) : 0;
		av[i] == 't' ? BIT_ON(flags, OPT_t) : 0;
		av[i] == 'g' ? BIT_ON(flags, OPT_g) : 0;
		if (flags & OPT_g)
			BIT_ON(flags, OPT_l);
		av[i] == 'u' ? BIT_ON(flags, OPT_u) : 0;
		av[i] == 'd' ? BIT_ON(flags, OPT_d) : 0;
		if (flags & OPT_d)
			BIT_OFF(flags, OPT_R);
		i++;
	}
	return (flags);
}
