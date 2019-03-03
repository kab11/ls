/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:00:03 by kblack            #+#    #+#             */
/*   Updated: 2019/02/26 22:05:22 by kblack           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include <dirent.h>
# include <grp.h>
# include <pwd.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <unistd.h>
# include "libft.h"

/*
** x = target variable; y = mask
** BIT_ON: force to 1; BIT_OFF: force to zero; BIT_FLIP: 0 ↔ 1
*/

# define BIT_ON(x, y) x |= y
# define BIT_OFF(x, y) x &= (~y)
# define BIT_FLIP(x, y) x ^= y

enum				e_flag
{
	OPT_a = 1 << 0,
	OPT_l = 1 << 1,
	OPT_R = 1 << 2,
	OPT_r = 1 << 3,
	OPT_t = 1 << 4,
	OPT_g = 1 << 5
};

typedef struct		s_info
{
	char			*permission;
	int				links;
	char			*o_name;
	char			*gp_name;
	int				bytes;
	char			*mtime;
	time_t				int_mtime;
	char			*name;
	char			*sym_link;
	int				total_bytes;
	char			*pwd;
	struct s_info	*next;
}					t_info;

typedef struct		s_ls
{
	int				flags;
	int				total;
	int				is_a_file;
	struct stat		stat;

	double			gt_link;
	double			gt_byte;
	double			link_len;
	double			byte_len;
	struct s_info	*dir_info;
}					t_ls;

int					main(int argc, char **argv);
void				main_handler(char *path, int flags);

void parse_flags(char **av, int flags);
int flag_handler(char *av);
void print_file_dir_error (char *av);

void				get_file_info(char *path, t_ls *ls);
char				*get_permissions(struct stat file);
void sort_by_time(t_info **list);
t_info *alpha_insert_sort(t_info *node, t_info *list);

void				ls_print_and_format(t_ls *ls, int flags);

t_info				*new_node();
void				link_padding(int num, t_ls *ls);
void				byte_padding(int num, t_ls *ls);
void				get_format(t_ls *ls);
void				get_total_bytes(t_ls *ls, int flags);

void				free_all_files(t_info *files);

void				save_file_info(t_info *node, t_ls *ls);

int					check_dir(char *name);
int					check_file(char *name);

#endif
