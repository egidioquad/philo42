/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equadrin <equadrin@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 15:12:47 by equadrin            #+#    #+#           */
/*   Updated: 2023/05/13 21:54:05 by equadrin           ###   ########.fr     */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

int	ft_atoi(char *str)
{
	int		i;
	long	result;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			result = result * 10 + (str[i++] - '0');
		else
			exit(write(2, "Input valid args\n", 18) * 0);
	}

	if (result < -2147483648 || result > 2147483647)
		exit(write(2, "Input valid args\n", 18) * 0);
	return ((int) result);
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}