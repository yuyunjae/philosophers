NAME = philo
CC = cc
CFLAG = -Wall -Wextra -Werror -g -fsanitize=thread
HEADERS = philosophers.h
SRCS_DIR = mandatory
SRCS = main.c	\
		ft_atoi.c	\
		ft_strncmp.c	\
		philo_do.c	\
		philo_env.c	\
		philo_utils.c	\
		philo.c

OBJS = $(SRCS:.c=.o)
SRCS := $(addprefix $(SRCS_DIR)/, $(SRCS))
HEADERS := $(addprefix $(SRCS_DIR)/, $(HEADERS))

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAG) $(OBJS) -o $@

$(SRCS_DIR)%.o : $(SRCS_DIR)%.c $(HEADERS)
	$(CC) $(CFLAG) -c $< -o $@

clean :
	rm -rf $(OBJS)

fclean :
	rm -rf $(OBJS) $(NAME)

re :
	@make fclean
	@make all

.PHONY: clean fclean all re bonus
