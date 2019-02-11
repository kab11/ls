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

void flag_input_error(char **av, int i)
{
	while (av[i])
	{
		printf("%s: %s: No such file or directory\n", av[0], av[i]);
		i++;
	}
	exit(-1);
}

void parse_flags(int ac, char **av, t_ls *ls)
{
	int i;
	int j;
	int k;

	i = 1;
	j = 0;
	while (ac-- > 1)
	{
		if (av[i][0] == '-')
		{
			while (av[i])
			{
				k = 1;
				while (av[i][0] == '-' && av[i][k])
				{
					av[i][k] == 'a' ? BIT_ON(ls->flags, OPT_a) : 0;
					av[i][k] == 'l' ? BIT_ON(ls->flags, OPT_l) : 0;
					av[i][k] == 'R' ? BIT_ON(ls->flags, OPT_R) : 0;
					av[i][k] == 'r' ? BIT_ON(ls->flags, OPT_r) : 0;
					av[i][k] == 't' ? BIT_ON(ls->flags, OPT_t) : 0;	
					k++;
				}
				if (av[i][0] != '-')
					flag_input_error(av, i);
				i++;
			}
		}
		else if (av[i][0] != '-')
			flag_input_error(av, i);
	}
}
