/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jules <jules@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:58:12 by rnakatan          #+#    #+#             */
/*   Updated: 2025/08/13 00:00:00 by jules            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ph_utils.h"
#include <limits.h>
#include <stdbool.h>

static int	ft_isspace(int c);
static int	overflow(int mns_flag, long res, const char c);
static int	judge_flag(char nptr);

/*
** Converts the initial portion of the string pointed to by nptr to int.
*/
int	ph_atoi(const char *nptr)
{
	int		i;
	int		mns_flag;
	long	res;

	i = 0;
	res = 0;
	mns_flag = 1;
	while (ft_isspace(nptr[i]))
	{
		i++;
	}
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		mns_flag = judge_flag(nptr[i++]);
	}
	while (nptr[i] == '0')
	{
		i++;
	}
	if (ph_isdigit(nptr[i]) == false)
	{
		return (0);
	}
	while (ph_isdigit(nptr[i]))
	{
		if (overflow(mns_flag, res, nptr[i]) == 0)
			return (0);
		else if (overflow(mns_flag, res, nptr[i]) == -1)
			return (-1);
		res = res * 10 + (nptr[i++] - '0');
	}
	return ((int)(res * mns_flag));
}

/*
** Checks for whitespace characters.
*/
static int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
	{
		return (1);
	}
	return (0);
}

/*
** Checks for long overflow before multiplication, preserving original logic.
*/
static int	overflow(int mns_flag, long res, const char c)
{
	long	p1;
	long	p2;
	long	p3;
	long	p4;

	p1 = (res * mns_flag > LONG_MAX / 10);
	p2 = (res * mns_flag == LONG_MAX / 10
			&& (c - '0') > LONG_MAX - res * mns_flag * 10);
	p3 = (res * mns_flag < LONG_MIN / 10);
	p4 = (res * mns_flag == LONG_MIN / 10
			&& -(c - '0') < LONG_MIN - res * mns_flag * 10);
	if (p1 || p2 || p3 || p4)
	{
		if (mns_flag == 1)
		{
			return (-1);
		}
		else
		{
			return (0);
		}
	}
	return (1);
}

/*
** Determines the sign from a character.
*/
static int	judge_flag(char nptr)
{
	if (nptr == '-')
	{
		return (-1);
	}
	else
	{
		return (1);
	}
}
