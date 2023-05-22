/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:40:04 by cafriem           #+#    #+#             */
/*   Updated: 2023/05/22 10:42:34 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_timer(t_data *main_s, int p_id)
{
	if (cal_time(main_s->phil[p_id]->death_time) > main_s->ttd)
	{
		pthread_mutex_lock(&main_s->print);
		pthread_mutex_lock(&main_s->death);
		if (main_s->dead == 0)
		{
			printf("%ld %d is dead\n", print_time(main_s->time), p_id + 1);
			main_s->dead = 1;
		}
		pthread_mutex_unlock(&main_s->print);
		pthread_mutex_unlock(&main_s->death);
		return (1);
	}
	return (0);
}

int	dead_checker(t_data *main_s)
{
	pthread_mutex_lock(&main_s->death);
	if (main_s->dead == 1)
	{
		pthread_mutex_unlock(&main_s->death);
		return (1);
	}
	pthread_mutex_unlock(&main_s->death);
	return (0);
}
