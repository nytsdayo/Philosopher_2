/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_dining.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 09:44:53 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/13 23:39:09 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_DINING_H
# define PH_DINING_H

#include <pthread.h>

typedef struct s_dining_data
{
	int	philo_num;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
}	t_dining_data;

typedef struct s_dining
{
	pthread_t	thread_id;
}	t_dining

#endif