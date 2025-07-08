# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anony <anony@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/26 15:27:45 by anony             #+#    #+#              #
#    Updated: 2025/04/10 13:05:52 by anony            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# UTILS_DIR = ft_printf_utils\\ 
UTILS_DIR = ft_printf_utils

FILES = $(UTILS_DIR)/ft_printchar_fd.c $(UTILS_DIR)/ft_printhexnblow_fd.c $(UTILS_DIR)/ft_printhexnbup_fd.c $(UTILS_DIR)/ft_printnb_fd.c $(UTILS_DIR)/ft_printptr_fd.c $(UTILS_DIR)/ft_printstr_fd.c $(UTILS_DIR)/ft_printunb_fd.c $(UTILS_DIR)/utils.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_printf.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c

OFILES = $(FILES:.c=.o)

# CC = gcc
CC = cc

# RM = del /f /q
RM = rm -f

CFLAGS = -Wall -Wextra -Werror

NAME = libft.a

all : $(NAME)

$(NAME) : $(OFILES)
	ar rcs $(NAME) $(OFILES)

%.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean :
	$(RM) $(OFILES)

fclean : clean
	$(RM) $(NAME)

re : fclean all