# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ycribier <ycribier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/07 21:28:19 by ael-kadh          #+#    #+#              #
#    Updated: 2014/02/09 19:26:44 by ycribier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc
FLAGS			=	-Wall -Wextra -Werror -g3
NAME_S			=	serveur
NAME_C			=	client
LIB				=	libft/libft.a
LIB_PATH		=	libft/
SRC_S			=	serveur.c decoding.c t_client.c extra.c
SRC_C			=	client.c encoding.c
INCLUDES		=	./includes
OBJ_S			=	$(SRC_S:.c=.o)
OBJ_C			=	$(SRC_C:.c=.o)

# COLORS
C_NO			=	"\033[00m"
C_OK			=	"\033[35m"
C_GOOD			=	"\033[32m"
C_ERROR			=	"\033[31m"
C_WARN			=	"\033[33m"

# DBG MESSAGE
SUCCESS			=	$(C_GOOD)SUCCESS$(C_NO)
OK				=	$(C_OK)OK$(C_NO)

all: $(NAME_S) $(NAME_C)

$(NAME_S): $(OBJ_S) $(LIB)
	@$(CC) $(FLAGS) -o $@ $^ -L $(LIB_PATH) -lft
	@echo "Compiling" [ $(NAME_S) ] $(SUCCESS)

$(NAME_C): $(OBJ_C) $(LIB)
	@$(CC) $(FLAGS) -o $@ $^ -L $(LIB_PATH) -lft
	@echo "Compiling" [ $(NAME_C) ] $(SUCCESS)

$(LIB):
	@make -C $(LIB_PATH)

%.o: %.c $(INCLUDES)/minitalk.h
	@$(CC) $(FLAGS) -c -o $@ $< -I $(LIB_PATH)$(INCLUDES) -I $(INCLUDES)
	@echo "Linking" [ $< ] $(OK)

clean:
	@rm -f $(OBJ_S) $(OBJ_C)
	@echo "Cleaning" [ $(NAME_S) ] [ $(NAME_C) ] "..." $(OK)

fclean: clean
	@rm -f $(NAME_S) $(NAME_C)
	@make -C $(LIB_PATH) fclean
	@echo "Delete" [ $(NAME_S) ] [ $(NAME_C) ] $(OK)

re: fclean all

.PHONY: all clean fclean re
