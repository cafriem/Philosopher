/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafriem <cafriem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 17:54:24 by cafriem           #+#    #+#             */
/*   Updated: 2023/05/23 13:01:44 by cafriem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct main_data	t_data;

typedef struct phil_data
{
	int				p_id;
	unsigned int	forks;
	struct timeval	set_time;
	struct timeval	death_time;
	t_data			*main_s;
}	t_philo;

typedef struct main_data
{
	struct timeval	time;
	int				no_philo;
	signed long		ttd;
	signed long		tte;
	signed long		tts;
	int				no_philote;
	int				dead;
	pthread_t		*tid;
	pthread_mutex_t	death;
	pthread_mutex_t	print;
	pthread_mutex_t	*mforks;
	t_philo			**phil;
}	t_data;

//--------philo.c---------//
int			start_sleeping(t_data *main_s,
				unsigned int p_id, signed long timer);
int			philo_looper(t_philo *phil);
void		*start(t_philo *phil);
void		onephilo(t_data *main_s);
//----------philo_utils.c---------//
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_atoi(const char *str);
//-----------philo_time.c-----------------------//
signed long	cal_time_print(struct timeval time, struct timeval current_time);
signed long	cal_time(struct timeval time);
long		print_time(struct timeval time);
//----------philo_mem.c---------------------//
void		ft_init(t_data *main_s, int argc, char *argv[]);
void		ft_philo_init(t_data *main_s);
void		freeing(t_data *main_s);
void		create_thread(t_data *main_s);
//------------philo_error.c-------------//
int			arg_checkers(int argc, char *argv[]);
int			ft_isdigit(int c);
int			letter_checker(char *argv[]);
//-----------philo_eat.c------------//
int			eating(t_data *main_s, int p_id, signed long timer);
int			eating_part1_even(t_data *main_s, int p_id);
int			eating_part2(t_data *main_s, int p_id);
int			start_eating(t_data *main_s, int p_id);
//-----------philo_death.c---------------//
int			death_timer(t_data *main_s, int p_id);
int			dead_checker(t_data *main_s);

#endif
