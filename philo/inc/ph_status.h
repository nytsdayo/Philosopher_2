/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_status.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 03:01:43 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/08 12:00:21 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_STATUS_H
# define PH_STATUS_H

typedef enum e_arg_status
{
	PH_VAILD_ARG,
	PH_INVAlID_ARGC,
	PH_INVALID_NOT_NUM,
	PH_INVALID_OUT_OF_RANGE,
	PH_MEMORY_ERROR,
	PH_MUTEX_ERROR,
	PH_THREAD_ERROR,
}				t_arg_status;

typedef enum e_philo_status
{
	PHILO_ALIVE,
	PHILO_FULL,
	PHILO_DEAD,
	PHILO_EXIT
}				t_philo_status;

typedef enum e_fork_status
{
	NOT_TAKEN,
	TAKEN
}				t_fork_status;

typedef enum e_dining_status
{
	PH_SUCCESS,
}				t_dining_status;

#endif