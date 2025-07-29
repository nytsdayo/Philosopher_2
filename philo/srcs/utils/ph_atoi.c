/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakatan <rnakatan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 00:58:12 by rnakatan          #+#    #+#             */
/*   Updated: 2025/07/15 01:48:47 by rnakatan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdbool.h>
#include "ph_utils.h"

static int	ft_isspace(int c);
static int	overflow(int mnsflag, long res, const char c);
static int	jugde_flag(char nptr);

int	ph_atoi(const char *nptr)
{
	int		i;
	int		mnsflag;
	long	res;

	i = 0;
	res = 0;
	mnsflag = 1;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
		mnsflag = jugde_flag(nptr[i++]);
	while (nptr[i] == '0')
		i++;
	if (ph_isdigit(nptr[i]) == false || nptr[i] == '0')
		return (0);
	while (ph_isdigit(nptr[i]))
	{
		if (overflow(mnsflag, res, nptr[i]) == 0)
			return (0);
		else if (overflow(mnsflag, res, nptr[i]) == -1)
			return (-1);
		res = res * 10 + (nptr[i++] - '0');
	}
	return (res * mnsflag);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	overflow(int mnsflag, long res, const char c)
{
	if ((res * mnsflag > LONG_MAX / 10 || (res * mnsflag == LONG_MAX / 10 && (c
					- '0') > LONG_MAX - res * mnsflag * 10)) || res
		* mnsflag < LONG_MIN / 10 || (res * mnsflag == LONG_MIN / 10 && -(c
				- '0') < LONG_MIN - res * mnsflag * 10))
	{
		if (mnsflag == 1)
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