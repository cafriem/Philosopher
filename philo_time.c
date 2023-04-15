#include "philo.h"

signed long	cal_time_print(struct timeval time, struct timeval current_time)
{
	signed long	f;
	signed long	r;

	f = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	r = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (f - r);
}

signed long	cal_time(struct timeval time)
{
	signed long	f;
	signed long	r;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	f = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	r = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (f - r);
}

long	print_time(struct timeval time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return(cal_time_print(time, current_time));
}