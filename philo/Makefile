NAME = philo

CFLAGS = -Wall -Werror -Wextra
SRCS = srcs/main.c
OBJS = $(SRCS:.c=.o)
INCS = inc/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o -I$(INCS) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re