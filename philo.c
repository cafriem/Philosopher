#include "philo.h"

int	death_timer(m_data *main_s, unsigned int p_id)
{
	if (cal_time(main_s->phil[p_id]->death_time) > main_s->TTD)
	{
		if (main_s->dead == 0)
		{
			printf("%ld %d is dead\n", print_time(main_s->time), p_id);
			main_s->dead = 1;
		}
		return (1);
	}
	return (0);
	//still needs work
}

void	eating(m_data main_s, unsigned int p_id, signed long timer)
{
	signed long	time;

	time = 0;
	death_timer(&main_s, p_id);
	printf("%ld %d is eating\n", print_time(main_s.time), p_id);
	gettimeofday(&main_s.phil[p_id]->set_time, NULL);
	gettimeofday(&main_s.phil[p_id]->death_time, NULL);
	while(timer > time)
	{
		if (death_timer(&main_s, p_id) == 1)
			break;
		time = cal_time(main_s.phil[p_id]->set_time);
		usleep(50);
	}
}

void	start_eating(m_data *main_s, unsigned int p_id)
{
	pthread_mutex_lock(&main_s->mforks[p_id]);
	if (p_id == (unsigned)main_s->No_Philo - 1)
	{
		pthread_mutex_lock(&main_s->mforks[0]);
		main_s->phil[p_id]->forks = 2;
		main_s->phil[0]->forks = 0;
		eating(*main_s, p_id, main_s->TTE);
		pthread_mutex_unlock(&main_s->mforks[p_id]);
		pthread_mutex_unlock(&main_s->mforks[0]);
	}
	else
	{
		pthread_mutex_lock(&main_s->mforks[p_id + 1]);
		main_s->phil[p_id]->forks = 2;
		main_s->phil[p_id + 1]->forks = 0;
		eating(*main_s, p_id, main_s->TTE);
		pthread_mutex_unlock(&main_s->mforks[p_id]);
		pthread_mutex_unlock(&main_s->mforks[p_id + 1]);
	}
}

void	start_sleeping(m_data *main_s,  unsigned int p_id, signed long timer)
{
	signed long	time;

	time = 0;
	print_time(main_s->time);
	death_timer(main_s, p_id);
	printf("%ld %d is sleeping\n", print_time(main_s->time), p_id);
	gettimeofday(&main_s->phil[p_id]->set_time, NULL);
	while(timer > time)
	{
		if (death_timer(main_s, p_id) == 1)
			break;
		time = cal_time(main_s->phil[p_id]->set_time);
		usleep(50);
	}
}

int	dead_checker(m_data *main_s)
{
	if (main_s->dead == 1)
		return (1);
	return (0);
}

void	*start(p_data *phil)
{
	int c;

	c = 0;
	if (phil->main_s->No_PhiloTE)
	{
		while (phil->main_s->No_PhiloTE > c)
		{
			if(dead_checker(phil->main_s) == 1)
				return (NULL);
			start_eating(phil->main_s, phil->p_id);
			if(dead_checker(phil->main_s) == 1)
				return (NULL);
			start_sleeping(phil->main_s, phil->p_id, phil->main_s->TTS);
			c++;
		}
	}
	else
	{
		while(phil)
		{
			if(dead_checker(phil->main_s) == 1)
				return (NULL);
			start_eating(phil->main_s, phil->p_id);
			if(dead_checker(phil->main_s) == 1)
				return (NULL);
			start_sleeping(phil->main_s, phil->p_id, phil->main_s->TTS);
		}
		return (NULL);
	}
	return (NULL);
}


void	Create_Thread(m_data *main_s)
{
	int	c;

	c = 0;
	gettimeofday(&main_s->time, NULL);
	while (c < main_s->No_Philo)
	{
		gettimeofday(&main_s->phil[c]->set_time, NULL);
		pthread_create(&main_s->tid[c], NULL, (void*)&start, main_s->phil[c]);
		c++;
	}
	c = 0;
	while (c < main_s->No_Philo)
	{
		pthread_join(main_s->tid[c], NULL);
		c++;
	}
}

int	main(int argc, char *argv[])
{
	m_data	*main_s;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong amount of arguments.\n");
		exit (0);
	}
	if (ft_atoi(argv[1]) < 2)
	{
		printf("Less than 2 philosopher.\n");
		exit (0);
	}
	main_s = ft_calloc(1, sizeof(m_data));
	main_s->No_Philo = ft_atoi(argv[1]);
	main_s->TTD = ft_atoi(argv[2]);
	main_s->TTE = ft_atoi(argv[3]);
	main_s->TTS = ft_atoi(argv[4]);
	main_s->phil = ft_calloc(main_s->No_Philo, sizeof(p_data*));
	main_s->tid = ft_calloc(main_s->No_Philo, sizeof(pthread_t));
	main_s->mforks = ft_calloc(main_s->No_Philo, sizeof(pthread_mutex_t));
	if (argc == 6)
		main_s->No_PhiloTE = ft_atoi(argv[5]);
	main_s->dead = 0;
	int	c;
	c = 0;
	while (c < main_s->No_Philo)
	{
		main_s->phil[c] = ft_calloc(1, sizeof(p_data));
		gettimeofday(&main_s->phil[c]->death_time, NULL);
		pthread_mutex_init(&main_s->mforks[c], NULL);
		main_s->phil[c]->p_id = c;
		main_s->phil[c]->forks = 1;
		main_s->phil[c]->main_s = main_s;
		c++;
	}
	Create_Thread(main_s);
	c = 0;
	while (c < main_s->No_Philo)
	{
		free(main_s->phil[c]);
		pthread_mutex_destroy(&main_s->mforks[c]);
		c++;
	}
	free(main_s->phil);
	free(main_s->tid);
	free(main_s->mforks);
}
