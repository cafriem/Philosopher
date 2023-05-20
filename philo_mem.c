/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_mem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:42:08 by cafriem           #+#    #+#             */
/*   Updated: 2023/05/20 18:23:51 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init(t_data *main_s, int argc, char *argv[])
{
	main_s->no_philo = ft_atoi(argv[1]);
	main_s->ttd = ft_atoi(argv[2]);
	if (main_s->no_philo == 1)
		onephilo(main_s);
	main_s->tte = ft_atoi(argv[3]);
	main_s->tts = ft_atoi(argv[4]);
	main_s->phil = ft_calloc(main_s->no_philo, sizeof(t_philo *));
	main_s->tid = ft_calloc(main_s->no_philo, sizeof(pthread_t));
	main_s->mforks = ft_calloc(main_s->no_philo, sizeof(pthread_mutex_t));
	if (argc == 6)
		main_s->no_philote = ft_atoi(argv[5]);
	main_s->dead = 0;
}

void	ft_philo_init(t_data *main_s)
{
	int	c;

	c = 0;
	while (c < main_s->no_philo)
	{
		main_s->phil[c] = ft_calloc(1, sizeof(t_philo));
		gettimeofday(&main_s->phil[c]->death_time, NULL);
		pthread_mutex_init(&main_s->mforks[c], NULL);
		main_s->phil[c]->p_id = c;
		main_s->phil[c]->forks = 1;
		main_s->phil[c]->main_s = main_s;
		c++;
	}
	pthread_mutex_init(&main_s->death, NULL);
	pthread_mutex_init(&main_s->print, NULL);
}

void	freeing(t_data *main_s)
{
	int	c;

	c = 0;
	while (c < main_s->no_philo)
	{
		free(main_s->phil[c]);
		pthread_mutex_destroy(&main_s->mforks[c]);
		c++;
	}
	pthread_mutex_destroy(&main_s->death);
	pthread_mutex_destroy(&main_s->print);
	free(main_s->phil);
	free(main_s->tid);
	free(main_s->mforks);
	free(main_s);
}

void	create_thread(t_data *main_s)
{
	int	c;

	c = 0;
	gettimeofday(&main_s->time, NULL);
	while (c < main_s->no_philo)
	{
		gettimeofday(&main_s->phil[c]->set_time, NULL);
		pthread_create(&main_s->tid[c], NULL, (void *)&start, main_s->phil[c]);
		c++;
	}
	c = 0;
	while (c < main_s->no_philo)
	{
		pthread_join(main_s->tid[c], NULL);
		c++;
	}
}
