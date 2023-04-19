#include "philo.h"

int	eating(m_data main_s, unsigned int p_id, signed long timer)
{
	signed long	time;

	time = 0;
	if(dead_checker(&main_s) == 1)
		return (1);
	// pthread_mutex_lock(&main_s.print);
	printf("%ld %d is eating\n", print_time(main_s.time), p_id);
	// pthread_mutex_unlock(&main_s.print);
	gettimeofday(&main_s.phil[p_id]->set_time, NULL);
	gettimeofday(&main_s.phil[p_id]->death_time, NULL);
	while(timer > time)
	{
		if (death_timer(&main_s, p_id) == 1)
			return (1);
		time = cal_time(main_s.phil[p_id]->set_time);
		usleep(200);
	}
	return (0);
}

int	start_eating(m_data *main_s, unsigned int p_id)
{
	int	c;

	c = 0;
	if (death_timer(main_s, p_id) == 1)
		return (1);
	if (dead_checker(main_s) == 1)
		return (1);
	pthread_mutex_lock(&main_s->mforks[p_id]);
	if (p_id == (unsigned)main_s->No_Philo - 1)
	{
		pthread_mutex_lock(&main_s->mforks[0]);
		main_s->phil[p_id]->forks = 2;
		// pthread_mutex_lock(&main_s->print);
		printf("%ld %d picked up a fork\n", print_time(main_s->time), p_id);
		printf("%ld %d picked up a fork\n", print_time(main_s->time), p_id);
		// pthread_mutex_unlock(&main_s->print);
		main_s->phil[0]->forks = 0;
		if (eating(*main_s, p_id, main_s->TTE) == 1)
			c = 1;
		pthread_mutex_unlock(&main_s->mforks[p_id]);
		pthread_mutex_unlock(&main_s->mforks[0]);
	}
	else
	{
		pthread_mutex_lock(&main_s->mforks[p_id + 1]);
		main_s->phil[p_id]->forks = 2;
		// pthread_mutex_lock(&main_s->print);
		printf("%ld %d picked up a fork\n", print_time(main_s->time), p_id);
		printf("%ld %d picked up a fork\n", print_time(main_s->time), p_id);
		// pthread_mutex_unlock(&main_s->print);
		main_s->phil[p_id + 1]->forks = 0;
		if (eating(*main_s, p_id, main_s->TTE) == 1)
			c = 1;
		pthread_mutex_unlock(&main_s->mforks[p_id]);
		pthread_mutex_unlock(&main_s->mforks[p_id + 1]);
	}
	return (c);
}