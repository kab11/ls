# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kblack <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/02 11:59:37 by kblack            #+#    #+#              #
#    Updated: 2019/02/02 11:59:41 by kblack           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	ft_ls

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror

SRC		=	file_utilities.c \
			flag_utilities.c \
			format_and_print.c \
			free_memory.c \
			get_info.c \
			handle_flags.c \
			main.c \
			permissions.c \
			sorting_functions.c \
			utilities.c

INC_FT	=	-I libft
LINK_FT	=	-L libft -l ft
FT		=	$(INC_FT) $(LINK_FT)

HDR = ft_ls.h
OFL = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFL)
	make -C libft
	$(CC) -o $@ $(CFLAGS) $(FT) $(OFL) -I .

$(OFL): $(SRC)
	@$(CC) $(CFLAGS) $(INC_FT) -I . -c $(SRC)

clean:
	rm -rf $(OFL)
	make -C libft clean

fclean: clean
	rm -rf $(NAME)
	make -C libft fclean

re: fclean all
	make -C libft re
