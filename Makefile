# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: khsadira <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/04 14:29:26 by khsadira          #+#    #+#              #
#    Updated: 2018/09/04 14:29:27 by khsadira         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	minishell

CC	=	gcc

CFLAGS	=	#-Wall -Wextra -Werror

SRC	=	ft_built_echo.c ft_ask_quote.c ft_treat_line2.c ft_built_cd.c ft_treat_line.c ft_manage_env.c ft_built_env.c ft_manage_free.c ft_builtin.c ft_manage_cmd.c ft_manage_lst.c controler.c get_next_line.c

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
