/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:00:03 by kblack            #+#    #+#             */
/*   Updated: 2019/02/02 12:00:05 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <sys/stat.h>
#include <uuid/uuid.h>

#include <dirent.h>
#include <grp.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "libft.h"

/* x = target variable; y = mask */
/* BIT_ON: force to 1; BIT_OFF: force to zero; BIT_FLIP: 0 ↔ 1 */

# define BIT_ON(x, y) x |= y
# define BIT_OFF(x, y) x &= (~y)
# define BIT_FLIP(x, y) x ^= y

enum flag
{
	OPT_a = 1 << 0,
	OPT_l = 1 << 1,
	OPT_R = 1 << 2,
	OPT_r = 1 << 3,
	OPT_t = 1 << 4
};

typedef struct s_ls
{
	int flags;
	char *name;
	int ino;
	struct s_ls *next;
}				t_ls;

int main(int argc, char **argv);

void parse_flags(int ac, char **av, t_ls *ls);

int printf_curr_dir(char *path);

#endif