#include "philo.h"

int	death_timer(m_data *main_s, unsigned int p_id)
{
	if (cal_time(main_s->phil[p_id]->death_time) > main_s->TTD)
	{
		pthread_mutex_lock(&main_s->death);
		if (main_s->dead == 0)
		{
			// pthread_mutex_lock(&main_s->print);
			printf("%ld %d is dead\n", print_time(main_s->time), p_id);
			// pthread_mutex_unlock(&main_s->print);
			main_s->dead = 1;
		}
		pthread_mutex_unlock(&main_s->death);
		return (1);
	}
	return (0);
}

int	dead_checker(m_data *main_s)
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
