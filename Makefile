# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anony <anony@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 13:50:41 by anony             #+#    #+#              #
#    Updated: 2025/07/14 17:40:37 by anony            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = minishell.c lexer.c initialization.c signalhandler.c parser.c expander.c

OFILES = $(FILES:.c=.o)

# LIBFT_DIR = libft\\ 
LIBFT_DIR = libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a

# CC = gcc
CC = cc

# RM = del /f /q
RM = rm -f

CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline

# NAME = minishell.exe
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