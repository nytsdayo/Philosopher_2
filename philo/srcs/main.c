/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 20:01:05 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/13 20:01:06 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "ph_dining.h"
#include "ph_utils.h"
#include "ph_status.h"

int	main(int argc, char **argv)
{
	t_dining_data	dining_data;
	int				arg_status;

	arg_status = ph_argument_check(argv, argc);
	if (arg_status != PH_VAILD_ARG)
	{
		fprintf(stderr, "Invalid arguments\n");
		return (1);
	}
	dining_data.philo_num = ph_atoi(argv[1]);
	dining_data.time_to_die = ph_atoi(argv[2]);
	dining_data.time_to_eat = ph_atoi(argv[3]);
	dining_data.time_to_sleep = ph_atoi(argv[4]);
	if (argc == 6)
		dining_data.max_eat_count = ph_atoi(argv[5]);
	else
		dining_data.max_eat_count = -1;
	if (ph_dining(dining_data) != PH_SUCCESS)
	{
		fprintf(stderr, "ph_dining error\n");
		return (1);
	}
	return (0);
}
