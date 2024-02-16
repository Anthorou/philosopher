# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aroussea <aroussea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/09 15:35:15 by aroussea          #+#    #+#              #
#    Updated: 2023/09/26 13:25:40 by aroussea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -pthread 
NAME = philo
SOURCE = src/philo.c \
		 src/operation.c \
		 src/utils.c \
		 src/free.c \
		 src/routine.c \
		 
HEADERS	:= -I ./include
OBJS = $(SOURCE:.c=.o)

all: $(NAME)

sanit: CFLAGS += -fsanitize=thread
sanit: re

%.o : %.c 
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)
	
$(NAME): $(OBJS) 
	@$(CC) $(CFLAGS) $(OBJS) $(HEADERS) -o $(NAME)
	@for i in 1 2 ; do \
		printf "\r\033[2K" ; \
		printf "$(YELLOW)$(HI)Compiling $(BLUE)." ; \
		sleep 0.5 ; \
		printf "." ; \
		sleep 0.5 ; \
		printf "." ; \
		sleep 0.5 ; \
		printf "$(END_COLOR)" ; \
	done
	@printf "\r$(BLUE)Compiled!$(END_COLOR)"

clean:
	@rm -f $(OBJS)
	@echo "$(ERASE)$(GREEN)Tout propre!$(END_COLOR)"
	
fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re


# **************************************************************************** #
# Colors

BLACK		=\033[30m
RED			=\033[31m
GREEN		=\033[32m
YELLOW		=\033[33m
BLUE		=\033[34m
PURPLE		=\033[35m
CYAN		=\033[36m
WHITE		=\033[37m

# # Text

ERASE		=\033[2K\r
END_COLOR	=\033[0m
BOLD		=\033[1m
FAINT		=\033[2m
ITALIC		=\033[3m
UNDERLINE	=\033[4m

# # Background

BG_BLACK	=\033[40m
BG_RED		=\033[41m
BG_GREEN	=\033[42m
BG_YELLOW	=\033[43m
BG_BLUE		=\033[44m
BG_PURPLE	=\033[45m
BG_CYAN		=\033[46m
BG_WHITE	=\033[47m

# highlight color

HI=\033[7m
# **************************************************************************** #
