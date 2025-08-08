#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "ph_dining.h"
#include "ph_utils.h"
#include "ph_status.h"

#define PHILO_NUM 5
#define DEAD_TIME 800
#define EAT_TIME 200
#define SLEEP_TIME 200
#define MAX_EAT_COUNT 0

int	main(int argc, char **argv)
{
	t_dining_data dining_data;
	(void)argc;
	(void)argv;
	dining_data.philo_num = PHILO_NUM;
	dining_data.time_to_die = DEAD_TIME;
	dining_data.time_to_eat = EAT_TIME;
	dining_data.time_to_sleep = SLEEP_TIME;
	dining_data.max_eat_count = MAX_EAT_COUNT;
	if (ph_dining(dining_data) != PH_SUCCESS)
	{
		fprintf(stderr, "ph_dining error\n");
		return (1);
	}
	return (0);
}
