
#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct main_data m_data;

typedef struct phil_data
{
	int				p_id;
	unsigned int	forks;
	struct timeval	set_time;
	struct timeval	death_time;
	m_data			*main_s;
}	p_data;

typedef struct main_data
{
	struct timeval	time;
	int				no_philo;
	signed long		ttd; // time to die
	signed long		tte; // time to eat
	signed long		tts; // time to sleep
	int				no_philote; // NO of times to eat
	int				dead;
	pthread_t		*tid;
	pthread_mutex_t	last_eating;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	*mforks;
	p_data			**phil;
}	m_data;

signed long	cal_time(struct timeval time);
signed long	cal_time_print(struct timeval time, struct timeval current_time);
long		print_time(struct timeval time);
int			dead_checker(m_data *main_s);
int			death_timer(m_data *main_s, int p_id);
int			eating(m_data *main_s, int p_id, signed long timer);
int			start_eating(m_data *main_s, int p_id);
void		freeing(m_data *main_s);
//-----------------------------------//
int			ft_atoi(const char *str);
void		*ft_calloc(size_t count, size_t size);
void		ft_bzero(void *s, size_t n);
void		arg_checkers(int argc, char *argv[]);

#endif
