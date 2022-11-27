NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = ./
SRC = philo.c routine.c monitor.c info_utils.c input_utils.c
SRC_BONUS = 
SRCS = $(addprefix $(SRC_DIR), $(SRC))
OBJS = $(SRCS:.c=.o)

ifdef SANITIZE
	CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
endif

ifdef THREAD
	CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g3
endif

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