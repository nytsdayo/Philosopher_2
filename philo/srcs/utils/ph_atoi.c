/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:58:12 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/13 20:01:51 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include "ph_utils.h"

static int	ft_isspace(int c);
static int	overflow(int mns_flag, long res, const char c);
static int	judge_flag(char nptr);

int	ph_atoi(const char *nptr)
{
	int		i;
	int		mns_flag;
	long	res;

	i = 0;
	res = 0;
	mns_flag = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		mns_flag = judge_flag(nptr[i++]);
	while (nptr[i] == '0')
		i++;
	if (ph_isdigit(nptr[i]) == false)
		return (0);
	while (ph_isdigit(nptr[i]))
	{
		if (overflow(mns_flag, res, nptr[i]) == 0)
			return (0);
		else if (overflow(mns_flag, res, nptr[i]) == -1)
			return (-1);
		res = res * 10 + (nptr[i++] - '0');
	}
	return (res * mns_flag);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	overflow(int mns_flag, long res, const char c)
{
	if ((res * mns_flag > LONG_MAX / 10 || (res * mns_flag == LONG_MAX / 10 && (c
					- '0') > LONG_MAX - res * mns_flag * 10)) || res
		* mns_flag < LONG_MIN / 10 || (res * mns_flag == LONG_MIN / 10 && -(c
				- '0') < LONG_MIN - res * mns_flag * 10))
	{
		if (mns_flag == 1)
			return (-1);
		else
			return (0);
	}
	return (1);
}

static int	judge_flag(char nptr)
{
	if (nptr == '-')
		return (-1);
	else
		return (1);
}
