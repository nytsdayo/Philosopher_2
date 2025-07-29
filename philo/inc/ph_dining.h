/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dining.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 09:44:53 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/29 15:59:27 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_DINING_H
# define PH_DINING_H

#include <pthread.h>
#include <stdbool.h>
#include "ph_mutex.h"

typedef struct s_dining_data
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	count_eat;
}	t_dining_data;

typedef struct s_philo_data
{
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	count_eat;
}	t_philo_data;

typedef struct s_philo_info
{
	int				id;
	t_fork			*left_fork;
	t_fork			*right_fork;
	long			last_eat_time;
	t_start_flag	*start_flag;
	t_print			*print_mutex;
	t_dining_data	*data;
}	t_philo_info;

typedef struct s_table_info
{
	int				philo_num;
	t_start_flag	*start_flag;
	t_start_time	*start_time;
}	t_table_info;

typedef struct s_philo
{
	pthread_t		thread;
	t_philo_info	*philo_info;
	t_table_info	*table_info;
}	t_philo;

typedef struct t_dining
{
	pthread_t		*threads;
	t_fork			**forks;
	t_philo			*philos;
	t_print			*print;
	t_dining_data	*data;
	t_table_info	*table_info;
}	t_dining;

int		ph_init_dining(t_dining **dining, t_dining_data *data);
void	*ph_philo_routine(void *arg);
int		ph_dining(t_dining_data *data);

#endif