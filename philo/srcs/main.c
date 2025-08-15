/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/13 00:00:00 by jules             #+#    #+#             */
/*   Updated: 2025/08/16 04:27:06 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_dining.h"
#include "ph_status.h"
#include "ph_utils.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void		ph_output_error(char *str);

/*
** The main function is the entry point of the program.
** It checks the arguments, initializes the dining data, and starts the dining
** simulation.
*/
int	main(int argc, char **argv)
{
	t_dining_data	dining_data;
	int				arg_status;

	arg_status = ph_argument_check(argv, argc);
	if (arg_status != PH_VAILD_ARG)
	{
		ph_output_error("Invalid arguments");
		return (EXIT_FAILURE);
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
		ph_output_error("ph_dining error");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static size_t	ph_strlen(char *str);

static void	ph_output_error(char *str)
{
	write(2, str, ph_strlen(str));
	write(2, "\n", 1);
}

static size_t	ph_strlen(char *str)
{
	int	len;

	len = 0;
	while (*str++)
		len++;
	return (len);
}
