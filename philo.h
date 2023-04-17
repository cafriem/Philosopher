
#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <signal.h>
# include "Libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct main_data m_data;

typedef struct phil_data
{
	unsigned int	p_id;
	unsigned int	forks;
	struct timeval	set_time;
	struct timeval	death_time;
	m_data			*main_s;
}	p_data;

typedef struct main_data
{
	struct timeval	time;
	int				No_Philo;
	signed long		TTD; // time to die
	signed long		TTE; // time to eat
	signed long		TTS; // time to sleep
	int				No_PhiloTE; // NO of times to eat
	int				dead;
	pthread_t		*tid;
	pthread_mutex_t	*mforks;
	p_data			**phil;
}	m_data;

signed long	cal_time(struct timeval time);
signed long	cal_time_print(struct timeval time, struct timeval current_time);
long		print_time(struct timeval time);

#endif