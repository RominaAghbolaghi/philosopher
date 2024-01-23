# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmohamma <rmohamma@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/17 16:20:18 by rmohamma          #+#    #+#              #
#    Updated: 2023/09/27 12:00:36 by rmohamma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	philo
CC				=	cc
RM				=	rm -f
HEADDIR			=	./includes/
CFLAGS			=	-Werror -Wextra -Wall -pthread

SRC_FILES	=	main\
			error\
			init_gl_info\
			init_ph_info\
			mutex\
			thread\
			philo_actions\
			thread_utils

HEAD_FILES	=	philo

SRC 			= $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 			= $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
HEAD			= $(addprefix $(HEADDIR), $(addsuffix .h, $(HEAD_FILES)))

SRC_DIR		= srcs/
OBJ_DIR		= obj/

OBJ_RESULT = $(OBJ)

END=\033[0m
GREEN = \033[0;92m
YELLOW = \033[0;93m
MAGENTA = \033[0;95m
CYAN = \033[0;96m

OBJ_MKDIR		=	create_dir

all: $(NAME)

$(NAME): $(OBJ_RESULT) $(HEAD)
	@$(CC) $(CFLAGS) $(OBJ_RESULT) -o $@ -I$(HEADDIR)
	@echo "$(MAGENTA)\n**********  Philo compiled **********\n$(END)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJ_MKDIR)
	@$(CC) $(CFLAGS) -c $^ -o $@ -I$(HEADDIR)
	@echo "$(CYAN)Compiling... \t$< $(END)"

$(OBJ_MKDIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@$(RM) -rf $(OBJ_DIR)
	@echo "$(YELLOW)\n**********  All objects removed  **************\n$(END)"

fclean:		clean
	@$(RM) -f $(NAME)
	@echo "$(GREEN)********  All executables removed  ************\n$(END)"

re:			fclean all

.PHONY:		all clean fclean re dirty scan
