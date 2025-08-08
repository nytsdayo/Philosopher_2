/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_mutex.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyts <nyts@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:28:39 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/07 22:02:02 by nyts             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PH_MUTEX_H
# define PH_MUTEX_H

# include <pthread.h>

typedef struct s_start_time
{
	pthread_mutex_t	*mutex;
	long			time;
}	t_start_time;

typedef struct s_fork
{
	pthread_mutex_t	*mutex;
	bool			is_used;
}	t_fork;

typedef struct s_print
{
	pthread_mutex_t	*mutex;
}	t_print;

#endif