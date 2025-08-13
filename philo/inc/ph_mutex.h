/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:28:39 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/14 03:12:20 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_MUTEX_H
# define PH_MUTEX_H

# include <pthread.h>
# include <stdbool.h>

typedef struct s_start_time
{
	pthread_mutex_t	mutex;
	long			time;
}	t_start_time;

typedef struct s_table_status
{
	pthread_mutex_t	mutex;
	bool			is_running;
}	t_table_status;

typedef struct s_philo_alive
{
	pthread_mutex_t	mutex;
	bool			value;
}	t_philo_alive;

typedef struct s_philo_eat_count
{
	pthread_mutex_t	mutex;
	int				value;
}	t_philo_eat_count;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_print
{
	pthread_mutex_t	mutex;
}	t_print;

#endif