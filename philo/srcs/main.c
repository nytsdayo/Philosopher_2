/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 01:06:30 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 19:30:47 by rnakatan         ###   ########.fr       */
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

#define PHILO_NUM 10
#define EAT_TIME 100
#define SLEEP_TIME 100
#define DEAD_TIME 200

int	main(int argc, char **argv)
{
	int	ret;
	t_dining_data	*data;
	(void)argc;
	(void)argv;
	(void)ret;

	// not yet imprement
	// if (ph_argument_check(argv, argc) != PH_VAILD_ARG)
	// 	ph_printerr();
	// if (ph_dining(argv, argc) != PH_SUCCESS)
	// 	ph_printerr();
	// ph_dining()
	data = malloc(sizeof(t_dining_data));
	if (!data)
		return (1);
	data->philo_num = PHILO_NUM;
	data->time_to_die = DEAD_TIME;
	data->time_to_eat = EAT_TIME;
	data->time_to_sleep = SLEEP_TIME;
	if (ph_dining(data) != PH_SUCCESS)
	{
		fprintf(stderr, "malloc error\n");
		return (1);
	}
	return (0);
}
