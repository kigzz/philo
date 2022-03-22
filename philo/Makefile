
#SETUP

NAME			=	philo
CC				=	gcc -Wall -Wextra -Werror
FLAGS			=	-pthread -Iincludes
RM				=	rm -rf

SRCS    		=	philo.c check_end.c clean_exit.c create_threads.c get_time.c init_rules.c print_status.c routine.c
SRCS_DIR		=	srcs/
SRCS_PATH		=	$(addprefix $(SRCS_DIR), $(SRCS))
OBJ_SRCS    	=	$(SRCS_PATH:%.c=%.o)

# BONUS


# RULES

%.o : %.c
					@$(CC) $(FLAGS) -c $< -o $@

all:				$(NAME)

$(NAME):			$(OBJ_SRCS)
					@$(CC) $(FLAGS) $(OBJ_SRCS) -o $(NAME)

clean:
					@$(RM) $(OBJ_SRCS)

fclean:				clean
					@$(RM) $(NAME) $(NAME_BONUS)

re:					fclean all

.PHONY:				all clean fclean bonus re