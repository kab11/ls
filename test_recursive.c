/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_recursive.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/22 14:09:30 by kblack            #+#    #+#             */
/*   Updated: 2019/02/22 14:09:38 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// typedef struct s_ls
// {
	
// } t_ls;

main_handler(char *path, t_ls *ls)
{
	DIR *dirp;
	struct dirent *dp;

	dirp = opendir(path);

	while ((dp = readdir(dirp)) != NULL)
	{
		lstat(path, )
		printf("dp->%s\n", );
	}
}

int main(int argc, char **argv)
{
	t_ls ls;

	ft_bzero(&ls, sizeof(ls));
	main_handler(".", &ls);
	return (0);
}