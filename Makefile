# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anony <anony@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/24 12:33:08 by anony             #+#    #+#              #
#    Updated: 2025/07/31 17:45:49 by anony            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES = minishell.c initshell.c parsing/clean.c parsing/cleanbis.c parsing/checkinput.c parsing/isquoteactive.c parsing/lexer.c parsing/nexttokenvalue.c parsing/utils.c parsing/expand.c parsing/removequotes.c parsing/replacevars.c parsing/exitvar.c parsing/envvar.c parsing/checkcommands.c parsing/parser.c parsing/commandargs.c parsing/commandredirs.c signal.c parsing.c exec/exec.c builtin/cd.c builtin/utils.c builtin/echo.c builtin/env.c builtin/exit.c builtin/export.c builtin/pwd.c builtin/unset.c

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
	$(CC) $(CFLAGS) $(OFILES) -L$(LIBFT_DIR) -lft -o $(NAME) $(LDFLAGS)

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