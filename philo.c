/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:41:11 by cafriem           #+#    #+#             */
/*   Updated: 2023/05/22 10:43:15 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_sleeping(t_data *main_s, unsigned int p_id, signed long timer)
{
	signed long	time;

	time = 0;
	if (death_timer(main_s, p_id) == 1)
		return (1);
	pthread_mutex_lock(&main_s->print);
	if (dead_checker(main_s) == 1)
	{
		pthread_mutex_unlock(&main_s->print);
		return (1);
	}
	printf("%ld %d is sleeping\n", print_time(main_s->time), p_id + 1);
	pthread_mutex_unlock(&main_s->print);
	gettimeofday(&main_s->phil[p_id]->set_time, NULL);
	while (timer > time)
	{
		if (death_timer(main_s, p_id) == 1)
			return (1);
		time = cal_time(main_s->phil[p_id]->set_time);
		usleep(200);
	}
	return (0);
}

int	philo_looper(t_philo *phil)
{
	if (dead_checker(phil->main_s) == 1)
		return (1);
	start_eating(phil->main_s, phil->p_id);
	if (dead_checker(phil->main_s) == 1)
		return (1);
	start_sleeping(phil->main_s, phil->p_id, phil->main_s->tts);
	if (dead_checker(phil->main_s) == 1)
		return (1);
	return (0);
}

void	*start(t_philo *phil)
{
	int	c;

	if (phil->main_s->no_philote)
	{
		c = 0;
		while (phil->main_s->no_philote > c)
		{
			if (philo_looper(phil) == 1)
				return (NULL);
			c++;
		}
	}
	else
	{
		while (phil)
		{
			if (philo_looper(phil) == 1)
				return (NULL);
		}
	}
	return (NULL);
}

void	onephilo(t_data *main_s)
{
	printf("0 1 picked up a fork\n");
	usleep(main_s->ttd * 1000);
	printf("%ld 1 is dead\n", main_s->ttd);
	free(main_s);
	exit(0);
}

int	main(int argc, char *argv[])
{
	t_data	*main_s;

	arg_checkers(argc, argv);
	letter_checker(argv);
	main_s = ft_calloc(1, sizeof(t_data));
	ft_init(main_s, argc, argv);
	ft_philo_init(main_s);
	create_thread(main_s);
	freeing(main_s);
}
