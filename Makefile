# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clouden <clouden@student.42madrid.com      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 12:44:04 by clouden           #+#    #+#              #
#    Updated: 2025/08/19 12:44:09 by clouden          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED		=	\033[0;31m
GREEN   =	\033[0;32m
RESET   =	\033[0m  
YELLOW  =	\033[1;33m
BLUE    =	\033[0;34m

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I./libft

NAME	=	pipex

SRCS	=	parser.c \
			pipe_works.c

OBJS	=	$(SRCS:%.c=%.o)

MAIN	= 	main.c
MAIN_OBJ=	$(MAIN:.c=.o)

LIBFT_DIR 	=	libft/
LIBFT		=	$(LIBFT_DIR)libft.a

TEST_SRCS	=	.test.c
TEST_OBJS	=	$(TEST_SRCS:%.c=%.o)
TEST_BIN	=	test

all:$(NAME)

$(NAME):$(OBJS) $(MAIN_OBJ) $(LIBFT)
	@echo "$(BLUE)[PIPEX]$(RESET) $< → $@"
	@$(CC) $(CFLAGS) $^ -o $@
# "To build the program $(NAME), you need all the object files ($(OBJS)) 
# and the library ($(LIBFT)).
# Then, run the compiler ($(CC)) with the flags ($(CFLAGS)) to link them 
# together into the final executable (-o $(NAME))."

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) all --no-print-directory

%.o: %.c
	@printf "$(BLUE)[COMPILING]$(RESET) %-21s → %s\n" $< $@
	@$(CC) $(CFLAGS) -c $< -o $@
# $< and $@ are automatic variables that work on a file by file basis
# it allows the ccommand to run oncce for each file in the list
# it exapnads the pattern separately

test: $(OBJS) $(TEST_OBJS) $(LIBFT)
	@printf "$(YELLOW)[TESTING]$(RESET) %-21s → %s\n" $< $@
	@$(CC) $(CFLAGS) $^ -o $(TEST_BIN)

clean:
	@echo "$(YELLOW)"
	@echo "+---------------------------+"
	@echo "|  🧹  CLEANING OBJECTS     |"
	@echo "+---------------------------+"
	@rm -rf *.o $(OBJS) $(MAIN_OBJ) $(TEST_OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@echo "$(RED)"
	@echo "+---------------------------+"
	@echo "|  🔥 REMOVING EXECUTABLES  |"
	@echo "+---------------------------+"
	@rm -f $(NAME) $(TEST_BIN)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RESET)"
	@echo "...now THAT'S effin' clean!\n"

re: fclean all

.PHONY: re all clean fclean

