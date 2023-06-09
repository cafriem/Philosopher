/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:45:38 by cafriem           #+#    #+#             */
/*   Updated: 2023/05/23 12:37:47 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	arg_checkers(int argc, char *argv[])
{
	int	counter;

	if (argc < 5 || argc > 6)
	{
		printf("Error : Wrong amount of arguments.\n");
		return (1);
	}
	counter = 1;
	while (argc > counter)
	{
		if (ft_atoi(argv[counter]) <= 0)
		{
			printf("Error : less than 0 or 0 in arguments.\n");
			return (1);
		}
		counter++;
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	letter_checker(char *argv[])
{
	int	w_counter;
	int	counter;

	w_counter = 1;
	while (argv[w_counter])
	{
		counter = 0;
		while (argv[w_counter][counter])
		{
			if (ft_isdigit(argv[w_counter][counter]) == 0)
			{
				printf("Error : letters not included\n");
				return (1);
			}
			counter++;
		}
		w_counter++;
	}
	return (0);
}
