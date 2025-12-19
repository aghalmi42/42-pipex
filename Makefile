# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aghalmi <aghalmi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/13 06:33:45 by aghalmi           #+#    #+#              #
#    Updated: 2025/12/19 11:13:41 by aghalmi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = srcs/main.c \
       srcs/error.c \
       srcs/path.c \
       srcs/files.c \
       srcs/pipe.c \
       srcs/exec.c \
       srcs/exec_utils.c \
       srcs/free.c \
       srcs/parsing.c \
       srcs/heredoc.c \
       srcs/exec_bonus.c \
       srcs/exec_bonus2.c \
       srcs/execute_bonus.c

SRCS_BONUS = srcs/main.c \
             srcs/exec_bonus.c \
             srcs/exec_bonus2.c \
             srcs/execute_bonus.c \
             srcs/error.c \
             srcs/free.c \
             srcs/path.c \
             srcs/files.c \
             srcs/pipe.c \
             srcs/exec.c \
             srcs/exec_utils.c \
             srcs/heredoc.c \
             srcs/parsing.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I./include -I./libft

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

bonus: $(LIBFT) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(OBJS_BONUS) -L$(LIBFT_DIR) -lft -o $(NAME)
	@touch bonus

clean:
	rm -f $(OBJS) $(OBJS_BONUS) bonus
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re bonus





# NAME		= pipex
# CC			= cc
# CFLAGS		= -Wall -Wextra -Werror -g3
# INCLUDES	= -I ./include -I./libft

# LIBFT_DIR = ./libft
# LIBFT = $(LIBFT_DIR)/libft.a

# SRCS_DIR		= srcs

# SRCS		= $(SRCS_DIR)/main.c \
# 			  $(SRCS_DIR)/error.c \
# 			  $(SRCS_DIR)/path.c \
# 			  $(SRCS_DIR)/files.c \
# 			  $(SRCS_DIR)/pipe.c \
# 			  $(SRCS_DIR)/exec.c  \
# 			  $(SRCS_DIR)/free.c \
# 			  $(SRCS_DIR)/parsing.c \
# 			  $(SRCS_DIR)/heredoc.c \
# 			  $(SRCS_DIR)/execute_bonus.c \
# 			  $(SRCS_DIR)/exec_bonus.c \
# 			  $(SRCS_DIR)/exec_bonus2.c \
# 			  $(LIBFT_DIR)/get_next_line.c \
# 			  $(LIBFT_DIR)/get_next_line_utils.c

# SRCS_BONUS  = $(SRCS_DIR)/main.c \
# 			  $(SRCS_DIR)/error.c \
# 			  $(SRCS_DIR)/path.c \
# 			  $(SRCS_DIR)/files.c \
# 			  $(SRCS_DIR)/pipe.c \
# 			  $(SRCS_DIR)/exec.c  \
# 			  $(SRCS_DIR)/free.c \
# 			  $(SRCS_DIR)/exec_bonus.c \
# 			  $(SRCS_DIR)/exec_bonus2.c \
# 			  $(SRCS_DIR)/execute_bonus.c \
# 			  $(SRCS_DIR)/heredoc.c \
# 			  $(SRCS_DIR)/parsing.c \
# 			  $(LIBFT_DIR)/get_next_line.c \
# 			  $(LIBFT_DIR)/get_next_line_utils.c


# OBJS		= $(SRCS:.c=.o)
# OBJS_BONUS  = $(SRCS_BONUS:.c=.o)

# all: $(NAME)

# %.o: %.c
# 	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
# $(LIBFT) :
# 			@make -C $(LIBFT_DIR) > /dev/null 2>&1

# $(NAME): $(LIBFT) $(OBJS)
# 	@$(CC) $(CFLAGS) $(OBJS) \
# 			-L$(LIBFT_DIR) -lft \
# 			-o $(NAME)

# clean:
# 		@rm -f $(OBJS)
# 		@make -C $(LIBFT_DIR) clean > /dev/null 2>&1

# fclean: clean
# 		@rm -f $(NAME)
# 		@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1

# re: fclean all

# .PHONY: all clean fclean re