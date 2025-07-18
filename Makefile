# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anony <anony@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 13:50:41 by anony             #+#    #+#              #
#    Updated: 2025/07/18 17:41:16 by anony            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = minishell.c initshell.c setenv.c cleanshell.c utils.c signal.c lexer.c nexttokenvalue.c isquoteactive.c

OFILES = $(FILES:.c=.o)

LIBFT_DIR = libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a

CC = cc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

NAME = minishell

all : $(NAME)

$(LIBFT_LIB) :
	make -C $(LIBFT_DIR)

$(NAME) : $(OFILES) $(LIBFT_LIB)
	$(CC) $(OFILES) -L$(LIBFT_DIR) -lft -o $(NAME) $(LDFLAGS)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	$(RM) $(OFILES)
	@make -C $(LIBFT_DIR) clean

fclean :
	$(RM) $(NAME)
	$(RM) $(OFILES)
	@make -C $(LIBFT_DIR) fclean

re : fclean all