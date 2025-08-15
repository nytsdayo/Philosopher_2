NAME = philo

CFLAGS = -Wall -Werror -Wextra -pthread -I inc/
SRCS = srcs/main.c \
	   srcs/ph_argument_check.c \
	   srcs/ph_init_dining.c \
	   srcs/ph_init_philos.c \
	   srcs/ph_philo_routine.c \
	   srcs/ph_monitor_routine.c \
	   srcs/ph_dining.c \
	   srcs/ph_philo_act_eat.c \
	   srcs/ph_print_action.c \
	   srcs/ph_isdead.c \
	   srcs/ph_release_forks.c \
	   srcs/ph_take_forks.c \
	   srcs/utils/ph_atoi.c \
	   srcs/utils/ph_isnum.c \
	   srcs/utils/ph_isdigit.c \
	   srcs/utils/ph_free_resources.c \
	   srcs/utils/ph_ms_sleep.c \
	   srcs/utils/ph_act_usleep.c \
	   srcs/utils/ph_get_now_time.c \
	   srcs/utils/ph_safe_print.c \
	   srcs/utils/ph_is_full.c \
	   srcs/utils/ph_isexit.c \
	   srcs/utils/ph_get_philo_state.c \
	   srcs/utils/ph_get_table_status.c \
	   srcs/utils/ph_wait_start.c
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