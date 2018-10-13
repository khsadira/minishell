# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khsadira <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/04 14:29:26 by khsadira          #+#    #+#              #
#    Updated: 2018/10/11 09:40:19 by khsadira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

SRC		=	ft_start_prog.c ft_print_error.c ft_list_to_tab.c ft_check_env_err.c \
			ft_built_unsetenv.c ft_built_setenv.c\
			ft_check_cd_error.c ft_addfct.c ft_check_path.c \
			ft_check_env_error.c ft_print_env.c ft_signal.c \
			ft_fork.c ft_rework_cmd.c ft_built_echo.c ft_built_cd.c \
			ft_manage_env.c ft_built_env.c ft_manage_free.c ft_builtin.c \
			ft_manage_cmd.c ft_manage_lst.c controler.c \

OBJ	=	$(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) libft/libft.a	
clean :
	rm -rf $(OBJ)
	make -C libft clean

fclean : clean
	rm -rf $(NAME)
	make -C libft fclean

re : fclean all

.PHONY : all clean fclean re
