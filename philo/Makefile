NAME = philo

CFLAGS = -Wall -Werror -Wextra -pthread
SRCS = main.c \
	   ph_argument_check.c \
	   ph_init_dining.c \
	   ph_init_philos.c \
	   ph_philo_routine.c \
	   ph_monitor_routine.c \
	   ph_dining.c \
	   ph_philo_act_eat.c \
	   ph_print_action.c \
	   ph_isdead.c \
	   ph_release_forks.c \
	   ph_take_forks.c \
	   ph_atoi.c \
	   ph_isnum.c \
	   ph_isdigit.c \
	   ph_free_resources.c \
	   ph_ms_sleep.c \
	   ph_act_usleep.c \
	   ph_get_now_time.c \
	   ph_safe_print.c \
	   ph_is_full.c \
	   ph_isexit.c \
	   ph_get_philo_state.c \
	   ph_get_table_status.c \
	   ph_wait_start.c
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

test:
	@cd ../ && bash ./test_args.sh

.PHONY: all clean fclean re test