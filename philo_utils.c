#include "philo.h"

void	freeing(m_data *main_s)
{
	int	c;

	c = 0;
	while (c < main_s->No_Philo)
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
}
