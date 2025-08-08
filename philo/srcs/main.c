/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 01:06:30 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/08 03:04:58 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ph_status.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "../inc/ph_dining.h"
#include "../inc/ph_utils.h"
#include "../inc/ph_status.h"

#define PHILO_NUM 1
#define EAT_TIME 99
#define SLEEP_TIME 100
#define DEAD_TIME 200
#define MAX_EAT_COUNT 3

int	main(int argc, char **argv)
{
	int	ret;
	t_dining_data dining_data;

	(void)argc;
	(void)argv;
	(void)ret;
	// not yet imprement
	// if (ph_argument_check(argv, argc) != PH_VAILD_ARG)
	// 	ph_printerr();
	dining_data.philo_num = PHILO_NUM;
	dining_data.time_to_die = DEAD_TIME;
	dining_data.time_to_eat = EAT_TIME;
	dining_data.time_to_sleep = SLEEP_TIME;
	dining_data.max_eat_count = MAX_EAT_COUNT;
	if (ph_dining(dining_data) != PH_SUCCESS)
	{
		fprintf(stderr, "malloc error\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
