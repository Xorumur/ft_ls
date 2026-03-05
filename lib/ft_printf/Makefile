# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlecherb <mlecherb@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 14:33:47 by mlecherb          #+#    #+#              #
#    Updated: 2021/10/27 16:38:14 by mlecherb         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a

OBJ			= $(SRCS:.c=.o)

CFLAGS		= -Wall -Wextra -Werror

SRCS =	ft_printf.c utils.c 

LIB = ft_printf.h

$(NAME):	$(OBJ)
			ar rcs $(NAME) $(OBJ)

all:		$(NAME)

clean:
			rm -f $(OBJ) 

fclean: 	clean
			rm -f $(NAME)

norme:
			norminette -R CheckForbiddenSourceHeader $(SRCS) ${LIB}

re:			fclean all

.PHONY :	all clean fclean re
