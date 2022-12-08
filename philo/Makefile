NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./
SRC = philo.c \
	routine.c \
	monitor.c \
	info_utils.c \
	input_utils.c
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

.PHONY: all clean fclean re sanitize thread