NAME = philo_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./
SRC = philo_bonus.c \
	philo_utils_bonus.c \
	routine_bonus.c \
	input_utils_bonus.c
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean: 
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

sanitize:
	make SANITIZE=1 re

thread:
	make THREAD=1 re

.PHONY: all clean fclean re sanitize thread