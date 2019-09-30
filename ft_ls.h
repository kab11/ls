/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kblack <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:00:03 by kblack            #+#    #+#             */
/*   Updated: 2019/03/05 22:56:21 by kblack           ###   ########.fr       */
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

# define ANSI_COLOR_RED		"\x1b[31m"
# define ANSI_COLOR_MAGENTA	"\x1b[35m"
# define BOLDCYAN			"\033[1m\033[36m"
# define ANSI_COLOR_RESET	"\x1b[0m"
# define GREEN_HIGHLIGHT	"\x1b[30m\x1b[42m"

# define FLAG "Ralrt"


enum				e_flag
{

	OPT_a = 1 << 0,
	OPT_l = 1 << 1,
	OPT_R = 1 << 2,
	OPT_r = 1 << 3,
	OPT_t = 1 << 4,
	ls_DIR = 1 << 8
};

typedef struct		s_info
{
	char			*permission;
	int				links;
	char			*o_name;
	char			*gp_name;
	int				bytes;
	char			*mtime;
	time_t			int_mtime;
	char			*atime;
	time_t			int_atime;
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
	struct stat		stat;

	double			gt_link;
	double			gt_byte;
	double			link_len;
	double			byte_len;
	struct s_info	*dir_info;
}					t_ls;

/*
** MAIN.C
*/
int		main(int argc, char **argv);
void	ft_ls(char *path, int flags);

/*
** FILE_UTILITIES.C
*/
int		check_dir(char *name);
int		check_file(char *name);
void	check_color(t_info *file);
void	print_long(t_info *node, t_ls *ls);

/*
** FLAG_UTILITIES.C
*/
int		flag_handler(char *av);

/*
** FORMAT_AND_PRINT.C
*/
void	ls_print_and_format(t_ls *ls, int flags);

/*
** FREE_MEMORY.C
*/
void	free_all_files(t_info *files);

/*
** GET_FILE_INFO.C
*/
void	get_file_info(char *path, t_ls *ls);
void	save_file_info(t_info *node, t_ls *ls);

/*
** HANDLE_FLAGS.C
*/
void	parse_flags(char **av, int flags);

/*
** PERMISSIONS.C
*/
char	*get_permissions(struct stat file);

/*
** SORTING_FUNCTIONS.C
*/
void	sort_by_time(t_info **list, int flags);
t_info	*alpha_insert_sort(t_info *node, t_info *list);
t_info	*sort_and_merge(t_info *a, t_info *b, int flags);

/*
** UTILITIES.C
*/
t_info	*new_node();
void	link_padding(int num, t_ls *ls);
void	byte_padding(int num, t_ls *ls);
void	get_format(t_ls *ls);
void	get_total_bytes(t_ls *ls, int flags);

#endif
