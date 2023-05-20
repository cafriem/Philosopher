#include "philo.h"

int	eating(m_data *main_s,  int p_id, signed long timer)
{
	signed long	time;

	time = 0;
	pthread_mutex_lock(&main_s->print);
	if(dead_checker(main_s) == 1)
	{
		pthread_mutex_unlock(&main_s->print);
		return (1);
	}
	printf("%ld %d is eating\n", print_time(main_s->time), p_id);
	pthread_mutex_unlock(&main_s->print);
	gettimeofday(&main_s->phil[p_id]->set_time, NULL);
	gettimeofday(&main_s->phil[p_id]->death_time, NULL);
	while(timer > time)
	{
		if (death_timer(main_s, p_id) == 1)
			return (1);
		time = cal_time(main_s->phil[p_id]->set_time);
		usleep(200);
	}
	return (0);
}

int	eating_part1(m_data *main_s, int p_id)
{
	int	c;

	pthread_mutex_lock(&main_s->mforks[p_id]);
	death_timer(main_s, p_id);
	pthread_mutex_lock(&main_s->print);
	if(dead_checker(main_s) == 1)
	{
		pthread_mutex_unlock(&main_s->print);
		pthread_mutex_unlock(&main_s->mforks[p_id]);
		pthread_mutex_unlock(&main_s->mforks[0]);
		return (1);
	}
	printf("%ld %d picked up a fork\n", print_time(main_s->time), p_id);
	printf("%ld %d picked up a fork\n", print_time(main_s->time), p_id);
	pthread_mutex_unlock(&main_s->print);
	c = eating(main_s, p_id, main_s->tte);
	pthread_mutex_unlock(&main_s->mforks[p_id]);
	pthread_mutex_unlock(&main_s->mforks[0]);
	return (c);
}

int	eating_part2(m_data *main_s, int p_id)
{
	int	c;

	c = 0;
	pthread_mutex_lock(&main_s->mforks[p_id]);
	pthread_mutex_lock(&main_s->mforks[p_id + 1]);
	death_timer(main_s, p_id);
	pthread_mutex_lock(&main_s->print);
	if(dead_checker(main_s) == 1)
	{
		pthread_mutex_unlock(&main_s->print);
		pthread_mutex_unlock(&main_s->mforks[p_id + 1]);
		pthread_mutex_unlock(&main_s->mforks[p_id]);
		return (1);
	}
	printf("%ld %d picked up a fork\n", print_time(main_s->time), p_id);
	printf("%ld %d picked up a fork\n", print_time(main_s->time), p_id);
	pthread_mutex_unlock(&main_s->print);
	c = eating(main_s, p_id, main_s->tte);
	pthread_mutex_unlock(&main_s->mforks[p_id]);
	pthread_mutex_unlock(&main_s->mforks[p_id + 1]);
	return (c);
}

int	start_eating(m_data *main_s, int p_id)
{
	if (death_timer(main_s, p_id) == 1)
		return (1);
	if (dead_checker(main_s) == 1)
		return (1);
	if (p_id == main_s->no_philo - 1)
		return (eating_part1(main_s, p_id));
	else
		return (eating_part2(main_s, p_id));
}