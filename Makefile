# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 06:33:45 by aghalmi           #+#    #+#              #
#    Updated: 2025/12/17 19:42:15 by aghalmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= pipex
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3
INCLUDES	= -I ./include -I./libft

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS_DIR		= srcs

SRCS		= $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/error.c \
			  $(SRCS_DIR)/path.c \
			  $(SRCS_DIR)/files.c \
			  $(SRCS_DIR)/pipe.c \
			  $(SRCS_DIR)/exec.c  \
			  $(SRCS_DIR)/free.c

SRCS_BONUS  = $(SRCS_DIR)/main.c \
			  $(SRCS_DIR)/error.c \
			  $(SRCS_DIR)/path.c \
			  $(SRCS_DIR)/files.c \
			  $(SRCS_DIR)/pipe.c \
			  $(SRCS_DIR)/exec.c  \
			  $(SRCS_DIR)/free.c \
			  $(SRCS_DIR)/exec_bonus.c \
			  $(SRCS_DIR)/exec_bonus2.c \
			  $(SRCS_DIR)/execute_bonus.c \
			  $(SRCS_DIR)/heredoc.c \
			  $(SRCS_DIR)/parsing.c


OBJS		= $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
$(LIBFT) :
			@make -C $(LIBFT_DIR) > /dev/null 2>&1

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) \
			-L$(LIBFT_DIR) -lft \
			-o $(NAME)

clean:
		@rm -f $(OBJS)
		@make -C $(LIBFT_DIR) clean > /dev/null 2>&1

fclean: clean
		@rm -f $(NAME)
		@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re