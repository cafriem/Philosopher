#include "philo.h"

int	start_sleeping(m_data *main_s,  unsigned int p_id, signed long timer)
{
	signed long	time;

	time = 0;
	if(death_timer(main_s, p_id) == 1)
		return (1);
	pthread_mutex_lock(&main_s->print);
	if(dead_checker(main_s) == 1)
	{
		pthread_mutex_unlock(&main_s->print);
		return (1);
	}
	printf("%ld %d is sleeping\n", print_time(main_s->time), p_id);
	pthread_mutex_unlock(&main_s->print);
	gettimeofday(&main_s->phil[p_id]->set_time, NULL);
	while(timer > time)
	{
		if (death_timer(main_s, p_id) == 1)
			return(1);
		time = cal_time(main_s->phil[p_id]->set_time);
		usleep(200);
	}
	return(0);
}

int	philo_looper(p_data *phil)
{
	if(dead_checker(phil->main_s) == 1)
		return (1);
	start_eating(phil->main_s, phil->p_id);
	if(dead_checker(phil->main_s) == 1)
		return (1);
	start_sleeping(phil->main_s, phil->p_id, phil->main_s->tts);
	if(dead_checker(phil->main_s) == 1)
		return (1);
	return (0);
}

void	*start(p_data *phil)
{
	int c;

	if (phil->main_s->no_philote)
	{
		c = 0;
		while (phil->main_s->no_philote > c)
		{
			if(philo_looper(phil) == 1)
				return (NULL);
			c++;
		}
	}
	else
	{
		while(phil)
		{
			if(philo_looper(phil) == 1)
				return (NULL);
		}
	}
	return (NULL);
}

void	create_thread(m_data *main_s)
{
	int	c;

	c = 0;
	gettimeofday(&main_s->time, NULL);
	while (c < main_s->no_philo)
	{
		gettimeofday(&main_s->phil[c]->set_time, NULL);
		pthread_create(&main_s->tid[c], NULL, (void*)&start, main_s->phil[c]);
		c++;
	}
	c = 0;
	while (c < main_s->no_philo)
	{
		pthread_join(main_s->tid[c], NULL);
		c++;
	}
}

void	onephilo(m_data *main_s)
{
	printf("0 0 picked up a fork\n");
	usleep(main_s->ttd * 1000);
	printf("%ld 0 is dead\n", main_s->ttd);
	free(main_s);
	exit(0);
}

void	ft_init(m_data *main_s, int argc, char *argv[])
{
	main_s->no_philo = ft_atoi(argv[1]);
	main_s->ttd = ft_atoi(argv[2]);
	if (main_s->no_philo == 1)
		onephilo(main_s);
	main_s->tte = ft_atoi(argv[3]);
	main_s->tts = ft_atoi(argv[4]);
	main_s->phil = ft_calloc(main_s->no_philo, sizeof(p_data*));
	main_s->tid = ft_calloc(main_s->no_philo, sizeof(pthread_t));
	main_s->mforks = ft_calloc(main_s->no_philo, sizeof(pthread_mutex_t));
	if (argc == 6)
		main_s->no_philote = ft_atoi(argv[5]);
	main_s->dead = 0;
}

void	ft_philo_init(m_data *main_s)
{
	int	c;

	c = 0;
	while (c < main_s->no_philo)
	{
		main_s->phil[c] = ft_calloc(1, sizeof(p_data));
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

void	arg_checkers(int argc, char *argv[])
{
	int	counter;

	if (argc < 5 || argc > 6)
	{
		printf("Error : Wrong amount of arguments.\n");
		exit (1);
	}
	counter = 1;
	while (argc > counter)
	{
		if (ft_atoi(argv[counter]) <= 0)
		{
			printf("Error : less than 0 or 0 in arguments.\n");
			exit (1);
		}
		counter++;
	}
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	letter_checker(char *argv[])
{
	int	w_counter;
	int	counter;

	w_counter = 1;
	counter = 0;

	while (argv[w_counter])
	{
		while (argv[w_counter][counter])
		{
			if (ft_isdigit(argv[w_counter][counter]) == 0)
			{
				printf("Error : letters not included\n");
				exit (1);
			}
			counter++;
		}
		w_counter++;
	}
}

int	main(int argc, char *argv[])
{
	m_data	*main_s;

	arg_checkers(argc, argv);
	letter_checker(argv);
	main_s = ft_calloc(1, sizeof(m_data));
	ft_init(main_s, argc, argv);
	ft_philo_init(main_s);
	create_thread(main_s);
	freeing(main_s);
}
