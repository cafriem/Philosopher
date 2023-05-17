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
	free(main_s);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	c;

	c = 0;
	while (c != n)
	{
		((unsigned char *)s)[c] = 0;
		c++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*result;

	if ((size != 0) && count > (SIZE_MAX / size))
		return (NULL);
	result = (void *)malloc(count * size);
	if (result == NULL)
		return (NULL);
	ft_bzero(result, count * size);
	return (result);
}

static int	ft_res(int c1, const char *str, int minus)
{
	int	c;

	c = 0;
	while (str[c1] >= '0' && str[c1] <= '9')
	{
		c = (c * 10) + (str[c1] - 48);
		c1++;
	}
	if (minus == -1)
		return (c * -1);
	return (c);
}

int	ft_atoi(const char *str)
{
	int	c;
	int	c1;
	int	minus;

	c1 = 0;
	c = 0;
	minus = 0;
	while (str[c1] == ' ' || (str[c1] >= 9 && str[c1] <= 13))
		c1++;
	while (str[c1] == '-' || str[c1] == '+')
	{
		if (str[c1] == '-')
			minus--;
		c++;
		c1++;
	}
	if (c > 1)
		return (0);
	return (ft_res(c1, str, minus));
}