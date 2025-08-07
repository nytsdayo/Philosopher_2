NAME = philo

CFLAGS = -Wall -Werror -Wextra -pthread -I inc/
SRCS = srcs/main.c \
	   srcs/ph_init_dining.c \
	   srcs/ph_init_philos.c \
	   srcs/ph_philo_routine.c \
	   srcs/ph_dining.c \
	   srcs/ph_philo_act_eat.c \
	   srcs/ph_print_action.c \
	   srcs/ph_isdead.c \
	   srcs/utils/ph_atoi.c \
	   srcs/utils/ph_isnum.c \
	   srcs/utils/ph_isdigit.c \
	   srcs/utils/ph_nop.c \
	   srcs/utils/ph_free_resources.c \
	   srcs/utils/ph_usleep.c \
	   srcs/utils/ph_get_now_time.c
OBJS = $(SRCS:.c=.o)
INCS = inc/

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o  $(NAME) $(OBJS)

debug: CFLAGS += -g
debug: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re