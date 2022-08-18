/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: merel <merel@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/09 10:21:53 by mevan-de      #+#    #+#                 */
/*   Updated: 2022/07/21 11:04:20 by mevan-de      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "../ft_printf/ft_printf.h"

int	ft_atoi(const char *str)
{
	long long	i;
	int			n;

	i = 0;
	n = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t'
		|| *str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-' )
			n = n * -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		i = i * 10 + (*str - 48);
		str++;
	}
	if (i > INT_MAX || i < INT_MIN)
	{
		ft_printf("Error\n");
		exit (1);
	}
	return ((int)i * n);
}
