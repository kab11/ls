/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 18:19:25 by kblack            #+#    #+#             */
/*   Updated: 2019/03/04 18:19:38 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/* 
** these 2 programs free any memory that was allocated thoughout the program to
** handle any possible leaks 
*/

void	free_file(t_info *file)
{
	(file->name != NULL) ? free(file->name) : 0;
	(file->pwd != NULL) ? free(file->pwd) : 0;
	(file->permission != NULL) ? free(file->permission) : 0;
	(file->sym_link != NULL) ? free(file->sym_link) : 0;
	(file->mtime != NULL) ? free(file->mtime) : 0;
	(file->atime != NULL) ? free(file->atime) : 0;
	free(file);
	file = NULL;
}

void	free_all_files(t_info *files)
{
	t_info	*temp;

	while (files != NULL)
	{
		temp = files->next;
		free_file(files);
		files = temp;
	}
}
